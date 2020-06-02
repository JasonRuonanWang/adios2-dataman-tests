#include <iostream>
#include <numeric>
#include <vector>
#include "adios2.h"
#include "common.h"

int main(int argc, char **argv)
{
    ParseArgs(argc, argv);

    std::vector<float> myFloats(variable_size);

    adios2::Params engineParams;
    engineParams["IPAddress"] = ip;
    engineParams["Port"] = port;
    engineParams["TransportMode"] = transport_method;

    adios2::ADIOS adios;
    adios2::IO io = adios.DeclareIO("TestIO");
    io.SetEngine("DataMan");
    io.SetParameters(engineParams);

    adios2::Engine engine = io.Open("Test", adios2::Mode::Read);

    auto varFloats = io.InquireVariable<float>("myfloats");

    for(int i=0; i<40; i++)
    {
        engine.Get<float>(varFloats, myFloats.data());
    }

    engine.Close();
    return 0;
}



