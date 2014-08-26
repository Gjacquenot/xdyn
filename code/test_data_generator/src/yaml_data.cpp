/*
 * yaml_data.cpp
 *
 *  Created on: 16 avr. 2014
 *      Author: cady
 */

#include "yaml_data.hpp"
#include <sstream>

std::string test_data::hydrostatic_test()
{
    std::stringstream ss;
    ss << "rotations:\n"
       << "    order by: angle\n"
       << "    convention: [z,y',x'']\n"
       << "\n"
       << "environmental constants:\n"
       << "    g: {value: 9.81, unit: m/s^2}\n"
       << "    rho: {value: 1000, unit: kg/m^3}\n"
       << "environment models:\n"
       << "  - model: no waves\n"
       << "    frame: NED\n"
       << "    z: {value: 0, unit: m}\n"
       << "  - model: no wind\n"
       << "    \n"
       << "# Fixed frame: NED\n"
       << "bodies: # All bodies have NED as parent frame\n"
       << "  - name: body 1\n"
       << "    mesh: anthineas.stl\n"
       << "    position of body frame relative to mesh:\n"
       << "        frame: mesh\n"
       << "        x: {value: 10, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: 0, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial position of body frame relative to NED:\n"
       << "        frame: NED\n"
       << "        x: {value: 0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: 0, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial velocity of body frame relative to NED:\n"
       << "        frame: body\n"
       << "        u: {value: 0, unit: m/s}\n"
       << "        v: {value: 0, unit: m/s}\n"
       << "        w: {value: 0, unit: m/s}\n"
       << "        p: {value: 0, unit: rad/s}\n"
       << "        q: {value: 0, unit: rad/s}\n"
       << "        r: {value: 0, unit: rad/s}\n"
       << "    dynamics:\n"
       << "        centre of inertia:\n"
       << "            frame: body 1\n"
       << "            x: {value: 0, unit: m}\n"
       << "            y: {value: 0, unit: m}\n"
       << "            z: {value: 0, unit: m}\n"
       << "        mass: {value: 1000, unit: tonne} # Caution: 'ton' is the british ton which is 907.185 kg\n"
       << "        rigid body inertia matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: body 1\n"
       << "            row 1: [1,0,0,0,0,0]\n"
       << "            row 2: [0,1,0,0,0,0]\n"
       << "            row 3: [0,0,1,0,0,0]\n"
       << "            row 4: [0,0,0,1,0,0]\n"
       << "            row 5: [0,0,0,0,1,0]\n"
       << "            row 6: [0,0,0,0,0,1]\n"
       << "        added mass matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: body 1\n"
       << "            row 1: [1,0,0,0,0,0]\n"
       << "            row 2: [0,1,0,0,0,0]\n"
       << "            row 3: [0,0,1,0,0,0]\n"
       << "            row 4: [0,0,0,1,0,0]\n"
       << "            row 5: [0,0,0,0,1,0]\n"
       << "            row 6: [0,0,0,0,0,1]\n"
       << "    external forces:\n"
       << "      - model: gravity\n"
       << "      - model: non-linear hydrostatic\n"
       << "    \n"
       << "\n"
       << "points:\n"
       << "  - name: P\n"
       << "    frame: body 1\n"
       << "    x: {value: 10, unit: m}\n"
       << "    y: {value: 10, unit: m}\n"
       << "    z: {value: 20, unit: m}\n"
       << "  - name: O\n"
       << "    frame: NED\n"
       << "    x: {value: 0, unit: m}\n"
       << "    y: {value: 0, unit: m}\n"
       << "    z: {value: 0, unit: m}\n"
       << "\n"
       << "blocked degrees of freedom body/NED->body:\n"
       << "   - body: body 1\n"
       << "     blocked: [x, theta]\n"
       << "    \n"
       << "outputs:\n"
       << "    positions:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,z]\n"
       << "    angles:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y,z]\n"
       << "    linear velocities:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular velocities:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "    linear accelerations:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular accelerations:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        #  = p,q\n"
       << "        axes: [x,y]\n"
       << "    forces and torques:\n"
       << "      - type: non-linear hydrostatic\n"
       << "        point name: centre of inertia\n"
       << "        point frame: body 1\n"
       << "        projected in frame: NED\n"
       << "        axes: [X, Z, K, N]\n";
    return ss.str();
}

