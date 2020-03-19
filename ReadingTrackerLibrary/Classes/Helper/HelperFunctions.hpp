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

namespace rtl {

    std::string GenerateId(const std::string& input);
    std::string& RightTrim(std::string& input);
    std::string& LeftTrim(std::string& input);
    std::string& Trim(std::string& input);

}

#endif /* HelperFunctions_hpp */
