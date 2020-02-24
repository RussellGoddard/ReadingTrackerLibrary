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
    this->dateBorn.tm_wday = 0;
    this->dateBorn.tm_isdst = 0;
    this->dateBorn.tm_gmtoff = 0;
    this->dateBorn.tm_zone = nullptr;
    
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
    this->dateBorn.tm_wday = 0;
    this->dateBorn.tm_isdst = 0;
    this->dateBorn.tm_gmtoff = 0;
    this->dateBorn.tm_zone = nullptr;
    
    time_t validateTime = std::mktime(&this->dateBorn);
    
    this->dateBorn = *std::gmtime(&validateTime);
    
    return;
}

void Author::addBookWritten(std::shared_ptr<Book> book) {
    this->booksWritten.push_back(book);

    sortUnique(this->booksWritten);
    
    return;
}

void Author::addBookWritten(std::vector<std::shared_ptr<Book>> books) {
    this->booksWritten.insert(std::end(this->booksWritten), std::begin(books), std::end(books));
    sortUnique(this->booksWritten);
    
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

std::string Author::printJson() const {
    std::string returnString;
    returnString = R"({"name":")" + this->getName() + R"(","dateBorn":")" + this->printDateBorn() + R"(","booksWritten":[)";
    for (std::shared_ptr<Book> x : this->getBooksWritten()) {
        returnString += x->printJson();
        returnString += ',';
    }
    if (returnString.back() == ',') {
        returnString.pop_back();
    }
    returnString += R"(]})";
    
    return returnString;
}

Author::Author(std::string name, time_t dateBorn, std::vector<std::shared_ptr<Book>> booksWritten) {
    this->setName(name);
    this->setDateBorn(dateBorn);
    this->addBookWritten(booksWritten);
}

Author::Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten) {
    this->setName(name);
    this->setDateBorn(dateBorn);
    this->addBookWritten(booksWritten);
    
}

Author::Author(std::string name, time_t dateBorn, std::shared_ptr<Book> bookWritten) {
    this->setName(name);
    this->setDateBorn(dateBorn);
    this->addBookWritten(bookWritten);
}

bool operator==(const Author& lhs, const Author& rhs) {
    
    /* disabled birthdate compare so that it is feasible that authors get combined appropriately
    tm lhstm = lhs.getDateBorn();
    tm rhstm = rhs.getDateBorn();
    time_t lhstt = std::mktime(&lhstm);
    time_t rhstt = std::mktime(&rhstm);
    
    if (lhstt != rhstt) {
        return false;
    }
     */
    if (lhs.getName() != rhs.getName()) {
        return false;
    }
    
    return true;
}


bool operator!=(const Author& lhs, const Author& rhs) {
    return !operator==(lhs, rhs);
}

//TO DO this shouldn't be in author
std::vector<std::string> splitString(const std::string& input, const std::string& delim) {
    std::vector<std::string> returnVector;
    std::size_t current = 0;
    std::size_t previous = 0;
    
    current = input.find_first_of(delim);
    
    while (current != input.npos) {
        returnVector.push_back(input.substr(previous, current - previous));
        previous = current + 1;
        current = input.find_first_of(delim, previous);
    }
    returnVector.push_back(input.substr(previous, current - previous));
    
    return returnVector;
}

//sort by last word in name then by birthdate
bool operator<(const Author& lhs, const Author& rhs) {
    //make names lower case for comparison
    std::string lowerLhsName = lhs.getName();
    std::string lowerRhsName = rhs.getName();
    std::transform(std::begin(lowerLhsName), std::end(lowerLhsName), std::begin(lowerLhsName), ::tolower);
    std::transform(std::begin(lowerRhsName), std::end(lowerRhsName), std::begin(lowerRhsName), ::tolower);
    
    std::vector<std::string> lhsName = splitString(lowerLhsName, " ");
    std::vector<std::string> rhsName = splitString(lowerRhsName, " ");
    
    if (lhsName.back() < rhsName.back()) { return true; }
    else if (lhsName.back() > rhsName.back()) { return false; }
    else {
        
        tm lhstm = lhs.getDateBorn();
        tm rhstm = rhs.getDateBorn();
        time_t lhstt = std::mktime(&lhstm);
        time_t rhstt = std::mktime(&rhstm);
        
        if (lhstt < rhstt) { return true; }
        else if (rhstt > lhstt) { return false; }
    }
    
    return false;
}
bool operator>(const Author& lhs, const Author& rhs) {
    return operator<(rhs, lhs);
}
bool operator>=(const Author& lhs, const Author& rhs) {
    return !operator<(lhs, rhs);
}
bool operator<=(const Author& lhs, const Author& rhs) {
    return !operator>(lhs, rhs);
}


