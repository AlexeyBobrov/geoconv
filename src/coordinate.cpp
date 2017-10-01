/** @file coordinate.cpp
 *  @brief the implementation of class Coordinate
 *  @author Bobrov A.E.
 *  @date 23.09.2017
 */

// declare
#include "types.h"
#include "coordinate.h"

// std
#include <cmath>
#include <string>
#include <vector>
#include <tuple>

// boost 
#include <boost/algorithm/string.hpp>

// this
#include "utils.h"

namespace converter
{
  namespace
  {
    using Coord = std::tuple<double, double, double>;
    Coord FromDDMMSS(const std::string &value)
    {
      if (value.empty())
      {
        throw std::runtime_error(ERROR_STR("String view of coordinate is not specified"));
      }

      std::vector<std::string> values;
      boost::split(values, value, boost::is_any_of(","));

      if (values.size() != 3)
      {
        throw std::runtime_error(ERROR_STR("value is not correct"));
      }

      const auto dd = std::stod(values[0]) + std::stod(values[1])/60.0f + std::stod(values[2])/3600.0f;

      return std::make_tuple(dd, 0.0f, 0.0f);
    }

    Coord FromDDMM(const std::string &value)
    {
      if (value.empty())
      {
        throw std::runtime_error(ERROR_STR("String view of coordinate is not specified"));
      }

      std::vector<std::string> values;
      boost::split(values, value, boost::is_any_of(","));

      if (values.size() != 2)
      {
        throw std::runtime_error(ERROR_STR("value is not correct"));
      }

      const auto dd = std::stod(values[0]) + std::stod(values[1]);
    
      return std::make_tuple(dd, 0.0f, 0.0f);
    }

    Coord DD2DDMM(const std::string &value)
    {
      if (value.empty())
      {
        throw std::runtime_error(ERROR_STR("String view of coordinate is not specified"));
      }

      const auto in = std::stod(value);
      const auto dd = std::trunc(in);
      const auto mm = std::trunc((in - dd) * 60.0f);
      
      return std::make_tuple(dd, mm, 0.0f);
    }

    Coord DD2DDMMSS(const std::string &value)
    {
      if (value.empty())
      {
        throw std::runtime_error(ERROR_STR("String view of coordinate is not specified"));
      }

      const auto in = std::stod(value);
      const auto dd = std::trunc(in);
      const auto mm = std::trunc((in - dd) * 60.0f);
      const auto ss = std::trunc((in - dd) * 60.0f - mm) * 60.0f;

      return std::make_tuple(dd, mm, ss);
    }
  }

  //--------------------------------------------------------------
  Coordinate::Coordinate(const std::string &value)
  {
    Coord coord;

    using namespace ::types;

    switch (IsType(value))
    {
      case CoordinateType::dd:
        coord = DD2DDMMSS(value);
        break;
      case CoordinateType::ddmm:
        coord = FromDDMM(value); 
        break;
      case CoordinateType::ddmmss:
        coord = FromDDMMSS(value);
        break;
      case CoordinateType::unknown: 
      default:
        throw std::runtime_error(ERROR_STR("Unknown type coordinate"));
    } 

    dd_ = std::get<0>(coord);
    mm_ = std::get<1>(coord);
    ss_ = std::get<2>(coord);
  }
  //--------------------------------------------------------------
  Coordinate::Coordinate(double dd, double mm, double ss)
    : dd_(dd)
    , mm_(mm)
    , ss_(ss)
  {
  }
  //--------------------------------------------------------------
  std::string ToString(const Coordinate &coord, types::CoordinateType type)
  {
    
    return {};
  }
}

