/*
 * EnvironmentAndFrames.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: cady
 */

#include "EnvironmentAndFrames.hpp"
#include "Kinematics.hpp"


EnvironmentAndFrames::EnvironmentAndFrames() : w(WaveModelPtr()),
                                               k(KinematicsPtr(new Kinematics())),
                                               rho(0),
                                               g(0)
{
}
