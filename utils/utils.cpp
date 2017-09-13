#include "utils.h"
#include "cms.h"
#include "json_util.h"
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <ul_sign.h>
#include <base/logging.h>
#include <sys/time.h>
#include <math.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <boost/math/distributions/students_t.hpp>

const double PI = 3.1415926535;
const double EARTH_RADIUS = 6378.137;  // unit : km

namespace gr {

/*    
Utils *Utils::_s_utils = NULL;
Utils *Utils::get_instance()
{
    if (_s_utils == NULL) {
        _s_utils = new Utils();
    }
    return _s_utils;
}
*/

int64_t Utils::get_current_us_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

bool Utils::is_yesterday(time_t last, time_t now)
{
    time_t time_stamp = now;
    int zero_stamp = 0;
    struct tm *time_struct;
 
    time_struct = localtime(&time_stamp);
    time_struct->tm_hour = 0;
    time_struct->tm_min = 0;
    time_struct->tm_sec = 0;
    
    zero_stamp = mktime(time_struct);
    if (last < zero_stamp) {
        return true;
    }
    return false;
}

uint64_t Utils::sign_fs64(const std::string &raw_content) 
{
    uint32_t high;
    uint32_t low;
    uint64_t sign;
    creat_sign_fs64(const_cast<char*>(&raw_content[0]), raw_content.size(), &high, &low);
    sign = high;
    sign = (sign << 32) + low;
    return sign;
}

bool Utils::is_double11_first(time_t last, time_t now)
{
    time_t time_stamp = now;
    int zero_stamp = 0;
    struct tm *time_struct;
 
    time_struct = localtime(&time_stamp);
    time_struct->tm_hour = 0;
    time_struct->tm_min = 0;
    time_struct->tm_sec = 0;
    int ts_month = time_struct->tm_mon + 1;
    int ts_day = time_struct->tm_mday;
    
    zero_stamp = mktime(time_struct);
    if (last < zero_stamp && ts_month == 11 && ts_day == 11) {
        return true;
    }
    return false;
}

bool Utils::is_sv_relaxtime(time_t now)
{
    time_t ts = now;
    tm *gmtm = localtime(&ts);
    int ts_hour = gmtm->tm_hour;
    int ts_wday = gmtm->tm_wday;
    if (ts_wday == 0 || ts_wday == 6) {
        return true;
    }
    if (ts_hour >= 18 && ts_hour < 23) {
        return true;
    }
    return false;
}

bool Utils::is_sv_relaxtime(time_t now, int start, int end)
{
    time_t ts = now;
    tm *gmtm = localtime(&ts);
    int ts_hour = gmtm->tm_hour;
    int ts_wday = gmtm->tm_wday;
    if (ts_hour >= start && ts_hour < end) {
        return true;
    }
    return false;
}

bool Utils::is_baibao_pushtime(time_t now){
    time_t ts = now;
    tm *gmtm = localtime(&ts);
    int ts_wday = gmtm->tm_wday;
    if (ts_wday == 0 || ts_wday == 6 || ts_wday == 5) {
        return false;
    }

    return false;
}

bool Utils::is_in_spantime(int start, int end, time_t now)
{
    time_t ts = now;
    tm *gmtm = localtime(&ts);
    int ts_hour = gmtm->tm_hour;
    if (ts_hour >= start && ts_hour < end) {
        return true;
    }
    return false;
}

bool Utils::is_in_spantime_minutes(int start_hour, int end_hour, 
                                   int start_min, int end_min, time_t now)
{
    time_t ts = now;
    int start = 0;
    int end = 0;
    int t = 0;

    if (start_hour < 0
        || start_hour > 23
        || end_hour < 0
        || end_hour > 23
        || start_min < 0
        || start_min > 59
        || end_min < 0
        || end_min > 59)
    {
        return false;
    }

    tm *gmtm = localtime(&ts);
    start = 60 * start_hour + start_min;
    end = 60 * end_hour +  end_min;
    t = 60 * gmtm->tm_hour + gmtm->tm_min;

    if (start < end) {
        if (t >= start && t < end) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (start > end) {
        if (t >= start || t < end) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

inline char to_hex_cpp(char code) {
    static char hex[] = "0123456789abcdef";
    return hex[code & 15];
}

std::string Utils::url_encode(const std::string& cppStr)
{
    const char *str = cppStr.c_str();
    const char *pstr = str;
    char *buf = (char *)malloc(strlen(str) * 3 + 1);
    memset(buf,0, strlen(str) * 3 + 1);
    char *pbuf = buf;
    while (*pstr) {
        if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
            *pbuf++ = *pstr;
        else if (*pstr == ' ')
            *pbuf++ = '+';
        else
            *pbuf++ = '%', *pbuf++ = to_hex_cpp(*pstr >> 4), *pbuf++ = to_hex_cpp(*pstr & 15);
        pstr++;
    }
    *pbuf = '\0';

    std::string tmpstr(buf);
    free(buf);

    return tmpstr;
} 

bool Utils::is_hot_video(int ext_ac, int type)
{
    std::string ac = std::to_string(ext_ac);
    /*
    if (ac.substr(ac.size() - 2).compare("00") == 0) {
        return true;
    }
    */
    if (ac.size() > 6) {
        std::string hot_str = ac.substr((ac.size() - 6), 2);
        if (type == 2) {
            //related vr is 02[xx]xxxx, [00,04] is hot video 
            if (hot_str.compare("00") == 0 ||
                hot_str.compare("04") == 0) {
                return true;
            }
        } else if (type == 5) {
            //bdh vr is 05[xx]xxxx, [05] is hot video 
            if (hot_str.compare("05") == 0) {
                return true;
            }
        } else if (type == 1) {
            //feed vr is 01[xx]xxxx, [00] is hot video 
            if (hot_str.compare("00") == 0) {
                return true;
            }
        }
    }
    return false;
}

bool Utils::rand1_with_p(int p_num)
{
    //srand((unsigned)time(NULL));
    int k = rand() % 100 + 1;
    if (k <= p_num) {
        return true;
    }
    return false;
}

int Utils::arrays_diff(std::vector<std::string> v1,
                       std::vector<std::string> v2,
                       std::vector<std::string> &v3)
{
    int size1 = v1.size();
    int size2 = v2.size();
    bool is_need = true;
    for (int i = 0; i < size1; i++) {  
        for (int j = 0; j < size2; j++) {  
            if (v1.at(i).compare(v2.at(j)) == 0) {
                is_need = false; 
                break;  
            }  
        }  
        if (is_need) {
            std::string elem = v1.at(i);
            v3.push_back(elem);  
        }
        is_need = true; 
     }
     return 1;
}

double Utils::get_distance(double longitude1, 
        double latitude1, 
        double longitude2,
        double latitude2)
{
    double lat1 = rad(latitude1);
    double lat2 = rad(latitude2);
    double long1 = rad(longitude1); 
    double long2 = rad(longitude2); 
    double a = lat1 - lat2;
    double b = long1 - long2;
    double distance = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(b / 2), 2)));  
    distance = distance * EARTH_RADIUS; 
    distance = round(distance * 10000) / 10000; 
    return distance;
}

double Utils::rad(double angle) {
    return angle * PI / 180;
}

void Utils::mercator2lonlat(double x, double y, double & lng, double & lat) {
    lng = x / 20037508.34 * 180;
    double lat_tmp = y / 20037508.34 * 180;
    lat =  180 / PI * (2 * atan(exp(lat_tmp * PI / 180)) - PI / 2);
}

bool Utils::has_intersection(const boost::unordered_set<std::string> &set1,
        const boost::unordered_set<std::string> &set2) {
    if (set1.size() <= set2.size()) {
        typename boost::unordered_set<std::string>::iterator it;
        for (it = set1.begin(); it != set1.end(); ++it) {
            if (set2.find(*it) != set2.end()) {
                return true;
            }
        }
        return false;
    } else {
        return has_intersection(set2, set1);
    }
}

void Utils::gen_rand_pos(std::set<int> &pos_set, const int merge_size, const int template_num) {
    int num = template_num;
    int rand_pos = 1;
    if (merge_size <= 2) {
        return;
    }
    while (num > 0) {
        int max_retry = 5;
        while (max_retry > 0) {
            bool pos_ok = true;
            rand_pos = rand() % (merge_size - 2) + 1;
            for (std::set<int>::iterator it = pos_set.begin(); it != pos_set.end(); ++it) {
                if (std::abs(*it - rand_pos) < 2) {
                    pos_ok = false;
                    break;
                }
            }
            if (true == pos_ok) {
                pos_set.insert(rand_pos);
                num--;
                break;
            }

            max_retry--;
            if (1 == max_retry) {
                pos_set.insert(rand_pos);
                num--;
                break;
            }
        }
    }
}

bool Utils::is_higher_app_version(const std::string &app_version, int v1, int v2) {
    std::vector<std::string> version_vec;
    if (app_version.size() > 0) {
        split(version_vec, app_version, boost::is_any_of("."));
    }
    if (version_vec.size() < 2) {
        return false;
    }
    int app_v1 = 0;
    try  { app_v1 = boost::lexical_cast<int>(version_vec[0]); }
    catch (...) {}
    int app_v2 = 0;
    try  { app_v2 = boost::lexical_cast<int>(version_vec[1]); }
    catch (...) {}

    if (app_v1 > v1) {
        return true;
    } else if (app_v1 == v1) {
        if (app_v2 >= v2) {
            return true;
        }
    }
    return false;
}

int Utils::compare_int_array(uint32_t (&a)[4], uint32_t (&b)[4]) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (a[i] > b[i]) {
            return 1;
        } else if (a[i] < b[i]) {
            return -1;
        } else {
            count++;
        }
    }
    if (count == 4) {
        return 0;
    }
    return 0;
}

