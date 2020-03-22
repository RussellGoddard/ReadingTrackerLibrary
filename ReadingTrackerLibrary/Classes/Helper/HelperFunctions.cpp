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

std::string rtl::GenerateId(const std::string& input) {
    //input is supposed to be clean/validated before this function
    //split string by word
    //toupper each word
    //convert each word to int * length of word + 13 for each word already done
    //add each int together
    //convert answer to hexadecimal string
    //return string
    
    std::vector<std::string> items;
    std::string token = "";
    std::stringstream ss(input);
    while (std::getline(ss, token, ' ')) {
        items.push_back(std::move(token));
    }
    
    boost::multiprecision::cpp_int id = 1;
    int adder = 13;
    for (std::string x : items) {
        std::transform(std::begin(x), std::end(x), std::begin(x), ::toupper);
        boost::multiprecision::cpp_int word = 0;
        for (char y : x) {
            word += y;
        }
        word *= x.size();
        word += adder;
        adder += 13;
        id *= word;
    }
    
    ss.str(std::string());
    ss.clear();
    ss << std::hex <<  id;
    
    return ss.str();
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
