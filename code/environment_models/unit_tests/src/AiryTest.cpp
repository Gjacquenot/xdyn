/*
 * AiryTest.cpp
 *
 *  Created on: Aug 1, 2014
 *      Author: cady
 */

#include "AiryTest.hpp"
#include "Airy.hpp"
#include "BretschneiderSpectrum.hpp"
#include "Cos2sDirectionalSpreading.hpp"
#include "DiracSpectralDensity.hpp"
#include "DiracDirectionalSpreading.hpp"
#include "SumOfWaveSpectralDensities.hpp"
#include "SumOfWaveDirectionalSpreadings.hpp"

#include "discretize.hpp"
#include "YamlWaveModelInput.hpp"
#include "Stretching.hpp"
#define _USE_MATH_DEFINE
#include <cmath>
#define PI M_PI

AiryTest::AiryTest() : a(ssc::random_data_generator::DataGenerator(54200))
{
}

AiryTest::~AiryTest()
{
}

void AiryTest::SetUp()
{
}

void AiryTest::TearDown()
{
}

#define EPS 1E-10
#define BIG_EPS 1E-4


TEST_F(AiryTest, single_frequency_single_direction_at_one_point)
{
    //! [AiryTest example]
    const double psi0 = PI/4;
    const double Hs = 3;
    const double Tp = 10;
    const double omega0 = 2*PI/Tp;
    const double omega_min = a.random<double>().greater_than(0);
    const double omega_max = a.random<double>().greater_than(omega_min);
    const size_t nfreq = a.random<size_t>().between(2,100);
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching s(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi0), omega_min, omega_max, nfreq, s);
    int random_seed = 0;
    const Airy wave(A, random_seed);

    const std::vector<double> x{a.random<double>()};
    const std::vector<double> y{a.random<double>()};
    const double phi = 3.4482969340598712549;
    const double k = 4.*PI*PI/Tp/Tp/9.81;
    //! [AiryTest example]
    //! [AiryTest expected output]
    for (double t = 0 ; t < 3*Tp ; t+=0.1)
    {
        ASSERT_NEAR(-Hs/2*sin(-2*PI/Tp*t+k*(x.at(0)*cos(psi0)+y.at(0)*sin(psi0)) +phi), wave.elevation(x,y,t).at(0), 1E-6);
    }
    //! [AiryTest expected output]
}

TEST_F(AiryTest, two_frequencies_single_direction_at_one_point)
{
    const double psi0 = PI/4;
    const double Hs = 3;
    const double Tp = 10;
    const double omega0 = 2*PI/Tp;
    const double omega_min = 0.01;
    const double omega_max = 10;
    const size_t nfreq = 50;
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching s(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs)+DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi0), omega_min, omega_max, nfreq, s);
    int random_seed = 0;
    const Airy wave(A, random_seed);

    const std::vector<double> x{a.random<double>()};
    const std::vector<double> y{a.random<double>()};
    const double phi = 3.4482969340598712549;
    const double k = 4.*PI*PI/Tp/Tp/9.81;
    for (double t = 0 ; t < 3*Tp ; t+=0.1)
    {
        ASSERT_NEAR(-Hs/sqrt(2)*sin(-2*PI/Tp*t + k*(x.at(0)*cos(psi0)+y.at(0)*sin(psi0)) +phi), wave.elevation(x,y,t).at(0), 1E-6);
    }
}

TEST_F(AiryTest, one_frequency_two_directions_at_one_point)
{
    const double psi0 = PI/4;
    const double Hs = 3;
    const double Tp = 10;
    const double omega0 = 2*PI/Tp;
    const double omega_min = 0.01;
    const double omega_max = 10;
    const size_t nfreq = 50;
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching s(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi0)+DiracDirectionalSpreading(psi0), omega_min, omega_max, nfreq, s);
    int random_seed = 0;
    const Airy wave(A, random_seed);

    const std::vector<double> x{a.random<double>()};
    const std::vector<double> y{a.random<double>()};
    const double phi = 3.4482969340598712549;
    const double k = 4.*PI*PI/Tp/Tp/9.81;
    for (double t = 0 ; t < 3*Tp ; t+=0.1)
    {
        ASSERT_NEAR(-Hs/sqrt(2)*sin(-2*PI/Tp*t + k*(x.at(0)*cos(psi0)+y.at(0)*sin(psi0)) +phi), wave.elevation(x,y,t).at(0), 1E-6);
    }
}

