#include <iostream>
#include <vector>

#include <adios2.h>

#include "common.h"

int main(int argc, char *argv[])
{

    string local_port = "12307";
    string remote_port = "12306";
    ParseArgs(argc, argv);

    // data
    std::vector<float> myFloats(1024);
    const std::size_t Nx = myFloats.size();
    for(size_t i=0; i<Nx; i++){
        myFloats[i]=i;
    }

    // adios
    adios::ADIOS adios(adios::Verbose::WARN, true);
    auto ioMyFloats = adios.DefineVariable<float>("myfloats", adios::Dims{Nx});
    adios::Method &datamanSettings = adios.DeclareMethod("WAN");
    if (!datamanSettings.IsUserDefined())
    {
        datamanSettings.SetEngine("DataManWriter");
        datamanSettings.SetParameters(
                "real_time=yes",
                "compression_method=" + compression_method,
                "compression_rate=" + compression_rate,
                "method_type=stream",
                "method=" + method,
                "monitoring=no",
                "local_ip=" + local_ip,
                "remote_ip=" + remote_ip,
                "local_port=" + local_port,
                "remote_port=" + remote_port);
    }
    auto datamanWriter = adios.Open("stream", "w", datamanSettings);
    for(int i=0; i<4; i++){
        datamanWriter->Write<float>(ioMyFloats, myFloats.data());
        datamanWriter->Close();
    }
    return 0;
}



