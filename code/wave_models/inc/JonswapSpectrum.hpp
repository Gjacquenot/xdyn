/*
 * JonswapSpectrum.hpp
 *
 *  Created on: Jul 30, 2014
 *      Author: cady
 */

#ifndef JONSWAPSPECTRUM_HPP_
#define JONSWAPSPECTRUM_HPP_

#include "WaveSpectrum.hpp"

/** \author cec
 *  \date Jul 30, 2014, 10:03:54 AM
 *  \brief
 *  \details
 *  \ingroup wave_models
 *  \section ex1 Example
 *  \snippet wave_models/unit_tests/src/JonswapSpectrum : public WaveSpectrumTest.cpp JonswapSpectrum : public WaveSpectrumTest example
 *  \section ex2 Expected output
 *  \snippet wave_models/unit_tests/src/JonswapSpectrum : public WaveSpectrumTest.cpp JonswapSpectrum : public WaveSpectrumTest expected output
 */
class JonswapSpectrum : public WaveSpectrum
{
    public:
        /**  \author cec
          *  \date Jul 30, 2014, 10:04:59 AM
          *  \brief JonswapSpectrum's only constructor
          *  \details Default constructor was disabled by making it private & providing no implementation
          *  \snippet module/unit_tests/src/JonswapSpectrumTest.cpp JonswapSpectrumTest method_example
          *  \see "Environmental Conditions and Environmental Loads", April 2014, DNV-RP-C205, Det Norske Veritas AS, page 49
          *  \see "Hydrodynamique des Structures Offshore", 2002, Bernard Molin, Editions TECHNIP, page 43
          */
        JonswapSpectrum(const double Hs,   //!< Significant wave height (in meters)
                        const double Tp,   //!< Mean wave period (in seconds)
                        const double gamma //!< Non-dimensional peak shape parameter
                        );

        /**  \author cec
          *  \date Jul 30, 2014, 9:40:33 AM
          *  \brief Computes the amplitude of the power spectrum at a given angular frequency
          *  \returns Amplitude of the power spectrum (in m^2 s)
          *  \snippet wave_models/unit_tests/src/WaveSpectrumTest.cpp WaveSpectrumTest get_example
          */
        double operator()(const double omega //!< Angular frequency (\f$2\pi f\f$) in rad/s of the significant wave height
                         ) const;


    private:
        double Hs;
        double Tp;
        double gamma;
};

#endif /* JONSWAPSPECTRUM_HPP_ */
