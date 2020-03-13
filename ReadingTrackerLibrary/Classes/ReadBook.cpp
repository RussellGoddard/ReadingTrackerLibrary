//
//  ReadBook.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "ReadBook.hpp"

void rtl::ReadBook::SetDateRead(time_t time) {
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

bool rtl::ReadBook::SetDateRead(std::string time) {
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
void rtl::ReadBook::SetRating(int rating) {
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
void rtl::ReadBook::SetRating(char rating) {
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
void rtl::ReadBook::SetRating(std::string rating) {
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

tm rtl::ReadBook::GetDateRead() const {
    return this->dateRead;
}

time_t rtl::ReadBook::GetDateReadAsTimeT() {
    return std::mktime(&dateRead);
}

std::string rtl::ReadBook::PrintDateRead() const {
    auto returnDate = boost::gregorian::date_from_tm(this->dateRead);
    return boost::gregorian::to_simple_string(returnDate);
}

int rtl::ReadBook::GetRating() const {
    return this->rating;
}

int rtl::ReadBook::GetReaderId() const {
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
std::string rtl::ReadBook::PrintJson() const {
    std::string returnString;
    
    returnString = this->Book::PrintJson(); //get Book as a JSON object
    returnString.pop_back(); //remove ending bracket
    
    //append ReadBook variables
    returnString += R"(,"rating":)" + std::to_string(this->GetRating()) + R"(,"dateRead":")" + this->PrintDateRead() + R"(","readerId":)" + std::to_string(this->GetReaderId()) + R"(})";
    
    return returnString;
}

//Brandon Sanderson   Mistborn: The Final Empire         541   Sep 13 2019  9
std::string rtl::ReadBook::PrintCommandLine() const {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(ReadBook::kWidthAuthor);
    returnStr << std::left << this->GetAuthor().substr(0, ReadBook::kWidthAuthor - 1);
    returnStr.width(ReadBook::kWidthTitle);
    returnStr << std::left << this->GetTitle().substr(0, ReadBook::kWidthTitle - 1);
    returnStr.width(ReadBook::kWidthPage);
    returnStr << std::left << std::to_string(this->GetPageCount()).substr(0, ReadBook::kWidthPage - 1);
    returnStr.width(ReadBook::kWidthDateRead);
    returnStr << std::left << this->PrintDateRead().substr(0, ReadBook::kWidthDateRead - 1);
    returnStr.width(ReadBook::kWidthRating);
    returnStr << std::left << std::to_string(this->GetRating()).substr(0, ReadBook::kWidthRating - 1);
    
    return returnStr.str();
}

//Author              Title                              Pages Date Read    Rating
std::string rtl::ReadBook::PrintCommandLineHeaders() {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(ReadBook::kWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(ReadBook::kWidthTitle);
    returnStr << std::left << "Title";
    returnStr.width(ReadBook::kWidthPage);
    returnStr << std::left << "Pages";
    returnStr.width(ReadBook::kWidthDateRead);
    returnStr << std::left << "Date Read";
    returnStr.width(ReadBook::kWidthRating);
    returnStr << std::left << "Rating";
    
    return returnStr.str();
}

rtl::ReadBook::ReadBook(int readerId, Book book, int rating, time_t dateRead) : Book(book.GetAuthor(), book.GetTitle(), book.GetSeries(), book.GetPublisher(), book.GetPageCount(), book.GetGenre(), book.GetPublishDateAsTimeT()) {
    this->readerId = readerId;
    this->SetDateRead(dateRead);
    this->SetRating(rating);
    
    return;
}

rtl::ReadBook::ReadBook(int readerId, Book book, int rating, std::string dateRead) : Book(book.GetAuthor(), book.GetTitle(), book.GetSeries(), book.GetPublisher(), book.GetPageCount(), book.GetGenre(), book.GetPublishDateAsTimeT()) {
    this->readerId = readerId;
    this->SetDateRead(dateRead);
    this->SetRating(rating);
    
    return;
}


rtl::ReadBook::ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, rtl::Genre genre, time_t publishDate, int rating, time_t dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->readerId = readerId;
    this->SetDateRead(dateRead);
    this->SetRating(rating);
    
    return;
}

rtl::ReadBook::ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->readerId = readerId;
    this->SetDateRead(dateRead);
    this->SetRating(rating);
    
    return;
}
    
bool rtl::operator==(const ReadBook& lhs, const ReadBook& rhs) {
    if (lhs.PrintJson() == rhs.PrintJson()) {
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
    
    if (lhs.GetAuthor() < rhs.GetAuthor()) { return true; }
    else if (lhs.GetAuthor() > rhs.GetAuthor()) { return false; }
    else {
        if (lhs.GetSeries() < rhs.GetSeries()) { return true; }
        else if (lhs.GetSeries() > rhs.GetSeries()) { return false; }
        else {
            tm lhstm;
            tm rhstm;
            time_t lhstt;
            time_t rhstt;
            
            lhstm = lhs.GetPublishDate();
            lhstt = std::mktime(&lhstm);
            rhstm = rhs.GetPublishDate();
            rhstt = std::mktime(&rhstm);
            
            if (lhstt < rhstt) { return true; }
            else if (lhstt > rhstt) { return false; }
            else {
                if (lhs.GetTitle() < rhs.GetTitle()) { return true; }
                else if (lhs.GetTitle() > rhs.GetTitle()) { return false; }
                else {
                    lhstm = lhs.GetDateRead();
                    lhstt = std::mktime(&lhstm);
                    rhstm = rhs.GetDateRead();
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
