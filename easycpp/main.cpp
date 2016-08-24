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
    // 生成 URL-encode 之后的请求字符串
    libraries::JsonObject json;
    string form_data;
    try{
        json = helpers::json_init("{\"name\":\"xiaohua\",\"sex\":\"0\"}");
        form_data = helpers::http_build_query(json);
        cout << "URLencode String:\n" << form_data << endl;
    } catch (std::exception &ex){
        cout << ex.what() << endl;
        return 1;
    }

    // post请求
    string reponse_data;
    int status = helpers::http_post("http://8.8.8.8:8888/test.php?token=123456", form_data, reponse_data);
    if(status == 0){
        cout << "Success:\n" << reponse_data << endl;
    }else{
        cout << "Failed:\n" << reponse_data << endl;
    }

    // get请求
    string reponse_data2;
    int status2 = helpers::http_get("http://8.8.8.8:8888/test.php?token=123456", reponse_data2, 60); // 60秒后超时, 默认30秒
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
