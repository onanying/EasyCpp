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

extern const int FILE_REPLACE;
extern const int FILE_APPEND;

namespace easycpp {
namespace helpers {

    /// 文件写入
    void file_put_contents(std::string file, std::string data, int mode = FILE_APPEND);

    /// 文件读取
    std::string file_get_contents(std::string file);

}
}

#endif
