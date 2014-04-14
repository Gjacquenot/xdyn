#include "StlReader.hpp"
#include "StlReaderException.hpp"
#include "STL_data.hpp"
#include "StlReaderTest.hpp"

TEST_F(StlReaderTest, number_of_facets_should_be_correct_for_a_single_facet_file)
{
	const VectorOfPoint3dTriplet facets = read_stl(stl_single_facet());
	ASSERT_EQ(1, facets.size());
}
TEST_F(StlReaderTest, number_of_facets_should_be_correct_for_a_three_facet_file)
{
	const VectorOfPoint3dTriplet facets = read_stl(stl_three_facets());
	ASSERT_EQ(3, facets.size());
}

TEST_F(StlReaderTest, should_be_able_to_read_a_single_facet_properly)
{
	const VectorOfPoint3dTriplet facets = read_stl(stl_single_facet());
	ASSERT_EQ(1, facets.size());
	ASSERT_DOUBLE_EQ(1.0, facets.at(0).p1.x);
	ASSERT_DOUBLE_EQ(2.1, facets.at(0).p1.y);
	ASSERT_DOUBLE_EQ(3.2, facets.at(0).p1.z);
	ASSERT_DOUBLE_EQ(2.1, facets.at(0).p2.x);
	ASSERT_DOUBLE_EQ(3.7, facets.at(0).p2.y);
	ASSERT_DOUBLE_EQ(4.5, facets.at(0).p2.z);
	ASSERT_DOUBLE_EQ(3.1, facets.at(0).p3.x);
	ASSERT_DOUBLE_EQ(4.5, facets.at(0).p3.y);
	ASSERT_DOUBLE_EQ(6.7, facets.at(0).p3.z);
}

TEST_F(StlReaderTest, should_be_able_to_read_several_facets_properly)
{
	const VectorOfPoint3dTriplet facets = read_stl(stl_three_facets());
	ASSERT_EQ(3, facets.size());
	ASSERT_DOUBLE_EQ(-0.50, facets.at(0).p1.x);
	ASSERT_DOUBLE_EQ(-0.50, facets.at(0).p1.y);
	ASSERT_DOUBLE_EQ(  1.0, facets.at(0).p1.z);
	ASSERT_DOUBLE_EQ( 0.50, facets.at(0).p2.x);
	ASSERT_DOUBLE_EQ(-0.50, facets.at(0).p2.y);
	ASSERT_DOUBLE_EQ(  1.0, facets.at(0).p2.z);
	ASSERT_DOUBLE_EQ( 0.50, facets.at(0).p3.x);
	ASSERT_DOUBLE_EQ( 0.50, facets.at(0).p3.y);
	ASSERT_DOUBLE_EQ(  1.0, facets.at(0).p3.z);

	ASSERT_DOUBLE_EQ(-0.50, facets.at(1).p1.x);
	ASSERT_DOUBLE_EQ(-0.50, facets.at(1).p1.y);
	ASSERT_DOUBLE_EQ(  1.0, facets.at(1).p1.z);
	ASSERT_DOUBLE_EQ( 0.50, facets.at(1).p2.x);
	ASSERT_DOUBLE_EQ( 0.50, facets.at(1).p2.y);
	ASSERT_DOUBLE_EQ(  1.0, facets.at(1).p2.z);
	ASSERT_DOUBLE_EQ(-0.50, facets.at(1).p3.x);
	ASSERT_DOUBLE_EQ( 0.50, facets.at(1).p3.y);
	ASSERT_DOUBLE_EQ(  1.0, facets.at(1).p3.z);

	ASSERT_DOUBLE_EQ( 0.50, facets.at(2).p1.x);
	ASSERT_DOUBLE_EQ(-0.50, facets.at(2).p1.y);
	ASSERT_DOUBLE_EQ( 0.00, facets.at(2).p1.z);
	ASSERT_DOUBLE_EQ(-0.50, facets.at(2).p2.x);
	ASSERT_DOUBLE_EQ(-0.50, facets.at(2).p2.y);
	ASSERT_DOUBLE_EQ( 0.00, facets.at(2).p2.z);
	ASSERT_DOUBLE_EQ(-0.50, facets.at(2).p3.x);
	ASSERT_DOUBLE_EQ( 0.50, facets.at(2).p3.y);
	ASSERT_DOUBLE_EQ( 0.00, facets.at(2).p3.z);
}

TEST_F(StlReaderTest, should_throw_an_exception_when_end_file_is_not_reached)
{
	const std::string data("solid MYSOLID\nfacet normal 0.4 0.4 0.2\nouterloop\n");
	ASSERT_THROW(read_stl(data),StlReaderException);

}
