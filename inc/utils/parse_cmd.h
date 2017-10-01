/** @file parse_cmd.h
 *  @brief declaration parse command line helpers
 *  @author Bobrov A.E.
 *  @date 20.09.2017
 */

#ifndef GEOCONV_PARSE_CMD_H_
#define GEOCONV_PARSE_CMD_H_

// std
#include <utility>
#include <string>
#include <tuple>

namespace converter
{
namespace utils
{
namespace command_line
{

bool ParseCmd(int argc, char *argv[], std::string &input);

}
}
}

#endif
