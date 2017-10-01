/** @file coordinate.h
 *  @brief the define of class Coordinate
 *  @author Bobrov A.E.
 *  @date 23.09.2017
 */

#ifndef _GEOCONV_COORDINATE_H_
#define _GEOCONV_COORDINATE_H_

// std
#include <string>

namespace converter
{
  class Coordinate final
  {
  public:
    explicit Coordinate(const std::string &value);
    explicit Coordinate(double dd, double mm, double ss);
    double GetDD() const { return dd_; }
    double GetMM() const { return mm_; }
    double GetSS() const { return ss_; }
  private:
    double dd_{};
    double mm_{};
    double ss_{};
  };
 
  namespace types
  {
    enum class CoordinateType;
  } 

  Coordinate Convert(const Coordinate &coord, types::CoordinateType type);
  std::string ToString(const Coordinate &coordinate, types::CoordinateType);
  
}

#endif

