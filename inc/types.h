/** @file types.h
 *  @brief the define common types
 *  @author Bobrov A.E.
 *  @date 21.09.2017
 */
#ifndef _GEOCONV_TYPES_H_
#define _GEOCONV_TYPES_H_

// std
#include <string>
#include <tuple>

namespace converter
{
namespace types
{
enum class CoordinateType
{
  unknown = 0,
  dd,
  ddmm,
  ddmmss,
};

struct Coordinate
{
  double dd {};
  double mm {};
  double ss {};  
  CoordinateType type = CoordinateType::unknown;
};

CoordinateType IsType(const std::string &value);

}
}

#endif

