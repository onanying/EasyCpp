/*
 * http辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_HTTP_INCLUDED
#define EASYCPP_HELPERS_HTTP_INCLUDED

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/foreach.hpp>

#include <easycpp/helpers/json.hpp>
#include <easycpp/helpers/type.hpp>
#include <easycpp/helpers/string.hpp>

const std::string HTTP_BUILD_KEYS_ALL = "HTTP_BUILD_KEYS_ALL";

namespace easycpp {
namespace helpers {

    /// POST请求
    int http_post(const std::string& host, const std::string& port, const std::string& page, const std::string& form_data, std::string& reponse_data, int timeout = 30)
    {
        try {
            boost::asio::ip::tcp::iostream stream;
            stream.expires_from_now(boost::posix_time::seconds(timeout));
            stream.connect(host, port);
            stream << "POST " << page << " HTTP/1.0\r\n";
            stream << "Host: " << host << ":" << port << "\r\n";
            stream << "Accept: */*\r\n";
            stream << "Content-Length: " << form_data.length() << "\r\n";
            stream << "Content-Type: application/x-www-form-urlencoded\r\n";
            stream << "Connection: close\r\n\r\n";
            stream << form_data;
            stream.flush();

            std::string status_code;
            std::string line;

            while (std::getline(stream, line) && line != "\r") {
                if(line.find("HTTP/") != std::string::npos){
                    status_code = line.substr(9, 3);
                }
            }
            while (std::getline(stream, line)) {
                reponse_data += line;
            }

            if (status_code.empty()) {
                reponse_data = "Invalid response";
                return -1;
            }

            // 状态码非200, 不支持301/302等跳转
            if (status_code != "200") {
                reponse_data = "Response returned with status code != 200 " ;
                return easycpp::helpers::c_int(status_code);
            }
        } catch(std::exception& e) {
            reponse_data = e.what();
            return -2;
        }
        return 0;
    }

    /// POST请求(重载)
    int http_post(std::string url, const std::string& form_data, std::string& reponse_data, const int timeout = 30)
    {
        // 去掉url中的协议头
        if (url.find("http://") != std::string::npos) {
            url = url.substr(7);
        }
        // 补充path
        if(url.find("/") == std::string::npos){
            url.append("/");
        }

        // 分隔符位置
        size_t path_index = url.find("/");
        // 分隔符位置
        size_t port_index = url.find(":");

        // 截取host字符串
        std::string host = url.substr(0, path_index);
        if(port_index != std::string::npos){
            host = url.substr(0, port_index);
        }

        // 截取port字符串
        std::string port = "80";
        if(port_index != std::string::npos){
            port = url.substr(port_index + 1, path_index - port_index - 1);
        }

        // 截取path字符串
        std::string page = url.substr(path_index, url.length() - path_index);

        return http_post(host, port, page, form_data, reponse_data, timeout);
    }

    /// GET请求
    int http_get(const std::string& host, const std::string& port, const std::string& page, std::string& reponse_data, const int timeout = 30)
    {
        try {
            boost::asio::ip::tcp::iostream stream;
            stream.expires_from_now(boost::posix_time::seconds(timeout));
            stream.connect(host, port);
            stream << "GET " << page << " HTTP/1.0\r\n";
            stream << "Host: " << host << ":" << port << "\r\n";
            stream << "Accept: */*\r\n";
            stream << "Connection: close\r\n\r\n";
            stream.flush();

            std::string status_code;
            std::string line;

            while (std::getline(stream, line) && line != "\r") {
                if(line.find("HTTP/") != std::string::npos){
                    status_code = line.substr(9, 3);
                }
            }
            while (std::getline(stream, line)) {
                reponse_data += line;
            }

            if (status_code.empty()) {
                reponse_data = "Invalid response";
                return -1;
            }

            // 状态码非200, 不支持301/302等跳转
            if (status_code != "200") {
                reponse_data = "Response returned with status code != 200 " ;
                return easycpp::helpers::c_int(status_code);
            }
        } catch(std::exception& e) {
            reponse_data = e.what();
            return -2;
        }
        return 0;
    }

    /// GET请求(重载)
    int http_get(std::string url, std::string& reponse_data, const int timeout = 30)
    {
        // 去掉url中的协议头
        if (url.find("http://") != std::string::npos) {
            url = url.substr(7);
        }
        // 补充path
        if(url.find("/") == std::string::npos){
            url.append("/");
        }

        // 分隔符位置
        size_t path_index = url.find("/");
        // 分隔符位置
        size_t port_index = url.find(":");

        // 截取host字符串
        std::string host = url.substr(0, path_index);
        if(port_index != std::string::npos){
            host = url.substr(0, port_index);
        }

        // 截取port字符串
        std::string port = "80";
        if(port_index != std::string::npos){
            port = url.substr(port_index + 1, path_index - port_index - 1);
        }

        // 截取page字符串
        std::string page = url.substr(path_index, url.length() - path_index);

        return http_get(host, port, page, reponse_data, timeout);
    }

    /// 生成http请求字符串
    std::string http_build_query(easycpp::libraries::JsonObject &json_obj, const std::string keys = HTTP_BUILD_KEYS_ALL)
    {
        std::string query_str;
        std::vector<std::string> keys_array;
        helpers::explode(",", keys, keys_array);
        BOOST_FOREACH (easycpp::libraries::JsonValue &v, json_obj) {
            std::string key = v.first;            
            std::string val = easycpp::helpers::json_get_string(json_obj, key);
            if (keys == HTTP_BUILD_KEYS_ALL) {
                query_str += ("&" + key + "=" + val);
            } else {
                BOOST_FOREACH (std::string &keys_v, keys_array) {
                    if(key == keys_v){
                        query_str += ("&" + key + "=" + val);
                    }
                }
            }
        }
        return query_str.empty() ? query_str : query_str.substr(1, query_str.size());
    }

}
}

#endif
