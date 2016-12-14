/*
 * 类型转换辅助函数
 * @author 刘健 59208859@qq.com
*/

#include <easycpp/helpers/type.h>

/// 转换为string类型
std::string easycpp::helpers::strval(int var)
{
    return boost::lexical_cast<std::string>(var);
}

/// 转换为int类型, 通过string
int easycpp::helpers::intval(std::string var)
{
    return boost::lexical_cast<int>(var);
}

/// 转换为int类型, 通过char数组
int easycpp::helpers::intval(char *var)
{
    return boost::lexical_cast<int>(var);
}
