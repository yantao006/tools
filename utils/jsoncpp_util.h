/***************************************************************************
 *
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @file jsoncpp_util.h
 * @author zhangluxin(com@baidu.com)
 * @date 2016/03/02 15:08:53
 * @brief
 *
 **/

#ifndef GR_JSONCPP_UTIL_H
#define GR_JSONCPP_UTIL_H 

#include <json/json.h>

namespace gr {
inline bool jsoncpp_is_string(const Json::Value& node, const char * name) {
    return (node.isObject() && node.isMember(name) && node[name].isString());
}

inline bool jsoncpp_is_int(const Json::Value& node, const char * name) {
    return (node.isObject() && node.isMember(name) && node[name].isInt());
}

inline bool jsoncpp_is_array(const Json::Value& node, const char * name) {
    return (node.isObject() && node.isMember(name) && 
            node[name].isArray() && node[name].size() > 0);
}

inline bool jsoncpp_is_object(const Json::Value& node, const char * name) {
    return (node.isObject() && node.isMember(name) && node[name].isObject());
}

inline bool jsoncpp_is_uint(const Json::Value& node, const char * name) {
    return (node.isObject() && node.isMember(name) && node[name].isUInt());
}

inline void jsoncpp_default(Json::Value& node, const char * name, const char* def) {
    if (!node.isMember(name) || !node[name].isString()) {
        node[name] = def;
    }
}

inline void jsoncpp_default(Json::Value& node, const char * name, int def) {
    if (!node.isMember(name) || !node[name].isInt()) {
        node[name] = def;
    }
}

inline bool jsoncpp_is_uint64(const Json::Value& node, const char * name) {
    /*
    *  Int/UInt is 64bit in jsoncpp
    */
    return (node.isObject() && node.isMember(name) && 
            (node[name].isUInt() || (node[name].isInt() && node[name].asInt() > -1)));
}

}

#endif  //__GR_JSONCPP_UTIL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
