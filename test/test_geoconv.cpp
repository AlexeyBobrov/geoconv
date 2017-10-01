/** @file test_geocoder.cpp
 *  @brief the implementation test for geocoder
 *  @author Bobrov A.E.
 *  @date 20.09.2016
 */

// std
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <type_traits>
#include <algorithm>

// boost
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>


// this
#include "convert.h"
#include "types.h"
#include "test_dataset.h"

namespace
{

using converter::types::Coordinate;
using converter::types::CoordinateType;

constexpr auto latitude = 47.126833;
constexpr auto longitude = 39.759479;

constexpr converter::types::Coordinate lat_dd { latitude, 0.f, 0.0f, converter::types::CoordinateType::dd };
constexpr converter::types::Coordinate lon_dd { longitude, 0.0f, 0.0f, converter::types::CoordinateType::dd };

constexpr converter::types::Coordinate lat_ddmm { 47.0f, 7.60998f, 0.f, converter::types::CoordinateType::ddmm };
constexpr converter::types::Coordinate lon_ddmm { 39.0f, 45.56874f, 0.f, converter::types::CoordinateType::ddmm };

constexpr converter::types::Coordinate lat_ddmmss { 47.0f, 7.0f, 36.5988f, converter::types::CoordinateType::ddmmss };
constexpr converter::types::Coordinate lon_ddmmss { 39.0f, 45.0f, 34.1244f, converter::types::CoordinateType::ddmmss };

template <typename FloatType>
bool IsFloatEqual(FloatType number_one, FloatType number_two, std::true_type)
{
 return (std::fabs(number_one - number_two) < 0.001f); 
}

template <typename FloatType>
bool IsFloatEqual(FloatType number_one, FloatType number_two)
{
  return IsFloatEqual(number_one, number_two, std::is_floating_point<FloatType>());
}

bool operator==(const converter::types::Coordinate &coord1, const converter::types::Coordinate &coord2)
{
  return (IsFloatEqual(coord1.dd, coord2.dd) && IsFloatEqual(coord1.mm, coord2.mm) && IsFloatEqual(coord1.ss, coord2.ss));
}


}

BOOST_AUTO_TEST_SUITE(test_geoconv)


BOOST_AUTO_TEST_CASE(test_conv_dd)
{
  using namespace converter;
  
  const auto dataset = test::Generate();

  for (const auto &i: dataset)
  {
    const auto dd = std::get<0>(i);
    const auto ddmm = std::get<1>(i);
    const auto ddmmss = std::get<2>(i);

    const auto ddmm_r = DDToDDMM(dd);
    const auto ddmmss_r = DDToDDMMSS(dd);

    BOOST_CHECK(ddmm_r == ddmm);
    BOOST_CHECK(ddmmss_r == ddmmss);
  }

}

BOOST_AUTO_TEST_CASE(test_conv_ddmm)
{
  using namespace converter;

  const auto dataset = test::Generate();

  for (const auto &i: dataset)
  {
    const auto dd = std::get<0>(i);
    const auto ddmm = std::get<1>(i);
    const auto ddmmss = std::get<2>(i);

    const auto dd_r = DDMMToDD(ddmm);
    const auto ddmmss_r = DDMMToDDMMSS(ddmm);

    BOOST_CHECK(dd == dd_r);
    BOOST_CHECK(ddmmss == ddmmss_r);
  }
}

BOOST_AUTO_TEST_CASE(test_conv_ddmmss)
{
  using namespace converter;

  const auto dataset = test::Generate();

  for (const auto &i: dataset)
  {
    const auto dd = std::get<0>(i);
    const auto ddmm = std::get<1>(i);
    const auto ddmmss = std::get<2>(i);

    const auto dd_r = DDMMSSToDD(ddmmss);
    const auto ddmm_r = DDMMSSToDDMM(ddmmss);

    BOOST_CHECK(dd == dd_r);
    BOOST_CHECK(ddmm == ddmm_r);
  }
}

BOOST_AUTO_TEST_SUITE_END()
