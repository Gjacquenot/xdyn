/*
 * DataSourceYamlSerializerException.hpp
 *
 *  Created on: 28 f�vr. 2014
 *      Author: maroff
 */

#ifndef DATASOURCEYAMLSERIALIZEREXCEPTION_HPP_
#define DATASOURCEYAMLSERIALIZEREXCEPTION_HPP_

#include "Exception.hpp"

class DataSourceYamlSerializerException : public Exception
{
    public:
        DataSourceYamlSerializerException(const char* s) :
                Exception(s)
        {
        }
};

#endif /* DATASOURCEYAMLSERIALIZEREXCEPTION_HPP_ */
