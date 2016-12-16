/*
 * 字符串辅助函数
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/helpers/string.h>

/// 替换字符
std::string easycpp::helpers::str_replace(const std::string find, const std::string replace, std::string string)
{
    if(find.empty() || string.empty()){
        return string;
    }
    size_t pos = 0;
    while(true) {
        pos = string.find(find, pos);
        if (pos == std::string::npos) {
            break;
        }
        string.replace(pos, find.size(), replace);
    }
    return string;
}

/// 把字符串打散为数组
std::vector<std::string> easycpp::helpers::explode(const std::string separator, const std::string string)
{
    std::vector<std::string> array;
    if(separator.empty() || string.empty()){
        return array;
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
    return array;
}

/// 把数组元素组合为字符串
std::string easycpp::helpers::implode(std::string separator, std::vector<std::string> array)
{
    std::string str;
    int size = array.size();
    for(int i = 0; i<size; i++){
        std::string item = array.at(i);
        str += separator + item.c_str();
    }
    return str.substr(1, str.size());
}
