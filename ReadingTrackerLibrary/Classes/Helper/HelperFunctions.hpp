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
#include <vector>
#include "SortUnique.hpp"

namespace rtl {
    enum class Genre { genreNotSet, detective, dystopia, fantasy, mystery, romance, scienceFiction, thriller, western, nonFiction, technical };

    Genre ConvertStringToGenre(std::string genre);
    std::string ConvertGenreToString(Genre genre);

    std::string& RightTrim(std::string& input);
    std::string& LeftTrim(std::string& input);
    std::string& Trim(std::string& input);
    std::vector<std::string> splitString(const std::string& input, const std::string& delim);
}

#endif /* HelperFunctions_hpp */
