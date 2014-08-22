#ifndef STL_WRITER_HPP_
#define STL_WRITER_HPP_

#include <ostream>
#include <string>

#include "GeometricTypes3d.hpp"

std::string write_stl(const VectorOfVectorOfPoints& mesh);
::std::ostream& operator<<(::std::ostream& os, const VectorOfVectorOfPoints& mesh);

#endif /* STL_WRITER_HPP_ */
