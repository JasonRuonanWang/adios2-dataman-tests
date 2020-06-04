#include <iostream>
#include <thread>
#include <numeric>
#include <vector>
#include "adios2.h"
#include "common.h"

int main(int argc, char **argv)
{
    ParseArgs(argc, argv);

    std::vector<float> myFloats;
    bool initialStep = true;

    std::cout << "Variable size = " << variable_size << std::endl;

    adios2::Params engineParams;
    engineParams["IPAddress"] = ip;
    engineParams["Port"] = port;
    engineParams["TransportMode"] = transport_method;
    engineParams["Monitor"] = "true";

    adios2::ADIOS adios;
    adios2::IO io = adios.DeclareIO("TestIO");
    io.SetEngine("DataMan");
    io.SetParameters(engineParams);

    adios2::Engine engine = io.Open("Test", adios2::Mode::Read);

    while(true)
    {
        auto status = engine.BeginStep();
        if(status == adios2::StepStatus::EndOfStream)
        {
            break;
        }
        auto varFloats = io.InquireVariable<float>("myfloats");
        if(initialStep)
        {
            auto shape = varFloats.Shape();
            myFloats.resize(std::accumulate(shape.begin(), shape.end(), sizeof(float), std::multiplies<size_t>()));
            initialStep = false;
        }

        engine.Get<float>(varFloats, myFloats.data());
        engine.EndStep();

    }

    engine.Close();
    return 0;
}



