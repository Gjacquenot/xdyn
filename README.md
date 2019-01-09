# X-DYN

[![License](https://img.shields.io/badge/License-EPL%202.0-blue.svg)](https://opensource.org/licenses/EPL-2.0)

X-DYN is a lightweight ship simulator modelling the dynamic behaviour of a ship a ship at sea, with its actuators, including some non-linear aspects of that behaviour and featuring a customizable maneuvring model.
It simulates the mechanical behaviour of a solid body in a fluid environment by
solving Newton's second law of motion, taking hydrodynamic forces into account.

It was developed by SIREHNA during the IRT Jules Verne's ["Bassin Numérique"
project](https://www.irt-jules-verne.fr/wp-content/uploads/bassin-numerique.pdf).

(c) 2014-2015, [IRT Jules Verne](https://www.irt-jules-verne.fr/), [SIREHNA](http://www.sirehna.com/), [Naval Group](https://www.naval-group.com/en/), [Bureau Veritas](https://www.bureauveritas.fr/), [Hydrocean](https://marine-offshore.bureauveritas.com/bvsolutions), [STX France](http://chantiers-atlantique.com/en/), [LHEEA](https://lheea.ec-nantes.fr/) for the initial version.

(c) 2015-2018 [SIREHNA](http://www.sirehna.com/) & [Naval Group](https://www.naval-group.com/en/) for all subsequent versions.

**Disclaimer**: This documentation was written for a French project, with
French participants, therefore it is in French. It will be translated
eventually. Also, please note that it is still a work-in-progress and, as such,
can be incomplete. Despite our best efforts, inaccuracies may remain. However,
the documentation will continue to evolve as new developments on X-DYN are
on-going.

## Getting Started

Pre-built binaries of X-DYN are available:
- [for Windows](https://github.com/sirehna/x-dyn/releases/download/v1.0.0/xdyn.exe)
- [for Debian](https://github.com/sirehna/x-dyn/releases/download/v1.0.0/xdyn.deb).

There are many other ways of using X-DYN, all of which are described in [the documentation]().

The **models** implemented inside X-DYN are described in detail in [this section]() of the documentation.
You can also learn how to use X-DYN using the [tutorials]().

## Building X-DYN from source

This section describes what you need to do if you wish to compile X-DYN
yourself.

### Prerequisites

To build X-DYN, the easiest is to use [Docker](https://www.docker.com/).

Depending on your platform, please refer to:

- [Get Docker CE for CentOS](https://docs.docker.com/install/linux/docker-ce/centos/)
- [Get Docker CE for Debian](https://docs.docker.com/install/linux/docker-ce/debian/)
- [Get Docker CE for Fedora](https://docs.docker.com/install/linux/docker-ce/fedora/)
- [Get Docker CE for Mac](https://docs.docker.com/docker-for-mac/install/)
- [Install Docker for Windows](https://docs.docker.com/docker-for-windows/install/)

You also need [make](https://en.wikipedia.org/wiki/Make_(software)).

### Installing

Once Docker is installed, use:

~~~~~~~{.bash}
make
~~~~~~~

to build both the Windows & the Debian versions.

If you only want one of the two versions, you can use:

~~~~~~~{.bash}
make debian
~~~~~~~

or

~~~~~~~{.bash}
make windows
~~~~~~~

which performs a cross-compilation for Windows using GCC.

The binaries can then be found in `build_windows` or `build_debian`,
respectively.

If you wish to build only part of the project, use:

~~~~~~~{.bash}
./ninja_windows.sh package
~~~~~~~

for example, to build the Windows package (ZIP file containing the XDYN executable)

or

~~~~~~~{.bash}
./ninja_debian.sh run_all_tests
~~~~~~~

to rebuild the Debian tests.

Once the build has finished, you can run the tests.

## Running the tests

To run the tests for Debian use:

~~~~~~~{.bash}
./run_all_tests_debian.sh
~~~~~~~

To run the Windows tests (using Wine in a Docker container) enter:

~~~~~~~{.bash}
./run_all_tests_windows.sh
~~~~~~~

The tests are written using Google test. These are both end-to-end tests and
unit tests. The end-to-end tests can be a bit long so you can disable them
using Google tests filters:

    ./run_all_tests_debian.sh --gtest_filter=-'*LONG*'

All arguments after the script name are passed to the GTest executable. Please
refer to [the Google Test documentation for details and other available
options](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#running-a-subset-of-the-tests).


## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [CMake](https://cmake.org/) - Used to compile C++ code for various platforms.
* [Make](https://www.gnu.org/software/make/) - Used for the one-step build described above.
* [GCC](http://gcc.gnu.org/) - Compiler used for both the Windows & Linux: Visual Studio is currently **not** supported.
* [Boost](https://www.boost.org/) - For command-line options, regular expressions, filesystem library.
* [yaml-cpp](https://github.com/jbeder/yaml-cpp) - To parse the input files.
* [HDF5](https://support.hdfgroup.org/products/hdf5_tools/index.html) - To store the outputs.
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) - For matrix manipulations.
* [Protobuf](https://developers.google.com/protocol-buffers/) - To communicate with a [HOS wave model server](https://github.com/LHEEA/HOS-ocean).
* [ZMQ](http://zeromq.org/) - To communicate with a [HOS wave model server](https://github.com/LHEEA/HOS-ocean).
* [CPP ZMQ](https://github.com/zeromq/cppzmq) - To communicate with a [HOS wave model server](https://github.com/LHEEA/HOS-ocean).
* [Pandoc](https://pandoc.org/) - To generate the documentation.
* [SSC](https://github.com/sirehna/ssc) - For websockets, unit decoding, interpolations, kinematics, CSV file reading, exception handling.

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to submit
issues & pull requests to X-DYN.
Our code of conduct is the [Contributor Covenant](CODE_OF_CONDUCT.md) (original
version available
[here](https://www.contributor-covenant.org/version/1/4/code-of-conduct) ).

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/sirehna/xdyn/tags).

## Authors

* [Charles-Edouard CADY](https://github.com/CharlesEdouardCady)
* [Guillaume JACQUENOT](https://github.com/GuillaumeJacquenot)

See also the list of [contributors](https://github.com/sirehna/xdyn/contributors) who participated in this project.

## License

This project is licensed under the Eclipse Public License (version 2) - see the [LICENSE.md](LICENSE.md) file for details.