TEST_F(AiryTest, bug)
{
    const double psi0 = PI;
    const double Hs = 2;
    const double Tp = 7;
    const double s = 1;
    const double omega_min = 0.1;
    const double omega_max = 6;
    const size_t nfreq = 101;
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(BretschneiderSpectrum(Hs, Tp), Cos2sDirectionalSpreading(psi0, s), omega_min, omega_max, nfreq, ss);
    int random_seed = 0;
    const Airy wave(A, random_seed);

    const std::vector<double> x{0};
    const std::vector<double> y{0};
    const double t = 0;

    ASSERT_LT(fabs(wave.elevation(x,y,t).at(0)), 5);

}

TEST_F(AiryTest, dynamic_pressure)
{
    const double psi0 = PI/4;
    const double Hs = 3;
    const double Tp = 10;
    const double omega0 = 2*PI/Tp;
    const double omega_min = a.random<double>().greater_than(0);
    const double omega_max = a.random<double>().greater_than(omega_min);
    const size_t nfreq = a.random<size_t>().between(2,100);
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi0), omega_min, omega_max, nfreq, ss);
    int random_seed = 0;
    const Airy wave(A, random_seed);

    const double x = a.random<double>().between(-100,100);
    const double y = a.random<double>().between(-100,100);
    const double z = a.random<double>().between(0,100);
    const double phi = 3.4482969340598712549;
    const double rho = 1024;
    const double g = 9.81;
    const double k = 4.*PI*PI/Tp/Tp/g;

    for (double t = 0 ; t < 3*Tp ; t+=0.1)
    {
        const double eta = 0;
        ASSERT_NEAR(Hs/2*rho*g*exp(-k*z)*sin(-2*PI/Tp*t + k*(x*cos(psi0)+y*sin(psi0)) +phi), wave.dynamic_pressure(rho,g,x,y,z,eta,t), 1E-6);
    }
}

TEST_F(AiryTest, validate_elevation_formula_against_results_from_sos)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2*PI/Tp;
    double psi = 0;
    double phi = 5.8268;
    double t = 0;
    const double g = 9.81;
    const double k = omega0*omega0/g;
    double x=-0.1; double y=0;
    ASSERT_NEAR(0.045232, Hs/2*cos(omega0*t-k*(x*cos(psi)+y*sin(psi))+phi), BIG_EPS);
    x=0.1;y=0;
    ASSERT_NEAR(0.044522, Hs/2*cos(omega0*t-k*(x*cos(psi)+y*sin(psi))+phi), BIG_EPS);
    x=0;y=-0.1;
    ASSERT_NEAR(0.044883, Hs/2*cos(omega0*t-k*(x*cos(psi)+y*sin(psi))+phi), BIG_EPS);
    x=0;y=0.1;
    ASSERT_NEAR(0.044883, Hs/2*cos(omega0*t-k*(x*cos(psi)+y*sin(psi))+phi), BIG_EPS);
    x=0;y=0;
    ASSERT_NEAR(0.044883, Hs/2*cos(omega0*t-k*(x*cos(psi)+y*sin(psi))+phi), BIG_EPS);
}

