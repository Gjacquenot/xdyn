#include "XdynForCS.hpp"
#include "HistoryParser.hpp"
#include "SimServerInputs.hpp"

SimServer::SimServer(const std::string& yaml_model, const std::string& solver, const double dt)
    : builder(yaml_model)
    , dt(dt)
    , stepper(builder, solver, dt)
{
}

std::vector<YamlState> SimServer::play_one_step(const std::string& raw_yaml)
{
    SimServerInputs simstepperinfo = parse_SimServerInputs(raw_yaml, builder.Tmax);
    if (simstepperinfo.Dt <= 0)
    {
        THROW(__PRETTY_FUNCTION__, InvalidInputException, "Dt should be greater than 0 but got Dt = " << simstepperinfo.Dt);
    }
    return stepper.step(simstepperinfo, simstepperinfo.Dt);
}
