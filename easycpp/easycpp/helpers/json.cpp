/*
 * json辅助函数
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/helpers/json.h>

/// 初始化json对象
easycpp::libraries::JsonObject easycpp::helpers::json_init(const std::string json_str)
{
    easycpp::libraries::JsonObject obj;
    std::stringstream ss(json_str);
    try {
        boost::property_tree::read_json(ss, obj);
    } catch (boost::property_tree::ptree_error& ex) {
        std::string err_str = "json_init error: " + json_str + "; ";
        err_str.append(ex.what());
        throw easycpp::libraries::Exception(err_str);
    }
    return obj;
}

/// 从json对象中获取json数组
std::vector<easycpp::libraries::JsonObject> easycpp::helpers::json_get_array(easycpp::libraries::JsonObject &obj, const std::string key)
{
    std::vector<easycpp::libraries::JsonObject> obj_ary;
    try {
        easycpp::libraries::JsonObject array = obj.get_child(key);
        BOOST_FOREACH(easycpp::libraries::JsonValue &v, array)
        {
            std::stringstream s;
            write_json(s, v.second);
            easycpp::libraries::JsonObject new_obj = json_init(s.str());
            obj_ary.push_back(new_obj);
        }
    } catch (boost::property_tree::ptree_error& ex) {
        std::string err_str = "json_get_array error: " + key + "; ";
        err_str.append(ex.what());
        throw easycpp::libraries::Exception(err_str);
    }
    return obj_ary;
}

/// 从json对象中获取json对象
easycpp::libraries::JsonObject easycpp::helpers::json_get_object(easycpp::libraries::JsonObject &obj, const std::string key)
{
    easycpp::libraries::JsonObject obj_child;
    try {
        obj_child = obj.get_child(key);
    } catch (boost::property_tree::ptree_error& ex) {
        std::string err_str = "json_get_object error: " + key + "; ";
        err_str.append(ex.what());
        throw easycpp::libraries::Exception(err_str);
    }
    return obj_child;
}

/// 从json对象中获取值， string
std::string easycpp::helpers::json_get_string(easycpp::libraries::JsonObject &obj, const std::string key)
{
    std::string val = "";
    try {
        val = obj.get<std::string>(key);
    } catch (boost::property_tree::ptree_error& ex) {
        std::string err_str = "json_get_string error: " + key + "; ";
        err_str.append(ex.what());
        throw easycpp::libraries::Exception(err_str);
    }
    return val;
}

/// 从json对象中获取值 int
int easycpp::helpers::json_get_int(easycpp::libraries::JsonObject &obj, const std::string key)
{
    int val = 0;
    try {
        val = obj.get<int>(key);
    } catch (boost::property_tree::ptree_error& ex) {
        std::string err_str = "json_get_int error: " + key + "; ";
        err_str.append(ex.what());
        throw easycpp::libraries::Exception(err_str);
    }
    return val;
}
