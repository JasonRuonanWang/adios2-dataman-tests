#include "cxxopts.hpp"
using namespace std;

string local_ip = "127.0.0.1";
string remote_ip = "127.0.0.1";
string method = "zmq";
string compression_method = "null";
string compression_rate = "6.0";
string num_channels = "4";

void ParseArgs(int argc, char **argv){

    cxxopts::Options options("ADIOS2 DataMan Testing", "");
    options.add_options()
        ("i,ip", "IP address to send data to", cxxopts::value<string>())
        ("p,port", "Port to send data to", cxxopts::value<string>())
        ("m,method", "DataMan transport plugin to use", cxxopts::value<string>())
        ("c,compression_method", "DataMan compression plugin to use", cxxopts::value<string>())
        ("r,compression_rate", "Compression rate", cxxopts::value<string>())
        ("n,num_channels", "Number of channels", cxxopts::value<string>())
        ;
    options.parse(argc, argv);

    if(options.count("ip") > 0){
        remote_ip = options["ip"].as<string>();
    }

    if(options.count("ip") > 0){
        local_ip = options["ip"].as<string>();
    }

    if(options.count("num_channels") > 0){
        num_channels = options["num_channels"].as<string>();
    }

    if(options.count("method") > 0){
        method = options["method"].as<string>();
    }

    if(options.count("compression_method") > 0){
        compression_method = options["compression_method"].as<string>();
    }

    if(options.count("compression_rate") > 0){
        compression_rate = options["compression_rate"].as<string>();
    }
}


