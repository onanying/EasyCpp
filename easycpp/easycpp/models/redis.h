/*
 * redis数据库模型类
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_MODELS_REDIS_INCLUDED
#define EASYCPP_MODELS_REDIS_INCLUDED

#include <iostream>
#include <string>
#include <map>

#include <hiredis/hiredis.h>

#include <easycpp/helpers/string.h>
#include <easycpp/helpers/type.h>
#include <easycpp/libraries/exception.h>

namespace easycpp {
namespace models {

    /*
     * redis模型类
    */
    class RedisModel
    {
    public:
        RedisModel(std::string ip, int port, std::string passwd);

        ~RedisModel();

        /// 获取字符串
        std::string getString(std::string key);

        /// 设置字符串(带有效期)
        bool setString(std::string key, std::string text, int expire = -1);

        /// 获取数组
        std::map<std::string, std::string>* getHash(std::string key);

        /// 设置数组(带有效期)
        bool setHash(std::string key, std::map<std::string, std::string> &array, int expire = -1);

        /// 往列表头部插入一条数据
        bool pushList(std::string key, std::string text);

        /// 从列表尾部拉取一条数据(带堵塞超时)
        std::string pullList(std::string key, int timeout = -1);

        /// 设置有效时间
        bool setExpire(std::string key, int expire);

    private:
        redisContext* conn;

        std::map<std::string, std::string> array;

        /// 关闭连接
        void closeConn();
    };

}
}

#endif