TEST_F(AiryTest, should_be_able_to_reproduce_results_from_sos_stab)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2*PI/Tp;
    double psi = 0;
    double phi = 5.8268;
    double t = 0;

    const double omega_min = a.random<double>().greater_than(0);
    const double omega_max = a.random<double>().greater_than(omega_min);
    const size_t nfreq = a.random<size_t>().between(2,100);
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, ss);
    const Airy wave(A, phi);

    std::vector<double> x{-0.1}; std::vector<double> y{0};
    EXPECT_NEAR(0.022754911240680714, wave.elevation(x,y,t).at(0), BIG_EPS);
    x.at(0)=0.1;y.at(0)=0;
    EXPECT_NEAR(0.021310005003521912, wave.elevation(x,y,t).at(0), BIG_EPS);
    x.at(0)=0;y.at(0)=-0.1;
    EXPECT_NEAR(0.022035312958930367, wave.elevation(x,y,t).at(0), BIG_EPS);
    x.at(0)=0;y.at(0)=0.1;
    EXPECT_NEAR(0.022035312958930367, wave.elevation(x,y,t).at(0), BIG_EPS);
    x.at(0)=0;y.at(0)=0;
    EXPECT_NEAR(0.022035312958930367, wave.elevation(x,y,t).at(0), BIG_EPS);
}

TEST_F(AiryTest, dynamic_pressure_compare_with_sos_stab)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2*PI/Tp;
    double psi = 0;
    double phi = 5.8268;
    double t = 0;
    const double rho = 1025;
    const double g = 9.81;

    const double omega_min = a.random<double>().greater_than(0);
    const double omega_max = a.random<double>().greater_than(omega_min);
    const size_t nfreq = a.random<size_t>().between(2,100);
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, ss);
    const Airy wave(A, phi);

    std::vector<double> x{-0.1}; std::vector<double> y{0};
    double z=0.2; double eta = wave.elevation(x,y,t).at(0);
    EXPECT_NEAR(-0.022033996863949721, wave.dynamic_pressure(rho,g,x.at(0),y.at(0),z,eta,t)/rho/g, BIG_EPS);
    x.at(0)=0.1;y.at(0)=0;z=0.2; eta = wave.elevation(x,y,t).at(0);
    EXPECT_NEAR(-0.020634867719409668, wave.dynamic_pressure(rho,g,x.at(0),y.at(0),z,eta,t)/rho/g, BIG_EPS);
    x.at(0)=0;y.at(0)=-0.1;z=0.2; eta = wave.elevation(x,y,t).at(0);
    EXPECT_NEAR(-0.021337196682411571, wave.dynamic_pressure(rho,g,x.at(0),y.at(0),z,eta,t)/rho/g, BIG_EPS);
    x.at(0)=0;y.at(0)=0.1;z=0.2;eta = wave.elevation(x,y,t).at(0);
    EXPECT_NEAR(-0.021337196682411571, wave.dynamic_pressure(rho,g,x.at(0),y.at(0),z,eta,t)/rho/g, BIG_EPS);
    x.at(0)=0;y.at(0)=0;z=0.1;eta = wave.elevation(x,y,t).at(0);
    EXPECT_NEAR(-0.021683445449540293, wave.dynamic_pressure(rho,g,x.at(0),y.at(0),z,eta,t)/rho/g, BIG_EPS);
    x.at(0)=0;y.at(0)=0;z=0.3;eta = wave.elevation(x,y,t).at(0);
    EXPECT_NEAR(-0.020996476935521684, wave.dynamic_pressure(rho,g,x.at(0),y.at(0),z,eta,t)/rho/g, BIG_EPS);
}

TEST_F(AiryTest, norm_of_orbital_velocity_should_only_depend_on_z)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2*PI/Tp;
    double psi = 0;
    double phi = 5.8268;
    double t = 0;
    const double g = 9.81;

    const double omega_min = a.random<double>().greater_than(0);
    const double omega_max = a.random<double>().greater_than(omega_min);
    const size_t nfreq = a.random<size_t>().between(2,100);
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, ss);
    const Airy wave(A, phi);

    ssc::kinematics::Point V;
    for (double z = 100 ; z < 200 ; z+=100)
    {
        double x=0; double y=0;
        ssc::kinematics::Point V = wave.orbital_velocity(g,x,y,z,t,0);
        const double ref = std::sqrt(V.x()*V.x() + V.y()*V.y() + V.z()*V.z());
        for (size_t i = 0 ; i < 100 ; ++i)
        {
            x = a.random<double>().between(-100,100);
            y = a.random<double>().between(-100,100);
            V = wave.orbital_velocity(g,x,y,z,t,0);
            const double norm = std::sqrt(V.x()*V.x() + V.y()*V.y() + V.z()*V.z());
            ASSERT_NEAR(ref, norm, EPS);
        }
    }
}

