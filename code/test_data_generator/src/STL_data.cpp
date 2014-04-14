/*
 * STL_data.cpp
 *
 *  Created on: 14 avr. 2014
 *      Author: jacquenot
 */



#include <sstream>
#include "STL_data.hpp"

std::string stl_single_facet()
{
    std::stringstream data;
    data << "solid MYSOLID\n"
         << "facet normal 0.4 0.4 0.2\n"
         << "    outerloop\n"
         << "    vertex  1.0 2.1 3.2\n"
         << "    vertex  2.1 3.7 4.5\n"
         << "    vertex  3.1 4.5 6.7\n"
         << "    endloop\n"
         << "endfacet\n"
         << "endsolid MYSOLID\n";
    return data.str();
}

std::string stl_cube()
{
    std::stringstream data;
    data << "solid MYSOLID\n"
         << "  facet normal   0.000000E+00  0.000000E+00   1.00000\n"
         << "    outer loop\n"
         << "      vertex  -0.500000     -0.500000       1.00000\n"
         << "      vertex   0.500000     -0.500000       1.00000\n"
         << "      vertex   0.500000      0.500000       1.00000\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal   0.000000E+00  0.000000E+00   1.00000\n"
         << "    outer loop\n"
         << "      vertex  -0.500000     -0.500000       1.00000\n"
         << "      vertex   0.500000      0.500000       1.00000\n"
         << "      vertex  -0.500000      0.500000       1.00000\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "\n"
         << "  facet normal   0.000000E+00  0.000000E+00  -1.00000\n"
         << "    outer loop\n"
         << "      vertex   0.500000     -0.500000      0.000000E+00\n"
         << "      vertex  -0.500000     -0.500000      0.000000E+00\n"
         << "      vertex  -0.500000      0.500000      0.000000E+00\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal   0.000000E+00  0.000000E+00  -1.00000\n"
         << "    outer loop\n"
         << "      vertex   0.500000     -0.500000      0.000000E+00\n"
         << "      vertex  -0.500000      0.500000      0.000000E+00\n"
         << "      vertex   0.500000      0.500000      0.000000E+00\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal   -1.00000      0.000000E+00  0.000000E+00\n"
         << "    outer loop\n"
         << "      vertex  -0.500000     -0.500000      0.000000E+00\n"
         << "      vertex  -0.500000     -0.500000       1.00000\n"
         << "      vertex  -0.500000      0.500000       1.00000\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal   -1.00000      0.000000E+00  0.000000E+00\n"
         << "    outer loop\n"
         << "      vertex  -0.500000     -0.500000      0.000000E+00\n"
         << "      vertex  -0.500000      0.500000       1.00000\n"
         << "      vertex  -0.500000      0.500000      0.000000E+00\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal    1.00000      0.000000E+00  0.000000E+00\n"
         << "    outer loop\n"
         << "      vertex   0.500000     -0.500000       1.00000\n"
         << "      vertex   0.500000     -0.500000      0.000000E+00\n"
         << "      vertex   0.500000      0.500000      0.000000E+00\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal    1.00000      0.000000E+00  0.000000E+00\n"
         << "    outer loop\n"
         << "      vertex   0.500000     -0.500000       1.00000\n"
         << "      vertex   0.500000      0.500000      0.000000E+00\n"
         << "      vertex   0.500000      0.500000       1.00000\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal   0.000000E+00  -1.00000      0.000000E+00\n"
         << "    outer loop\n"
         << "      vertex  -0.500000     -0.500000      0.000000E+00\n"
         << "      vertex   0.500000     -0.500000      0.000000E+00\n"
         << "      vertex   0.500000     -0.500000       1.00000\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal   0.000000E+00  -1.00000      0.000000E+00\n"
         << "    outer loop\n"
         << "      vertex  -0.500000     -0.500000      0.000000E+00\n"
         << "      vertex   0.500000     -0.500000       1.00000\n"
         << "      vertex  -0.500000     -0.500000       1.00000\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal   0.000000E+00   1.00000      0.000000E+00\n"
         << "    outer loop\n"
         << "      vertex  -0.500000      0.500000       1.00000\n"
         << "      vertex   0.500000      0.500000       1.00000\n"
         << "      vertex   0.500000      0.500000      0.000000E+00\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "  facet normal   0.000000E+00   1.00000      0.000000E+00\n"
         << "    outer loop\n"
         << "      vertex  -0.500000      0.500000       1.00000\n"
         << "      vertex   0.500000      0.500000      0.000000E+00\n"
         << "      vertex  -0.500000      0.500000      0.000000E+00\n"
         << "    endloop\n"
         << "  endfacet\n"
         << "endsolid MYSOLID\n";
    return data.str();
}

