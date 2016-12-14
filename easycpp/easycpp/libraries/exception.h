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
        Exception(std::string &msg);

        Exception(const char* msg);

        ~Exception() throw();

        const char* what() const throw();
    private:
        std::string msg_;
    };

}
}

#endif
