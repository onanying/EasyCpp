#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/deadline_timer.hpp>

#include <easycpp/helpers/json.hpp>
#include <easycpp/helpers/string.hpp>
#include <easycpp/helpers/type.hpp>
#include <easycpp/models/redis.hpp>
#include <easycpp/helpers/file.hpp>
#include <easycpp/helpers/datetime.hpp>
#include <easycpp/helpers/http.hpp>
#include <easycpp/helpers/log.hpp>

using namespace easycpp;
using namespace std;

int main()
{

    models::RedisModel rm("127.0.0.1", 6379, "123456");

    while(true){
    string s = rm.getString("apns_badge:100008");
        cout << "-----" << s << endl;
        sleep(3);
    }

    return 0;
}
