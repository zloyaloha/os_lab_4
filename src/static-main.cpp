extern "C" {
    #include "gcf-pi.h"
}

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

extern "C" {
    #include "gcf-pi.h"
}

namespace Commands {
    const int PI = 1;
    const int GCF = 2;
    const int EXIT = -1;
}

void tokenize(std::vector<int> &args, const std::string &input) {
    std::stringstream ss(input);
    std::string s;
    while (std::getline(ss, s, ' ')) {
        args.push_back(std::stoi(s));
    }
}

void messageToUser() {
    std::cout << "~ Hello, world! ~" << std::endl;
    std::cout << "~ You in a static-main.cpp ~" << std::endl;
    std::cout << "~ You can use 3 commands ~" << std::endl;
    std::cout << "~ Enter 1 and the number - the length of the series (calculation accuracy) to find the approximate value of Pi ~" << std::endl;
    std::cout << "~ Enter 2 and two numbers to find GCF of them ~" << std::endl;
    std::cout << "~ Enter -1 to stop programm ~" << std::endl;
}

int main() {
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
            case Commands::PI:
                std::cout << "Lenght of series = " << args[1] << " Pi = " << Pi(args[1]) << std::endl;
                break;
            case Commands::GCF:
                std::cout << "Number 1 = " << args[1] << " Number 2 = " << args[2] << " GCF = " << GCF(args[1], args[2]) << std::endl;
                break;
            case Commands::EXIT:
                return -1;
                break;
            default:
                std::cout << "Unknown command" << std::endl;
                break;
        }
        args.clear();
    }
}