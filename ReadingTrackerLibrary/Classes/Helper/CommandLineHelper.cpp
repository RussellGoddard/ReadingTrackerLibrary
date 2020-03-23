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
std::string rtl::CommandLine::PrintCommandLineSimple(const std::shared_ptr<rtl::Author> input) {
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

template<> std::string rtl::CommandLine::PrintCommandLineDetailed(const std::shared_ptr<rtl::Author> input) {
    /*
     std::string authorId;
     std::string name;
     struct tm dateBorn;
     std::vector<std::shared_ptr<rtl::Book>> booksWritten;
     */
    
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr << std::left;
    returnStr << std::setw(15) << "Name: " << std::setw(65) << input->GetName().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "AuthorId: " << std::setw(65) << input->GetAuthorId().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Date Born: " << std::setw(65) << input->PrintDateBorn().substr(0, 65) << std::endl;
    returnStr << std::setw(80) << "Books Written:" << std::endl;
    for (auto x : input->GetBooksWritten()) {
        returnStr << rtl::CommandLine::PrintCommandLineDetailed(x);
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
std::string rtl::CommandLine::PrintCommandLineSimple(const std::shared_ptr<rtl::Book> input) {
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

template<> std::string rtl::CommandLine::PrintCommandLineDetailed(const std::shared_ptr<rtl::Book> input) {
    /*
    std::string title;
    std::string bookId;
    std::string author;
    std::string authorId;
    std::string series;
    Genre genre;
    int pageCount;
    std::string publisher;
    tm publishDate;
    std::vector<std::string> isbnVector;
    std::vector<std::string> oclcVector;
     */
    
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr << std::left;
    returnStr << std::setw(15) << "Title: " << std::setw(65) << input->GetTitle().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "BookId: " << std::setw(65) << input->GetBookId().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Author Name: " << std::setw(65) << input->GetAuthor().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "AuthorId: " << std::setw(65) << input->GetAuthorId().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Series: " << std::setw(65) << input->GetSeries().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Genre: " << std::setw(65) << input->PrintGenre().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Page Count: " << std::setw(65) << std::to_string(input->GetPageCount()).substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Publisher: " << std::setw(65) << input->GetPublisher().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Publish Date: " << std::setw(65) << input->PrintPublishDate().substr(0, 65) << std::endl;
    
    returnStr << std::setw(15) << "ISBN: ";
    std::string seperator = "";
    std::string isbnString = "";
    for (auto x : input->GetIsbn()) {
        isbnString += seperator + x;
        seperator = ", ";
    }
    returnStr << std::setw(65) << isbnString.substr(0, 65) << std::endl;
    seperator = "";
    
    returnStr << std::setw(15) << "OCLC: ";
    std::string oclcString = "";
    for (auto x : input->GetOclc()) {
        oclcString += seperator + x;
        seperator = ", ";
    }
    returnStr << std::setw(65) << oclcString.substr(0, 65) << std::endl;
    seperator = "";
    
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
std::string rtl::CommandLine::PrintCommandLineSimple(const std::shared_ptr<rtl::ReadBook> input) {
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

template<> std::string rtl::CommandLine::PrintCommandLineDetailed(const std::shared_ptr<rtl::ReadBook> input)
{
    /*
     std::string readerId
     std::string rating
     tm dateRead
     std::string title;
     std::string bookId;
     std::string author;
     std::string authorId;
     std::string series;
     Genre genre;
     int pageCount;
     std::string publisher;
     tm publishDate;
     std::vector<std::string> isbnVector;
     std::vector<std::string> oclcVector;
     */
    
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr << std::left;
    returnStr << rtl::CommandLine::PrintCommandLineDetailed(static_cast<std::shared_ptr<rtl::Book>>(input));
    returnStr << std::setw(15) << "ReaderId: " << std::setw(65) << input->GetReaderId() << std::endl;
    returnStr << std::setw(15) << "Rating: " << std::setw(65) << input->GetRating() << std::endl;
    returnStr << std::setw(15) << "Date Read: " << std::setw(65) << input->PrintDateRead() << std::endl;
    
    return returnStr.str();
}
