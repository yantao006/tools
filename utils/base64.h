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

