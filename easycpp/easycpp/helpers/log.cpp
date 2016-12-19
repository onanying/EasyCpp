/*
 * 日志辅助函数
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/helpers/log.h>

/// 输出错误日志
void easycpp::helpers::log_error(std::string tag, std::string msg, std::string subdir)
{
    std::string data = easycpp::helpers::datetime()+ " | ERROR | " + tag + " | " + msg + "\n";
    easycpp::helpers::file_put_contents("log/" + (subdir == "" ? "" : subdir + "/") + "error.log", data, FILE_APPEND);
}

/// 输出调试日志
void easycpp::helpers::log_debug(std::string tag, std::string msg, std::string subdir)
{
    std::string data = easycpp::helpers::datetime() + " | DEBUG | " + tag + " | " + msg + "\n";
    easycpp::helpers::file_put_contents("log/" + (subdir == "" ? "" : subdir + "/") + "debug.log", data, FILE_APPEND);
}

/// 输出信息日志
void easycpp::helpers::log_info(std::string tag, std::string msg, std::string subdir)
{
    std::string data = easycpp::helpers::datetime() + " | INFO | " + tag + " | " + msg + "\n";
    easycpp::helpers::file_put_contents("log/" + (subdir == "" ? "" : subdir + "/") + "info.log", data, FILE_APPEND);
}
