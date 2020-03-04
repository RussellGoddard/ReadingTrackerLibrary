//
//  ReadBook.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "ReadBook.hpp"

//used for printCommandLine and printCommandLineHeaders
//TODO implement namespaces
int widthAuthorRB = 20;
int widthTitleRB = 35;
int widthPageRB = 6;
int widthDateReadRB = 13;
int widthRatingRB = 6;

void rtlBook::ReadBook::setDateRead(time_t time) {
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

//only reads MMM dd YYYY
void rtlBook::ReadBook::setDateRead(std::string time) {
    if (time.size() != 11) {
        return;
    }
    
    std::string month = time.substr(0, 3);
    std::string day = time.substr(4, 2);
    std::string year = time.substr(7, 4);
    
    int intYear;
    int intMonth = rtlBook::convertAbbrMonthToInt(month);
    int intDay;
    
    if (intMonth == -1) {
        return;
    }
    
    try {
        intDay = stoi(day);
        intYear = stoi(year) - 1900; //TODO HANDLE DATES BEFORE 1970
    }
    catch (std::invalid_argument) {
        //don't change date
        return;
    }
    
    if (intDay <= 0) {
        return;
    }
    else if (intYear <= 0) {
        return;
    }
    
    this->dateRead.tm_year = intYear;
    this->dateRead.tm_mon = intMonth;
    this->dateRead.tm_mday = intDay;
    this->dateRead.tm_sec = 0;
    this->dateRead.tm_min = 0;
    this->dateRead.tm_hour = 0;
    this->dateRead.tm_wday = 0;
    this->dateRead.tm_isdst = 0;
    this->dateRead.tm_gmtoff = 0;
    this->dateRead.tm_zone = nullptr;
    
    time_t validateTime = std::mktime(&this->dateRead);
    
    this->dateRead = *std::gmtime(&validateTime);

    return;
}

//1-10 rating scale
void rtlBook::ReadBook::setRating(int rating) {
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
void rtlBook::ReadBook::setRating(char rating) {
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
void rtlBook::ReadBook::setRating(std::string rating) {
    try {
        int newRating = std::stoi(rating);
        //rating cannot be less than 1, if it is don't change anything
        if (newRating <= 0) {
            return;
        }
        
        this->rating = newRating;
    } catch (std::invalid_argument) {
        //keep rating what it was
    }
    
    return;
}

tm rtlBook::ReadBook::getDateRead() const {
    return this->dateRead;
}

time_t rtlBook::ReadBook::getDateReadAsTimeT() {
    
    return std::mktime(&dateRead);
}

std::string rtlBook::ReadBook::printDateRead() const {
    char buffer [50];
    std::strftime(buffer, 50, "%b %d %Y", &this->dateRead);
    return buffer;
}

int rtlBook::ReadBook::getRating() const {
    return this->rating;
}

int rtlBook::ReadBook::getReaderId() const {
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
std::string rtlBook::ReadBook::printJson() const {
    std::string returnString;
    
    returnString = this->Book::printJson(); //get Book as a JSON object
    returnString.pop_back(); //remove ending bracket
    
    //append ReadBook variables
    returnString += R"(,"rating":)" + std::to_string(this->getRating()) + R"(,"dateRead":")" + this->printDateRead() + R"(","readerId":)" + std::to_string(this->getReaderId()) + R"(})";
    
    return returnString;
}

//Brandon Sanderson   Mistborn: The Final Empire         541   Sep 13 2019  9
std::string rtlBook::ReadBook::printCommandLine() const {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(widthAuthorRB);
    returnStr << std::left << this->getAuthor().substr(0, widthAuthorRB - 1);
    returnStr.width(widthTitleRB);
    returnStr << std::left << this->getTitle().substr(0, widthTitleRB - 1);
    returnStr.width(widthPageRB);
    returnStr << std::left << std::to_string(this->getPageCount()).substr(0, widthPageRB - 1);
    returnStr.width(widthDateReadRB);
    returnStr << std::left << this->printDateRead().substr(0, widthDateReadRB - 1);
    returnStr.width(widthRatingRB);
    returnStr << std::left << std::to_string(this->getRating()).substr(0, widthRatingRB - 1);
    
    return returnStr.str();
}

//Author              Title                              Pages Date Read    Rating
std::string rtlBook::ReadBook::printCommandLineHeaders() {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(widthAuthorRB);
    returnStr << std::left << "Author";
    returnStr.width(widthTitleRB);
    returnStr << std::left << "Title";
    returnStr.width(widthPageRB);
    returnStr << std::left << "Pages";
    returnStr.width(widthDateReadRB);
    returnStr << std::left << "Date Read";
    returnStr.width(widthRatingRB);
    returnStr << std::left << "Rating";
    
    return returnStr.str();
}

rtlBook::ReadBook::ReadBook(int readerId, Book book, int rating, time_t dateRead) : Book(book.getAuthor(), book.getTitle(), book.getSeries(), book.getPublisher(), book.getPageCount(), book.getGenre(), book.getPublishDateAsTimeT()) {
    this->readerId = readerId;
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}

rtlBook::ReadBook::ReadBook(int readerId, Book book, int rating, std::string dateRead) : Book(book.getAuthor(), book.getTitle(), book.getSeries(), book.getPublisher(), book.getPageCount(), book.getGenre(), book.getPublishDateAsTimeT()) {
    this->readerId = readerId;
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}


rtlBook::ReadBook::ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, rtlBook::Genre genre, time_t publishDate, int rating, time_t dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->readerId = readerId;
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}

rtlBook::ReadBook::ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->readerId = readerId;
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}
    
bool rtlBook::operator==(const ReadBook& lhs, const ReadBook& rhs) {
    if (lhs.printJson() == rhs.printJson()) {
        return true;
    }
    
    return false;
}

bool rtlBook::operator!=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator==(lhs, rhs);
}

bool rtlBook::operator<(const ReadBook& lhs, const ReadBook& rhs) {
    //see if this can be simplified TODO
    //sort by Book comparison then by dateRead
    //TODO simplify this by calling Book==Book then only compare ReadBook by dateRead
    
    tm lhstm;
    tm rhstm;
    time_t lhstt;
    time_t rhstt;
    
    if (lhs.getAuthor() < rhs.getAuthor()) { return true; }
    else if (lhs.getAuthor() > rhs.getAuthor()) { return false; }
    else {
        if (lhs.getSeries() < rhs.getSeries()) { return true; }
        else if (lhs.getSeries() > rhs.getSeries()) { return false; }
        else {
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

bool rtlBook::operator>(const ReadBook& lhs, const ReadBook& rhs) {
    return operator<(rhs, lhs);
}

bool rtlBook::operator<=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator>(lhs, rhs);
}

bool rtlBook::operator>=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator<(lhs, rhs);
}
