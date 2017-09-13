/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file sofa_common.h
 * @author renke(com@baidu.com)
 * @date 2016/09/07 16:46:47
 * @brief 
 *  
 **/

#ifndef  GR_SOFA_COMMON_H
#define  GR_SOFA_COMMON_H

//#include "redisprotocol.pb.h"
//#include "drredis.pb.h"
//#include "common.h"
#include <string>
#include <vector>
#include <json/json.h>
#include <stdint.h>
#include <boost/unordered_set.hpp>
#include "time.h"

namespace gr {

class SofaCommon 
{
public:
    SofaCommon() {}
    ~SofaCommon() {}
    //static SofaCommon *get_instance();
    //static void get_current_us_time();
    static std::string get_reqstr_by_key(Json::Value &req_json, const std::string key);
    static std::string convert_sid(const std::string sid);
    /*
    static void process_sofaparam_adapt_result(Json::Value &sofa_params,
                                               Json::Value &ad_value,
                                               Json::Value &loc_value);
    static void get_sofavrparams(SVideoRedisMessage &svideo_redis_msg,
                                 Json::Value &req_json,
                                 unsigned int log_id,
                                 const int req_type,
                                 const int req_count,
                                 Json::Value &sofavr_params);
    static void convert_sofavr_response(Json::Value *sofavr_resp,
                                        const int src_type,
                                        Json::Value &sofavr_conv_after);
    static void add_nnews_to_vec(int nredis_szie,
                            boost::unordered_set<uint64_t> &nids_set,
                            NewsMessage &news_redis_msg,
                            std::vector<NewsItem> &news_vec);
    static void add_drnews_to_vec(int dredis_szie,
                            boost::unordered_set<uint64_t> &nids_set,
                            DRNewsRedisMessage &dr_news_redis_msg,
                            std::vector<NewsItem> &news_vec);
    static void get_issued_news_vec(NewsMessage &news_redis_msg,
                            DRNewsRedisMessage &dr_news_redis_msg,
                            std::vector<NewsItem> &news_vec);
    */
private:
    //static SofaCommon *_s_utils;
};

}

#endif  //__SOFA_COMMON_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
