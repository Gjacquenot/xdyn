#include <iostream>
#include <cstdlib> // EXIT_FAILURE, EXIT_SUCCESS

#include <ssc/check_ssc_version.hpp>

#include "utilities_for_InputDataSimServer.hpp"
#include "InputData.hpp"
#include "OptionPrinter.hpp"

std::string description(const std::string& des)
{
    std::stringstream ss;
    ss << des << " created during the project 'Bassin Numerique (IRT Jules Verne)'." << std::endl
       << "(c) SIREHNA 2014-2015." << std::endl
       << std::endl
       << "ID: @GIT_SHA1@" << std::endl
       << "SHA of the SSC used: " << LONG_SSC_GIT_SHA << std::endl
       << std::endl;
    return ss.str();
}

bool invalid(const InputDataSimServer& input)
{
    if (input.empty()) return true;
    if (input.yaml_filenames.empty())
    {
        std::cerr << "Error: no input YAML files defined: need at least one." << std::endl;
        return true;
    }
    if (input.solver.empty())
    {
        std::cerr << "Error: no solver defined." << std::endl;
        return true;
    }
    if (input.initial_timestep<=0)
    {
        std::cerr << "Error: initial time step is negative or zero." << std::endl;
        return true;
    }
    return false;
}

po::options_description get_options_description(InputDataSimServer& input_data)
{
    po::options_description desc("Options");
    desc.add_options()
        ("help,h",                                                                       "Show this help message")
        ("yml,y",      po::value<std::vector<std::string> >(&input_data.yaml_filenames), "Name(s) of the YAML file(s)")
        ("solver,s",   po::value<std::string>(&input_data.solver)->default_value("rk4"), "Name of the solver: euler,rk4,rkck for Euler, Runge-Kutta 4 & Runge-Kutta-Cash-Karp respectively.")
        ("dt",         po::value<double>(&input_data.initial_timestep),                  "Initial time step (or value of the fixed time step for fixed step solvers)")
        ("tstart",     po::value<double>(&input_data.tstart)->default_value(0),          "Date corresponding to the beginning of the simulation (in seconds)")
        ("tend",       po::value<double>(&input_data.tend),                              "Last time step")
        ("output,o",   po::value<std::string>(&input_data.output_filename),              "Name of the output file where all computed data will be exported.\nPossible values/extensions are csv, tsv, json, hdf5, h5, ws")
        ("waves,w",    po::value<std::string>(&input_data.wave_output),                  "Name of the output file where the wave heights will be stored ('output' section of the YAML file). In case output is made to a HDF5 file or web sockets, this option appends the wave height to the main output")
        ("commands,c", po::value<std::string>(&input_data.command_file),                 "Name of the YAML file storing the commands for controlled forces")
        ("debug,d",                                                                      "Used by the application's support team to help error diagnosis. Allows us to pinpoint the exact location in code where the error occurred (do not catch exceptions), eg. for use in a debugger.")
        ("port,p",     po::value<short unsigned int>(&input_data.port),                  "port for the websocket server")
        ;
    return desc;
}

BooleanArguments parse_input(int argc, char **argv, const po::options_description& desc)
{
    po::positional_options_description p;
    p.add("yml", -1);
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc)
                                                 .positional(p)
                                                 .run(), vm);
    po::notify(vm);
    BooleanArguments ret;
    ret.help = vm.count("help")>0;
    ret.debug = vm.count("debug")>0;
    return ret;
}

int get_input_data(int argc, char **argv, InputDataSimServer& input_data)
{
    const po::options_description desc = get_options_description(input_data);
    const BooleanArguments has = parse_input(argc, argv, desc);
    input_data.catch_exceptions = not(has.debug);
    if (has.help)
    {
        print_usage(std::cout, desc, argv[0], "This is a ship simulator");
        return EXIT_SUCCESS;
    }
    else if (invalid(input_data))
    {
        print_usage(std::cout, desc, argv[0], "This is a ship simulator");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int display_help(char *argv, InputDataSimServer& input_data)
{
    const po::options_description desc = get_options_description(input_data);
    print_usage(std::cout, desc, argv, "This is a ship simulator");
    return EXIT_SUCCESS;
}

void print_usage(std::ostream& os, const po::options_description& desc, const std::string& program_name, const std::string& des)
{
    po::positional_options_description positionalOptions;
    os << description(des) << std::endl;
    rad::OptionPrinter::printStandardAppDesc(program_name + " <yaml file>",
                                             os,
                                             desc,
                                             &positionalOptions);
    os << desc << std::endl
       << std::endl;
}

void copy_stream(const std::ostream& from_stream, std::ostream& to_stream)
{
    to_stream.copyfmt(from_stream);                                  //1
    to_stream.clear(from_stream.rdstate());                          //2
    to_stream.basic_ios<char>::rdbuf(from_stream.rdbuf());           //3
}
