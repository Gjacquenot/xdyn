#ifndef OBSERVERS_AND_API_INC_SIMSERVER_HPP_
#define OBSERVERS_AND_API_INC_SIMSERVER_HPP_

#include "ConfBuilder.hpp"
#include "SimStepper.hpp"
#include "HistoryParser.hpp"

class SimServer
{
    public :
        SimServer(const std::string& yaml_model,
                  const std::string& solver,
                  const double dt);

        std::vector<YamlState> play_one_step(const std::string& raw_yaml);

    private :
        SimServer();
        ConfBuilder builder;
        const double dt;
        SimStepper stepper;
};

#endif /* OBSERVERS_AND_API_INC_SIMSERVER_HPP_ */
