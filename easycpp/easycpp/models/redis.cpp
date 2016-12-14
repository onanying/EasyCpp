/*
 * redis数据库模型类
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/models/redis.h>

easycpp::models::RedisModel::RedisModel(std::string ip, int port, std::string passwd)
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

easycpp::models::RedisModel::~RedisModel()
{
    closeConn(); // 关闭连接
    array.clear(); // 清除数据
}

/// 获取字符串
std::string easycpp::models::RedisModel::getString(std::string key)
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
bool easycpp::models::RedisModel::setString(std::string key, std::string text, int expire)
{
    // 设置数据
    key = "string:" + key;
    text = easycpp::helpers::str_replace(" ", "", text);
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
    if(expire > -1){
        setExpire(key, expire);
    }
    // 返回状态
    return true;
}

/// 获取数组
std::map<std::string, std::string>* easycpp::models::RedisModel::getHash(std::string key)
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
        std::string key, val;
        for (size_t i = 0; i < reply->elements; i++) {
            if(i % 2 == 0){
                key = reply->element[i]->str;
            }else{
                val = reply->element[i]->str;
                array[key] = val;
            }
        }
    }
    freeReplyObject(reply);
    return &array;
}

/// 设置数组(带有效期)
bool easycpp::models::RedisModel::setHash(std::string key, std::map<std::string, std::string> &array, int expire)
{
    // 设置数据
    key = "array:" + key;
    std::string cmd = "HMSET " + key;
    for (std::map<std::string, std::string>::iterator it = array.begin(); it != array.end(); ++it) {
        std::string key = it->first;
        std::string val = it->second;
        val = easycpp::helpers::str_replace(" ", "", val);
        cmd = cmd + " " + key + " " + val;
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
    if(expire > -1){
        setExpire(key, expire);
    }
    // 返回状态
    return true;
}

/// 往列表头部插入一条数据
bool easycpp::models::RedisModel::pushList(std::string key, std::string text)
{
    // 设置数据
    key = "list:" + key;
    text = easycpp::helpers::str_replace(" ", "", text);
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
std::string easycpp::models::RedisModel::pullList(std::string key, int timeout)
{
    key = "list:" + key;
    std::string cmd;
    if(timeout == -1){
        cmd = "RPOP " + key;
    }else{
        cmd = "BRPOP " + key + " " + easycpp::helpers::strval(timeout);
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

/// 关闭连接
void easycpp::models::RedisModel::closeConn()
{
    redisFree(conn);
}

/// 设置有效时间
bool easycpp::models::RedisModel::setExpire(std::string key, int expire)
{
    // 设置
    std::string cmd = "EXPIRE " + key + " " + easycpp::helpers::strval(expire);
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
