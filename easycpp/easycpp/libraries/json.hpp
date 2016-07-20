/*
 * json处理类
 * @author 刘健 59208859@qq.com
*/

#ifndef EASYCPP_LIBRARIES_JSON_INCLUDED
#define EASYCPP_LIBRARIES_JSON_INCLUDED

#include <boost/property_tree/ptree.hpp>

namespace easycpp {
namespace libraries {

    typedef boost::property_tree::ptree JsonObject;
    typedef boost::property_tree::ptree::value_type JsonValue;

}
}

#endif
