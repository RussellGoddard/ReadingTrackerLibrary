//
//  ReadBook.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "ReadBook.hpp"

void ReadBook::setDateRead(time_t time) {
    this->dateRead = *std::gmtime(&time);
    
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
    
    int intMonth = convertAbbrMonthToInt(month);
    
    if (intMonth == -1) {
        return;
    }
    
    this->dateRead.tm_mon = intMonth;
    this->dateRead.tm_mday = stoi(day) - 1; //days are zero based in struct tm
    this->dateRead.tm_year = stoi(year) - 1900;
    
    time_t validateTime = std::mktime(&this->dateRead);
    
    this->dateRead = *std::gmtime(&validateTime);
    
    return;
}

time_t ReadBook::getDateRead() {
    return std::mktime(&dateRead);
}

std::string ReadBook::printDateRead() {
    char buffer [50];
    std::strftime(buffer, 50, "%b %d %Y", &this->dateRead);
    return buffer;
}

//0-10 rating scale
void ReadBook::setRating(int rating) {
    if (rating < 0) {
        rating = 0;
    }
    else if (rating > 10) {
        rating = 10;
    }
    this->rating = rating;
    
    return;
}

int ReadBook::getRating() {
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
std::string ReadBook::printJson() {
    std::string returnString;
    
    returnString = this->Book::printJson(); //get Book as a JSON object
    returnString.pop_back(); //remove ending bracket
    
    //append ReadBook variables
    returnString += R"(,"rating":)" + std::to_string(this->getRating()) + R"(,"dateRead":")" + this->printDateRead() + R"("})";
    
    return returnString;
}

ReadBook::ReadBook(Book book, int rating, time_t time) : Book(book.getAuthor(), book.getTitle(), book.getSeries(), book.getPublisher(), book.getPageCount(), book.getGenre()) {
    this->dateRead = *std::gmtime(&time);
    this->rating = rating;
    
    return;
}

ReadBook::ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, int rating, time_t time) : Book(author, title, series, publisher, pageCount, genre) {
    this->dateRead = *std::gmtime(&time);
    this->rating = rating;
    
    return;
}

ReadBook::ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, int rating, std::string time) : Book(author, title, series, publisher, pageCount, convertStringToGenre(genre)) {
    this->setDateRead(time);
    this->rating = rating;
    
    return;
}
    
