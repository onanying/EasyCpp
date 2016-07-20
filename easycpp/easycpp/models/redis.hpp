/*
 * redis数据库模型类
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_MODELS_REDIS_INCLUDED
#define EASYCPP_MODELS_REDIS_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include <hiredis/hiredis.h>

#include <easycpp/helpers/string.hpp>
#include <easycpp/helpers/type.hpp>
#include <easycpp/libraries/exception.hpp>

namespace easycpp {
namespace models {

    /*
     * redis哈希数据类
    */
    class Kv
    {
    public:
        std::string key;
        std::string val;
    };

    /*
     * redis模型类
    */
    class RedisModel
    {
    public:
        RedisModel(std::string ip, int port, std::string passwd)
        {
            // 连接
            conn = redisConnect(ip.c_str(), port);
            if(conn->err){
                std::string err_str("redis conn failed; ");
                err_str.append(conn->errstr);
                err_str += "; ";
                throw easycpp::libraries::Exception(err_str);
            }else{
                // 校验密码
                redisReply* reply = (redisReply*)redisCommand(conn, "AUTH %s", passwd.c_str());
                if(reply == NULL){
                    throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
                }
                int reply_type = reply->type;
                freeReplyObject(reply);
                if(reply_type == REDIS_REPLY_ERROR){
                    throw easycpp::libraries::Exception("redis auth failed; ");
                }
            }
        }

        ~RedisModel()
        {
            closeConn(); // 关闭连接
            array.clear(); // 清除数据
        }

        /// 获取字符串
        std::string getString(std::string key)
        {
            key = "string:" + key;
            std::string cmd = "GET " + key;
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            // 取数据
            std::string value = "";
            if (reply->type == REDIS_REPLY_STRING) {
                value = reply->str;
            }
            freeReplyObject(reply);
            return value;
        }

        /// 设置字符串(带有效期)
        bool setString(std::string key, std::string text, int expire = 0)
        {
            // 设置数据
            key = "string:" + key;
            easycpp::helpers::str_replace(" ", "", text);
            std::string cmd = "SET " + key + " " + text;
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            int reply_type = reply->type;
            freeReplyObject(reply);
            // 返回状态
            if (reply_type == REDIS_REPLY_ERROR) {
                return false;
            }
            // 设置有效时间(秒)
            setExpire(key, expire);
            // 返回状态
            return true;
        }

        /// 获取数组
        std::vector<Kv>* getArray(std::string key)
        {
            key = "array:" + key;
            std::string cmd = "HGETALL " + key;
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            array.clear(); // 清除之前的数据
            if (reply->type == REDIS_REPLY_ARRAY) {
                Kv tmp;
                for (size_t i = 0; i < reply->elements; i++) {
                    if(i % 2 == 0){
                        tmp.key = reply->element[i]->str;
                    }else{
                        tmp.val = reply->element[i]->str;
                        array.push_back(tmp);
                    }
                }
            }
            freeReplyObject(reply);
            return &array;
        }

        /// 设置数组(带有效期)
        bool setArray(std::string key, std::vector<Kv> &array, int expire = 0)
        {
            // 设置数据
            key = "array:" + key;
            std::string cmd = "HMSET " + key;
            for (size_t i = 0; i < array.size(); i++) {
                Kv* kv = &array.at(i);
                easycpp::helpers::str_replace(" ", "", kv->val);
                cmd = cmd + " " + kv->key + " " + kv->val;
            }
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            int reply_type = reply->type;
            freeReplyObject(reply);
            // 返回状态
            if (reply_type == REDIS_REPLY_ERROR) {
                return false;
            }
            // 设置有效时间(秒)
            setExpire(key, expire);
            // 返回状态
            return true;
        }

        /// 获取表格的一行数据
        std::vector<Kv>* getRow(std::string table, std::string id)
        {
            std::string key = table + ":" + id;
            std::string cmd = "HGETALL " + key;
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            array.clear(); // 清除之前的数据
            if (reply->type == REDIS_REPLY_ARRAY) {
                Kv tmp;
                for (size_t i = 0; i < reply->elements; i++) {
                    if(i % 2 == 0){
                        tmp.key = reply->element[i]->str;
                    }else{
                        tmp.val = reply->element[i]->str;
                        array.push_back(tmp);
                    }
                }
            }
            freeReplyObject(reply);
            return &array;
        }

        /// 设置表格的一行数据(带有效期)
        bool setRow(std::string table, std::string id, std::vector<Kv> &array, int expire = 0)
        {
            // 设置数据
            std::string key = table + ":" + id;
            std::string cmd = "HMSET " + key;
            for (size_t i = 0; i < array.size(); i++) {
                Kv* kv = &array.at(i);
                easycpp::helpers::str_replace(" ", "", kv->val);
                cmd = cmd + " " + kv->key + " " + kv->val;
            }
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            int reply_type = reply->type;
            freeReplyObject(reply);
            // 返回状态
            if (reply_type == REDIS_REPLY_ERROR) {
                return false;
            }
            // 设置有效时间(秒)
            setExpire(key, expire);
            // 返回状态
            return true;
        }

        /// 从哈希表获取指定key的值
        static std::string getHashItem(std::vector<Kv>* array, std::string key)
        {
            for (size_t i = 0; i < array->size(); i++) {
                Kv* kv = &array->at(i);
                if (key == kv->key) {
                    return kv->val;
                }
            }
            return "";
        }

        /// 往列表头部插入一条数据
        bool pushList(std::string key, std::string text)
        {
            // 设置数据
            key = "list:" + key;
            easycpp::helpers::str_replace(" ", "", text);
            std::string cmd = "LPUSH " + key + " " + text;
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            int reply_type = reply->type;
            freeReplyObject(reply);
            // 返回状态
            if (reply_type == REDIS_REPLY_ERROR) {
                return false;
            }
            return true;
        }

        /// 从列表尾部拉取一条数据(带堵塞超时)
        std::string pullList(std::string key, int timeout = 0)
        {
            key = "list:" + key;
            std::string cmd;
            if(timeout == 0){
                cmd = "RPOP " + key;
            }else{
                cmd = "BRPOP " + key + " " + easycpp::helpers::c_str(timeout);
            }
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            std::string value = "";
            if (reply->type == REDIS_REPLY_STRING) {
                value = reply->str;
            }
            if (reply->type == REDIS_REPLY_ARRAY) {
                value = reply->element[1]->str;
            }
            freeReplyObject(reply);
            return value;
        }

    private:
        redisContext* conn;
        std::vector<Kv> array;

        /// 关闭连接
        void closeConn()
        {
            redisFree(conn);
        }

        /// 设置有效时间
        bool setExpire(std::string key, int expire)
        {
            if(expire == 0){
                return false;
            }
            // 设置
            std::string cmd = "EXPIRE " + key + " " + easycpp::helpers::c_str(expire);
            redisReply* reply = (redisReply*)redisCommand(conn, cmd.c_str());
            // 重要错误, redis需重新连接
            if(reply == NULL){
                throw easycpp::libraries::Exception("redis cmd failed, please connect again; ");
            }
            int reply_type = reply->type;
            freeReplyObject(reply);
            // 返回状态
            if (reply_type == REDIS_REPLY_ERROR) {
                return false;
            }
            return true;
        }
    };

}
}

#endif
