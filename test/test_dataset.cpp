/** @file test_dataset.cpp
 *  @brief the generate data
 *  @author Bobrov A.E.
 *  @date 25.09.2017
 */

// std
#include <list>

// this 
#include "test_dataset.h"
#include "types.h"

namespace test
{
  DataSet Generate()
  {
    using converter::types::CoordinateType;
    using converter::types::Coordinate;

    auto set_0 = std::make_tuple(Coordinate{ 47.126833, 0.f, 0.f, CoordinateType::dd },
        Coordinate{ 47.0f, 7.60998f, 0.f, CoordinateType::ddmm },
        Coordinate{ 47.0f, 7.0f, 36.5988f, CoordinateType::ddmmss } );
    
    auto set_1 = std::make_tuple(Coordinate{ 39.759479, 0.f, 0.f, CoordinateType::dd },
        Coordinate { 39.0f, 45.56874f, 0.f, CoordinateType::ddmm },
        Coordinate { 39.f, 45.f, 34.1244f, CoordinateType::ddmmss }); 
    
    auto set_2 = std::make_tuple(Coordinate{ 50.097757, 0.f, 0.f, CoordinateType::dd },
        Coordinate { 50.f, 5.86542, 0.f, CoordinateType::ddmm },
        Coordinate { 50.f, 5.0f, 51.9252, CoordinateType::ddmmss } );
    
    auto set_3 = std::make_tuple(Coordinate{ 40.433535, 0.0f, 0.0f, CoordinateType::dd },
        Coordinate { 40.f, 26.0121f, 0.f, CoordinateType::ddmm },
        Coordinate { 40.f, 26.f, 0.726f, CoordinateType::ddmmss });

    DataSet result;
    result.push_back(std::move(set_0));
    result.push_back(std::move(set_1));
    result.push_back(std::move(set_2));
    result.push_back(std::move(set_3));

    return result;
  }
}
