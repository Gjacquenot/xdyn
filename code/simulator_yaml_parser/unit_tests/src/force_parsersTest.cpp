/*
 * force_parsersTest.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: cady
 */

#include "force_parsersTest.hpp"
#include "force_parsers.hpp"

force_parsersTest::force_parsersTest() : a(ssc::random_data_generator::DataGenerator(86556))
{
}

force_parsersTest::~force_parsersTest()
{
}

void force_parsersTest::SetUp()
{
}

void force_parsersTest::TearDown()
{
}

TEST_F(force_parsersTest, gravity)
{
    const GravityParameters p = parse_gravity("g:\n  unit: m/s^2\n  value: 9.81\nmodel: gravity");
    ASSERT_DOUBLE_EQ(9.81, p.g);
}

TEST_F(force_parsersTest, hydrostatic)
{
    const double rho = parse_hydrostatic("rho:\n  unit: kg/m^3\n  value: 1024\nmodel: hydrostatic");
    ASSERT_DOUBLE_EQ(1024, rho);
}

TEST_F(force_parsersTest, damping)
{
    const std::string yaml = "        damping matrix at the center of gravity projected in the body frame:\n"
                             "            frame: body 1\n"
                             "            row 1: [  2,   3,   5,   7,  11,  13]\n"
                             "            row 2: [ 17,  19,  23,  29,  31,  37]\n"
                             "            row 3: [ 41,  43,  47,  53,  59,  61]\n"
                             "            row 4: [ 67,  71,  73,  79,  83,  89]\n"
                             "            row 5: [ 97, 101, 103, 107, 109, 113]\n"
                             "            row 6: [127, 131, 137, 139, 149, 151]\n";
    const Eigen::Matrix<double,6,6> D = parse_quadratic_damping(yaml);
    ASSERT_DOUBLE_EQ(2.,(double)D(0,0));
    ASSERT_DOUBLE_EQ(3.,(double)D(0,1));
    ASSERT_DOUBLE_EQ(5.,(double)D(0,2));
    ASSERT_DOUBLE_EQ(7.,(double)D(0,3));
    ASSERT_DOUBLE_EQ(11.,(double)D(0,4));
    ASSERT_DOUBLE_EQ(13.,(double)D(0,5));
    ASSERT_DOUBLE_EQ(17.,(double)D(1,0));
    ASSERT_DOUBLE_EQ(19.,(double)D(1,1));
    ASSERT_DOUBLE_EQ(23.,(double)D(1,2));
    ASSERT_DOUBLE_EQ(29.,(double)D(1,3));
    ASSERT_DOUBLE_EQ(31.,(double)D(1,4));
    ASSERT_DOUBLE_EQ(37.,(double)D(1,5));
    ASSERT_DOUBLE_EQ(41.,(double)D(2,0));
    ASSERT_DOUBLE_EQ(43.,(double)D(2,1));
    ASSERT_DOUBLE_EQ(47.,(double)D(2,2));
    ASSERT_DOUBLE_EQ(53.,(double)D(2,3));
    ASSERT_DOUBLE_EQ(59.,(double)D(2,4));
    ASSERT_DOUBLE_EQ(61.,(double)D(2,5));
    ASSERT_DOUBLE_EQ(67.,(double)D(3,0));
    ASSERT_DOUBLE_EQ(71.,(double)D(3,1));
    ASSERT_DOUBLE_EQ(73.,(double)D(3,2));
    ASSERT_DOUBLE_EQ(79.,(double)D(3,3));
    ASSERT_DOUBLE_EQ(83.,(double)D(3,4));
    ASSERT_DOUBLE_EQ(89.,(double)D(3,5));
    ASSERT_DOUBLE_EQ(97.,(double)D(4,0));
    ASSERT_DOUBLE_EQ(101.,(double)D(4,1));
    ASSERT_DOUBLE_EQ(103.,(double)D(4,2));
    ASSERT_DOUBLE_EQ(107.,(double)D(4,3));
    ASSERT_DOUBLE_EQ(109.,(double)D(4,4));
    ASSERT_DOUBLE_EQ(113.,(double)D(4,5));
    ASSERT_DOUBLE_EQ(127.,(double)D(5,0));
    ASSERT_DOUBLE_EQ(131.,(double)D(5,1));
    ASSERT_DOUBLE_EQ(137.,(double)D(5,2));
    ASSERT_DOUBLE_EQ(139.,(double)D(5,3));
    ASSERT_DOUBLE_EQ(149.,(double)D(5,4));
    ASSERT_DOUBLE_EQ(151.,(double)D(5,5));
}
