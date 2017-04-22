#include "cxxopts.hpp"
using namespace std;

string local_ip = "127.0.0.1";
string local_port = "12306";
string remote_ip = "127.0.0.1";
string remote_port = "12307";
string method = "mdtm";

void ParseArgs(int argc, char **argv){

    cxxopts::Options options("ADIOS2 DataMan Testing", "");
    options.add_options()
        ("i,ip", "IP address to send data to", cxxopts::value<string>())
        ("p,port", "Port to send data to", cxxopts::value<int>())
        ("m,method", "DataMan plugin to use", cxxopts::value<string>())
        ;
    options.parse(argc, argv);

    if(options.count("ip") > 0){
        remote_ip = options["ip"].as<string>();
    }

    if(options.count("port") > 0){
        remote_port = options["port"].as<int>();
    }

    if(options.count("method") > 0){
        method = options["method"].as<string>();
    }
}


