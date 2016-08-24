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
    std::string datetime();

    /// 获取当前日期
    std::string date();

    /// 获取当前时间戳
    long timestamp();

}
}

#endif