std::string test_data::full_example()
{
    std::stringstream ss;
    ss << "rotations:\n"
       << "    order by: angle\n"
       << "    convention: [z,y',x'']\n"
       << "\n"
       << "environmental constants:\n"
       << "    g: {value: 9.81, unit: m/s^2}\n"
       << "    rho: {value: 1000, unit: kg/m^3}\n"
       << "environment models:\n"
       << "  - model: no waves\n"
       << "    constant wave height in NED frame: {value: 12, unit: m}\n"
       << "  - model: no wind\n"
       << "    \n"
       << "# Fixed frame: NED\n"
       << "bodies: # All bodies have NED as parent frame\n"
       << "  - name: body 1\n"
       << "    mesh: anthineas.stl\n"
       << "    position of body frame relative to mesh:\n"
       << "        frame: mesh\n"
       << "        x: {value: 10, unit: m}\n"
       << "        y: {value: 21, unit: cm}\n"
       << "        z: {value: 33, unit: km}\n"
       << "        phi: {value: 1, unit: rad}\n"
       << "        theta: {value: 3, unit: rad}\n"
       << "        psi: {value: 2, unit: rad}\n"
       << "    initial position of body frame relative to NED:\n"
       << "        frame: NED\n"
       << "        x: {value: 4, unit: m}\n"
       << "        y: {value: 8, unit: m}\n"
       << "        z: {value: 12, unit: m}\n"
       << "        phi: {value: 1.3, unit: rad}\n"
       << "        theta: {value: 1.4, unit: rad}\n"
       << "        psi: {value: 1.5, unit: rad}\n"
       << "    initial velocity of body frame relative to NED:\n"
       << "        frame: body 1\n"
       << "        u: {value: -8, unit: m/s}\n"
       << "        v: {value: -9, unit: m/s}\n"
       << "        w: {value: 14, unit: m/s}\n"
       << "        p: {value: 56, unit: rad/s}\n"
       << "        q: {value: 7, unit: rad/s}\n"
       << "        r: {value: 6, unit: rad/s}\n"
       << "    dynamics:\n"
       << "        centre of inertia:\n"
       << "            frame: body 1\n"
       << "            x: {value: 4, unit: m}\n"
       << "            y: {value: 7, unit: m}\n"
       << "            z: {value: -10, unit: m}\n"
       << "        mass: {value: 1000, unit: tonne} # Caution: 'ton' is the british ton which is 907.185 kg\n"
       << "        rigid body inertia matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: body 1\n"
       << "            row 1: [1,2,3,4,5,6]\n"
       << "            row 2: [7,2,1,2,11,13]\n"
       << "            row 3: [20,30,3,80,0.9,0.1]\n"
       << "            row 4: [0,0,0,4,0,0]\n"
       << "            row 5: [0,0,0,0,5,0]\n"
       << "            row 6: [0,0,0,0,0,6]\n"
       << "        added mass matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: body 1\n"
       << "            row 1: [1,2,3,4,5,6]\n"
       << "            row 2: [-7,2,1,2,11,13]\n"
       << "            row 3: [-20,30,3,80,0.9,0.1]\n"
       << "            row 4: [0,0,0,4.1,0,0]\n"
       << "            row 5: [0,0,0,0,5.2,0]\n"
       << "            row 6: [0,0,0,0,0,6.3]\n"
       << "    external forces:\n"
       << "      - model: gravity\n"
       << "      - model: non-linear hydrostatic\n"
       << "    \n"
       << "\n"
       << "points:\n"
       << "  - name: P\n"
       << "    frame: body 1\n"
       << "    x: {value: 10, unit: m}\n"
       << "    y: {value: 10, unit: m}\n"
       << "    z: {value: 20, unit: m}\n"
       << "  - name: O\n"
       << "    frame: NED\n"
       << "    x: {value: 3, unit: cm}\n"
       << "    y: {value: -7, unit: dm}\n"
       << "    z: {value: 0.3, unit: km}\n"
       << "\n"
       << "blocked degrees of freedom body/NED->body:\n"
       << "   - body: body 1\n"
       << "     blocked: [x, theta]\n"
       << "    \n"
       << "outputs:\n"
       << "    positions:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,z]\n"
       << "    angles:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y,z]\n"
       << "    linear velocities:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular velocities:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "    linear accelerations:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular accelerations:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        #  = p,q\n"
       << "        axes: [x,y]\n"
       << "    forces and torques:\n"
       << "      - type: non-linear hydrostatic\n"
       << "        point name: centre of inertia\n"
       << "        point frame: body 1\n"
       << "        projected in frame: NED\n"
       << "        axes: [X, Z, K, N]\n";
    return ss.str();
}

