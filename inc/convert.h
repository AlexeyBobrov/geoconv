/** @file convert.h
 *  @brief The define helpers convert function
 *  @author Bobrov A.E.
 *  @date 24.09.2017
 */
#ifndef _GEOCONV_CONVERTER_H_
#define _GEOCONV_CONVERTER_H_

// std
#include <string>

// this
#include "types.h"

namespace converter
{
  /** @brief convert from string */
  types::Coordinate FromString(const std::string &coord);
  
  /** @brief convert to string */
  std::string ToString(const types::Coordinate &coord);

  /** @brief convert dd -> ddmm */
  types::Coordinate DDToDDMM(const types::Coordinate &coord);

  /** @brief convert dd -> ddmmss */
  types::Coordinate DDToDDMMSS(const types::Coordinate &coord);

  /** @brief convert ddmm -> dd */
  types::Coordinate DDMMToDD(const types::Coordinate &coord);
  
  /** @brief convert ddmm -> ddmmss */
  types::Coordinate DDMMToDDMMSS(const types::Coordinate &coord);

  /** @brief convert ddmmss -> dd */
  types::Coordinate DDMMSSToDD(const types::Coordinate &coord);

  /** @brief convert ddmmss -> ddmm */
  types::Coordinate DDMMSSToDDMM(const types::Coordinate &coord);
}

#endif 
