/** @file convert.cpp
 *  @brief the implementation of the convert functions
 *  @author Bobrov A.E.
 *  @date 24.09.2017
 */
// declare
#include "convert.h"

// std
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

// boost
#include <boost/algorithm/string.hpp>

// this
#include "utils.h"

namespace detail
{
  converter::types::Coordinate ToDD(const std::string &str)
  {
    if (str.empty())
    {
      throw std::runtime_error(ERROR_STR("String view of coordinate is not specified"));
    }

    return { std::stod(str), 0.0f, 0.0f, converter::types::CoordinateType::dd };
  }

  converter::types::Coordinate ToDDMM(const std::string &str)
  {
    if (str.empty())
    {
      throw std::runtime_error(ERROR_STR("String view of coodinate is not specified"));
    }
    
    std::vector<std::string> parts;
    boost::split(parts, str, boost::is_any_of(" "));

    if (parts.size() != 2)
    {
      throw std::runtime_error(ERROR_STR("String view is not ddmm"));
    }

    const auto dd = std::stod(parts[0]);
    const auto mm = std::stod(parts[1]);

    return { dd, mm, 0.0f, converter::types::CoordinateType::ddmm };
  }

  converter::types::Coordinate ToDDMMSS(const std::string &str)
  {
    if (str.empty())
    {
      throw std::runtime_error(ERROR_STR("String view of coodinate is not specified"));
    }
    
    std::vector<std::string> parts;
    boost::split(parts, str, boost::is_any_of(" "));
    
    if (parts.size() != 3)
    {
      throw std::runtime_error(ERROR_STR("String view is not ddmmss"));
    }

    const auto dd = std::stod(parts[0]);
    const auto mm = std::stod(parts[1]);
    const auto ss = std::stod(parts[2]);

    return { dd, mm, ss, converter::types::CoordinateType::ddmmss };
  }
}

namespace converter
{
  //-----
  types::Coordinate FromString(const std::string &coord)
  {
    switch (types::IsType(coord))
    {
      case types::CoordinateType::dd:
        return detail::ToDD(coord);
      case types::CoordinateType::ddmm:
        return detail::ToDDMM(coord);
      case types::CoordinateType::ddmmss:
        return detail::ToDDMMSS(coord);
      case types::CoordinateType::unknown:
        break;
    }
    
    throw std::runtime_error(ERROR_STR("Unknown type of coord"));
  }
  //----
  std::string ToString(const types::Coordinate &coord)
  {
    constexpr auto maxdigits = 6;

    std::ostringstream os;

    switch (coord.type)
    {
      case types::CoordinateType::dd:
        os << std::setprecision(maxdigits) << coord.dd;
        break;
      case types::CoordinateType::ddmm:
        os << coord.dd  
          << " " << std::setprecision(maxdigits) << coord.mm;
        break;
      case types::CoordinateType::ddmmss:
        os << coord.dd
          << " " << coord.mm
          << " " << std::setprecision(maxdigits) << coord.ss;
        break;
      case types::CoordinateType::unknown:
      default:
        throw std::runtime_error(ERROR_STR("Unknown type coordinate"));
    }

    return os.str();
  }

  //-----
  types::Coordinate DDToDDMM(const types::Coordinate &coord)
  {
    if (types::CoordinateType::dd != coord.type)
    {
      throw std::runtime_error(ERROR_STR("Mistmatch type coord (dd)"));
    }
    const auto dd = std::trunc(coord.dd);
    const auto mm = (coord.dd - dd) * 60.0f;

    return { dd, mm, 0.f, types::CoordinateType::ddmm };
  }
  //------
  types::Coordinate DDToDDMMSS(const types::Coordinate &coord)
  {
    if (types::CoordinateType::dd != coord.type)
    {
      throw std::runtime_error(ERROR_STR("Mismatch type coord (dd)"));
    }

    const auto dd = std::trunc(coord.dd);
    const auto mm = std::trunc((coord.dd - dd) * 60.0f);
    const auto ss = ((coord.dd - dd) * 60.f - mm) * 60.0f;
    
    return { dd, mm, ss, types::CoordinateType::ddmmss };
  }
  //------
  types::Coordinate DDMMToDD(const types::Coordinate &coord)
  {
    if (types::CoordinateType::ddmm != coord.type)
    {
      throw std::runtime_error(ERROR_STR("Mismatch type coord (ddmm)"));
    }
    
    const auto dd = coord.dd + (coord.mm / 60.0f);

    return { dd, 0.f, 0.f, types::CoordinateType::dd };
  }
  //------
  types::Coordinate DDMMToDDMMSS(const types::Coordinate &coord)
  {
    if (types::CoordinateType::ddmm != coord.type)
    {
      throw std::runtime_error(ERROR_STR("Mismatch type coord (ddmm)"));
    }

    const auto mm = std::trunc(coord.mm);
    const auto ss = (coord.mm - mm) * 60.f;
    
    return { coord.dd, mm, ss, types::CoordinateType::ddmmss };
  }
  //-----
  types::Coordinate DDMMSSToDD(const types::Coordinate &coord)
  {
    if (types::CoordinateType::ddmmss != coord.type)
    {
      throw std::runtime_error(ERROR_STR("Mismtach type coord (ddmmss)"));
    }

    const auto dd = coord.dd + (coord.mm / 60.0f) + (coord.ss / 3600.0f);

    return { dd, 0.0f, 0.0f, types::CoordinateType::dd };

    return {};
  }
  //-----
  types::Coordinate DDMMSSToDDMM(const types::Coordinate &coord)
  {
    if (types::CoordinateType::ddmmss != coord.type)
    {
      throw std::runtime_error(ERROR_STR("Mismatch type coord (ddmmss)"));
    }

    const auto mm = coord.mm + (coord.ss / 60.0f);

    return { coord.dd, mm, 0.0f, types::CoordinateType::ddmm };
  }

}
