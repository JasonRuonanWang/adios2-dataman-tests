#include <iostream>
#include <vector>

#include <adios2.h>

#include "common.h"

int main(int argc, char *argv[])
{

    ParseArgs(argc, argv);

    std::vector<float> myFloats(variable_size);
    for(size_t i=0; i<myFloats.size(); i++)
    {
        myFloats[i]=i;
    }

    adios2::Dims shape({1000000});
    adios2::Dims start({0});
    adios2::Dims count({1000000});

    adios2::Params engineParams;
    engineParams["IPAddress"] = ip;
    engineParams["Port"] = port;
    engineParams["TransportMode"] = transport_method;

    adios2::ADIOS adios;
    adios2::IO io = adios.DeclareIO("TestIO");
    io.SetEngine("DataMan");
    io.SetParameters(engineParams);

    auto varFloats = io.DefineVariable<float>("myfloats", shape, start, count);

    adios2::Engine engine = io.Open("Test", adios2::Mode::Write);

    for(int i=0; i<40; i++)
    {
        engine.Put<float>(varFloats, myFloats.data());
    }

    engine.Close();

    return 0;
}



