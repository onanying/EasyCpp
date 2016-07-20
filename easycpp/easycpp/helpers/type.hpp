/*
 * 类型转换辅助函数
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_HELPERS_TYPE_INCLUDED
#define EASYCPP_HELPERS_TYPE_INCLUDED

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

namespace easycpp {
namespace helpers {

    /// 转换为string类型
    std::string c_str(int var)
    {
        return boost::lexical_cast<std::string>(var);
    }

    /// 转换为int类型, 通过string
    int c_int(std::string var)
    {
        return boost::lexical_cast<int>(var);
    }

    /// 转换为int类型, 通过char数组
    int c_int(char *var)
    {
        return boost::lexical_cast<int>(var);
    }

}
}

#endif
