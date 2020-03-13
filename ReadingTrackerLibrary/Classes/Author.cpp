//
//  Author.cpp
//  Reading Tracker
//
//  Created by Frobu on 11/3/19.
//

#include "Author.hpp"

void rtl::Author::SetName(std::string name) {
    this->name = name;
    return;
}

void rtl::Author::SetDateBorn(time_t dateBorn) {
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

bool rtl::Author::SetDateBorn(std::string dateBorn) {
    try {
        auto d = boost::gregorian::from_string(dateBorn);
        this->dateBorn = boost::gregorian::to_tm(d);
    } catch (std::exception& ex) {
        //TODO: add logging
        return false;
    }
    
    return true;
}

void rtl::Author::AddBookWritten(std::shared_ptr<rtl::Book> book) {
    this->booksWritten.push_back(book);
    rtl::SortUnique(this->booksWritten);
    return;
}

void rtl::Author::AddBookWritten(std::vector<std::shared_ptr<rtl::Book>> books) {
    this->booksWritten.insert(std::end(this->booksWritten), std::begin(books), std::end(books));
    rtl::SortUnique(this->booksWritten);
    return;
}

std::string rtl::Author::GetName() const {
    return name;
}

tm rtl::Author::GetDateBorn() const {
    return this->dateBorn;
}

time_t rtl::Author::GetDateBornTimeT() {
    return std::mktime(&this->dateBorn);
}

std::string rtl::Author::PrintDateBorn() const {
    auto returnDate = boost::gregorian::date_from_tm(this->dateBorn);
    return boost::gregorian::to_simple_string(returnDate);
}

std::vector<std::shared_ptr<rtl::Book>> rtl::Author::GetBooksWritten() const {
    return this->booksWritten;
}

std::string rtl::Author::PrintJson() const {
    std::string returnString;
    returnString = R"({"name":")" + this->GetName() + R"(","dateBorn":")" + this->PrintDateBorn() + R"(","booksWritten":[)";
    for (std::shared_ptr<rtl::Book> x : this->GetBooksWritten()) {
        returnString += x->PrintJson();
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
std::string rtl::Author::PrintCommandLine() const {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(Author::kWidthAuthor);
    returnStr << std::left << this->GetName().substr(0, Author::kWidthAuthor - 1);
    returnStr.width(Author::kWidthDateBorn);
    returnStr << std::left << this->PrintDateBorn().substr(0, Author::kWidthDateBorn - 1);
    if (!this->GetBooksWritten().empty()) {
        std::vector<std::shared_ptr<rtl::Book>> booksWritten = this->GetBooksWritten();
        returnStr.width(Author::kWidthTitle);
        returnStr << std::left << booksWritten.at(0)->GetTitle().substr(0, Author::kWidthTitle - 1);
        returnStr.width(Author::kWidthYear);
        returnStr << std::left << booksWritten.at(0)->PrintPublishDate().substr(0, 4);
        for (int i = 1; i < booksWritten.size(); ++i) {
            returnStr << std::endl;
            returnStr.width(Author::kWidthAuthor + Author::kWidthDateBorn);
            returnStr << std::left << " ";
            returnStr.width(Author::kWidthTitle);
            returnStr << std::left << booksWritten.at(i)->GetTitle().substr(0, Author::kWidthTitle - 1);
            returnStr.width(Author::kWidthYear);
            returnStr << std::left << booksWritten.at(i)->PrintPublishDate().substr(0, 4);
        }
    }
    
    return returnStr.str();
}

//Author              Date Born   Books Written                               Year
std::string rtl::Author::PrintCommandLineHeaders() {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(Author::kWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(Author::kWidthDateBorn);
    returnStr << std::left << "Date Born";
    returnStr.width(Author::kWidthTitle);
    returnStr << std::left << "Books Written";
    returnStr.width(Author::kWidthYear);
    returnStr << std::left << "Year";

    return returnStr.str();
}

rtl::Author::Author(std::string name, time_t dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten) {
    this->SetName(name);
    this->SetDateBorn(dateBorn);
    this->AddBookWritten(booksWritten);
}

rtl::Author::Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten) {
    this->SetName(name);
    this->SetDateBorn(dateBorn);
    this->AddBookWritten(booksWritten);
}

rtl::Author::Author(std::string name, time_t dateBorn, std::shared_ptr<rtl::Book> bookWritten) {
    this->SetName(name);
    this->SetDateBorn(dateBorn);
    this->AddBookWritten(bookWritten);
}

bool rtl::operator==(const Author& lhs, const Author& rhs) {
    
    /* TODO: add way to combine authors even if birthdate is missing/inccorrect somehow, disabled birthdate compare so that it is feasible that authors get combined appropriately
    tm lhstm = lhs.getDateBorn();
    tm rhstm = rhs.getDateBorn();
    time_t lhstt = std::mktime(&lhstm);
    time_t rhstt = std::mktime(&rhstm);
    
    if (lhstt != rhstt) {
        return false;
    }
     */
    if (lhs.GetName() != rhs.GetName()) {
        return false;
    }
    
    return true;
}


bool rtl::operator!=(const Author& lhs, const Author& rhs) {
    return !operator==(lhs, rhs);
}

//TODO: this shouldn't be in author
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
    //TODO: there is probably a way to do an insensitive case string compare
    //make names lower case for comparison
    std::string lowerLhsName = lhs.GetName();
    std::string lowerRhsName = rhs.GetName();
    std::transform(std::begin(lowerLhsName), std::end(lowerLhsName), std::begin(lowerLhsName), ::tolower);
    std::transform(std::begin(lowerRhsName), std::end(lowerRhsName), std::begin(lowerRhsName), ::tolower);
    
    std::vector<std::string> lhsName = splitString(lowerLhsName, " ");
    std::vector<std::string> rhsName = splitString(lowerRhsName, " ");
    
    if (lhsName.back() < rhsName.back()) { return true; }
    else if (lhsName.back() > rhsName.back()) { return false; }
    else {
        
        tm lhstm = lhs.GetDateBorn();
        tm rhstm = rhs.GetDateBorn();
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


