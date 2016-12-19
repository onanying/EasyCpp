/*
 * 日期时间辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_DATETIME_INCLUDED
#define EASYCPP_HELPERS_DATETIME_INCLUDED

#include <iostream>
#include <time.h>
#include <string>

namespace easycpp {
namespace helpers {

    /// 获取当前日期
    std::string date(std::string format, long timestamp = -1);

    /// 获取当前时间戳
    long timestamp();

}
}

#endif
