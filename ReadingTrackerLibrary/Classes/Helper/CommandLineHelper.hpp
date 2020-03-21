//
//  CommandLineHelper.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/21/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef CommandLineHelper_hpp
#define CommandLineHelper_hpp

#include <ios>
#include <sstream>
#include <string>
#include "Author.hpp"
#include "ReadBook.hpp"

namespace rtl::CommandLine {

    std::string PrintAuthorCommandLineHeaders();
    std::string PrintBookCommandLineHeaders();
    std::string PrintReadBookCommandLineHeaders();
    template <typename T>
    std::string PrintCommandLine(const std::shared_ptr<T> input);
    template<> std::string PrintCommandLine(const std::shared_ptr<rtl::Author> input);
    template<> std::string PrintCommandLine(const std::shared_ptr<rtl::Book> input);
    template<> std::string PrintCommandLine(const std::shared_ptr<rtl::ReadBook> input);
    
    namespace {
            //used for printCommandLine and printCommandLineHeaders AUTHOR
            const int kAuthorWidthAuthor = 20;
            const int kAuthorWidthDateBorn = 12;
            const int kAuthorWidthTitle = 44;
            const int kAuthorWidthYear = 4;

            //used for printCommandLine and printCommandLineHeaders BOOK
            const int kBookWidthAuthor = 20;
            const int kBookWidthTitle = 35;
            const int kBookWidthSeries = 20;
            const int kBookWidthPage = 5;

            //used for printCommandLine and printCommandLineHeaders READBOOK
            const int kReadBookWidthAuthor = 20;
            const int kReadBookWidthTitle = 35;
            const int kReadBookWidthPage = 6;
            const int kReadBookWidthDateRead = 13;
            const int kReadBookWidthRating = 6;
    }
}

#endif /* CommandLineHelper_hpp */
