//
//  HelperFunctions.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/19/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "HelperFunctions.hpp"

rtl::Genre rtl::ConvertStringToGenre(std::string genre) {
    rtl::Genre returnGenre;
    
    if (genre == "detective") { returnGenre = rtl::Genre::detective; }
    else if (genre == "dystopia") { returnGenre = rtl::Genre::dystopia; }
    else if (genre == "fantasy") { returnGenre = rtl::Genre::fantasy; }
    else if (genre == "mystery") { returnGenre = rtl::Genre::mystery; }
    else if (genre == "romance") { returnGenre = rtl::Genre::romance; }
    else if (genre == "science fiction" || genre == "sci fi") { returnGenre = rtl::Genre::scienceFiction; }
    else if (genre == "thriller") { returnGenre = rtl::Genre::thriller; }
    else if (genre == "western") { returnGenre = rtl::Genre::western; }
    else if (genre == "non-fiction" || genre == "nonfiction") { returnGenre = rtl::Genre::nonFiction; }
    else if (genre == "technical") { returnGenre = rtl::Genre::technical; }
    else { returnGenre = rtl::Genre::genreNotSet; }
    return returnGenre;
}

//taken from Effective C++
template<typename E>
constexpr auto toUnderlyingType(E e)
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}

std::string rtl::ConvertGenreToString(rtl::Genre genre) {
    
    std::vector<std::string> genreString { "genre not set", "detective", "dystopia", "fantasy", "mystery", "romance", "science fiction", "thriller", "western", "non-fiction", "technical" };
    
    int index = toUnderlyingType(genre);
    
    return genreString[index];
}

std::string& rtl::LeftTrim(std::string& input) {
  auto it2 =  std::find_if(input.begin(), input.end(), [](char ch){ return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(input.begin(), it2);
  return input;
}

std::string& rtl::RightTrim(std::string& input) {
  auto it1 = std::find_if(input.rbegin(), input.rend(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(it1.base(), input.end());
  return input;
}

std::string& rtl::Trim(std::string& str) {
   return rtl::LeftTrim(rtl::RightTrim(str));
}
