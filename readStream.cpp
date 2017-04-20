/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * helloADIOSNoXML_OOP.cpp
 *
 *  Created on: Jan 9, 2017
 *      Author: wfg
 */

#include <iostream>
#include <numeric>
#include <vector>

#include "adios2.h"

void getcb(const void *data, std::string doid, std::string var,
           std::string dtype, std::vector<std::size_t> varshape)
{
    std::cout << "data object ID = " << doid << "\n"; // do you need to flush?
    std::cout << "variable name = " << var << "\n";
    std::cout << "data type = " << dtype << "\n";

    std::size_t varsize = std::accumulate(varshape.begin(), varshape.end(), 1,
                                          std::multiplies<std::size_t>());

    for (unsigned int i = 0; i < varsize; ++i)
        std::cout << ((float *)data)[i] << " ";
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    const bool adiosDebug = true;
    adios::ADIOS adios(adios::Verbose::WARN, adiosDebug);

    try
    {
        adios::Method &datamanSettings = adios.DeclareMethod("WAN");
        if (!datamanSettings.IsUserDefined())
        {
            datamanSettings.SetEngine("DataManReader");
            datamanSettings.SetParameters(
                "real_time=yes",
                "method_type=stream",
                "method=zmq",
                "monitoring=yes",
                "local_ip=127.0.0.1",
                "remote_ip=127.0.0.1",
                "local_port=12307",
                "remote_port=12306");
        }

        auto datamanReader = adios.Open("stream", "r", datamanSettings);

        if (datamanReader == nullptr)
            throw std::ios_base::failure("ERROR: failed to create DataMan I/O engine at Open\n");

        datamanReader->SetCallBack(getcb);

        while(1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        adios::Variable<double> *ioMyDoubles = datamanReader->InquireVariableDouble("ioMyDoubles");
        if (ioMyDoubles == nullptr)
            std::cout << "Variable ioMyDoubles not read...yet\n";

        datamanReader->Close();
    }
    catch (std::invalid_argument &e)
    {
        std::cout << "Invalid argument exception, STOPPING PROGRAM\n";
        std::cout << e.what() << "\n";
    }
    catch (std::ios_base::failure &e)
    {
        std::cout << "System exception, STOPPING PROGRAM\n";
        std::cout << e.what() << "\n";
    }
    catch (std::exception &e)
    {
        std::cout << "Exception, STOPPING PROGRAM\n";
        std::cout << e.what() << "\n";
    }

    return 0;
}
