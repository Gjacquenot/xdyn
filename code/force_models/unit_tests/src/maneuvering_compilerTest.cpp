/*
 * maneuvering_compilerTest.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: cady
 */


#include "maneuvering_compilerTest.hpp"
#include "maneuvering_compiler.hpp"

maneuvering_compilerTest::maneuvering_compilerTest() : a(ssc::random_data_generator::DataGenerator(2121545))
{
}

maneuvering_compilerTest::~maneuvering_compilerTest()
{
}

void maneuvering_compilerTest::SetUp()
{
}

void maneuvering_compilerTest::TearDown()
{
}

double evaluate(const std::string& stuff, const BodyStates& states, const double t, ssc::data_source::DataSource& ds);
double evaluate(const std::string& stuff, const BodyStates& states, const double t, ssc::data_source::DataSource& ds)
{
    const auto n = maneuvering::compile(stuff);
    const auto f = n->get_lambda();
    return f(states, ds, t);
}

double test_compile(const std::string& stuff);
double test_compile(const std::string& stuff)
{
    BodyStates states;
    ssc::data_source::DataSource ds;
    const double t = 0;
    return evaluate(stuff, states, t, ds);
}

double test_compile(const std::string& stuff, ssc::data_source::DataSource& ds);
double test_compile(const std::string& stuff, ssc::data_source::DataSource& ds)
{
    BodyStates states;
    const double t = 0;
    return evaluate(stuff, states, t, ds);
}

TEST_F(maneuvering_compilerTest, can_compile_constant)
{
    ASSERT_DOUBLE_EQ(0,         test_compile("0"));
    ASSERT_DOUBLE_EQ(2,         test_compile("2"));
    ASSERT_DOUBLE_EQ(1.234e-6,  test_compile("1.234e-6"));
    ASSERT_DOUBLE_EQ(-1.234e-6, test_compile("-1.234e-6"));
}

TEST_F(maneuvering_compilerTest, can_compile_sum)
{
    ASSERT_DOUBLE_EQ(3,    test_compile("1+2"));
    ASSERT_DOUBLE_EQ(0.79, test_compile("-1.21+2"));
}

TEST_F(maneuvering_compilerTest, can_compile_product)
{
    ASSERT_DOUBLE_EQ(24,    test_compile("20*1.2"));
}

TEST_F(maneuvering_compilerTest, can_compile_cosine)
{
    ASSERT_DOUBLE_EQ(1,    test_compile("cos(0)"));
}

TEST_F(maneuvering_compilerTest, can_compile_sine)
{
    ASSERT_DOUBLE_EQ(sin(1),    test_compile("sin(1)"));
}

TEST_F(maneuvering_compilerTest, can_compile_exp_and_log)
{
    ASSERT_DOUBLE_EQ(1,    test_compile("exp(log(1))"));
    ASSERT_DOUBLE_EQ(10,   test_compile("exp(log(10))"));
}

TEST_F(maneuvering_compilerTest, can_compile_sqrt)
{
    ASSERT_DOUBLE_EQ(5,    test_compile("sqrt(25)"));
}

TEST_F(maneuvering_compilerTest, can_compile_abs)
{
    ASSERT_DOUBLE_EQ(2.5e3,    test_compile("abs(-2.5e3)"));
}

TEST_F(maneuvering_compilerTest, can_compile_identifier)
{
    ssc::data_source::DataSource ds;
    ds.set("Var_", 123.456);
    ASSERT_DOUBLE_EQ(123.456,    test_compile("Var_", ds));
}

TEST_F(maneuvering_compilerTest, can_compile_operations_on_identifiers)
{
    ssc::data_source::DataSource ds;
    ds.set("a", 123.456);
    ds.set("b", 456.789);
    ASSERT_DOUBLE_EQ(123.456+456.789,    test_compile("a+b", ds));
}

TEST_F(maneuvering_compilerTest, can_compile_identifiers_with_indexes)
{
    ssc::data_source::DataSource ds;
    ds.set("Var_1", 1.0);
    ds.set("Var_2", 2.0);
    ASSERT_DOUBLE_EQ(1.0,    test_compile("Var_1", ds));
    //ASSERT_DOUBLE_EQ(2.0,    test_compile("Var_2", ds));
    //ASSERT_DOUBLE_EQ(2.0,    test_compile("Var_2^Var_1", ds));
}
