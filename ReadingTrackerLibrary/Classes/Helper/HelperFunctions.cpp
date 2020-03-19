//
//  HelperFunctions.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/19/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "HelperFunctions.hpp"

//TODO: introduce something to handle ints larger than long long (boost?)
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
    
    unsigned long long id = 1;
    int adder = 13;
    for (std::string x : items) {
        std::transform(std::begin(x), std::end(x), std::begin(x), ::toupper);
        unsigned long long word = 0;
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
