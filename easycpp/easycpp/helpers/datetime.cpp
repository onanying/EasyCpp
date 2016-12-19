/*
 * 日期时间辅助函数
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/helpers/datetime.h>

/// 获取当前日期
std::string easycpp::helpers::date(std::string format, long timestamp)
{
    time_t t = (timestamp == -1 ? time(0) : timestamp);
    char tmp[50];
    strftime(tmp, sizeof(tmp), format.c_str(), localtime(&t));
    return std::string(tmp);
}

/// 获取当前时间戳
long easycpp::helpers::timestamp(){
    time_t rawtime;
    return time(&rawtime);
}
