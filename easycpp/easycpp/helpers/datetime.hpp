/*
 * 日期时间辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_DATETIME_INCLUDED
#define EASYCPP_HELPERS_DATETIME_INCLUDED

#include <iostream>
#include <string>

namespace easycpp {
namespace helpers {

    /// 获取当前日期时间
    std::string datetime()
    {
        time_t t = time(0);
        char tmp[20];
        strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A", localtime(&t));
        return std::string(tmp);
    }

    /// 获取当前日期
    std::string date()
    {
        time_t t = time(0);
        char tmp[11];
        strftime(tmp, sizeof(tmp), "%Y/%m/%d", localtime(&t));
        return std::string(tmp);
    }

    /// 获取当前时间戳
    long timestamp(){
        time_t rawtime;
        return time(&rawtime);
    }

}
}

#endif
