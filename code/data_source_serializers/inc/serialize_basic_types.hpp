/*
 * serialize_basic_types.hpp
 *
 *  Created on: 28 feb 2014
 *      Author: cec
 */

#ifndef SERIALIZE_BASIC_TYPES_HPP_
#define SERIALIZE_BASIC_TYPES_HPP_

#include "DataSourceYamlSerializer.hpp"



template <> bool TypeWriter<DataSourceYamlSerializer,double>::write(const std::string& type, const boost::any& value);




#endif /* SERIALIZE_BASIC_TYPES_HPP_ */
