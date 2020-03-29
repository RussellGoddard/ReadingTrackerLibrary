//
//  CommandLineHelpers.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/26/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef CommandLineHelpers_hpp
#define CommandLineHelpers_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace rtl::CommandLine {
    std::string PrintHeaderNumber();
    std::string PrintNumberSelector(int number);
    void OutputLine(std::ostream& outputStream, std::string output);
    void OutputLine(std::ostream& outputStream, std::vector<std::string> output);
    std::string GetInput(std::istream& inputStream);
};

#endif /* CommandLineHelpers_hpp */
