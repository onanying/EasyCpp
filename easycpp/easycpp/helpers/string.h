/*
 * 字符串辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_STRING_INCLUDED
#define EASYCPP_HELPERS_STRING_INCLUDED

#include <iostream>
#include <string>
#include <vector>

namespace easycpp {
namespace helpers {

    /// 替换字符
    std::string str_replace(const std::string find, const std::string replace, std::string string);

    /// 把字符串打散为数组
    std::vector<std::string> explode(const std::string separator, const std::string string);

    /// 把数组元素组合为字符串
    std::string implode(std::string separator, std::vector<std::string> array);

}
}

#endif
