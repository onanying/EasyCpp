EasyCpp
---
一个用于网络开发的C++ 敏捷开发框架

    大量按网络开发业务需求封装的辅助函数、类、模型

#### 依赖库
---
该框架大量使用了boost库

    all                       boost库
    models/redis.hpp          hiredis库 & libevent库
    
#### 安装

    unzip easycpp
    cd easycpp
    ./install.sh
    
#### 使用范例


```
#include <easycpp/helpers/json.hpp>
using namespace easycpp;
using namespace std;
string str = "{\"uid\":\"10086\"}";
libraries::JsonObject json_obj;
helpers::json_init(json_obj, str);
string uid = helpers::json_get_string(json_obj, "uid");
cout << uid << endl;
```


#### 头文件列表

    easycpp/helpers/datatime.hpp
    easycpp/helpers/file.hpp
    easycpp/helpers/http.hpp
    easycpp/helpers/json.hpp
    easycpp/helpers/log.hpp
    easycpp/helpers/string.hpp
    easycpp/helpers/type.hpp
    easycpp/libraries/exception.hpp
    easycpp/libraries/json.hpp
    easycpp/models/redis.hpp
    
