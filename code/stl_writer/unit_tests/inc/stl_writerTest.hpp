/*
 * stl_writerTest.hpp
 *
 *  Created on: Aug 22, 2014
 *      Author: cady
 */

#ifndef STL_WRITERTEST_HPP_
#define STL_WRITERTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class stl_writerTest : public ::testing::Test
{
    protected:
        stl_writerTest();
        virtual ~stl_writerTest();
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};

#endif  /* STL_WRITERTEST_HPP_ */
