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

std::string Author::getName() {
    return name;
}

void Author::setDateBorn(time_t dateBorn) {
    this->dateBorn = *std::gmtime(&dateBorn);
    
    return;
}

void Author::setDateBorn(std::string dateBorn) {
    if (dateBorn.size() != 11) {
        return;
    }
    
    std::string month = dateBorn.substr(0, 3);
    std::string day = dateBorn.substr(4, 2);
    std::string year = dateBorn.substr(7, 4);
    
    int intMonth = convertAbbrMonthToInt(month);
    
    if (intMonth == -1) {
        return;
    }
    
    this->dateBorn.tm_mon = intMonth;
    this->dateBorn.tm_mday = stoi(day) - 1; //days are zero based in struct tm
    this->dateBorn.tm_year = stoi(year) - 1900;
    
    time_t validateTime = std::mktime(&this->dateBorn);
    
    this->dateBorn = *std::gmtime(&validateTime);
    
    return;
}

time_t Author::getDateBorn() {
    return std::mktime(&this->dateBorn);
}

std::string Author::printDateBorn() {
    char buffer [50];
    std::strftime(buffer, 50, "%b %d %Y", &this->dateBorn);
    return buffer;
}

void Author::addBookWritten(std::shared_ptr<Book> book) {
    this->booksWritten.push_back(book);
    
    return;
}

void Author::addBooksWritten(std::vector<std::shared_ptr<Book>> books) {
    this->booksWritten.insert(std::end(this->booksWritten), std::begin(books), std::end(books));
    
    return;
}

std::vector<std::shared_ptr<Book>> Author::getBooksWritten() {
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