TEST_F(AiryTest, orbital_velocity_non_regression_test)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2*PI/Tp;
    double psi = PI/3;
    double phi = 5.8268;
    double t = 0;
    const double g = 9.81;

    const double omega_min = a.random<double>().greater_than(0);
    const double omega_max = a.random<double>().greater_than(omega_min);
    const size_t nfreq = a.random<size_t>().between(2,100);
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, ss);
    const Airy wave(A, phi);

    ssc::kinematics::Point V;
    double x=-0.1; double y=0; double z=0.2;
    V = wave.orbital_velocity(g,x,y,z,t,0);
    ASSERT_EQ("NED", V.get_frame());
    EXPECT_NEAR(-0.013625903643418017, V.x(), EPS);
    EXPECT_NEAR(-0.023600757409437876, V.y(), EPS);
    EXPECT_NEAR(0.054396641584981066, V.z(), EPS);
    x=0.1;y=0;z=0.2;
    V = wave.orbital_velocity(g,x,y,z,t,0);
    EXPECT_EQ("NED", V.get_frame());
    EXPECT_NEAR(-0.013186340021821508, V.x(), EPS);
    EXPECT_NEAR(-0.022839410883673743, V.y(), EPS);
    EXPECT_NEAR(0.054828253332012813, V.z(), EPS);
    x=0;y=-0.1;z=0.2;
    V = wave.orbital_velocity(g,x,y,z,t,0);
    EXPECT_EQ("NED", V.get_frame());
    EXPECT_NEAR(-0.013785918416543868, V.x(), EPS);
    EXPECT_NEAR(-0.02387791112645346, V.y(), EPS);
    EXPECT_NEAR(0.054235130955620707, V.z(), EPS);
    x=0;y=0.1;z=0.2;
    V = wave.orbital_velocity(g,x,y,z,t,0);
    EXPECT_EQ("NED", V.get_frame());
    EXPECT_NEAR(-0.013024588330772734, V.x(), EPS);
    EXPECT_NEAR(-0.022559248736567082, V.y(), EPS);
    EXPECT_NEAR(0.054982688288036041, V.z(), EPS);
    x=0;y=0;z=0.1;
    V = wave.orbital_velocity(g,x,y,z,t,0);
    EXPECT_EQ("NED", V.get_frame());
    EXPECT_NEAR(-0.013624110585758166, V.x(), EPS);
    EXPECT_NEAR(-0.023597651742470114, V.y(), EPS);
    EXPECT_NEAR(0.055500467086839214, V.z(), EPS);
    x=0;y=0;z=0.3;
    V = wave.orbital_velocity(g,x,y,z,t,0);
    EXPECT_EQ("NED", V.get_frame());
    EXPECT_NEAR(-0.013192475538380495, V.x(), EPS);
    EXPECT_NEAR(-0.022850037910084588, V.y(), EPS);
    EXPECT_NEAR(0.053742117681957483, V.z(), EPS);
}

TEST_F(AiryTest, orbital_velocity_sanity_check)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2*PI/Tp;

    double t = 0;
    const double g = 9.81;

    const double omega_min = a.random<double>().greater_than(0);
    const double omega_max = a.random<double>().greater_than(omega_min);
    const size_t nfreq = a.random<size_t>().between(2,100);

    const double psi = a.random<double>().between(-PI, PI);
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);


    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, ss);
        const Airy wave(A, a.random<double>().between(-PI,PI));
        const double x=a.random<double>().between(-100,100);
        const double y=a.random<double>().between(-100,100);
        const double z=a.random<double>().between(2,5);
        const ssc::kinematics::Point V = wave.orbital_velocity(g,x,y,z,t,0);
        ASSERT_NEAR(std::abs(cos(psi)),std::abs(V.x()/hypot(V.x(),V.y())), EPS) << "i = " << i;
        ASSERT_NEAR(std::abs(sin(psi)),std::abs(V.y()/hypot(V.x(),V.y())), EPS) << "i = " << i;
    }
}

