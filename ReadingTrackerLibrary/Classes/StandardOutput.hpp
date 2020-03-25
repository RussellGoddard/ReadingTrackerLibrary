//
//  StandardOutput.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/24/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef StandardOutput_hpp
#define StandardOutput_hpp

#include <string>

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

    class StandardOutput {
    public:
        virtual std::string PrintJson() const = 0;
        virtual std::string PrintCommandLineSimple() const = 0;
        virtual std::string PrintCommandLineDetailed() const = 0;
        virtual std::string PrintCommandLineHeader() const = 0; //TODO: this really should be static
        
        static std::string GenerateId(const std::string& input) {
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
    };

}


#endif /* StandardOutput_hpp */
