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
    // 判断文件存在
    if(!file_exists(file)){
        // 新建目录
        std::string path = dirname(file);
        mkdir(path);
    }
    // 写入文件
    std::ofstream outdata;
    if(mode == FILE_REPLACE){
        outdata.open(file.c_str());
    }
    if(mode == FILE_APPEND){
        outdata.open(file.c_str(), std::ios::app);
    }
    outdata << data;
    outdata.close();
}

/// 文件读取
std::string easycpp::helpers::file_get_contents(std::string path)
{
    std::ifstream t(path.c_str(), std::ios::in | std::ios::binary);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string contents(buffer.str());
    return contents;
}

/// 判断文件存在性
bool easycpp::helpers::file_exists(std::string path)
{
    // 取得当前目录
    boost::filesystem::path current_path = boost::filesystem::current_path();
    // 生成文件路径
    boost::filesystem::path file_path = current_path / path;
    // 判断文件存在性
    if(boost::filesystem::exists(file_path))
    {
        return true;
    }
    return false;
}

/// 返回路径中的目录部分
std::string easycpp::helpers::dirname(std::string path)
{
    std::vector<std::string> file_array = helpers::explode("/", path);
    file_array.pop_back();
    return helpers::implode("/", file_array);
}

/// 返回路径中的文件名部分
std::string easycpp::helpers::basename(std::string path)
{
    std::vector<std::string> file_array = helpers::explode("/", path);
    std::string back_str = file_array.at(file_array.size() - 1);
    return back_str;
}

/// 创建目录
void easycpp::helpers::mkdir(std::string path)
{
    // 取得当前目录
    boost::filesystem::path current_path = boost::filesystem::current_path();
    // 逐级建立目录
    std::vector<std::string> array = helpers::explode("/", path);
    boost::filesystem::path dir_path = current_path;
    int size = array.size();
    for(int i = 0; i < size; i++){
        std::string dir = array.at(i);
        // 生成目录路径
        dir_path = dir_path / dir.c_str();
        // 创建目录
        boost::filesystem::create_directory(dir_path);
        // 设置当前目录
        boost::filesystem::current_path(dir_path);
    }
    // 恢复默认当前目录
    boost::filesystem::current_path(current_path);
}

/// 返回目录中的所有文件的文件名
std::vector<std::string> easycpp::helpers::readdir(std::string path)
{
    std::vector<std::string> filenames;
    boost::filesystem::path dirPath(path);
    if (boost::filesystem::exists(dirPath)) {
        boost::filesystem::directory_iterator end_iter;
        for (boost::filesystem::directory_iterator iter(dirPath); iter!=end_iter; ++iter) {
            if (boost::filesystem::is_regular_file(iter->status())) {
                filenames.push_back(iter->path().string());
            }
        }
    }
    return filenames;
}
