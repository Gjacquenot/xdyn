/*
 * DefaultSurfaceElevation.cpp
 *
 *  Created on: 22 avr. 2014
 *      Author: cady
 */

#include "DefaultSurfaceElevation.hpp"
#include "InternalErrorException.hpp"

DefaultSurfaceElevation::DefaultSurfaceElevation(
        const double wave_height_,
        const ssc::kinematics::PointMatrixPtr& output_mesh_,
        const std::pair<std::size_t,std::size_t> output_mesh_size_):
            SurfaceElevationInterface(output_mesh_, output_mesh_size_), zwave(wave_height_)
{
}

std::vector<double> DefaultSurfaceElevation::wave_height(const std::vector<double> &x, const std::vector<double> &y, const double) const
{
    if (x.size() != y.size()) {
        THROW(__PRETTY_FUNCTION__, InternalErrorException, "Error when calculating surface elevation for a flat sea surface: the x and y vectors don't have the same size (size of x: " << x.size() << ", size of y: "<< y.size() << ")");
    }
    return std::vector<double>(x.size(), zwave);
}

ssc::kinematics::PointMatrix DefaultSurfaceElevation::orbital_velocity(
    const double,                  //!< gravity (in m/s^2)
    const std::vector<double>& x,  //!< x-positions in the NED frame (in meters)
    const std::vector<double>& y,  //!< y-positions in the NED frame (in meters)
    const std::vector<double>& z,  //!< z-positions in the NED frame (in meters)
    const double,                  //!< current instant (in seconds)
    const std::vector<double>& eta //!< Wave elevations at (x,y) in the NED frame (in meters)
    ) const
{
    if (x.size() != y.size() || x.size() != z.size() || x.size() != eta.size())
    {
        THROW(__PRETTY_FUNCTION__, InternalErrorException, "Error when calculating orbital velocity: the x, y, z and eta vectors don't have the same size (size of x: "
            << x.size() << ", size of y: " << y.size() << ", size of z: " << z.size() << ", size of eta: " << eta.size() << ")");
    }
    return ssc::kinematics::PointMatrix(ssc::kinematics::Matrix3Xd::Zero(3,x.size()), "NED");
}

std::vector<double> DefaultSurfaceElevation::dynamic_pressure(const double,                 //!< water density (in kg/m^3)
                                                              const double,                 //!< gravity (in m/s^2)
                                                              const std::vector<double> &x, //!< x-positions in the NED frame (in meters)
                                                              const std::vector<double> &,  //!< y-positions in the NED frame (in meters)
                                                              const std::vector<double> &,  //!< z-positions in the NED frame (in meters)
                                                              const std::vector<double> &,  //!< Wave elevations at (x,y) in the NED frame (in meters)
                                                              const double                  //!< Current time instant (in seconds)
                                                              ) const
{
    return std::vector<double>(x.size(), 0);
}