std::string test_data::falling_ball_example()
{
    std::stringstream ss;
    ss << "rotations:\n"
       << "    order by: angle\n"
       << "    convention: [z,y',x'']\n"
       << "\n"
       << "environmental constants:\n"
       << "    g: {value: 9.81, unit: m/s^2}\n"
       << "    rho: {value: 1000, unit: kg/m^3}\n"
       << "environment models: []\n"
       << "\n"
       << "bodies: # All bodies have NED as parent frame\n"
       << "  - name: ball\n"
       << "    position of body frame relative to mesh:\n"
       << "        frame: mesh\n"
       << "        x: {value: 0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: -10, unit: m}\n"
       << "        phi: {value: 1, unit: rad}\n"
       << "        theta: {value: 3, unit: rad}\n"
       << "        psi: {value: 2, unit: rad}\n"
       << "    initial position of body frame relative to NED:\n"
       << "        frame: NED\n"
       << "        x: {value: 4, unit: m}\n"
       << "        y: {value: 8, unit: m}\n"
       << "        z: {value: 12, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial velocity of body frame relative to NED:\n"
       << "        frame: ball\n"
       << "        u: {value: 1, unit: m/s}\n"
       << "        v: {value: 0, unit: m/s}\n"
       << "        w: {value: 0, unit: m/s}\n"
       << "        p: {value: 0, unit: rad/s}\n"
       << "        q: {value: 0, unit: rad/s}\n"
       << "        r: {value: 0, unit: rad/s}\n"
       << "    dynamics:\n"
       << "        centre of inertia:\n"
       << "            frame: ball\n"
       << "            x: {value: 0, unit: m}\n"
       << "            y: {value: 0, unit: m}\n"
       << "            z: {value: 0.5, unit: m}\n"
       << "        mass: {value: 1000, unit: tonne}\n"
       << "        rigid body inertia matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: ball\n"
       << "            row 1: [1E6,0,0,0,0,0]\n"
       << "            row 2: [0,1E6,0,0,0,0]\n"
       << "            row 3: [0,0,1E6,0,0,0]\n"
       << "            row 4: [0,0,0,1E6,0,0]\n"
       << "            row 5: [0,0,0,0,1E6,0]\n"
       << "            row 6: [0,0,0,0,0,1E6]\n"
       << "        added mass matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: ball\n"
       << "            row 1: [0,0,0,0,0,0]\n"
       << "            row 2: [0,0,0,0,0,0]\n"
       << "            row 3: [0,0,0,0,0,0]\n"
       << "            row 4: [0,0,0,0,0,0]\n"
       << "            row 5: [0,0,0,0,0,0]\n"
       << "            row 6: [0,0,0,0,0,0]\n"
       << "    external forces:\n"
       << "      - model: gravity\n"
       << "        g: {value: 9.81, unit: m/s^2}\n"
       << "\n"
       << "points:\n"
       << "  - name: P\n"
       << "    frame: ball\n"
       << "    x: {value: 10, unit: m}\n"
       << "    y: {value: 10, unit: m}\n"
       << "    z: {value: 20, unit: m}\n"
       << "  - name: O\n"
       << "    frame: NED\n"
       << "    x: {value: 0, unit: m}\n"
       << "    y: {value: 0, unit: m}\n"
       << "    z: {value: 0, unit: m}\n"
       << "\n"
       << "blocked degrees of freedom body/NED->body: []\n"
       << "\n"
       << "outputs:\n"
       << "    positions:\n"
       << "      - point: O\n"
       << "        relative to frame: ball\n"
       << "        projected in frame: ball\n"
       << "        axes: [x,z]\n"
       << "    angles:\n"
       << "      - frame: ball\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: ball\n"
       << "        axes: [x,y,z]\n"
       << "    linear velocities:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: ball\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular velocities:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: ball\n"
       << "        axes: [x,y]\n"
       << "    linear accelerations:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: ball\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular accelerations:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: ball\n"
       << "        #  = p,q\n"
       << "        axes: [x,y]\n"
       << "    forces and torques:\n"
       << "      - type: non-linear hydrostatic\n"
       << "        point name: centre of inertia\n"
       << "        point frame: ball\n"
       << "        projected in frame: NED\n"
       << "        axes: [X, Z, K, N]\n";
    return ss.str();
}

