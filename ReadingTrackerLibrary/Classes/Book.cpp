//
//  Book.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "Book.hpp"

int convertAbbrMonthToInt(std::string month) {
    if (month == "Jan") {
        return 0;
    }
    else if (month == "Feb") {
        return 1;
    }
    else if (month == "Mar") {
        return 2;
    }
    else if (month == "Apr") {
        return 3;
    }
    else if (month == "May") {
        return 4;
    }
    else if (month == "Jun") {
        return 5;
    }
    else if (month == "Jul") {
        return 6;
    }
    else if (month == "Aug") {
        return 7;
    }
    else if (month == "Sep") {
        return 8;
    }
    else if (month == "Oct") {
        return 9;
    }
    else if (month == "Nov") {
        return 10;
    }
    else if (month == "Dec") {
        return 11;
    }
    return -1;
}

std::string Book::getAuthor() const {
    return this->author;
}

std::string Book::getTitle() const {
    return this->title;
}

std::string Book::getSeries() const {
    return series;
}

int Book::getPageCount() const {
    return pageCount;
}

std::string Book::getPublisher() const {
    return this->publisher;
}

Genre Book::getGenre() const {
    return genre;
}

std::string Book::printGenre() const {
    return convertGenreToString(this->genre);
}
/*
{
    "author" : "Robert Jordan",
    "title" : "Eye of the World",
    "publisher" : "Tor Books",
    "genre" : "fantasy",
    "pageCount" : 782
}
*/
std::string Book::printJson() const {
    std::string returnString;
    returnString = R"({"author":")" + this->getAuthor() + R"(","title":")" + this->getTitle() + R"(","series":")" + this->getSeries() + R"(","publisher":")" + this->getPublisher() + R"(","genre":")" + this->printGenre() + R"(","pageCount":)" + std::to_string(this->getPageCount()) + R"(})";
    return returnString;
}

time_t Book::getPublishDate() {
    return std::mktime(&this->publishDate);
}

std::string Book::printPublishDate() const {
    char buffer [50];
    std::strftime(buffer, 50, "%b %d %Y", &this->publishDate);
    return buffer;
}

void Book::setAuthor(std::string author) {
    this->author = author;
    
    return;
}

void Book::setTitle(std::string title) {
    this->title = title;
    
    return;
}

void Book::setSeries(std::string series) {
    this->series = series;
    
    return;
}

void Book::setPublisher(std::string publisher) {
    this->publisher = publisher;
    
    return;
}

void Book::setPageCount(int pageCount) {
    this->pageCount = pageCount;
    
    return;
}

void Book::setGenre(Genre genre) {
    this->genre = genre;
    
    return;
}

void Book::setGenre(std::string genre) {
    this->genre = convertStringToGenre(genre);
    
    return;
}

void Book::setPublishDate(time_t publishDate) {
    this->publishDate = *std::gmtime(&publishDate);
    
    return;
}

void Book::setPublishDate(std::string publishDate) {
    if (publishDate.size() != 11) {
        return;
    }
    
    std::string month = publishDate.substr(0, 3);
    std::string day = publishDate.substr(4, 2);
    std::string year = publishDate.substr(7, 4);
    
    int intMonth = convertAbbrMonthToInt(month);
    
    if (intMonth == -1) {
        return;
    }
    
    this->publishDate.tm_mon = intMonth;
    this->publishDate.tm_mday = stoi(day); //days are zero based in struct tm
    this->publishDate.tm_year = stoi(year) - 1900;
    
    time_t validateTime = std::mktime(&this->publishDate);
    
    this->publishDate = *std::gmtime(&validateTime);
    
    return;
}

Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, time_t publishDate) {
    this->author = author;
    this->title = title;
    this->series = series;
    this->publisher = publisher;
    this->pageCount = pageCount;
    this->genre = genre;
    this->publishDate = *std::gmtime(&publishDate);
    
    return;
}

Genre Book::convertStringToGenre(std::string genre) {
    Genre returnGenre;
    
    if (genre == "detective") { returnGenre = detective; }
    else if (genre == "dystopia") { returnGenre = dystopia; }
    else if (genre == "fantasy") { returnGenre = fantasy; }
    else if (genre == "mystery") { returnGenre = mystery; }
    else if (genre == "romance") { returnGenre = romance; }
    else if (genre == "science fiction") { returnGenre = scienceFiction; }
    else if (genre == "thriller") { returnGenre = thriller; }
    else if (genre == "western") { returnGenre = western; }
    else { returnGenre = genreNotSet; }
    return returnGenre;
}

std::string Book::convertGenreToString(Genre genre) {
    std::string returnString;
    switch(genre) {
        case detective:
            returnString = "detective";
            break;
        case dystopia:
            returnString = "dystopia";
            break;
        case fantasy:
            returnString = "fantasy";
            break;
        case mystery:
            returnString = "mystery";
            break;
        case romance:
            returnString = "romance";
            break;
        case scienceFiction:
            returnString = "science fiction";
            break;
        case thriller:
            returnString = "thriller";
            break;
        case western:
            returnString = "western";
            break;
        case genreNotSet: //fall through to default
        default:
            returnString = "genre not set";
            break;
    }
    
    return returnString;
}

bool operator==(const Book& lhs, const Book& rhs) {
    if (lhs.printJson() == rhs.printJson()) {
        return true;
    }
    
    return false;
}

bool operator!=(const Book& lhs, const Book& rhs) {
    return !operator==(lhs, rhs);
}

bool operator<(const Book& lhs, const Book& rhs) {
    //see if this can be simplified TODO
    //sort by author -> series -> publish date -> title
    
    if (lhs.getAuthor() < rhs.getAuthor()) { return true; }
    else if (lhs.getAuthor() > rhs.getAuthor()) { return false; }
    else {
        if (lhs.getSeries() < rhs.getSeries()) { return true; }
        else if (lhs.getSeries() > rhs.getSeries()) { return false; }
        else {
            if (lhs.printPublishDate() < rhs.printPublishDate()) { return true; }
            else if (lhs.printPublishDate() > rhs.printPublishDate()) { return false; }
            else {
                if (lhs.getTitle() < rhs.getTitle()) { return true; }
                else if (lhs.getTitle() > rhs.getTitle()) { return false; }
            }
        }
    }
    
    return true;
}

bool operator>(const Book& lhs, const Book& rhs) {
    return operator<(rhs, lhs);
}

bool operator<=(const Book& lhs, const Book& rhs) {
    return !operator>(lhs, rhs);
}

bool operator>=(const Book& lhs, const Book& rhs) {
    return !operator<(lhs, rhs);
}
