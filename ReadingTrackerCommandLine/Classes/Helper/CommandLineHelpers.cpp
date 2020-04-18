//
//  CommandLineHelpers.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/26/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "CommandLineHelpers.hpp"

std::string rtl::CommandLine::PrintHeaderNumber() {
    return "#: ";
}

std::string rtl::CommandLine::PrintNumberSelector(int number) {
    if (number > 9 || number < 0) {
        BOOST_LOG_TRIVIAL(info) << "Print number selector potential range issue: " << number;
    }
    
    return std::to_string(number) + ": ";
}

void rtl::CommandLine::OutputLine(std::ostream& outputStream, std::string output) {
    outputStream << output << std::endl;
    return;
}

void rtl::CommandLine::OutputLine(std::ostream& outputStream, std::vector<std::string> output) {
    for (std::string x : output) {
        outputStream << x << std::endl;
    }
    return;
}

std::string rtl::CommandLine::GetInput(std::istream& inputStream) {
    std::string returnString;
    std::getline(inputStream, returnString);
    return returnString;
}