std::string test_data::oscillating_cube_example()
{
    std::stringstream ss;
    ss << "rotations:\n"
       << "    order by: angle\n"
       << "    convention: [z,y',x'']\n"
       << "\n"
       << "environmental constants:\n"
       << "    g: {value: 9.81, unit: m/s^2}\n"
       << "    rho: {value: 1026, unit: kg/m^3}\n"
       << "environment models:\n"
       << "  - model: no waves\n"
       << "    constant wave height in NED frame: {value: 0, unit: m}\n"
       << "  - model: no wind\n"
       << "\n"
       << "bodies: # All bodies have NED as parent frame\n"
       << "  - name: cube\n"
       << "    mesh: cube.stl\n"
       << "    position of body frame relative to mesh:\n"
       << "        frame: mesh\n"
       << "        x: {value: 0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: 0.5, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial position of body frame relative to NED:\n"
       << "        frame: NED\n"
       << "        x: {value:  0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: 0.5, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial velocity of body frame relative to NED:\n"
       << "        frame: cube\n"
       << "        u: {value: 0, unit: m/s}\n"
       << "        v: {value: 0, unit: m/s}\n"
       << "        w: {value: 0, unit: m/s}\n"
       << "        p: {value: 0, unit: rad/s}\n"
       << "        q: {value: 0, unit: rad/s}\n"
       << "        r: {value: 0, unit: rad/s}\n"
       << "    dynamics:\n"
       << "        centre of inertia:\n"
       << "            frame: cube\n"
       << "            x: {value: 0, unit: m}\n"
       << "            y: {value: 0, unit: m}\n"
       << "            z: {value: 0.5, unit: m}\n"
       << "        mass: {value: 1, unit: tonne}\n"
       << "        rigid body inertia matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: cube\n"
       << "            row 1: [1E3,0,0,0,0,0]\n"
       << "            row 2: [0,1E3,0,0,0,0]\n"
       << "            row 3: [0,0,1E3,0,0,0]\n"
       << "            row 4: [0,0,0,1E3,0,0]\n"
       << "            row 5: [0,0,0,0,1E3,0]\n"
       << "            row 6: [0,0,0,0,0,1E3]\n"
       << "        added mass matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: cube\n"
       << "            row 1: [0,0,0,0,0,0]\n"
       << "            row 2: [0,0,0,0,0,0]\n"
       << "            row 3: [0,0,0,0,0,0]\n"
       << "            row 4: [0,0,0,0,0,0]\n"
       << "            row 5: [0,0,0,0,0,0]\n"
       << "            row 6: [0,0,0,0,0,0]\n"
       << "    external forces:\n"
       << "      - model: gravity\n"
       << "      - model: non-linear hydrostatic\n"
       << "\n"
       << "points:\n"
       << "  - name: P\n"
       << "    frame: cube\n"
       << "    x: {value: 0, unit: m}\n"
       << "    y: {value: 0, unit: m}\n"
       << "    z: {value: 0, unit: m}\n"
       << "\n"
       << "blocked degrees of freedom body/NED->body: []\n"
       << "\n"
       << "outputs:\n"
       << "    positions:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    angles:\n"
       << "      - frame: cube\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    linear velocities:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,y]\n"
       << "    angular velocities:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    linear accelerations:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular accelerations:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        #  = p,q\n"
       << "        axes: [x,y]\n"
       << "    forces and torques:\n"
       << "      - type: non-linear hydrostatic\n"
       << "        point name: centre of inertia\n"
       << "        point frame: cube\n"
       << "        projected in frame: NED\n"
       << "        axes: [X, Y, Z, K, M, N]\n";
    return ss.str();
}

