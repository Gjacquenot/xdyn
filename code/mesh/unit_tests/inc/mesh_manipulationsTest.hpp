/*
 * mesh_manipulationsTest.hpp
 *
 *  Created on: May 20, 2014
 *      Author: cady
 */

#ifndef MESH_MANIPULATIONSTEST_HPP_
#define MESH_MANIPULATIONSTEST_HPP_

#include "gtest/gtest.h"

class mesh_manipulationsTest : public ::testing::Test
{
    protected:
        mesh_manipulationsTest();
	    virtual ~mesh_manipulationsTest();
        virtual void SetUp();
        virtual void TearDown();

};

#endif  /* MESH_MANIPULATIONSTEST_HPP_ */
