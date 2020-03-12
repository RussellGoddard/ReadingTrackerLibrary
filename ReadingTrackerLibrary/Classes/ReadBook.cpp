//
//  ReadBook.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "ReadBook.hpp"

void rtl::ReadBook::setDateRead(time_t time) {
    this->dateRead = *std::gmtime(&time);
    this->dateRead.tm_sec = 0;
    this->dateRead.tm_min = 0;
    this->dateRead.tm_hour = 0;
    this->dateRead.tm_wday = 0;
    this->dateRead.tm_isdst = 0;
    this->dateRead.tm_gmtoff = 0;
    this->dateRead.tm_zone = nullptr;
    
    return;
}

bool rtl::ReadBook::setDateRead(std::string time) {
    try {
        auto d = boost::gregorian::from_string(time);
        this->dateRead = boost::gregorian::to_tm(d);
    } catch (std::exception& ex) {
        //TODO: add logging
        return false;
    }
    
    return true;
}

//1-10 rating scale
void rtl::ReadBook::setRating(int rating) {
    if (rating < 1) {
        rating = 1;
    }
    else if (rating > 10) {
        rating = 10;
    }
    this->rating = rating;
    
    return;
}

//will result in rating being set to 0
void rtl::ReadBook::setRating(char rating) {
    int newRating = -1;
    std::stringstream sstream;
    
    sstream << rating;
    sstream >> newRating;
    
    //if rating == 0 then failed to convert to an integer or the rating passed was zero which is invalid
    if (newRating >= 1 && newRating <= 10) {
        this->rating = newRating;
    }
    
    return;
}

//will attempt a stoi if it fails set rating to 0
void rtl::ReadBook::setRating(std::string rating) {
    try {
        int newRating = std::stoi(rating);
        //rating cannot be less than 1, if it is don't change anything
        if (newRating <= 0) {
            return;
        }
        
        this->rating = newRating;
    } catch (std::invalid_argument) {
        //TODO: log error
        //keep rating what it was
    }
    
    return;
}

tm rtl::ReadBook::getDateRead() const {
    return this->dateRead;
}

time_t rtl::ReadBook::getDateReadAsTimeT() {
    return std::mktime(&dateRead);
}

std::string rtl::ReadBook::printDateRead() const {
    auto returnDate = boost::gregorian::date_from_tm(this->dateRead);
    return boost::gregorian::to_simple_string(returnDate);
}

int rtl::ReadBook::getRating() const {
    return this->rating;
}

int rtl::ReadBook::getReaderId() const {
    return this->readerId;
}

/*
{
    "author" : "Robert Jordan",
    "title" : "Eye of the World",
    "publisher" : "Tor Books",
    "series" : "The Wheel of Time",
    "genre" : "fantasy",
    "pageCount" : 782,
    "rating" : 9,
    "dateRead" : "Sat Oct 26 18:09:27 2019"
}
*/
std::string rtl::ReadBook::printJson() const {
    std::string returnString;
    
    returnString = this->Book::printJson(); //get Book as a JSON object
    returnString.pop_back(); //remove ending bracket
    
    //append ReadBook variables
    returnString += R"(,"rating":)" + std::to_string(this->getRating()) + R"(,"dateRead":")" + this->printDateRead() + R"(","readerId":)" + std::to_string(this->getReaderId()) + R"(})";
    
    return returnString;
}

//Brandon Sanderson   Mistborn: The Final Empire         541   Sep 13 2019  9
std::string rtl::ReadBook::printCommandLine() const {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(ReadBook::cWidthAuthor);
    returnStr << std::left << this->getAuthor().substr(0, ReadBook::cWidthAuthor - 1);
    returnStr.width(ReadBook::cWidthTitle);
    returnStr << std::left << this->getTitle().substr(0, ReadBook::cWidthTitle - 1);
    returnStr.width(ReadBook::cWidthPage);
    returnStr << std::left << std::to_string(this->getPageCount()).substr(0, ReadBook::cWidthPage - 1);
    returnStr.width(ReadBook::cWidthDateRead);
    returnStr << std::left << this->printDateRead().substr(0, ReadBook::cWidthDateRead - 1);
    returnStr.width(ReadBook::cWidthRating);
    returnStr << std::left << std::to_string(this->getRating()).substr(0, ReadBook::cWidthRating - 1);
    
    return returnStr.str();
}

//Author              Title                              Pages Date Read    Rating
std::string rtl::ReadBook::printCommandLineHeaders() {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(ReadBook::cWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(ReadBook::cWidthTitle);
    returnStr << std::left << "Title";
    returnStr.width(ReadBook::cWidthPage);
    returnStr << std::left << "Pages";
    returnStr.width(ReadBook::cWidthDateRead);
    returnStr << std::left << "Date Read";
    returnStr.width(ReadBook::cWidthRating);
    returnStr << std::left << "Rating";
    
    return returnStr.str();
}

rtl::ReadBook::ReadBook(int readerId, Book book, int rating, time_t dateRead) : Book(book.getAuthor(), book.getTitle(), book.getSeries(), book.getPublisher(), book.getPageCount(), book.getGenre(), book.getPublishDateAsTimeT()) {
    this->readerId = readerId;
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}

rtl::ReadBook::ReadBook(int readerId, Book book, int rating, std::string dateRead) : Book(book.getAuthor(), book.getTitle(), book.getSeries(), book.getPublisher(), book.getPageCount(), book.getGenre(), book.getPublishDateAsTimeT()) {
    this->readerId = readerId;
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}


rtl::ReadBook::ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, rtl::Genre genre, time_t publishDate, int rating, time_t dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->readerId = readerId;
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}

rtl::ReadBook::ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->readerId = readerId;
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}
    
bool rtl::operator==(const ReadBook& lhs, const ReadBook& rhs) {
    if (lhs.printJson() == rhs.printJson()) {
        return true;
    }
    
    return false;
}

bool rtl::operator!=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator==(lhs, rhs);
}

bool rtl::operator<(const ReadBook& lhs, const ReadBook& rhs) {
    //TODO: see if this can be simplified
    //sort by Book comparison then by dateRead
    //TODO: simplify this by calling Book==Book then only compare ReadBook by dateRead
    
    if (lhs.getAuthor() < rhs.getAuthor()) { return true; }
    else if (lhs.getAuthor() > rhs.getAuthor()) { return false; }
    else {
        if (lhs.getSeries() < rhs.getSeries()) { return true; }
        else if (lhs.getSeries() > rhs.getSeries()) { return false; }
        else {
            tm lhstm;
            tm rhstm;
            time_t lhstt;
            time_t rhstt;
            
            lhstm = lhs.getPublishDate();
            lhstt = std::mktime(&lhstm);
            rhstm = rhs.getPublishDate();
            rhstt = std::mktime(&rhstm);
            
            if (lhstt < rhstt) { return true; }
            else if (lhstt > rhstt) { return false; }
            else {
                if (lhs.getTitle() < rhs.getTitle()) { return true; }
                else if (lhs.getTitle() > rhs.getTitle()) { return false; }
                else {
                    lhstm = lhs.getDateRead();
                    lhstt = std::mktime(&lhstm);
                    rhstm = rhs.getDateRead();
                    rhstt = std::mktime(&rhstm);
                    
                    if (lhstt < rhstt) { return true; }
                    else if (rhstt > lhstt) { return false; }
                }
            }
        }
    }
    
    return false;
}

bool rtl::operator>(const ReadBook& lhs, const ReadBook& rhs) {
    return operator<(rhs, lhs);
}

bool rtl::operator<=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator>(lhs, rhs);
}

bool rtl::operator>=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator<(lhs, rhs);
}