TEST_F(AiryTest, orbital_velocity_and_elevation_should_have_opposite_signs)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2*PI/Tp;

    double t = 0;
    const double g = 9.81;

    const double omega_min = a.random<double>().greater_than(0);
    const double omega_max = a.random<double>().greater_than(omega_min);
    const size_t nfreq = a.random<size_t>().between(2,100);

    const double psi = a.random<double>().between(0, PI/4);
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);


    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, ss);
        const Airy wave(A, a.random<double>().between(-PI,PI));
        const std::vector<double> x{a.random<double>().between(-100,100)};
        const std::vector<double> y{a.random<double>().between(-100,100)};
        const double z=a.random<double>().between(2,5);
        const ssc::kinematics::Point V = wave.orbital_velocity(g, x.at(0), y.at(0), z, t, 0);
        const double eta = wave.elevation(x, y, t).at(0);
        ASSERT_LE(V.x()*eta,0);
        ASSERT_LE(V.y()*eta,0);
    }

}

TEST_F(AiryTest, should_get_different_results_when_using_two_different_spectra)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2*PI/Tp;
    const double psi = 2*PI/3;
    const double omega_min = 0;
    const double omega_max = 10;
    const size_t nfreq = 11;
    YamlStretching y;
    y.h = 0;
    y.delta = 1;
    const Stretching s(y);
    const DiscreteDirectionalWaveSpectrum A1 = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, s);
    const DiscreteDirectionalWaveSpectrum A2 = discretize(DiracSpectralDensity(omega0, 10*Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, s);
    const Airy wave1(A1, 0);
    const Airy wave2(A2, 0);
    const std::vector<double> rao_module = {1};// {{1,2,3},{4,5,6},{7,8,9},{0,1,2},{3,4,5},{6,7,8},{9,0,1},{2,3,4},{5,6,7},{8,9,0}};
    const std::vector<double> rao_phase = {9}; //{{9,8,7},{6,5,4},{1,4,7},{8,5,2},{7,5,3},{1,5,9},{4,5,6},{7,8,9},{6,5,4},{4,8,6}};

    ASSERT_GT(std::abs(wave1.evaluate_rao(4,5,6,rao_module,rao_phase)-wave2.evaluate_rao(4,5,6,rao_module,rao_phase)), 1E-6);
}

/**
 * \code{.py}
 * from math import pi, cos, sin
 * phase = 0.0
 * Hs = 0.1
 * Tp = 5
 * omega = 2 * pi / Tp
 * psi = 2 * pi / 3.0
 * x = 4
 * y = 5
 * t = 6
 * rao_module = 1
 * rao_phase = 9
 * cos_psi = cos(psi)
 * sin_psi = sin(psi)
 * k = omega * omega / 9.81
 * a = Hs / 2.0
 * result = rao_module * a * cos(-omega * t + k * (x * cos_psi + y * sin_psi) + rao_phase + phase)
 * \endcode
 */
TEST_F(AiryTest, RAO_non_regression_test)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2.0 * PI / Tp;
    const double psi = 2.0 * PI / 3.0;
    const double omega_min = 0;
    const double omega_max = 10;
    const size_t nfreq = 11;
    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const Stretching ss(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, ss);
    const Airy wave(A, 0.0);
    const std::vector<double> rao_module = {1};// {{1,2,3},{4,5,6},{7,8,9},{0,1,2},{3,4,5},{6,7,8},{9,0,1},{2,3,4},{5,6,7},{8,9,0}};
    const std::vector<double> rao_phase = {9}; //{{9,8,7},{6,5,4},{1,4,7},{8,5,2},{7,5,3},{1,5,9},{4,5,6},{7,8,9},{6,5,4},{4,8,6}};
    ASSERT_NEAR(-0.048261600164461897, wave.evaluate_rao(4,5,6,rao_module,rao_phase), 1E-6);
}

