/*
 * DampingForceModelTest.hpp
 *
 *  Created on: Oct 2, 2014
 *      Author: jacquenot
 */

#ifndef DAMPINGFORCEMODELTEST_HPP_
#define DAMPINGFORCEMODELTEST_HPP_

#include "gtest/gtest.h"
#include <ssc/random_data_generator.hpp>

class DampingForceModelTest : public ::testing::Test
{
    protected:
    DampingForceModelTest();
        virtual ~DampingForceModelTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif  /* DAMPINGFORCEMODELTEST_HPP_ */
