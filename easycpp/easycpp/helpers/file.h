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
#include <boost/filesystem.hpp>
#include <easycpp/helpers/string.h>

extern const int FILE_REPLACE;
extern const int FILE_APPEND;

namespace easycpp {
namespace helpers {

    /// 文件写入
    void file_put_contents(std::string file, std::string data, int mode = FILE_APPEND);

    /// 文件读取
    std::string file_get_contents(std::string path);

    /// 判断文件存在性
    bool file_exists(std::string path);

    /// 返回路径中的目录部分
    std::string dirname(std::string path);

    /// 返回路径中的文件名部分
    std::string basename(std::string path);

    /// 创建目录
    void mkdir(std::string path);

}
}

#endif
