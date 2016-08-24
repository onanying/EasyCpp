/*
 * 异常处理类
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/libraries/exception.h>

easycpp::libraries::Exception::Exception(std::string &msg)
{
    msg_ = msg;
}

easycpp::libraries::Exception::Exception(const char *msg)
{
    msg_ = std::string(msg);
}

easycpp::libraries::Exception::~Exception() throw()
{

}

const char* easycpp::libraries::Exception::what() const throw()
{
    return msg_.c_str();
}
