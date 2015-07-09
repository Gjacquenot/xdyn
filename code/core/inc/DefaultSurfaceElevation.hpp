/*
 * DefaultWaveModel.hpp
 *
 *  Created on: 22 avr. 2014
 *      Author: cady
 */

#ifndef DEFAULTSURFACELEVATION_HPP_
#define DEFAULTSURFACELEVATION_HPP_

#include <ssc/kinematics.hpp>
#include "SurfaceElevationInterface.hpp"

/** \brief Flat sea surface.
 *  \details The relative height is zwave-z, so a negative
 *           value implies the point is above the water and a
 *           positive value implies it's underneath. This convention
 *           was chosen because it should simplify the computation of the
 *           hydrostatic forces (no sign change).
 *  \addtogroup hydro_models
 *  \ingroup hydro_models
 *  \section ex1 Example
 *  \snippet hydro_models/unit_tests/src/DefaultWaveModelTest.cpp DefaultWaveModelTest example
 *  \section ex2 Expected output
 *  \snippet hydro_models/unit_tests/src/DefaultWaveModelTest.cpp DefaultWaveModelTest expected output
 */
class DefaultSurfaceElevation : public SurfaceElevationInterface
{
    public:
        DefaultSurfaceElevation(const double wave_height,
                                const ssc::kinematics::PointMatrixPtr& output_mesh,
                                const std::pair<std::size_t,std::size_t> output_mesh_size = std::make_pair((std::size_t)0,(std::size_t)0));

    private:
        DefaultSurfaceElevation(); // Disabled

        /**  \brief Flat sea surface model.
          *  \returns zwave;
          *  \snippet hydro_models/unit_tests/src/DefaultWaveModelTest.cpp DefaultWaveModelTest wave_height_example
          */
        double wave_height(const double x, //!< x-coordinate of the point, relative to the centre of the NED frame, projected in the NED frame
                           const double y, //!< y-coordinate of the point, relative to the centre of the NED frame, projected in the NED frame
                           const double t //!< Current instant (in seconds)
                           ) const;

        double dynamic_pressure(const double rho, //!< water density (in kg/m^3)
                                const double g,   //!< gravity (in m/s^2)
                                const double x,   //!< x-position in the NED frame (in meters)
                                const double y,   //!< y-position in the NED frame (in meters)
                                const double z,   //!< z-position in the NED frame (in meters)
                                const double eta, //!< Wave elevation at (x,y) in the NED frame (in meters)
                                const double t    //!< Current time instant (in seconds)
                                ) const;

        double zwave;
};

#endif /* DEFAULTSURFACELEVATION_HPP_ */
