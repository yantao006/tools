#ifndef  GR_UTILS_H
#define  GR_UTILS_H

#include <string>
#include <vector>
#include <stdint.h>
#include <rapidjson.h>
#include <baidu/rpc/redis.h>
#include <boost/unordered_set.hpp>
#include "time.h"

namespace gr {

struct redis_cmd_t {
    std::string cmd;
    std::string key;
    std::string value;
    std::string timeout;
};

class Utils 
{
public:
    Utils() {}
    ~Utils() {}
    //static Utils *get_instance();
    static int64_t get_current_us_time();
    static bool is_yesterday(time_t last, time_t now);
    static bool is_in_spantime(int h_start, int h_end, time_t now);
    static bool is_in_spantime_minutes(int start_hour, int end_hour, 
                                       int start_min, int end_min, time_t now);
    static bool is_sv_relaxtime(time_t now);
    static bool is_sv_relaxtime(time_t now, int start, int end);
    static bool is_double11_first(time_t last, time_t now);
    static bool is_hot_video(int ext_ac, int type);
    static std::string url_encode(const std::string& cppStr);
    static bool rand1_with_p(int p_num);
    static uint64_t sign_fs64(const std::string &raw_content);
    static int arrays_diff(std::vector<std::string> v1,
                           std::vector<std::string> v2,
                           std::vector<std::string> &v_diff);
    static double get_distance(double long1, double lat1, double long2, double lat2);
    static double rad(double angle);
    static void mercator2lonlat(double x, double y, double & lng, double & lat);
    static bool has_intersection(const boost::unordered_set<std::string> &set1,
            const boost::unordered_set<std::string> &set2);
    static void gen_rand_pos(std::set<int> &pos_set, const int merge_size, const int template_num);
    static bool is_higher_app_version(const std::string &app_version, int v1, int v2);
    static bool is_filter_ios_image_video(const std::string &app_version, uint32_t channel_id,
        rapidjson::Document &sess_doc);
    static uint32_t get_cuid_hash(const std::string &key);
    static void string_split(const std::string& s, 
                             const std::string& delim, 
                             std::vector< std::string > &ret);
    static uint64_t create_sign(const char *str);
    static bool is_baibao_pushtime(time_t now);
    static bool is_hit_smfw(const std::map<std::string, std::string> &smfw, 
        const std::string &key, const std::string &value);
    static unsigned int stoui(const std::string &strvalue);
    static int two_samples_t_test(double mean1, double std1, int64_t size1,
        double mean2, double std2, int64_t size2, double sig_level);
    //反解redis request protocol (support: get, del, setex)
    static bool parse_from_redis_request(const baidu::rpc::RedisRequest& request, 
        std::vector<redis_cmd_t>& redis_cmd_list);
private:
    //static Utils *_s_utils;
    static int compare_int_array(uint32_t (&a)[4], uint32_t (&b)[4]);
    static void generator_int_array(const std::string &app_version, uint32_t (&a)[4]);

};

}

#endif  //__UTILS_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
