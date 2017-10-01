/** @file parse_cmd.cpp
 *  @brief the implementation helpers of command line
 *  @author Bobrov A.E.
 *  @date 20.09.2017
 */

// declare
#include "utils/parse_cmd.h"

// std
#include <iostream>

// boost
#include <boost/assert.hpp>
#include <boost/program_options.hpp>

// this
#include "geoconv_version.h"

namespace converter
{
namespace utils
{
namespace command_line
{

bool ParseCmd(int argc, char *argv[], std::string &input)
{
  namespace bp = boost::program_options;
  
  BOOST_ASSERT_MSG(argc, "Count argument is null");
  BOOST_ASSERT_MSG(argv, "Command line is nullptr");

  bp::options_description option_desc("Allow options");
  std::string type;
  std::string value;

  option_desc.add_options()
    ("help,h", "Display the program usage and exit")
    ("version,v", "Display the program version and exit")
    ("data,d", bp::value<std::string>(&value)->required(), "Data: latitude; longitude (required), example: 32,38.234; 47,83.3493");
  
  bp::variables_map options;
  bp::store(bp::command_line_parser(argc, argv).options(option_desc).run(), options);

  if (options.empty() || options.count("help"))
  {
    std::cerr << option_desc << std::endl;
    return false;
  }  
  else if (options.count("version"))
  {
    std::cout << geoconv::version::getText() << std::endl;
    return false;
  }

  bp::notify(options);
  
  std::swap(input, value);
  
  return true;
}
}
}
}