std::string test_data::stable_cube_example()
{
    std::stringstream ss;
    ss << "rotations:\n"
       << "    order by: angle\n"
       << "    convention: [z,y',x'']\n"
       << "\n"
       << "environmental constants:\n"
       << "    g: {value: 9.81, unit: m/s^2}\n"
       << "    rho: {value: 1026, unit: kg/m^3}\n"
       << "environment models:\n"
       << "  - model: no waves\n"
       << "    constant wave height in NED frame: {value: 0, unit: m}\n"
       << "  - model: no wind\n"
       << "\n"
       << "bodies: # All bodies have NED as parent frame\n"
       << "  - name: cube\n"
       << "    mesh: cube.stl\n"
       << "    position of body frame relative to mesh:\n"
       << "        frame: mesh\n"
       << "        x: {value: 0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: 0.5, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial position of body frame relative to NED:\n"
       << "        frame: NED\n"
       << "        x: {value:  0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: 0.4746588693957115, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial velocity of body frame relative to NED:\n"
       << "        frame: cube\n"
       << "        u: {value: 0, unit: m/s}\n"
       << "        v: {value: 0, unit: m/s}\n"
       << "        w: {value: 0, unit: m/s}\n"
       << "        p: {value: 0, unit: rad/s}\n"
       << "        q: {value: 0, unit: rad/s}\n"
       << "        r: {value: 0, unit: rad/s}\n"
       << "    dynamics:\n"
       << "        centre of inertia:\n"
       << "            frame: cube\n"
       << "            x: {value: 0, unit: m}\n"
       << "            y: {value: 0, unit: m}\n"
       << "            z: {value: 0.5, unit: m}\n"
       << "        mass: {value: 1, unit: tonne}\n"
       << "        rigid body inertia matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: cube\n"
       << "            row 1: [1E3,0,0,0,0,0]\n"
       << "            row 2: [0,1E3,0,0,0,0]\n"
       << "            row 3: [0,0,1E3,0,0,0]\n"
       << "            row 4: [0,0,0,1E3,0,0]\n"
       << "            row 5: [0,0,0,0,1E3,0]\n"
       << "            row 6: [0,0,0,0,0,1E3]\n"
       << "        added mass matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: cube\n"
       << "            row 1: [0,0,0,0,0,0]\n"
       << "            row 2: [0,0,0,0,0,0]\n"
       << "            row 3: [0,0,0,0,0,0]\n"
       << "            row 4: [0,0,0,0,0,0]\n"
       << "            row 5: [0,0,0,0,0,0]\n"
       << "            row 6: [0,0,0,0,0,0]\n"
       << "    external forces:\n"
       << "      - model: gravity\n"
       << "      - model: non-linear hydrostatic\n"
       << "\n"
       << "points:\n"
       << "  - name: P\n"
       << "    frame: cube\n"
       << "    x: {value: 0, unit: m}\n"
       << "    y: {value: 0, unit: m}\n"
       << "    z: {value: 0, unit: m}\n"
       << "\n"
       << "blocked degrees of freedom body/NED->body: []\n"
       << "\n"
       << "outputs:\n"
       << "    positions:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    angles:\n"
       << "      - frame: cube\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    linear velocities:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,y]\n"
       << "    angular velocities:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    linear accelerations:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular accelerations:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        #  = p,q\n"
       << "        axes: [x,y]\n"
       << "    forces and torques:\n"
       << "      - type: non-linear hydrostatic\n"
       << "        point name: centre of inertia\n"
       << "        point frame: cube\n"
       << "        projected in frame: NED\n"
       << "        axes: [X, Y, Z, K, M, N]\n";
    return ss.str();
}

