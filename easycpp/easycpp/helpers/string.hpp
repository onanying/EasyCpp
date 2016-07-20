/*
 * 字符串辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_STRING_INCLUDED
#define EASYCPP_HELPERS_STRING_INCLUDED

#include <iostream>
#include <string>

namespace easycpp {
namespace helpers {

    /// 替换字符
    void str_replace(const std::string find, const std::string replace, std::string& string)
    {
        size_t pos = 0;
        while(true) {
            pos = string.find(find, pos);
            if (pos == std::string::npos) {
                break;
            }
            string.replace(pos, find.size(), replace);
        }
    }

}
}

#endif
