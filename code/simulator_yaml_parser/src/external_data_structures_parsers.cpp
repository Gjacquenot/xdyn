/*
 * external_data_structures_parsers.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: cady
 */

#include "external_data_structures_parsers.hpp"
#include "yaml.h"
#include "SimulatorYamlParserException.hpp"
#include "parse_unit_value.hpp"

template <typename T> void try_to_parse(const YAML::Node& node, const std::string& key, T& value)
{
    const YAML::Node * n = node.FindValue(key);
    if (n) (*n) >> value;
}

void parse_point_with_name(const YAML::Node& node, YamlPoint& p, const std::string& name)
{
    YamlCoordinates c;
    node >> c;
    p = c;
    node["frame"] >> p.frame;
    p.name = name;
}

void operator >> (const YAML::Node& node, YamlRotation& g)
{
    node["convention"] >> g.convention;
    node["order by"] >> g.order_by;
}

void operator >> (const YAML::Node& node, YamlBody& b)
{
    node["name"] >> b.name;
    try_to_parse(node, "mesh", b.mesh);
    node["external forces"] >> b.external_forces;
    node["position of body frame relative to mesh"] >> b.position_of_body_frame_relative_to_mesh;
    node["initial position of body frame relative to NED"] >> b.initial_position_of_body_frame_relative_to_NED_projected_in_NED;
    node["initial velocity of body frame relative to NED"] >> b.initial_velocity_of_body_frame_relative_to_NED_projected_in_body;
    node["dynamics"] >> b.dynamics;
}

void operator >> (const YAML::Node& node, YamlModel& m)
{
    node["model"] >> m.model;
    YAML::Emitter out;
    out << node;
    m.yaml = out.c_str();
}

void operator >> (const YAML::Node& node, YamlPosition& p)
{
    node >> p.angle;
    node >> p.coordinates;
    node["frame"] >> p.frame;
}

void operator >> (const YAML::Node& node, YamlAngle& a)
{
    parse_uv(node["phi"], a.phi);
    parse_uv(node["theta"], a.theta);
    parse_uv(node["psi"], a.psi);
}

void operator >> (const YAML::Node& node, YamlCoordinates& c)
{
    parse_uv(node["x"], c.x);
    parse_uv(node["y"], c.y);
    parse_uv(node["z"], c.z);
}

void operator >> (const YAML::Node& node, YamlSpeed& s)
{
    node["frame"] >> s.frame;
    parse_uv(node["u"], s.u);
    parse_uv(node["v"], s.v);
    parse_uv(node["w"], s.w);
    parse_uv(node["p"], s.p);
    parse_uv(node["q"], s.q);
    parse_uv(node["r"], s.r);
}

void operator >> (const YAML::Node& node, YamlDynamics& d)
{
    parse_point_with_name(node["centre of inertia"], d.centre_of_inertia, "centre of inertia");
    parse_uv(node["mass"], d.mass);
    node["rigid body inertia matrix at the center of buoyancy projected in the body frame"] >> d.rigid_body_inertia;
    node["added mass matrix at the center of buoyancy projected in the body frame"] >> d.added_mass;
}

void operator >> (const YAML::Node& node, YamlPoint& p)
{
    std::string name;
    node["name"] >> name;
    parse_point_with_name(node, p,name);
}


void operator >> (const YAML::Node& node, YamlDynamics6x6Matrix& m)
{
    node["frame"] >> m.frame;
    node["row 1"] >> m.row_1;
    node["row 2"] >> m.row_2;
    node["row 3"] >> m.row_3;
    node["row 4"] >> m.row_4;
    node["row 5"] >> m.row_5;
    node["row 6"] >> m.row_6;
}

void operator >> (const YAML::Node& node, YamlBlockedDegreesOfFreedom& m)
{
    node["body"] >> m.body;
    node["blocked"] >> m.blocked;
}

void operator >> (const YAML::Node& node, YamlOutput& p)
{
    node["axes"] >> p.axes;
    node["projected in frame"] >> p.projected_in_frame;
}

void operator >> (const YAML::Node& node, YamlPositionOutput& p)
{
    YamlOutput o;
    node >> o;
    p = o;
    node["point"] >> p.point;
    node["relative to frame"] >> p.relative_to_frame;
}

void operator >> (const YAML::Node& node, YamlAnglesOutput& p)
{
    YamlOutput o;
    node >> o;
    p = o;
    node["frame"] >> p.frame;
    node["relative to frame"] >> p.relative_to_frame;
}

void operator >> (const YAML::Node& node, YamlForcesAndTorquesOutput& f)
{
    node["axes"] >> f.axes;
    node["point frame"] >> f.point_frame;
    node["point name"] >> f.point_name;
    node["projected in frame"] >> f.projected_in_frame;
    node["type"] >> f.type;
}

void operator >> (const YAML::Node& node, YamlEnvironmentalConstants& f)
{
    parse_uv(node["g"], f.g);
    parse_uv(node["rho"], f.rho);
}
