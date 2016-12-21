/*
 * 日志辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_LOG_INCLUDED
#define EASYCPP_HELPERS_LOG_INCLUDED

#include <iostream>
#include <string>

#include <easycpp/helpers/file.h>
#include <easycpp/helpers/datetime.h>

namespace easycpp {
namespace helpers {

    /// 输出错误日志
    void log_error(std::string tag, std::string msg, std::string path = "");

    /// 输出调试日志
    void log_debug(std::string tag, std::string msg, std::string path = "");

    /// 输出信息日志
    void log_info(std::string tag, std::string msg, std::string path = "");

}
}

#endif
