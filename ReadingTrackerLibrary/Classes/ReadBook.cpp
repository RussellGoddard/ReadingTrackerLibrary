//
//  ReadBook.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "ReadBook.hpp"

void ReadBook::setDateRead(time_t time) {
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
void ReadBook::setDateRead(std::string time) {
    if (time.size() != 11) {
        return;
    }
    
    std::string month = time.substr(0, 3);
    std::string day = time.substr(4, 2);
    std::string year = time.substr(7, 4);
    
    int intYear;
    int intMonth = convertAbbrMonthToInt(month);
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
void ReadBook::setRating(int rating) {
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
void ReadBook::setRating(char rating) {
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
void ReadBook::setRating(std::string rating) {
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

tm ReadBook::getDateRead() const {
    return this->dateRead;
}

time_t ReadBook::getDateReadAsTimeT() {
    
    return std::mktime(&dateRead);
}

std::string ReadBook::printDateRead() const {
    char buffer [50];
    std::strftime(buffer, 50, "%b %d %Y", &this->dateRead);
    return buffer;
}

int ReadBook::getRating() const {
    return this->rating;
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
std::string ReadBook::printJson() const {
    std::string returnString;
    
    returnString = this->Book::printJson(); //get Book as a JSON object
    returnString.pop_back(); //remove ending bracket
    
    //append ReadBook variables
    returnString += R"(,"rating":)" + std::to_string(this->getRating()) + R"(,"dateRead":")" + this->printDateRead() + R"("})";
    
    return returnString;
}

ReadBook::ReadBook(Book book, int rating, time_t dateRead) : Book(book.getAuthor(), book.getTitle(), book.getSeries(), book.getPublisher(), book.getPageCount(), book.getGenre(), book.getPublishDateAsTimeT()) {
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}

ReadBook::ReadBook(Book book, int rating, std::string dateRead) : Book(book.getAuthor(), book.getTitle(), book.getSeries(), book.getPublisher(), book.getPageCount(), book.getGenre(), book.getPublishDateAsTimeT()) {
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}


ReadBook::ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, time_t publishDate, int rating, time_t dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}

ReadBook::ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->setDateRead(dateRead);
    this->setRating(rating);
    
    return;
}
    
bool operator==(const ReadBook& lhs, const ReadBook& rhs) {
    if (lhs.printJson() == rhs.printJson()) {
        return true;
    }
    
    return false;
}

bool operator!=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator==(lhs, rhs);
}

bool operator<(const ReadBook& lhs, const ReadBook& rhs) {
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

bool operator>(const ReadBook& lhs, const ReadBook& rhs) {
    return operator<(rhs, lhs);
}

bool operator<=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator>(lhs, rhs);
}

bool operator>=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator<(lhs, rhs);
}
