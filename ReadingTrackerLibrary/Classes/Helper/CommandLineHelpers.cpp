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
    if (number > 9 || number < 1) {
        //TODO: log this
    }
    
    return std::to_string(number) + ": ";
}
