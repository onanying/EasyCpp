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

#include <easycpp/helpers/json.h>
#include <easycpp/helpers/type.h>
#include <easycpp/helpers/string.h>

extern const std::string HTTP_BUILD_ALL_KEYS;

namespace easycpp {
namespace helpers {

    /// POST请求
    int http_post(const std::string& host, const std::string& port, const std::string& page, const std::string& form_data, std::string& reponse_data, int timeout = 30);

    /// POST请求(重载)
    int http_post(std::string url, const std::string& form_data, std::string& reponse_data, const int timeout = 30);

    /// GET请求
    int http_get(const std::string& host, const std::string& port, const std::string& page, std::string& reponse_data, const int timeout = 30);

    /// GET请求(重载)
    int http_get(std::string url, std::string& reponse_data, const int timeout = 30);

    /// url编码
    std::string urlencode(const std::string& str);

    /// url解码
    std::string urldecode(const std::string& str);

    /// 生成http请求字符串
    std::string http_build_query(easycpp::libraries::JsonObject &query_data, const std::string filter = HTTP_BUILD_ALL_KEYS);

}
}

#endif
