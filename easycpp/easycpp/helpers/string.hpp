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
    void str_replace(const std::string find, const std::string replace, std::string& string)
    {
        if(find.empty() || string.empty()){
            return;
        }
        size_t pos = 0;
        while(true) {
            pos = string.find(find, pos);
            if (pos == std::string::npos) {
                break;
            }
            string.replace(pos, find.size(), replace);
        }
    }

    /// 把字符串打散为数组
    void explode(const std::string separator, const std::string string, std::vector<std::string> &array)
    {
        if(separator.empty() || string.empty()){
            return;
        }
        size_t pos = 0;
        size_t start = 0;
        while(true) {
            pos = string.find(separator, pos);
            if (pos == std::string::npos) {
                std::string str = string.substr(start);
                array.push_back(str);
                break;
            }
            std::string str = string.substr(start, pos - start);
            array.push_back(str);
            pos++;
            start = pos;
        }
    }

}
}

#endif
