#include "cxxopts.hpp"
using namespace std;

string ip = "127.0.0.1";
string port = "12306";
string transport_method = "fast";
string compression_method = "";
string compression_rate = "6.0";
size_t variable_size = 1024;
size_t steps = 1024;

void ParseArgs(int argc, char **argv){

    cxxopts::Options options("ADIOS2 DataMan Testing", "");
    options.add_options()
        ("i,ip", "IP address to send data to", cxxopts::value<string>())
        ("p,port", "Port to send data to", cxxopts::value<string>())
        ("m,transport_method", "DataMan transport plugin to use", cxxopts::value<string>())
        ("c,compression_method", "DataMan compression plugin to use", cxxopts::value<string>())
        ("r,compression_rate", "Compression rate", cxxopts::value<string>())
        ("s,variable_size", "Variable Size", cxxopts::value<size_t>())
        ("t,steps", "steps", cxxopts::value<size_t>())
        ;
    options.parse(argc, argv);

    if(options.count("ip") > 0){
        ip = options["ip"].as<string>();
    }

    if(options.count("port") > 0){
        port = options["port"].as<string>();
    }

    if(options.count("transport_method") > 0){
        transport_method = options["transport_method"].as<string>();
    }

    if(options.count("compression_method") > 0){
        compression_method = options["compression_method"].as<string>();
    }

    if(options.count("compression_rate") > 0){
        compression_rate = options["compression_rate"].as<string>();
    }

    if(options.count("steps") > 0){
        steps = options["steps"].as<size_t>();
    }

    if(options.count("variable_size") > 0){
        variable_size = options["variable_size"].as<size_t>();
    }
}