TEST_F(AiryTest, should_respect_dirac_inputs)
{
    const double Hs = 0.1;
    const double Tp = 5;
    const double omega0 = 2.0 * PI / Tp;
    const double psi = 2.0 * PI / 3.0;
    const double omega_min = 0;
    const double omega_max = 10;
    const size_t nfreq = 11;
    YamlStretching ys;
    const Stretching ss(ys);
    const DiscreteDirectionalWaveSpectrum A = discretize(DiracSpectralDensity(omega0, Hs), DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, ss);
    const Airy wave(A, 0.0);
    FlatDiscreteDirectionalWaveSpectrum s = wave.get_spectrum();
    ASSERT_EQ(1, s.a.size());
    ASSERT_EQ(1, s.omega.size());
    ASSERT_EQ(1, s.psi.size());
    ASSERT_EQ(1, s.cos_psi.size());
    ASSERT_EQ(1, s.sin_psi.size());
    ASSERT_EQ(1, s.k.size());
    ASSERT_EQ(1, s.phase.size());
    ASSERT_NEAR(Hs/2.0, s.a[0], 1e-10);
    ASSERT_NEAR(omega0, s.omega[0], 1e-10);
    ASSERT_NEAR(psi, s.psi[0], 1e-10);
    ASSERT_NEAR(cos(psi), s.cos_psi[0], 1e-10);
    ASSERT_NEAR(sin(psi), s.sin_psi[0], 1e-10);
    ASSERT_NEAR(omega0 * omega0 / 9.81, s.k[0], 1e-10);
    ASSERT_NEAR(0.0, s.phase[0], 1e-10);
}

TEST_F(AiryTest, orbital_velocities_and_dynamic_pressure_should_decrease_with_depth_in_finite_depth)
{
    const double Hs = 1;
    const double Tp = 5;
    const double psi = 0;
    const double omega0 = 2*PI/Tp;
    const double g = 9.81;
    const double rho = 1000;

    const double omega_min = 0.1;
    const double omega_max = 10;
    const size_t nfreq = 100;


    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const double h = 40;
    const double t = 0;
    const Stretching stretching(ys);
    const DiracSpectralDensity S(omega0, Hs);
    const DiscreteDirectionalWaveSpectrum A = discretize(S, DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, h, stretching);
    const double random_phase = a.random<double>().between(-PI,PI);
    const Airy wave(A, random_phase);
    const double k = S.get_wave_number(omega0,h);

    const std::vector<double> x{a.random<double>().between(-10, 10)};
    const std::vector<double> y{a.random<double>().between(-10, 10)};

    const double z1 = 1;
    const double z2 = 30;

    const double eta = wave.elevation(x, y, t).at(0);
    const ssc::kinematics::Point V1 = wave.orbital_velocity(g, x.at(0), y.at(0), z1, t, eta);
    const ssc::kinematics::Point V2 = wave.orbital_velocity(g, x.at(0), y.at(0), z2, t, eta);
    const double pdyn1 = wave.dynamic_pressure(rho, g, x.at(0), y.at(0), z1, eta, t);
    const double pdyn2 = wave.dynamic_pressure(rho, g, x.at(0), y.at(0), z2, eta, t);

    const double eps=1E-6;

    ASSERT_NEAR(cosh(k*(h-z1))/cosh(k*(h-z2)),((double)V1.v(0))/((double)V2.v(0)), eps);
    ASSERT_NEAR(cosh(k*(h-z1))/cosh(k*(h-z2)),pdyn1/pdyn2, eps);
    ASSERT_LT(0, rho*g*z1+pdyn1);
    ASSERT_LT(0, rho*g*z2+pdyn2);
    ASSERT_LT(std::abs(pdyn2), std::abs(pdyn1));
    ASSERT_LE(std::abs((double)V2.v(0)),std::abs((double)V1.v(0)));
    ASSERT_LE(std::abs((double)V2.v(1)),std::abs((double)V1.v(1)));
    ASSERT_LE(std::abs((double)V2.v(2)),std::abs((double)V1.v(2)));
    ASSERT_NEAR(sinh(k*(h-z1))/sinh(k*(h-z2)),((double)V1.v(2))/((double)V2.v(2)), eps);
}

