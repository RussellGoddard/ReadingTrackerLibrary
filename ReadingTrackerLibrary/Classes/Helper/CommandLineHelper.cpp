//
//  CommandLineHelper.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/21/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "CommandLineHelper.hpp"

//Author              Date Born   Books Written                               Year
std::string rtl::CommandLine::PrintAuthorCommandLineHeaders()  {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kAuthorWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(kAuthorWidthDateBorn);
    returnStr << std::left << "Date Born";
    returnStr.width(kAuthorWidthTitle);
    returnStr << std::left << "Books Written";
    returnStr.width(kAuthorWidthYear);
    returnStr << std::left << "Year";

    return returnStr.str();
}

/*
Brandon Sanderson   Dec 19 1975 Mistborn: The Final Empire                  2006
                                Mistborn: The Well of Ascension             2007
                                Mistborn: The Hero of Ages                  2008
 */
template <>
std::string rtl::CommandLine::PrintCommandLine(const std::shared_ptr<rtl::Author> input) {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kAuthorWidthAuthor);
    returnStr << std::left << input->GetName().substr(0, kAuthorWidthAuthor - 1);
    returnStr.width(kAuthorWidthDateBorn);
    returnStr << std::left << input->PrintDateBorn().substr(0, kAuthorWidthDateBorn - 1);
    if (!input->GetBooksWritten().empty()) {
        std::vector<std::shared_ptr<rtl::Book>> booksWritten = input->GetBooksWritten();
        returnStr.width(kAuthorWidthTitle);
        returnStr << std::left << booksWritten.at(0)->GetTitle().substr(0, kAuthorWidthTitle - 1);
        returnStr.width(kAuthorWidthYear);
        returnStr << std::left << booksWritten.at(0)->PrintPublishDate().substr(0, 4);
        for (int i = 1; i < booksWritten.size(); ++i) {
            returnStr << std::endl;
            returnStr.width(kAuthorWidthAuthor + kAuthorWidthDateBorn);
            returnStr << std::left << " ";
            returnStr.width(kAuthorWidthTitle);
            returnStr << std::left << booksWritten.at(i)->GetTitle().substr(0, kAuthorWidthTitle - 1);
            returnStr.width(kAuthorWidthYear);
            returnStr << std::left << booksWritten.at(i)->PrintPublishDate().substr(0, 4);
        }
    }
    
    return returnStr.str();
}

//Author              Title                              Series              Pages
std::string rtl::CommandLine::PrintBookCommandLineHeaders() {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kBookWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(kBookWidthTitle);
    returnStr << std::left << "Title";
    returnStr.width(kBookWidthSeries);
    returnStr << std::left << "Series";
    returnStr.width(kBookWidthPage);
    returnStr << std::left << "Pages";
    
    return returnStr.str();
}

//Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541
template <>
std::string rtl::CommandLine::PrintCommandLine(const std::shared_ptr<rtl::Book> input) {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kBookWidthAuthor);
    returnStr << std::left << input->GetAuthor().substr(0, kBookWidthAuthor - 1);
    returnStr.width(kBookWidthTitle);
    returnStr << std::left << input->GetTitle().substr(0, kBookWidthTitle - 1);
    returnStr.width(kBookWidthSeries);
    returnStr << std::left << input->GetSeries().substr(0, kBookWidthSeries - 1);
    returnStr.width(kBookWidthPage);
    returnStr << std::left << std::to_string(input->GetPageCount()).substr(0, kBookWidthPage);
    
    return returnStr.str();
}

//Author              Title                              Pages Date Read    Rating
std::string rtl::CommandLine::PrintReadBookCommandLineHeaders() {
    
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kReadBookWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(kReadBookWidthTitle);
    returnStr << std::left << "Title";
    returnStr.width(kReadBookWidthPage);
    returnStr << std::left << "Pages";
    returnStr.width(kReadBookWidthDateRead);
    returnStr << std::left << "Date Read";
    returnStr.width(kReadBookWidthRating);
    returnStr << std::left << "Rating";
    
    return returnStr.str();
}

//Brandon Sanderson   Mistborn: The Final Empire         541   Sep 13 2019  9
template <>
std::string rtl::CommandLine::PrintCommandLine(const std::shared_ptr<rtl::ReadBook> input) {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kReadBookWidthAuthor);
    returnStr << std::left << input->GetAuthor().substr(0, kReadBookWidthAuthor - 1);
    returnStr.width(kReadBookWidthTitle);
    returnStr << std::left << input->GetTitle().substr(0, kReadBookWidthTitle - 1);
    returnStr.width(kReadBookWidthPage);
    returnStr << std::left << std::to_string(input->GetPageCount()).substr(0, kReadBookWidthPage - 1);
    returnStr.width(kReadBookWidthDateRead);
    returnStr << std::left << input->PrintDateRead().substr(0, kReadBookWidthDateRead - 1);
    returnStr.width(kReadBookWidthRating);
    returnStr << std::left << std::to_string(input->GetRating()).substr(0, kReadBookWidthRating - 1);
    
    return returnStr.str();
}