std::string test_data::stable_rolling_cube_test()
{
    std::stringstream ss;
    ss << "rotations:\n"
       << "    order by: angle\n"
       << "    convention: [z,y',x'']\n"
       << "\n"
       << "environmental constants:\n"
       << "    g: {value: 9.81, unit: m/s^2}\n"
       << "    rho: {value: 1000, unit: kg/m^3}\n"
       << "environment models:\n"
       << "  - model: no waves\n"
       << "    constant wave height in NED frame: {value: 0, unit: m}\n"
       << "  - model: no wind\n"
       << "\n"
       << "bodies: # All bodies have NED as parent frame\n"
       << "  - name: cube\n"
       << "    mesh: cube.stl\n"
       << "    position of body frame relative to mesh:\n"
       << "        frame: mesh\n"
       << "        x: {value: 0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: 0.5, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial position of body frame relative to NED:\n"
       << "        frame: NED\n"
       << "        x: {value:  0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: 0.25, unit: m}\n"
       << "        phi: {value: 0, unit: deg}\n"
       << "        theta: {value: 2, unit: deg}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial velocity of body frame relative to NED:\n"
       << "        frame: cube\n"
       << "        u: {value: 0, unit: m/s}\n"
       << "        v: {value: 0, unit: m/s}\n"
       << "        w: {value: 0, unit: m/s}\n"
       << "        p: {value: 0, unit: rad/s}\n"
       << "        q: {value: 0, unit: deg/s}\n"
       << "        r: {value: 0, unit: rad/s}\n"
       << "    dynamics:\n"
       << "        centre of inertia:\n"
       << "            frame: cube\n"
       << "            x: {value: 0, unit: m}\n"
       << "            y: {value: 0, unit: m}\n"
       << "            z: {value: 0.4, unit: m}\n"
       << "        mass: {value: 750, unit: kg}\n"
       << "        rigid body inertia matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: cube\n"
       << "            row 1: [83.33,0,0,0,0,0]\n"
       << "            row 2: [0,83.33,0,0,0,0]\n"
       << "            row 3: [0,0,83.33,0,0,0]\n"
       << "            row 4: [0,0,0,83.33,0,0]\n"
       << "            row 5: [0,0,0,0,83.33,0]\n"
       << "            row 6: [0,0,0,0,0,83.33]\n"
       << "        added mass matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: cube\n"
       << "            row 1: [0,0,0,0,0,0]\n"
       << "            row 2: [0,0,0,0,0,0]\n"
       << "            row 3: [0,0,0,0,0,0]\n"
       << "            row 4: [0,0,0,0,0,0]\n"
       << "            row 5: [0,0,0,0,0,0]\n"
       << "            row 6: [0,0,0,0,0,0]\n"
       << "    external forces:\n"
       << "      - model: gravity\n"
       << "      - model: non-linear hydrostatic\n"
       << "\n"
       << "points:\n"
       << "  - name: P\n"
       << "    frame: cube\n"
       << "    x: {value: 0, unit: m}\n"
       << "    y: {value: 0, unit: m}\n"
       << "    z: {value: 0, unit: m}\n"
       << "\n"
       << "blocked degrees of freedom body/NED->body: []\n"
       << "\n"
       << "outputs:\n"
       << "    positions:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    angles:\n"
       << "      - frame: cube\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    linear velocities:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,y]\n"
       << "    angular velocities:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y,z]\n"
       << "    linear accelerations:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular accelerations:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: cube\n"
       << "        #  = p,q\n"
       << "        axes: [x,y]\n"
       << "    forces and torques:\n"
       << "      - type: non-linear hydrostatic\n"
       << "        point name: centre of inertia\n"
       << "        point frame: cube\n"
       << "        projected in frame: NED\n"
       << "        axes: [X, Y, Z, K, M, N]\n"
       << "\n";
    return ss.str();
}

