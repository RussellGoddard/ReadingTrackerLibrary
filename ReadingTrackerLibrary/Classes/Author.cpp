//
//  Author.cpp
//  Reading Tracker
//
//  Created by Frobu on 11/3/19.
//

#include "Author.hpp"

void Author::setName(std::string name) {
    this->name = name;
    
    return;
}

void Author::setDateBorn(time_t dateBorn) {
    this->dateBorn = *std::gmtime(&dateBorn);
    this->dateBorn.tm_sec = 0;
    this->dateBorn.tm_min = 0;
    this->dateBorn.tm_hour = 0;
    
    return;
}

void Author::setDateBorn(std::string dateBorn) {
    if (dateBorn.size() != 11) {
        return;
    }
    
    std::string month = dateBorn.substr(0, 3);
    std::string day = dateBorn.substr(4, 2);
    std::string year = dateBorn.substr(7, 4);
    
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
    
    this->dateBorn.tm_year = intYear;
    this->dateBorn.tm_mon = intMonth;
    this->dateBorn.tm_mday = intDay;
    this->dateBorn.tm_sec = 0;
    this->dateBorn.tm_min = 0;
    this->dateBorn.tm_hour = 0;
    
    time_t validateTime = std::mktime(&this->dateBorn);
    
    this->dateBorn = *std::gmtime(&validateTime);
    
    return;
}

void Author::addBookWritten(std::shared_ptr<Book> book) {
    this->booksWritten.push_back(book);
    
    return;
}

void Author::addBookWritten(std::vector<std::shared_ptr<Book>> books) {
    this->booksWritten.insert(std::end(this->booksWritten), std::begin(books), std::end(books));
    
    return;
}

std::string Author::getName() const {
    return name;
}

tm Author::getDateBorn() const {
    return this->dateBorn;
}

time_t Author::getDateBornTimeT() {
    return std::mktime(&this->dateBorn);
}

std::string Author::printDateBorn() const {
    char buffer [50];
    std::strftime(buffer, 50, "%b %d %Y", &this->dateBorn);
    return buffer;
}

std::vector<std::shared_ptr<Book>> Author::getBooksWritten() const {
    return this->booksWritten;
}

Author::Author(std::string name, time_t dateBorn, std::vector<std::shared_ptr<Book>> booksWritten) {
    this->name = name;
    this->setDateBorn(dateBorn);
    this->booksWritten = booksWritten;
}

Author::Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten) {
    this->name = name;
    this->setDateBorn(dateBorn);
    this->booksWritten = booksWritten;
}
