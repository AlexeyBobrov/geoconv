/** @file utils.h
 *  @brief The define common helpers 
 *  @author Bobrov A.E.
 *  @date 22.09.2017
 */
#ifndef _GEOCONV_UTILS_H_
#define _GEOCONV_UTILS_H_

#include <string>

#define ERROR_STR(x) (std::string("[") + __PRETTY_FUNCTION__ + std::string("]:") \
    + std::to_string(__LINE__) + std::string(": '") + x + std::string("'"))

namespace utils
{

}

#endif

