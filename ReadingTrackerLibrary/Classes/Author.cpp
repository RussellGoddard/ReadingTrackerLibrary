//
//  Author.cpp
//  Reading Tracker
//
//  Created by Frobu on 11/3/19.
//

#include "Author.hpp"

//used for printCommandLine and printCommandLineHeaders
//TODO implement namespaces
int widthAuthorA = 20;
int widthDateBornA = 12;
int widthTitleA = 44;
int widthYearA = 4;


void rtl::Author::setName(std::string name) {
    this->name = name;
    
    return;
}

void rtl::Author::setDateBorn(time_t dateBorn) {
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

void rtl::Author::setDateBorn(std::string dateBorn) {
    if (dateBorn.size() != 11) {
        return;
    }
    
    std::string month = dateBorn.substr(0, 3);
    std::string day = dateBorn.substr(4, 2);
    std::string year = dateBorn.substr(7, 4);
    
    int intYear;
    int intMonth = rtl::convertAbbrMonthToInt(month);
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

void rtl::Author::addBookWritten(std::shared_ptr<rtl::Book> book) {
    this->booksWritten.push_back(book);

    sortUnique(this->booksWritten);
    
    return;
}

void rtl::Author::addBookWritten(std::vector<std::shared_ptr<rtl::Book>> books) {
    this->booksWritten.insert(std::end(this->booksWritten), std::begin(books), std::end(books));
    sortUnique(this->booksWritten);
    
    return;
}

std::string rtl::Author::getName() const {
    return name;
}

tm rtl::Author::getDateBorn() const {
    return this->dateBorn;
}

time_t rtl::Author::getDateBornTimeT() {
    return std::mktime(&this->dateBorn);
}

std::string rtl::Author::printDateBorn() const {
    char buffer [50];
    std::strftime(buffer, 50, "%b %d %Y", &this->dateBorn);
    return buffer;
}

std::vector<std::shared_ptr<rtl::Book>> rtl::Author::getBooksWritten() const {
    return this->booksWritten;
}

std::string rtl::Author::printJson() const {
    std::string returnString;
    returnString = R"({"name":")" + this->getName() + R"(","dateBorn":")" + this->printDateBorn() + R"(","booksWritten":[)";
    for (std::shared_ptr<rtl::Book> x : this->getBooksWritten()) {
        returnString += x->printJson();
        returnString += ',';
    }
    if (returnString.back() == ',') {
        returnString.pop_back();
    }
    returnString += R"(]})";
    
    return returnString;
}

/*
Brandon Sanderson   Dec 19 1975 Mistborn: The Final Empire                  2006
                                Mistborn: The Well of Ascension             2007
                                Mistborn: The Hero of Ages                  2008
 */
std::string rtl::Author::printCommandLine() const {
    std::stringstream returnStr;
    std::string test;
    returnStr.fill(' ');
    
    returnStr.width(widthAuthorA);
    returnStr << std::left << this->getName().substr(0, widthAuthorA - 1);
    returnStr.width(widthDateBornA);
    returnStr << std::left << this->printDateBorn().substr(0, widthDateBornA - 1);
    if (!this->getBooksWritten().empty()) {
        std::vector<std::shared_ptr<rtl::Book>> booksWritten = this->getBooksWritten();
        returnStr.width(widthTitleA);
        returnStr << std::left << booksWritten.at(0)->getTitle().substr(0, widthTitleA - 1);
        returnStr.width(widthYearA);
        returnStr << std::left << booksWritten.at(0)->printPublishDate().substr(booksWritten.at(0)->printPublishDate().size() - 4);
test = returnStr.str();
        for (int i = 1; i < booksWritten.size(); ++i) {
            returnStr << std::endl;
            returnStr.width(widthAuthorA + widthDateBornA);
            returnStr << std::left << " ";
            returnStr.width(widthTitleA);
            returnStr << std::left << booksWritten.at(i)->getTitle().substr(0, widthTitleA - 1);
            returnStr.width(widthYearA);
            returnStr << std::left << booksWritten.at(i)->printPublishDate().substr(booksWritten.at(0)->printPublishDate().size() - 4);
        }
    }
    
test = returnStr.str();
    return returnStr.str();
}

//Author              Date Born   Books Written                               Year
std::string rtl::Author::printCommandLineHeaders() {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(widthAuthorA);
    returnStr << std::left << "Author";
    returnStr.width(widthDateBornA);
    returnStr << std::left << "Date Born";
    returnStr.width(widthTitleA);
    returnStr << std::left << "Books Written";
    returnStr.width(widthYearA);
    returnStr << std::left << "Year";

    return returnStr.str();
}

rtl::Author::Author(std::string name, time_t dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten) {
    this->setName(name);
    this->setDateBorn(dateBorn);
    this->addBookWritten(booksWritten);
}

rtl::Author::Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten) {
    this->setName(name);
    this->setDateBorn(dateBorn);
    this->addBookWritten(booksWritten);
    
}

rtl::Author::Author(std::string name, time_t dateBorn, std::shared_ptr<rtl::Book> bookWritten) {
    this->setName(name);
    this->setDateBorn(dateBorn);
    this->addBookWritten(bookWritten);
}

bool rtl::operator==(const Author& lhs, const Author& rhs) {
    
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


bool rtl::operator!=(const Author& lhs, const Author& rhs) {
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
bool rtl::operator<(const Author& lhs, const Author& rhs) {
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

bool rtl::operator>(const Author& lhs, const Author& rhs) {
    return operator<(rhs, lhs);
}

bool rtl::operator>=(const Author& lhs, const Author& rhs) {
    return !operator<(lhs, rhs);
}

bool rtl::operator<=(const Author& lhs, const Author& rhs) {
    return !operator>(lhs, rhs);
}


