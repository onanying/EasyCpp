#include <easycpp/helpers/string.h>
#include <easycpp/helpers/datetime.h>
#include <easycpp/helpers/file.h>
#include <easycpp/helpers/log.h>
#include <easycpp/helpers/type.h>
#include <easycpp/helpers/json.h>

#include <vector>

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
    int status = helpers::http_post("http://114.119.4.5:8888/test.php?token=123456", form_data, reponse_data);
    if(status == 0){
        cout << "Success:\n" << reponse_data << endl;
    }else{
        cout << "Failed:\n" << reponse_data << endl;
    }

    // get请求
    string reponse_data2;
    int status2 = helpers::http_get("http://114.119.4.5:8888/test.php?token=123456", reponse_data2, 60); // 60秒后超时, 默认30秒
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
