/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file base64.h
 * @author renke(com@baidu.com)
 * @date 2017/03/21 16:46:47
 * @brief 
 *  
 **/

#ifndef  GR_BASE64_H
#define  GR_BASE64_H

#include <string>

namespace gr {

class Base64 
{
public:
    Base64() {}
    ~Base64() {}
    //static Base64 *get_instance();
    static bool is_base64(unsigned char c);
    static std::string base64_encode(unsigned char const* , unsigned int len);
    static std::string base64_decode(std::string const& s);

private:
    //static Base64 *_s_utils;
};

}

#endif  //__BASE64_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
