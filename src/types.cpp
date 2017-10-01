/** @file types.cpp
 *  @brief the implementation helpers types
 *  @author Bobrov A.E.
 *  @date 23.09.2017
 */

// declare
#include "types.h"

// std
#include <algorithm>

// this
#include "utils.h"

namespace converter
{
namespace types
{
CoordinateType IsType(const std::string &value)
{
  const auto count = std::count(std::cbegin(value), std::cend(value), ' ');

  switch (count)
  {
    case 0:
      return CoordinateType::dd;
    case 1:
      return CoordinateType::ddmm;
    case 2:
      return CoordinateType::ddmmss;
  }

  throw std::runtime_error(ERROR_STR("Unknown input type"));
}
}
}
