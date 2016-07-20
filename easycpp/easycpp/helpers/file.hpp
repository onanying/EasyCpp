/*
 * 文件辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_FILE_INCLUDED
#define EASYCPP_HELPERS_FILE_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

const int FILE_REPLACE = 0;
const int FILE_APPEND = 1;

namespace easycpp {
namespace helpers {

    /// 文件写入
    void file_put_contents(std::string file, std::string data, int mode = FILE_APPEND)
    {
        std::ofstream outdata;
        if(mode == FILE_REPLACE){
            outdata.open(file.c_str());
        }
        if(mode == FILE_APPEND){
            outdata.open(file.c_str(), std::ios::app);
        }
        outdata << data << std::endl;
        outdata.close();
    }

    /// 文件读取
    std::string file_get_contents(std::string file)
    {
        std::ifstream t(file.c_str(), std::ios::in | std::ios::binary);
        std::stringstream buffer;
        buffer << t.rdbuf();
        std::string contents(buffer.str());
        return contents;
    }

}
}

#endif
