/*
 * http辅助函数
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/helpers/http.h>

namespace easycpp {
namespace helpers {

    /// POST请求
    int http_post(const std::string& host, const std::string& port, const std::string& page, easycpp::libraries::JsonObject& form_data, std::string& reponse_data, int timeout)
    {
        std::string query_data = http_build_query(form_data); // 生成http请求字符串
        try {
            boost::asio::ip::tcp::iostream stream;
            stream.expires_from_now(boost::posix_time::seconds(timeout));
            stream.connect(host, port);
            stream << "POST " << page << " HTTP/1.0\r\n";
            stream << "Host: " << host << ":" << port << "\r\n";
            stream << "Accept: */*\r\n";
            stream << "Content-Length: " << query_data.length() << "\r\n";
            stream << "Content-Type: application/x-www-form-urlencoded\r\n";
            stream << "Connection: close\r\n\r\n";
            stream << query_data;
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
                return easycpp::helpers::intval(status_code);
            }
        } catch(std::exception& e) {
            reponse_data = e.what();
            return -2;
        }
        return 0;
    }

    /// POST请求(重载)
    int http_post(std::string url, easycpp::libraries::JsonObject& form_data, std::string& reponse_data, const int timeout)
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
    int http_get(const std::string& host, const std::string& port, const std::string& page, std::string& reponse_data, const int timeout)
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
                return easycpp::helpers::intval(status_code);
            }
        } catch(std::exception& e) {
            reponse_data = e.what();
            return -2;
        }
        return 0;
    }

    /// GET请求(重载)
    int http_get(std::string url, std::string& reponse_data, const int timeout)
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

    /// url编码
    std::string urlencode(const std::string& str)
    {
        std::string src = str;
        char hex[] = "0123456789ABCDEF";
        std::string result;
        for (size_t i = 0; i < src.size(); ++i) {
            unsigned char cc = src[i];
            if (cc == ' ' || cc == '.' || (cc >= 48 && cc <= 57) || (cc >=97 && cc <= 122) || (cc >=65 && cc <= 90)) {
                if(cc == ' '){
                    result += '+';
                }else{
                    result += cc;
                }
            } else {
                unsigned char c = static_cast<unsigned char>(src[i]);
                result += '%';
                result += hex[c / 16];
                result += hex[c % 16];
            }
        }
        return result;
    }

    /// url解码
    std::string urldecode(const std::string& str)
    {
        std::string result;
        int hex = 0;
        for (size_t i = 0; i < str.length(); ++i)
        {
            switch (str[i])
            {
            case '+':
                result += ' ';
                break;
            case '%':
                if (isxdigit(str[i + 1]) && isxdigit(str[i + 2]))
                {
                    std::string hexStr = str.substr(i + 1, 2);
                    hex = strtol(hexStr.c_str(), 0, 16);
                    //字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@]
                    //可以不经过编码直接用于URL
                    if (!((hex >= 48 && hex <= 57) || //0-9
                        (hex >=97 && hex <= 122) ||   //a-z
                        (hex >=65 && hex <= 90) ||    //A-Z
                        //一些特殊符号及保留字[$-_.+!*'(),]  [$&+,/:;=?@]
                        hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
                        || hex == 0x2a || hex == 0x2b|| hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
                        || hex == 0x3A || hex == 0x3B|| hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
                        ))
                    {
                        result += char(hex);
                        i += 2;
                    }
                    else result += '%';
                }else {
                    result += '%';
                }
                break;
            default:
                result += str[i];
                break;
            }
        }
        return result;
    }

    /// 生成http请求字符串
    std::string http_build_query(easycpp::libraries::JsonObject &query_data)
    {
        std::string query_str;
        BOOST_FOREACH (easycpp::libraries::JsonValue &v, query_data) {
            std::string key = v.first;            
            std::string val = easycpp::helpers::json_get_string(query_data, key);
            val = urlencode(val);
            query_str += ("&" + key + "=" + val);
        }
        return query_str.empty() ? query_str : query_str.substr(1, query_str.size());
    }

}
}
