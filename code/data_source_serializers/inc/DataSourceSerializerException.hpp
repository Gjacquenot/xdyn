/*
 * DataSourceSerializerException.hpp
 *
 *  Created on: 28 f�vr. 2014
 *      Author: maroff
 */

#ifndef DATASOURCESERIALIZEREXCEPTION_HPP_
#define DATASOURCESERIALIZEREXCEPTION_HPP_


#include "Exception.hpp"

class DataSourceSerializerException : public Exception
{
    public:
        DataSourceSerializerException(const char* s) :
                Exception(s)
        {
        }
};


#endif /* DATASOURCESERIALIZEREXCEPTION_HPP_ */
