/*
 * 文件辅助函数
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/helpers/file.h>

const int FILE_REPLACE = 0;
const int FILE_APPEND = 1;

/// 文件写入
void easycpp::helpers::file_put_contents(std::string file, std::string data, int mode)
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
std::string easycpp::helpers::file_get_contents(std::string file)
{
    std::ifstream t(file.c_str(), std::ios::in | std::ios::binary);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string contents(buffer.str());
    return contents;
}
