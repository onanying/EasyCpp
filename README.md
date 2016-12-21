#EasyCpp
一个用于网络开发的C++ 敏捷开发框架，大量按网络开发业务需求封装的辅助函数、类、模型
    

## 依赖库 (libraries)

    all                       boost库
    models/redis.hpp          hiredis库 & libevent库
    
## 安装 (install)

```
unzip easycpp
cd easycpp/build-easycpp-Debug
make distclean
make
make install
```

## 案例 (case)
高性能异步http服务器 [async-http-server](https://github.com/onanying/async-http-server)

## 头文件列表 (files)

    easycpp/helpers/datatime.h
    easycpp/helpers/file.h
    easycpp/helpers/http.h
    easycpp/helpers/json.h
    easycpp/helpers/log.h
    easycpp/helpers/string.h
    easycpp/helpers/type.h
    easycpp/libraries/exception.h
    easycpp/libraries/json.h
    easycpp/models/redis.h

## 函数列表 (function)

- date
- timestamp
- file_put_contents
- file_get_contents
- file_exists
- dirname
- basename
- mkdir
- readdir
- http_post
- http_get
- urlencode
- urldecode
- http_build_query
- json_init
- json_get_array
- json_get_object
- json_get_string
- json_get_int
- log_error
- log_debug
- log_info
- str_replace
- explode
- implode
- strval
- intval

## 使用范例 (sample)

### 字符串辅助函数

```cpp
/**
 * 字符串辅助函数
 */
#include <iostream>
#include <string>
#include <vector>
#include <easycpp/helpers/string.h>

using namespace easycpp;
using namespace std;

int main()
{

    // 替换字符
    string s = "aaabbbaaa";
    string ns = helpers::str_replace("b", "a", s);

    // 把字符串打散为数组
    string s1 = "aaa,bbb,ccc";
    vector<string> ary = helpers::explode(",", s1);

    return 0;
}
```
### 日期时间辅助函数

```cpp
/**
 * 日期时间辅助函数
 */
#include <iostream>
#include <string>
#include <easycpp/helpers/datetime.h>

using namespace easycpp;
using namespace std;

int main()
{

    // 获取当前日期时间
    string datetime = helpers::date("%Y/%m/%d %X");

    // 获取当前日期
    string date = helpers::date("%Y-%m-%d");
    
    // 获取当前时间戳
    long time = helpers::timestamp();

    return 0;
}
```
### 文件辅助函数

```cpp
/**
 * 文件辅助函数
 */
#include <iostream>
#include <string>
#include <easycpp/helpers/file.h>

using namespace easycpp;
using namespace std;

int main()
{

    // 文件写入
    string s1 = "我的文本";
    helpers::file_put_contents("test.txt", s1, FILE_APPEND);
    
    // 文件读取
    string s2 = helpers::file_get_contents("test.txt");

    // 判断文件存在
    if(file_exists(file)){
	// 存在
    }

    // 返回路径中的目录部分
    std::string path = helpers::dirname("log/info.log");

    // 返回路径中的文件名部分
    std::string path = helpers::basename("log/info.log");

    // 创建目录
    helpers::mkdir("log/2016");

    // 返回目录中的所有文件的文件名
    vector<string> filenames = helpers::readdir("cache");

    return 0;
}
```
### 日志辅助函数

```cpp
/**
 * 日志辅助函数
 */
#include <iostream>
#include <string>
#include <easycpp/helpers/log.h>

using namespace easycpp;
using namespace std;

int main()
{


    string tag = "send_error";
    string msg = "uid[123],name[哈哈],sex[0]";

    // 错误日志， 写入到文件 log/error.20161219.log
    helpers::log_error(tag, msg);

    // 信息日志， 写入到文件 log/info.20161219.log
    helpers::log_info(tag, msg);

    // 调试日志， 写入到文件 log/debug.20161219.log
    helpers::log_debug(tag, msg);

    // 带子目录， 写入到文件 log/2016/debug.20161219.log
    helpers::log_debug(tag, msg, "2016");

    return 0;
}
```
### 类型转换辅助函数

```cpp
/**
 * 类型转换辅助函数
 */
#include <iostream>
#include <string>
#include <easycpp/helpers/type.h>

using namespace easycpp;
using namespace std;

int main()
{

    // 数字转字符
    string s = helpers::strval(123);

    // 字符转数字
    int n = helpers::intval("123");

    return 0;
}
```
### json辅助函数

```cpp
/**
 * json辅助函数
 */
#include <iostream>
#include <string>
#include <easycpp/helpers/json.h>

using namespace easycpp;
using namespace std;

int main()
{

    try{

        string json_str = "{\"name\":\"xiaohua\",\"sex\":0,\"more\":{\"height\":175},\"datas\":[{\"item\":1},{\"item\":2}]}";

        // 初始化
        libraries::JsonObject js_obj = helpers::json_init(json_str);

        // 获取string
        string v1 = helpers::json_get_string(js_obj, "name");
        cout << "name: " << v1 << endl;

        // 获取int
        int v2 = helpers::json_get_int(js_obj, "sex");
        cout << "sex: " << v2 << endl;

        // 获取object
        libraries::JsonObject new_obj = helpers::json_get_object(js_obj, "more");
        int v3 = helpers::json_get_int(new_obj, "height");
        cout << "height: " << v3 << endl;

        // 获取array
        vector<libraries::JsonObject> array = helpers::json_get_array(js_obj, "datas");
        for (int i = 0; i < array.size(); ++i) {
            libraries::JsonObject &obj = array.at(i);
            int v4 = helpers::json_get_int(obj, "item");
            cout << "item: " << v4 << endl;
        }

    } catch (exception &ex) {
        cout << ex.what() << endl;
    }

    return 0;
}
```
### http辅助函数

```cpp
/**
 * http辅助函数
 */
#include <iostream>
#include <string>
#include <easycpp/helpers/http.h>

using namespace easycpp;
using namespace std;

int main()
{
    // 构建要post的数据
    libraries::JsonObject form_data;
    try{
        form_data = helpers::json_init("{\"name\":\"小花\",\"sex\":\"0\"}");
    } catch (std::exception &ex){
        cout << ex.what() << endl;
        return 1;
    }
    // post请求
    string reponse_data;
    int status = helpers::http_post("http://0.0.0.0:8888/test.php?token=123456", form_data, reponse_data);
    if(status == 0){
        cout << "Success:\n" << reponse_data << endl;
    }else{
        cout << "Failed:\n" << reponse_data << endl;
    }

    // get请求
    string reponse_data2;
    int status2 = helpers::http_get("http://0.0.0.0:8888/test.php?token=123456", reponse_data2, 60); // 60秒后超时, 默认30秒
    if(status2 == 0){
        cout << "Success:\n" << reponse_data2 << endl;
    }else{
        cout << "Failed:\n" << reponse_data2 << endl;
    }

    // URLencode
    string str1 = "name=小花&sex=女&height=168";
    cout << "URLencode:\n" << helpers::urlencode(str1) << endl;

    // URLdecode
    cout << "URLdecode:\n" << helpers::urldecode(str1) << endl;

    return 0;
}
```
### redis模型

```cpp
/**
 * redis模型
 */
#include <iostream>
#include <string>
#include <easycpp/models/redis.h>

using namespace easycpp;
using namespace std;

int main()
{

    try{

        // 连接redis
        models::RedisModel redis("127.0.0.1", 6379, "123456");

        /* string类型 */
        // 设置string
        redis.setString("token", "b12cc6c0cc5b4875af4b1334ceac782b10");
        // 设置string (带有效期)
        redis.setString("token", "b12cc6c0cc5b4875af4b1334ceac782b10", 60);
        // 获取string
        string s1 = redis.getString("token");
        cout << "token: " << s1 << endl;

        /* Hash类型 */
        // 赋值
        map<string, string> array;
        array["name"] = "xiaohua";
        array["height"] = "176";
        // 设置Hash
        redis.setHash("user", array);
        // 设置Hash (带有效期)
        redis.setHash("user", array, 60);
        // 获取Hash
        map<string, string> *array1 = redis.getHash("user");
        for (map<string, string>::iterator it = array1->begin(); it != array1->end(); ++it) {
            cout << "array key: " << it->first << endl;
            cout << "array val: " << it->second << endl;
        }

        /* List类型 */
        // 插入列表头部
        redis.pushList("queue_user", "update_xiaohua_info");
        redis.pushList("queue_user", "insert_xiaohua_info");
        // 从列表尾部弹出一条数据
        string res = redis.pullList("queue_user");
        cout << "list: " << res << endl;

    } catch (exception &ex) {
        cout << "ERROR: " << ex.what() << endl;
    }

    return 0;
}
```
