#include "sofa_common.h"
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <sys/time.h>

namespace gr {

/*    
SofaCommon *SofaCommon::_s_utils = NULL;
SofaCommon *SofaCommon::get_instance()
{
    if (_s_utils == NULL) {
        _s_utils = new SofaCommon();
    }
    return _s_utils;
}
*/

std::string SofaCommon::convert_sid(const std::string sid)
{
    std::string cov_sid = "";
    if (sid.size() == 0) {
        return cov_sid;
    } else {
        std::vector<std::string> vec_sid;
        split(vec_sid, sid, boost::is_any_of("-"));
        for (int i = 0; i < vec_sid.size(); i++) {
            if (vec_sid[i].find("_") != std::string::npos) {
                cov_sid.append(vec_sid[i].replace(vec_sid[i].find("_"), 1, ""));
                cov_sid.append("_");
            }
        }
        if (!cov_sid.empty()) {
            cov_sid.erase(cov_sid.size() - 1, 1);
        }
        return cov_sid;
    }
    return cov_sid;
}

std::string SofaCommon::get_reqstr_by_key(Json::Value &req_json, const std::string key)
{
    std::string reqstr = "";
    if (req_json.isObject()       &&
        req_json.isMember(key)    &&
        req_json[key].isString()) {
        reqstr = req_json[key].asString();
    }
    return reqstr;
}

#if 0
void SofaCommon::process_sofaparam_adapt_result(Json::Value &sofa_params,
                                                Json::Value &ad_value,
                                                Json::Value &loc_value)
{
    sofa_params["adapt_result"] = "";
    std::string ut = ad_value["ut"].asString();
    std::string ua = ad_value["ua"].asString();
    std::string ut_lower = ut;
    boost::to_lower(ut_lower);
    std::string province = "null";
    std::string city = "null";
    std::string district = "null";
    std::string browser = "null";
    if (!loc_value["loc_province"].asString().empty()) {
        province = loc_value["loc_province"].asString();
    }
    if (!loc_value["loc_city"].asString().empty()) {
        city = loc_value["loc_city"].asString();
    }
    if (!loc_value["loc_district"].asString().empty()) {
        district = loc_value["loc_district"].asString();
    }
    if (!ad_value["browser"].asString().empty()) {
        browser = ad_value["browser"].asString();
    }

    if (ut_lower.find("iphone") != std::string::npos) {
        std::vector<std::string> vec_ua;
        split(vec_ua, ua, boost::is_any_of("_"));
        if (vec_ua.size() >= 4) {
            std::string adapt = "apple@iphone@" + vec_ua[2] + "@" + vec_ua[3] + "@" +
                vec_ua[1] + "@" + vec_ua[0] + "@" + browser + "@" + province + "@" + 
                city + "@" + district;
            sofa_params["adapt_result"] = adapt;
        } else {
            std::string adapt = "apple@iphone@null@null@null@null@" + browser + "@" + 
                province + "@" + city + "@" + district;
            sofa_params["adapt_result"] = adapt;
        }
        //rec_params["adapt_result"] = Utils::url_encode(adapt);
    } else {
        std::vector<std::string> vec;
        split(vec, ut, boost::is_any_of("_"));
        std::vector<std::string> vec_ua;
        split(vec_ua, ua, boost::is_any_of("_"));
        if (vec_ua.size() >= 4) {
            std::string adapt = vec[vec.size() - 1] + "@" + vec[0] + "@" + vec_ua[2] + "@" + 
                vec_ua[3] + "@" + vec_ua[1] + "@" + vec_ua[0] + "@" + browser + "@" + 
                province + "@" + city + "@" + district;
            sofa_params["adapt_result"] = adapt;
        } else {
            std::string adapt = vec[vec.size() - 1] + "@" + vec[0] + "@null@null@null@null@" +
                browser + "@" + province + "@" + city + "@" + district;
            sofa_params["adapt_result"] = adapt;
        }
    }
}

void SofaCommon::get_sofavrparams(SVideoRedisMessage &svideo_redis_msg,
                               Json::Value &req_json,
                               unsigned int log_id,
                               const int req_type,
                               const int req_count,
                               Json::Value &sofavr_params)
{
    std::ostringstream display;
    int display_num = 0;
    if (svideo_redis_msg.issued_ids_size() > 0) {
        int32_t delete_index = svideo_redis_msg.delete_index();
        for (int i = delete_index; i < svideo_redis_msg.issued_ids_size(); ++i) {
            display << svideo_redis_msg.issued_ids(i) << ",";
            display_num++;
        }
        for (int i = 0; i < delete_index && i < svideo_redis_msg.issued_ids_size(); ++i) {
            display << svideo_redis_msg.issued_ids(i) << ",";
            display_num++;
        }
    }
    /*
    for (int i = 0; i < svideo_redis_msg.issued_items_size(); ++i) {
        display << svideo_redis_msg.issued_items(i).id() << ",";
        display_num++;
    }
    */
    sofavr_params["display"] = display.str().substr(0, display.str().length() - 1);
    sofavr_params["adapt_result"] = "";
    std::string sid = "";
    if (req_json.isMember("smfw")  &&
        req_json["smfw"].isObject()) {
        Json::Value::Members mem = req_json["smfw"].getMemberNames();
        Json::Value::Members::iterator iter;      
        for (iter = mem.begin(); iter != mem.end(); iter++) {
            if (req_json["smfw"][*iter].type() == Json::stringValue) {
                sid.append(*iter);
                sid.append(req_json["smfw"][*iter].asString());
                sid.append("_");
            }
        }     
    } 
    sofavr_params["sid"] = sid.substr(0, sid.length() - 1);
    sofavr_params["sample_name"] = "mhd";
    sofavr_params["cuid"] = get_reqstr_by_key(req_json, "cuid"); 
    sofavr_params["uid"] = get_reqstr_by_key(req_json, "uid");
    sofavr_params["bid"] = get_reqstr_by_key(req_json, "baiduid");
    sofavr_params["user_ip"] = get_reqstr_by_key(req_json, "ip");
    sofavr_params["delete_index"] = svideo_redis_msg.delete_index();
    //sofavr_params["type"] = VIDEO_ATTENTION;
    sofavr_params["type"] = req_type;
    sofavr_params["recnums"] = req_count;
    sofavr_params["logid"] = log_id;
    sofavr_params["p_params"] = svideo_redis_msg.p_params();
    /*
    if (_req_json.isMember("attention")    &&
        _req_json["attention"].isString()) {
        sofavr_params["attention"] = _req_json["attention"].asString();
    }
    if (_req_json.isMember("cnt_deviation")    &&
        _req_json["cnt_deviation"].isInt()) {
        sofavr_params["cnt_deviation"] = _req_json["cnt_deviation"].asInt();
    }
    */
}

void SofaCommon::convert_sofavr_response(Json::Value *sofavr_resp,
                                      const int src_type,
                                      Json::Value &sofavr_conv_after)
{
    //Json::Value *sofavr_resp = _sofavr.get_sofavr_resp();
    if (sofavr_resp->isObject()                     &&
        sofavr_resp->isMember("result")             &&
        (*sofavr_resp)["result"].isObject()           &&
        (*sofavr_resp)["result"].isMember("_ret")     &&
        (*sofavr_resp)["result"]["_ret"].isObject()) {
        Json::Value ret = (*sofavr_resp)["result"]["_ret"];

        if (ret.isMember("ridinfos")    &&
                ret["ridinfos"].isArray()) {
            for (int i = 0; i < ret["ridinfos"].size(); i++) {
                if (ret["ridinfos"][i].isObject()  &&
                        ret["ridinfos"][i].isMember("rid")      &&
                        //ret["ridinfos"][i]["rid"].isInt()    &&
                        ret["ridinfos"][i].isMember("display")    &&
                        ret["ridinfos"][i]["display"].isObject()  &&
                        ret["ridinfos"][i]["display"].isMember("brief")  &&
                        ret["ridinfos"][i]["display"]["brief"].isString()) {
                    Json::Value id;
                    id["id"] = ret["ridinfos"][i]["rid"].asUInt64();
                    if (ret["ridinfos"][i].isMember("p_params")  &&
                            ret["ridinfos"][i]["p_params"].isString()) {
                        id["p_params"] = ret["ridinfos"][i]["p_params"].asString();
                    }
                    Json::Value display = ret["ridinfos"][i]["display"];
                    Json::Value brief = display.removeMember("brief");

                    id["cs"] = brief.asString();
                    id["display_strategy"] = display;
                    // add ext field

                    Json::Value rec_src;
                    rec_src.append(src_type);
                    if (ret["ridinfos"][i]["ext"].isObject()) {
                        id["ext"] = ret["ridinfos"][i]["ext"]; 
                    } else {
                        id["ext"] = Json::objectValue; 
                    }
                    id["ext"]["rec_src"] = rec_src;
                    if (display.isMember("type") && display["type"].isInt()) {
                        id["ext"]["type"] = display["type"].asInt();
                    }
                    sofavr_conv_after.append(id);
                }
            }
        }
    }
}

void SofaCommon::add_nnews_to_vec(int nredis_size,
                            boost::unordered_set<uint64_t> &nids_set,
                            NewsMessage &news_redis_msg,
                            std::vector<NewsItem> &news_vec) {
    if (nids_set.count(news_redis_msg.nids(nredis_size))) {
        return;
    } else {
        NewsItem item(news_redis_msg.nids(nredis_size),
            news_redis_msg.cs1s(nredis_size),
            news_redis_msg.cs2s(nredis_size),
            news_redis_msg.tss(nredis_size)
            );
        news_vec.push_back(item);
        nids_set.insert(news_redis_msg.nids(nredis_size));
    }
}

void SofaCommon::add_drnews_to_vec(int dredis_size,
                            boost::unordered_set<uint64_t> &nids_set,
                            DRNewsRedisMessage &dr_news_redis_msg,
                            std::vector<NewsItem> &news_vec) {
    if (nids_set.count(dr_news_redis_msg.issued_items(dredis_size).nid())) {
        return;
    } else {
        NewsItem item(dr_news_redis_msg.issued_items(dredis_size).nid(),
                      dr_news_redis_msg.issued_items(dredis_size).cs1(),
                      dr_news_redis_msg.issued_items(dredis_size).cs2(),
                      dr_news_redis_msg.issued_items(dredis_size).timestamp()
        );
        news_vec.push_back(item);
        nids_set.insert(dr_news_redis_msg.issued_items(dredis_size).nid());
    }
}

void SofaCommon::get_issued_news_vec(NewsMessage &news_redis_msg,
                            DRNewsRedisMessage &dr_news_redis_msg,
                            std::vector<NewsItem> &news_vec) {
    int last = dr_news_redis_msg.issued_items_size() - 1;
    int dredis_size = dr_news_redis_msg.issued_items_size(); 
    uint64_t dr_ts1 = 0;
    uint64_t dr_ts2 = 0;
    if (dredis_size > 0) {
        dr_ts1 = dr_news_redis_msg.issued_items(0).timestamp();
    }
    if (last >= 0) {
        dr_ts2 = dr_news_redis_msg.issued_items(last).timestamp();
    }
    int nredis_size = std::min(news_redis_msg.nids_size(), news_redis_msg.cs1s_size());
    nredis_size = std::min(nredis_size, news_redis_msg.cs2s_size());
    nredis_size = std::min(nredis_size, news_redis_msg.tss_size());
    boost::unordered_set<uint64_t> nids_set;
    if (dr_ts1 > dr_ts2) {
        while (nredis_size > 0 && dredis_size > 0) {
            if (news_redis_msg.tss(nredis_size - 1) <= 
                dr_news_redis_msg.issued_items(dredis_size - 1).timestamp()) {
                add_nnews_to_vec(nredis_size - 1, nids_set, news_redis_msg, news_vec);
                nredis_size--;
            } else {
                add_drnews_to_vec(dredis_size - 1, nids_set, dr_news_redis_msg, news_vec);
                dredis_size--;
            }
        }
        while (nredis_size > 0) {
            add_nnews_to_vec(nredis_size - 1, nids_set, news_redis_msg, news_vec);
            nredis_size--;
        }
        while (dredis_size > 0) {
            add_drnews_to_vec(dredis_size - 1, nids_set, dr_news_redis_msg, news_vec);
            dredis_size--;
        }
    } else {
        int i = 0;
        while (nredis_size > 0 && i < dredis_size) {
            if (news_redis_msg.tss(nredis_size - 1) <= 
                dr_news_redis_msg.issued_items(i).timestamp()) {
                add_nnews_to_vec(nredis_size - 1, nids_set, news_redis_msg, news_vec);
                nredis_size--;
            } else {
                add_drnews_to_vec(i, nids_set, dr_news_redis_msg, news_vec);
                i++;
            }
        }
        while (nredis_size > 0) {
            add_nnews_to_vec(nredis_size - 1, nids_set, news_redis_msg, news_vec);
            nredis_size--;
        }
        while (i < dredis_size) {
            add_drnews_to_vec(i, nids_set, dr_news_redis_msg, news_vec);
            i++;
        }
    }
}
#endif

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