std::string test_data::anthineas_hydrostatic_test()
{
    std::stringstream ss;
    ss << "rotations:\n"
       << "    order by: angle\n"
       << "    convention: [z,y',x'']\n"
       << "\n"
       << "environmental constants:\n"
       << "    g: {value: 9.81, unit: m/s^2}\n"
       << "    rho: {value: 1025, unit: kg/m^3}\n"
       << "environment models:\n"
       << "  - model: no waves\n"
       << "    constant wave height in NED frame: {value: 0, unit: m}\n"
       << "  - model: no wind\n"
       << "    \n"
       << "# Fixed frame: NED\n"
       << "bodies: # All bodies have NED as parent frame\n"
       << "  - name: Anthineas\n"
       << "    mesh: anthineas.stl\n"
       << "    position of body frame relative to mesh:\n"
       << "        frame: mesh\n"
       << "        x: {value: 9.355, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: -3.21, unit: m}\n"
       << "        phi: {value: 0, unit: rad}\n"
       << "        theta: {value: 0, unit: rad}\n"
       << "        psi: {value: 0, unit: rad}\n"
       << "    initial position of body frame relative to NED:\n"
       << "        frame: NED\n"
       << "        x: {value: 0, unit: m}\n"
       << "        y: {value: 0, unit: m}\n"
       << "        z: {value: -5, unit: m}\n"
       << "        phi: {value: 0, unit: deg}\n"
       << "        theta: {value: -.0058, unit: rad}\n"
       << "        psi: {value: 0, unit: deg}\n"
       << "    initial velocity of body frame relative to NED:\n"
       << "        frame: body 1\n"
       << "        u: {value: 0, unit: m/s}\n"
       << "        v: {value: 0, unit: m/s}\n"
       << "        w: {value: 0, unit: m/s}\n"
       << "        p: {value: 0, unit: rad/s}\n"
       << "        q: {value: 0, unit: rad/s}\n"
       << "        r: {value: 0, unit: rad/s}\n"
       << "    dynamics:\n"
       << "        centre of inertia:\n"
       << "            frame: body 1\n"
       << "            x: {value: 0.258, unit: m}\n"
       << "            y: {value: 0, unit: m}\n"
       << "            z: {value: 0.432, unit: m}\n"
       << "        mass: {value: 253.31, unit: tonne} # Caution: 'ton' is the british ton which is 907.185 kg\n"
       << "        rigid body inertia matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: body 1\n"
       << "            row 1: [253310,0,0,0,0,0]\n"
       << "            row 2: [0,253310,0,0,0,0]\n"
       << "            row 3: [0,0,253310,0,0,0]\n"
       << "            row 4: [0,0,0,1.522e6,0,0]\n"
       << "            row 5: [0,0,0,0,8.279e6,0]\n"
       << "            row 6: [0,0,0,0,0,7.676e6]\n"
       << "        added mass matrix at the center of buoyancy projected in the body frame:\n"
       << "            frame: body 1\n"
       << "            row 1: [3.519e4,0,0,0,0,0]\n"
       << "            row 2: [0,3.023e5,0,0,0,0]\n"
       << "            row 3: [0,0,1.980e5,0,0,0]\n"
       << "            row 4: [0,0,0,3.189e5,0,0]\n"
       << "            row 5: [0,0,0,0,8.866e6,0]\n"
       << "            row 6: [0,0,0,0,0,6.676e6]\n"
       << "    external forces:\n"
       << "      - model: gravity\n"
       << "      - model: non-linear hydrostatic\n"
       << "    \n"
       << "\n"
       << "points:\n"
       << "  - name: P\n"
       << "    frame: body 1\n"
       << "    x: {value: 10, unit: m}\n"
       << "    y: {value: 10, unit: m}\n"
       << "    z: {value: 20, unit: m}\n"
       << "  - name: O\n"
       << "    frame: NED\n"
       << "    x: {value: 0, unit: m}\n"
       << "    y: {value: 0, unit: m}\n"
       << "    z: {value: 0, unit: m}\n"
       << "\n"
       << "blocked degrees of freedom body/NED->body:\n"
       << "   - body: body 1\n"
       << "     blocked: []\n"
       << "outputs:\n"
       << "    positions:\n"
       << "      - point: O\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,z]\n"
       << "    angles:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y,z]\n"
       << "    linear velocities:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular velocities:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "    linear accelerations:\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        axes: [x,y]\n"
       << "      - point: P\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: NED\n"
       << "        axes: [z]\n"
       << "    angular accelerations:\n"
       << "      - frame: body 1\n"
       << "        relative to frame: NED\n"
       << "        projected in frame: body 1\n"
       << "        #  = p,q\n"
       << "        axes: [x,y]\n"
       << "    forces and torques:\n"
       << "      - type: non-linear hydrostatic\n"
       << "        point name: centre of inertia\n"
       << "        point frame: body 1\n"
       << "        projected in frame: NED\n"
       << "        axes: [X, Z, K, N]\n";

    return ss.str();
}

