/** @file test_dataset.h
 *  @brief the define helpers for generate data set
 *  @author Bobrov A.E.
 *  @date 25.09.2017
 */

#ifndef _GEOCONV_DATASET_H_
#define _GEOCONV_DATASET_H_

// std
#include <list>
#include <tuple>

// this
#include "types.h"

namespace test
{
using DataEntry = std::tuple<converter::types::Coordinate,
      converter::types::Coordinate, 
      converter::types::Coordinate>;

using DataSet = std::list<DataEntry>;

DataSet Generate();

}

#endif
