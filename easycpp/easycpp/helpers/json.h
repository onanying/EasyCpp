/*
 * json辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_JSON_INCLUDED
#define EASYCPP_HELPERS_JSON_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <easycpp/libraries/exception.h>
#include <easycpp/libraries/json.h>

namespace easycpp {
namespace helpers {

    /// 初始化json对象
    easycpp::libraries::JsonObject json_init(const std::string json_str);

    /// 从json对象中获取json数组
    std::vector<easycpp::libraries::JsonObject> json_get_array(easycpp::libraries::JsonObject &obj, const std::string key);

    /// 从json对象中获取json对象
    easycpp::libraries::JsonObject json_get_object(easycpp::libraries::JsonObject &obj, const std::string key);

    /// 从json对象中获取值， string
    std::string json_get_string(easycpp::libraries::JsonObject &obj, const std::string key);

    /// 从json对象中获取值 int
    int json_get_int(easycpp::libraries::JsonObject &obj, const std::string key);

}
}

#endif
