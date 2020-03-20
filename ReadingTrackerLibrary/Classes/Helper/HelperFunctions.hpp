//
//  HelperFunctions.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/19/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef HelperFunctions_hpp
#define HelperFunctions_hpp


#include <ios>
#include <string>
#include <sstream>
#include <vector>
#include "SortUnique.hpp"

//below pragma's are taken from https://stackoverflow.com/a/13492589 to suppress warnings from boost
// save diagnostic state
#pragma GCC diagnostic push

// turn off the specific warning
#pragma GCC diagnostic ignored "-Wcomma"
#pragma GCC diagnostic ignored "-Wdocumentation"

#include <boost/multiprecision/cpp_int.hpp>

// turn the warnings back on
#pragma GCC diagnostic pop


namespace rtl {

    std::string GenerateId(const std::string& input);
    std::string& RightTrim(std::string& input);
    std::string& LeftTrim(std::string& input);
    std::string& Trim(std::string& input);

}

#endif /* HelperFunctions_hpp */