void Utils::generator_int_array(const std::string &app_version, uint32_t (&a)[4]) {
    std::vector<std::string> version_vec;
    if (app_version.size() > 0) {
        split(version_vec, app_version, boost::is_any_of("."));
        for (int i = 0; i < version_vec.size() && i < 4; i++) {
            try  { a[i] = boost::lexical_cast<uint32_t>(version_vec[i]); }
            catch (...) {}
        }
    } 
}

bool Utils::is_filter_ios_image_video(const std::string &app_version, uint32_t channel_id,
    rapidjson::Document &sess_doc)
{
    boost::unordered_set<uint32_t> channel_set = 
        CMS::get_instance()->get_forbidden_channel_info();
    rapidjson::Value version_info(rapidjson::kArrayType);
    CMS::get_instance()->get_forbidden_version_info(version_info, sess_doc);
    if (channel_set.count(channel_id) &&
        version_info.IsArray() &&
        version_info.Size() > 0) {
        uint32_t req_ver[4] = {0};
        generator_int_array(app_version, req_ver);
        for (int i = 0; i < version_info.Size(); i++) {
            if (version_info[i].IsObject() &&
                json_is_string(version_info[i], "begin") &&
                json_is_string(version_info[i], "after")) {
                uint32_t begin_ver[4] = {0};
                uint32_t after_ver[4] = {0};
                generator_int_array(version_info[i]["begin"].GetString(), begin_ver);
                generator_int_array(version_info[i]["after"].GetString(), after_ver);
                if (compare_int_array(req_ver, begin_ver) >= 0 &&
                    compare_int_array(req_ver, after_ver) <= 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Utils::is_hit_smfw(const std::map<std::string, std::string> &smfw, 
    const std::string &key, const std::string &value) {
    if (smfw.find(key) != smfw.end()) {
        std::string v = smfw.at(key);
        if (v.compare(value) == 0) {
            return true;
        }
    }
    return false;
}

uint32_t Utils::get_cuid_hash(const std::string &key)
{
    boost::hash<std::string> string_hash;
    return string_hash(key);
}

void Utils::string_split(const std::string& s, 
                         const std::string& delim,
                         std::vector< std::string > &ret)  
{  
    size_t last = 0;  
    size_t index=s.find_first_of(delim,last);  
    while (index!=std::string::npos)  
    {  
        ret.push_back(s.substr(last,index-last));  
        last=index+1;  
        index=s.find_first_of(delim,last);  
    }  
    if (index-last>0)  
    {  
        ret.push_back(s.substr(last,index-last));  
    }  

    return;
}  

uint64_t Utils::create_sign(const char *str) 
{
    if (str == NULL){
        return 0;
    }
    int len = strlen(str);
    if (len == 0){
        return 0;
    }
    uint64_t sign = 0;
    creat_sign_fs64((char*)str, len, (uint32_t*) (&sign), ((uint32_t*)(&sign) + 1));
    return sign; 
}

unsigned int Utils::stoui(const std::string &strvalue)
{
    unsigned long ulvalue = stoul(strvalue);
    unsigned int uvalue = static_cast<unsigned int>(ulvalue);
    return uvalue;
}

/*
 * two samples t-test
 * @return: -1 if sample1 < sample2
 *           1 if sample1 > sample2
 *           0 else
 */
int Utils::two_samples_t_test(double mean1, double std1,
        int64_t size1, double mean2, double std2, int64_t size2, double sig_level)
{
    if (size1 <= 1 || size2 <= 1) {
        return 0;
    }
    if (std1 < 0 || std2 < 0) {
        return 0;
    }
    // Degrees of freedom:
    double v = std1 * std1 / size1 + std2 * std2 / size2;
    v *= v;
    double t1 = std1 * std1 / size1;
    t1 *= t1;
    t1 /=  (size1 - 1);
    double t2 = std2 * std2 / size2;
    t2 *= t2;
    t2 /= (size2 - 1);
    if (fabs(t1 + t2) < 1e-6 || isnan(t1+t2)) {
        return 0;
    }
    v /= (t1 + t2);
    if (v <= 1e-6 || isnan(v)) {
        return 0;
    }
    // t-statistic:
    double t_stat = (mean1 - mean2) / sqrt(std1 * std1 / size1 + std2 * std2 / size2);
    if (isnan(t_stat)) {
        return 0;
    }
    try{
        boost::math::students_t dist(v);

        // Sample 1 Mean <  Sample 2 Mean
        if (cdf(dist, t_stat) < sig_level) {
            return -1;
        }
        // Sample 1 Mean >  Sample 2 Mean
        if (cdf(complement(dist, t_stat)) < sig_level){
            return 1;
        }
    }catch (...) {}
    return 0;
}
bool Utils::parse_from_redis_request(const baidu::rpc::RedisRequest& request, 
        std::vector<redis_cmd_t>& cmd_list) {
    base::IOBuf buf;
    std::string request_str;
    if (!request.SerializeTo(&buf)) {
        return false;
    }
    buf.copy_to(&request_str);
    size_t src_size = request_str.size();
    const char* src = request_str.data();
    int start_pos = 0;
    while (src_size - start_pos > 4 && src[start_pos] == '*') {
        int line_num = atoi(src + start_pos + 1);
        start_pos = request_str.find_first_of("\r\n", start_pos + 1) + 2;
        if (line_num < 2 || start_pos < 1 || src_size - start_pos < 4) {
            break;
        }
        
        redis_cmd_t redis_cmd;
        cmd_list.push_back(redis_cmd);
        auto* p_redis_cmd = &cmd_list[cmd_list.size() - 1];
        
        std::vector<std::string*> cmd_params;
        cmd_params.push_back(&p_redis_cmd->cmd);
        cmd_params.push_back(&p_redis_cmd->key);
        cmd_params.push_back(&p_redis_cmd->timeout);
        cmd_params.push_back(&p_redis_cmd->value);
        for (int i = 0; i < line_num && i < cmd_params.size(); ++i) { 
            if (src_size - start_pos <  1) {
                break;
            }
            int cmd_str_size = atoi(src + start_pos + 1);
            start_pos = request_str.find_first_of("\r\n", start_pos + 1) + 2;
            if (cmd_str_size < 1 || start_pos < 2 || 
                src_size - start_pos < cmd_str_size) {
                break;
            }
            cmd_params[i]->assign(request_str, start_pos, cmd_str_size);
            start_pos = start_pos + cmd_str_size + 2;
        }
        boost::to_upper(p_redis_cmd->cmd);
    }
    return true;
}

}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
