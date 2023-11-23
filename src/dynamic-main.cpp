#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void* libHandle = NULL;

float (*Pi)(int) = NULL;
int (*GCF)(int, int) = NULL;

using ptr_pi = float (*)(int);
using ptr_gcf = int (*)(int, int);

namespace Commands {
    const int Contract = 0;
    const int PI = 1;
    const int GCF = 2;
    const int EXIT = -1;
}

namespace Mode {
    const bool FIRST = 0;
    const bool SECOND = 1;
}

namespace LibsPath {
    const char * LIB1 = "../build/liblib1.so";
    const char * LIB2 = "../build/liblib2.so";
}

bool mode = Mode::SECOND;

void tokenize(std::vector<int> &args, const std::string &input) {
    std::stringstream ss(input);
    std::string s;
    while (std::getline(ss, s, ' ')) {
        args.push_back(std::stoi(s));
    }
}

void messageToUser() {
    std::cout << "~ Hello, world! ~" << std::endl;
    std::cout << "~ You in a dynamic-main.cpp ~" << std::endl;
    std::cout << "~ You can use 4 commands ~" << std::endl;
    std::cout << "~ Enter 0 to change contract ~" << std::endl;
    std::cout << "~ Enter 1 and the number - the length of the series (calculation accuracy) to find the approximate value of Pi ~" << std::endl;
    std::cout << "~ Enter 2 and two numbers to find GCF of them ~" << std::endl;
    std::cout << "~ Enter -1 to stop programm ~" << std::endl;
}

void loadDynamicLib(const bool contract) {
    switch (contract) {
        case Mode::FIRST: {
	        libHandle = dlopen(LibsPath::LIB1, RTLD_LAZY);
	        break;
        }
        case Mode::SECOND:{
	        libHandle = dlopen(LibsPath::LIB2, RTLD_LAZY);
	        break;
        }
    }
    if (libHandle == NULL){
	    perror("dlopen");
	    exit(EXIT_FAILURE);
    }
}

void loadContract() {
    loadDynamicLib(mode);
    Pi = (ptr_pi)dlsym(libHandle, "Pi");
    GCF = (ptr_gcf)dlsym(libHandle, "Pi");
}

void changeContract(){
    dlclose(libHandle);
    switch (mode) {
	    case Mode::FIRST:{
		    mode = Mode::SECOND;
		    break;
	    }
	    case Mode::SECOND:{
	        mode = Mode::FIRST;
	        break;
	    }
    }
    loadContract();
}



int main() {
    loadContract();
    messageToUser();
    std::string input;
    std::vector<int> args;
    while (true) {
        std::getline(std::cin, input, '\n');
        tokenize(args, input);
        int cmd = args[0];
        if (args.size() > 3) {
            std::cout << "Wrong number of args" << std::endl;
            continue;
        }
        switch (cmd) {
            case Commands::PI: {
                std::cout << "Lenght of series = " << args[1] << " Pi = " << Pi(args[1]) << std::endl;
                break;
            }
            case Commands::GCF: {
                std::cout << "Number 1 = " << args[1] << " Number 2 = " << args[2] << " GCF = " << GCF(args[1], args[2]) << std::endl;
                break;
            }
            case Commands::EXIT:
                return -1;
                break;
            case Commands::Contract:
                changeContract();
                std::cout << "Contract changed" << std::endl;
                break;
            default:
                std::cout << "Unknown command" << std::endl;
                break;
        }
        args.clear();
    }
    dlclose(libHandle);
}