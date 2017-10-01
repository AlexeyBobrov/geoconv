/** @file main.cpp
 *  @brief the entry point 
 *  @author Bobrov A.E.
 *  @date 19.09.2017
 */

// std
#include <algorithm> 
#include <exception>
#include <iostream>
#include <iomanip>
#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <vector>

// boost 
#include <boost/algorithm/string.hpp>
#include <boost/assert.hpp>

// this
#include "convert.h"
#include "types.h"
#include "utils/parse_cmd.h"
#include "utils.h"

using FunctionDics = std::multimap<converter::types::CoordinateType,
      std::function<converter::types::Coordinate(converter::types::Coordinate)>>;

FunctionDics Generate()
{
  using converter::types::CoordinateType;

  FunctionDics functions;

  functions.emplace(CoordinateType::dd, converter::DDToDDMM);
  functions.emplace(CoordinateType::dd, converter::DDToDDMMSS);
  functions.emplace(CoordinateType::ddmm, converter::DDMMToDD);
  functions.emplace(CoordinateType::ddmm, converter::DDMMToDDMMSS);
  functions.emplace(CoordinateType::ddmmss, converter::DDMMSSToDD);
  functions.emplace(CoordinateType::ddmmss, converter::DDMMSSToDDMM);

  return functions;
}

int main(int argc, char *argv[])
{  
  using namespace converter;
  
  try
  {

    std::string in;
    if (converter::utils::command_line::ParseCmd(argc, argv, in))
    { 
      std::vector<std::string> parts_coords;
      boost::split(parts_coords, in, boost::is_any_of(";"));
      std::for_each(std::begin(parts_coords), std::end(parts_coords), 
          [](auto &i)
          {
            boost::trim(i);
          }); 
      
     
      for (const auto &k: parts_coords)
      {
        const auto type = types::IsType(k);
        auto funcs = Generate();

        std::cout << "Input data: '" << k << "'\n"; 
        auto range = funcs.equal_range(type);
        std::for_each(std::get<0>(range), std::get<1>(range),
            [k](auto &i)
            {
              auto func = std::get<1>(i);
              const auto coord = func(FromString(k));
              std::cout << " -> '" << ToString(coord) << "'\n";
            });

        std::cout << '\n';
      }
    }
    else
    {
      throw std::runtime_error(ERROR_STR("Failed parse command line"));
    }
  }
  catch (const std::exception &err)
  {
    std::cerr << err.what() << std::endl;
  }

  
  return 0;
}