TEST_F(AiryTest, orbital_velocities_and_dynamic_pressure_should_decrease_with_depth_in_infinite_depth)
{
    const double Hs = 3;
    const double Tp = 5;
    const double psi = 0;
    const double omega0 = 2*PI/Tp;
    const double g = 9.81;
    const double rho = 1000;

    const double omega_min = 0.1;
    const double omega_max = 10;
    const size_t nfreq = 100;


    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const double t = 0;
    const Stretching stretching(ys);
    const DiracSpectralDensity S(omega0, Hs);
    const DiscreteDirectionalWaveSpectrum A = discretize(S, DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, stretching);
    const double random_phase = a.random<double>().between(-PI,PI);
    const Airy wave(A, random_phase);
    const double k = S.get_wave_number(omega0);

    const std::vector<double> x{a.random<double>().between(-10, 10)};
    const std::vector<double> y{a.random<double>().between(-10, 10)};

    const double z1 = 4;
    const double z2 = 30;

    const double eta = wave.elevation(x, y, t).at(0);
    const ssc::kinematics::Point V1 = wave.orbital_velocity(g, x.at(0), y.at(0), z1, t, eta);
    const ssc::kinematics::Point V2 = wave.orbital_velocity(g, x.at(0), y.at(0), z2, t, eta);
    const double pdyn1 = wave.dynamic_pressure(rho, g, x.at(0), y.at(0), z1, eta, t);
    const double pdyn2 = wave.dynamic_pressure(rho, g, x.at(0), y.at(0), z2, eta, t);
    const double ptot1 = rho*g*z1+pdyn1;
    const double ptot2 = rho*g*z2+pdyn2;

    const double eps=1E-6;

    ASSERT_LT(ptot1, ptot2);
    ASSERT_LT(0, rho*g*z1+pdyn1);
    ASSERT_LT(0, rho*g*z2+pdyn2);
    ASSERT_LT(std::abs(pdyn2), std::abs(pdyn1));
    ASSERT_NEAR(exp(-k*z1)/exp(-k*z2),((double)V1.v(0))/((double)V2.v(0)), eps);
    ASSERT_NEAR(exp(-k*z1)/exp(-k*z2),pdyn1/pdyn2, eps);
    ASSERT_LE(std::abs((double)V2.v(0)),std::abs((double)V1.v(0)));
    ASSERT_LE(std::abs((double)V2.v(1)),std::abs((double)V1.v(1)));
    ASSERT_LE(std::abs((double)V2.v(2)),std::abs((double)V1.v(2)));
    ASSERT_NEAR(exp(-k*z1)/exp(-k*z2),((double)V1.v(2))/((double)V2.v(2)), eps);
}

TEST_F(AiryTest, total_pressure_should_always_be_positive_in_finite_depth)
{
    const double Hs = 3;
    const double Tp = 5;
    const double psi = 0;
    const double omega0 = 2*PI/Tp;
    const double g = 9.81;
    const double rho = 1000;

    const double omega_min = 0.1;
    const double omega_max = 10;
    const size_t nfreq = 100;


    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const double h = 40;
    const double t = 0;
    const Stretching stretching(ys);
    const DiracSpectralDensity S(omega0, Hs);
    const DiscreteDirectionalWaveSpectrum A = discretize(S, DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, h, stretching);
    const double random_phase = a.random<double>().between(-PI,PI);
    const Airy wave(A, random_phase);

    const size_t n = 100;
    for (size_t i = 0 ; i < n ; ++i)
    {
        const std::vector<double> x{a.random<double>().between(-100, 100)};
        const std::vector<double> y{a.random<double>().between(-100, 100)};
        const double eta = wave.elevation(x, y, t).at(0);
        const double z = eta + (h-eta)*((double)i)/((double)(n-1));
        ASSERT_LE(0, rho * g * z + wave.dynamic_pressure(rho, g, x.at(0), y.at(0), z, eta, t));
    }
}

