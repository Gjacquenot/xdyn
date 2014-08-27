#ifndef YAMLSPECTRAINPUT_HPP_
#define YAMLSPECTRAINPUT_HPP_

struct YamlAiry
{
    YamlAiry();
    int seed; // Random generator ssed (to generate the random phases)
};

struct YamlJonswap
{
    YamlJonswap();
    double Hs;    //!< Significant wave height (in meters)
    double Tp;    //!< Mean wave period (in seconds)
    double gamma; //!< Non-dimensional peak shape parameter
};

struct YamlBretschneider
{
    YamlBretschneider();
    double Hs;    //!< Significant wave height (in meters)
    double Tp;    //!< Mean wave period (in seconds)
};

struct YamlDiracDirectionalSpreading
{
    YamlDiracDirectionalSpreading();
    double psi0; //!< Primary wave direction in radians.
};

struct YamlDiracSpectralDensity
{
    YamlDiracSpectralDensity();
    double omega0; //!< Angular frequency (\f$2\pi f\f$) in rad/s of the significant wave height
    double Hs;     //!< Significant wave height (in meters)
};

struct YamlPiersonMoskowitzSpectralDensity
{
    YamlPiersonMoskowitzSpectralDensity();
    double Hs;   //!< Significant wave height (in meters)
    double Tp;   //!< Mean wave period (in seconds));
};

#endif /* YAMLSPECTRAINPUT_HPP_ */
