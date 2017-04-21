#include <iostream>
#include <vector>
#include "adios2.h"

using namespace std;

int main(int argc, char *argv[])
{
    string ip="127.0.0.1", port;
    if(argc >= 2){
        ip = argv[1];
        if(argc >= 3){
            port = argv[2];
        }
    }

    adios::ADIOS adios(adios::Verbose::WARN, true);
    std::vector<float> myFloats(1024);
    const std::size_t Nx = myFloats.size();
    for(size_t i=0; i<Nx; i++){
        myFloats[i]=i;
    }

    auto ioMyFloats = adios.DefineVariable<float>("myfloats", adios::Dims{Nx});
    adios::Method &datamanSettings = adios.DeclareMethod("WAN");
    if (!datamanSettings.IsUserDefined())
    {
        datamanSettings.SetEngine("DataManWriter");
        datamanSettings.SetParameters(
                "real_time=yes",
                "method_type=stream",
                "method=zmq",
                "monitoring=no",
                "local_ip=127.0.0.1",
                "remote_ip=" + ip,
                "local_port=12306",
                "remote_port=12307");
    }

    auto datamanWriter = adios.Open("stream", "w", datamanSettings);
    if (datamanWriter == nullptr)
        throw std::ios_base::failure("ERROR: failed to create DataMan I/O engine at Open\n");

    for(int i=0; i<100; i++){
        datamanWriter->Write<float>(ioMyFloats, myFloats.data());
        datamanWriter->Close();
    }
    return 0;
}