TEST_F(AiryTest, total_pressure_should_always_be_positive_in_infinite_depth)
{
    const double Hs = 3;
    const double Tp = 5;
    const double psi = 0;
    const double omega0 = 2*PI/Tp;
    const double g = 9.81;
    const double rho = 1000;

    const double omega_min = 0.1;
    const double omega_max = 10;
    const size_t nfreq = 100;


    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const double t = 0;
    const Stretching stretching(ys);
    const DiracSpectralDensity S(omega0, Hs);
    const DiscreteDirectionalWaveSpectrum A = discretize(S, DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, stretching);
    const double random_phase = a.random<double>().between(-PI,PI);
    const Airy wave(A, random_phase);

    const size_t n = 100;
    for (size_t i = 0 ; i < n ; ++i)
    {
        const std::vector<double> x{a.random<double>().between(-100, 100)};
        const std::vector<double> y{a.random<double>().between(-100, 100)};
        const double eta = wave.elevation(x, y, t).at(0);
        const double z = eta + (10000-eta)*((double)i)/((double)(n-1));
        ASSERT_LE(0, rho * g * z + wave.dynamic_pressure(rho, g, x.at(0), y.at(0), z, eta, t));
    }
}

TEST_F(AiryTest, dynamic_pressure_and_orbital_velocities_should_be_0_outside_water_in_finite_depth)
{
    const double Hs = 3;
    const double Tp = 5;
    const double psi = 0;
    const double omega0 = 2*PI/Tp;
    const double g = 9.81;
    const double rho = 1000;

    const double omega_min = 0.1;
    const double omega_max = 10;
    const size_t nfreq = 100;


    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const double t = 0;
    const Stretching stretching(ys);
    const DiracSpectralDensity S(omega0, Hs);
    const double h = 40;
    const DiscreteDirectionalWaveSpectrum A = discretize(S, DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, h, stretching);
    const double random_phase = a.random<double>().between(-PI,PI);
    const Airy wave(A, random_phase);

    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const std::vector<double> x{a.random<double>().between(-100, 100)};
        const std::vector<double> y{a.random<double>().between(-100, 100)};
        const double eta = wave.elevation(x, y, t).at(0);
        ASSERT_DOUBLE_EQ(0, wave.dynamic_pressure(rho, g, x.at(0), y.at(0), eta - 0.1, eta, t));
        ASSERT_DOUBLE_EQ(0, wave.dynamic_pressure(rho, g, x.at(0), y.at(0), h + 0.1, eta, t));
        ASSERT_DOUBLE_EQ(0, wave.orbital_velocity(g, x.at(0), y.at(0), eta - 0.1, t, eta).v.norm());
        ASSERT_DOUBLE_EQ(0, wave.orbital_velocity(g, x.at(0), y.at(0), h + 0.1, t, eta).v.norm());
        const auto V = wave.orbital_velocity(g, x.at(0), y.at(0), h, t, eta).v;
        ASSERT_DOUBLE_EQ(0, (double)V(2)); // Sea bed is impervious
    }
}

TEST_F(AiryTest, dynamic_pressure_and_orbital_velocities_should_be_0_above_water_in_infinite_depth)
{
    const double Hs = 3;
    const double Tp = 5;
    const double psi = 0;
    const double omega0 = 2*PI/Tp;
    const double g = 9.81;
    const double rho = 1000;

    const double omega_min = 0.1;
    const double omega_max = 10;
    const size_t nfreq = 100;


    YamlStretching ys;
    ys.h = 0;
    ys.delta = 1;
    const double t = 0;
    const Stretching stretching(ys);
    const DiracSpectralDensity S(omega0, Hs);
    const DiscreteDirectionalWaveSpectrum A = discretize(S, DiracDirectionalSpreading(psi), omega_min, omega_max, nfreq, stretching);
    const double random_phase = a.random<double>().between(-PI,PI);
    const Airy wave(A, random_phase);

    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const std::vector<double> x{a.random<double>().between(-100, 100)};
        const std::vector<double> y{a.random<double>().between(-100, 100)};
        const double eta = wave.elevation(x, y, t).at(0);
        ASSERT_DOUBLE_EQ(0, wave.dynamic_pressure(rho, g, x.at(0), y.at(0), eta - 0.1, eta, t));
        ASSERT_DOUBLE_EQ(0, wave.orbital_velocity(g, x.at(0), y.at(0), eta - 0.1, t, eta).v.norm());
    }
}
