/*
 * SimpleHeadingKeepingController.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: cady
 */
#include "SimpleHeadingKeepingController.hpp"

#include "BodyStates.hpp"
#include "external_data_structures_parsers.hpp"
#include <ssc/yaml_parser.hpp>

#include "yaml.h"

#define _USE_MATH_DEFINE
#include <cmath>
#define PI M_PI

std::string SimpleHeadingKeepingController::model_name() {return "simple heading controller";}

SimpleHeadingKeepingController::Yaml::Yaml() : name(), ksi(0), Tp(0)
{
}

SimpleHeadingKeepingController::Yaml SimpleHeadingKeepingController::parse(const std::string& yaml)
{
    std::stringstream stream(yaml);
    YAML::Parser parser(stream);
    YAML::Node node;
    parser.GetNextDocument(node);
    Yaml ret;
    node["name"] >> ret.name;
    node["ksi"] >> ret.ksi;
    ::ssc::yaml_parser::parse_uv(node["Tp"], ret.Tp);
    return ret;
}

SimpleHeadingKeepingController::SimpleHeadingKeepingController(const Yaml& input, const std::string& body_name_, const EnvironmentAndFrames& env_) :
        ControllableForceModel(input.name, {"psi_co"}, YamlPosition(YamlCoordinates(),YamlAngle(), body_name_), body_name_, env_),
        ksi(input.ksi),
        omega0(2*PI/input.Tp),
        rotation_convention("angle", {"z","y'","x''"})
{
}

ssc::kinematics::Vector6d SimpleHeadingKeepingController::get_force(const BodyStates& states, const double, const std::map<std::string,double>& commands) const
{
    ssc::kinematics::Vector6d ret = ssc::kinematics::Vector6d::Zero();

    const auto angles = states.get_angles(rotation_convention);
    const double delta_psi = commands.at("psi_co") - angles.psi;
    const double sigma_zz = states.total_inertia->operator()(2,2);
    const double K_psi = sigma_zz*omega0*omega0;
    const double K_r = 2*ksi*omega0*sigma_zz;
    ret(5) = K_psi*delta_psi - K_r*states.r();
    return ret;
}
