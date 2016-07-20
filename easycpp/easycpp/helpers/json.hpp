/*
 * json辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_JSON_INCLUDED
#define EASYCPP_HELPERS_JSON_INCLUDED

#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <easycpp/libraries/exception.hpp>
#include <easycpp/libraries/json.hpp>

namespace easycpp {
namespace helpers {

    /// 初始化json对象
    void json_init(easycpp::libraries::JsonObject &obj, const std::string json_str)
    {
        std::stringstream ss(json_str);
        try {
            boost::property_tree::read_json(ss, obj);
        } catch (boost::property_tree::ptree_error& ex) {
            std::string errStr = "json_init error: " + json_str + "; ";
            errStr.append(ex.what());
            throw easycpp::libraries::Exception(errStr);
        }
    }

    /// 从json对象中获取json数组
    void json_get_array(easycpp::libraries::JsonObject &obj, std::vector<easycpp::libraries::JsonObject> &obj_ary, const std::string key)
    {
        try {
            easycpp::libraries::JsonObject array = obj.get_child(key);
            BOOST_FOREACH(boost::property_tree::ptree::value_type &v, array)
            {
                std::stringstream s;
                write_json(s, v.second);
                easycpp::libraries::JsonObject new_obj;
                json_init(new_obj, s.str());
                obj_ary.push_back(new_obj);
            }
        } catch (boost::property_tree::ptree_error& ex) {
            std::string errStr = "json_get_array error: " + key + "; ";
            errStr.append(ex.what());
            throw easycpp::libraries::Exception(errStr);
        }
    }

    /// 从json对象中获取json对象
    void json_get_object(easycpp::libraries::JsonObject &obj, easycpp::libraries::JsonObject &obj_child, const std::string key)
    {
        try {
            obj_child = obj.get_child(key);
        } catch (boost::property_tree::ptree_error& ex) {
            std::string errStr = "json_get_object error: " + key + "; ";
            errStr.append(ex.what());
            throw easycpp::libraries::Exception(errStr);
        }
    }

    /// 从json对象中获取值， string
    std::string json_get_string(easycpp::libraries::JsonObject &obj, const std::string key)
    {
        std::string val = "";
        try {
            val = obj.get<std::string>(key);
        } catch (boost::property_tree::ptree_error& ex) {
            std::string errStr = "json_get_string error: " + key + "; ";
            errStr.append(ex.what());
            throw easycpp::libraries::Exception(errStr);
        }
        return val;
    }

    /// 从json对象中获取值 int
    int json_get_int(easycpp::libraries::JsonObject &obj, const std::string key)
    {
        int val = 0;
        try {
            val = obj.get<int>(key);
        } catch (boost::property_tree::ptree_error& ex) {
            std::string errStr = "json_get_int error: " + key + "; ";
            errStr.append(ex.what());
            throw easycpp::libraries::Exception(errStr);
        }
        return val;
    }

}
}

#endif
