#include <iostream>
#include <numeric>
#include <vector>
#include "adios2.h"
#include "common.h"

void getcb(const void *data, std::string doid, std::string var,
           std::string dtype, std::vector<std::size_t> varshape)
{
    std::cout << "data object ID = " << doid << "\n"; // do you need to flush?
    std::cout << "variable name = " << var << "\n";
    std::cout << "data type = " << dtype << "\n";
    std::size_t varsize = std::accumulate(varshape.begin(), varshape.end(), 1, std::multiplies<std::size_t>());
    if(varsize > 256) varsize = 256;
    for (unsigned int i = 0; i < varsize; ++i)
        std::cout << ((float *)data)[i] << " ";
    std::cout << std::endl;
}

int main(int argc, char **argv)
{

    string local_ip = "0.0.0.0";
    string local_port = "12306";
    string remote_port = "12307";
    ParseArgs(argc, argv);

    // adios
    adios::ADIOS adios(adios::Verbose::WARN, true);
    adios::Method &datamanSettings = adios.DeclareMethod("WAN");
    if (!datamanSettings.IsUserDefined())
    {
        datamanSettings.SetEngine("DataManReader");
        datamanSettings.SetParameters(
                "real_time=yes",
                "method_type=stream",
                "method=" + method,
                "num_channels=" + num_channels,
                "monitoring=yes",
                "local_ip=" + local_ip,
                "remote_ip=" + remote_ip,
                "local_port=" + local_port,
                "remote_port=" + remote_port);
    }

    auto datamanReader = adios.Open("stream", "r", datamanSettings);
    datamanReader->SetCallBack(getcb);
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    datamanReader->Close();
    return 0;
}



