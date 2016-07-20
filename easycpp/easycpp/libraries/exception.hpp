/*
 * 异常处理类
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_LIBRARIES_EXCEPTION_INCLUDED
#define EASYCPP_LIBRARIES_EXCEPTION_INCLUDED

#include <iostream>
#include <string>
#include <exception>

namespace easycpp {
namespace libraries {

    class Exception : public std::exception
    {
    public:
        Exception(std::string& msg) : msg_(msg)
        {}

        Exception(const char* msg) : msg_(msg)
        {}

        ~Exception(void) throw ()
        {}

        const char * what(void) const throw ()
        {
            return msg_.c_str();
        }
    private:
        const std::string msg_;
    };

}
}

#endif
