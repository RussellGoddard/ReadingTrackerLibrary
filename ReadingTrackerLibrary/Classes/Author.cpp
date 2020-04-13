//
//  Author.cpp
//  Reading Tracker
//
//  Created by Frobu on 11/3/19.
//

#include "Author.hpp"

bool rtl::Author::SetName(std::string name) {
    //TODO: validation
    this->name = name;
    return true;
}

bool rtl::Author::SetDateBorn(boost::posix_time::ptime dateBorn) {
    this->dateBorn = boost::posix_time::to_tm(dateBorn);
    return true;
}

bool rtl::Author::SetDateBorn(std::string dateBorn) {
    try {
        auto d = boost::gregorian::from_string(dateBorn);
        this->dateBorn = boost::gregorian::to_tm(d);
    } catch (std::exception& ex) {
        std::string exceptionMessage = ex.what();
        exceptionMessage += " dateBorn: " + dateBorn;
        BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        return false;
    }
    
    return true;
}

bool rtl::Author::AddBookWritten(std::shared_ptr<rtl::Book> book) {
    //TODO: add false path
    this->booksWritten.push_back(book);
    rtl::SortUnique(this->booksWritten);
    return true;
}

bool rtl::Author::AddBookWritten(std::vector<std::shared_ptr<rtl::Book>> books) {
    //TODO: false path
    this->booksWritten.insert(std::end(this->booksWritten), std::begin(books), std::end(books));
    rtl::SortUnique(this->booksWritten);
    return true;
}

std::string rtl::Author::GetAuthorId() const {
    return this->authorId;
}

std::string rtl::Author::GetName() const {
    return this->name;
}

tm rtl::Author::GetDateBorn() const {
    return this->dateBorn;
}

boost::posix_time::ptime rtl::Author::GetDateBornPosixTime() {
    return boost::posix_time::ptime_from_tm(this->dateBorn);
}

std::string rtl::Author::PrintDateBorn() const {
    auto returnDate = boost::gregorian::date_from_tm(this->dateBorn);
    return boost::gregorian::to_simple_string(returnDate);
}

std::vector<std::shared_ptr<rtl::Book>> rtl::Author::GetBooksWritten() const {
    return this->booksWritten;
}



rtl::SetsPtr rtl::Author::GetUpdateFunction(std::string input) {
    //TODO: make case insensitive
    //TODO: message about not changing authorId, about adding books written
    if (input == this->kAuthor) { return static_cast<rtl::SetsPtr>(&rtl::Author::SetName); }
    else if (input == this->kAuthorId) { return nullptr; }
    else if (input == this->kDateBorn) { return static_cast<rtl::SetsPtr>(&rtl::Author::SetDateBorn); }
    else if (input == this->kBooksWritten) { return nullptr; }
    else { return nullptr; }
}

std::string rtl::Author::PrintJson() const {
    std::string returnString;
    returnString = R"({"authorId":")" + this->GetAuthorId() + R"(","name":")" + this->GetName() + R"(","dateBorn":")" + this->PrintDateBorn() + R"(","booksWritten":[)";
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

std::string rtl::Author::PrintSimple() const {
    /*
    Brandon Sanderson   Dec 19 1975 Mistborn: The Final Empire                  2006
                                    Mistborn: The Well of Ascension             2007
                                    Mistborn: The Hero of Ages                  2008
     */
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kWidthAuthor);
    returnStr << std::left << this->GetName().substr(0, kWidthAuthor - 1);
    returnStr.width(kWidthDateBorn);
    returnStr << std::left << this->PrintDateBorn().substr(0, kWidthDateBorn - 1);
    if (!this->GetBooksWritten().empty()) {
        std::vector<std::shared_ptr<rtl::Book>> booksWritten = this->GetBooksWritten();
        returnStr.width(kWidthTitle);
        returnStr << std::left << booksWritten.at(0)->GetTitle().substr(0, kWidthTitle - 1);
        returnStr.width(kWidthYear);
        returnStr << std::left << booksWritten.at(0)->PrintPublishDate().substr(0, 4);
        for (int i = 1; i < booksWritten.size(); ++i) {
            returnStr << std::endl;
            returnStr.width(kWidthAuthor + kWidthDateBorn + 3);
            returnStr << std::left << " ";
            returnStr.width(kWidthTitle);
            returnStr << std::left << booksWritten.at(i)->GetTitle().substr(0, kWidthTitle - 1);
            returnStr.width(kWidthYear);
            returnStr << std::left << booksWritten.at(i)->PrintPublishDate().substr(0, 4);
        }
    }
    
    return returnStr.str();
}

std::string rtl::Author::PrintDetailed() const {
    /*
     std::string authorId;
     std::string name;
     struct tm dateBorn;
     std::vector<std::shared_ptr<rtl::Book>> booksWritten;
     */
    
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr << std::left;
    returnStr << std::setw(15) << this->kAuthor + ": " << std::setw(65) << this->GetName().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kAuthorId + ": " << std::setw(65) << this->GetAuthorId().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kDateBorn + ": " << std::setw(65) << this->PrintDateBorn().substr(0, 65) << std::endl;
    returnStr << std::setw(80) << this->kBooksWritten + ": " << std::endl;
    for (auto x : this->GetBooksWritten()) {
        returnStr << x->PrintDetailed();
        returnStr << std::endl;
    }
    
    return returnStr.str();
}

std::string rtl::Author::PrintHeader() const {
    //Author              Date Born   Books Written                               Year
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(kWidthDateBorn);
    returnStr << std::left << "Date Born";
    returnStr.width(kWidthTitle);
    returnStr << std::left << "Books Written";
    returnStr.width(kWidthYear);
    returnStr << std::left << "Year";

    return returnStr.str();
}

rtl::Author::Author(std::string name, boost::posix_time::ptime dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten) {
    this->SetName(name);
    this->SetDateBorn(dateBorn);
    this->AddBookWritten(booksWritten);
    this->authorId = GenerateId(name);
}

rtl::Author::Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten) {
    this->SetName(name);
    this->SetDateBorn(dateBorn);
    this->AddBookWritten(booksWritten);
    this->authorId = GenerateId(name);
}

bool rtl::operator==(const Author& lhs, const Author& rhs) {
    
    //TODO: add way to combine authors even if birthdate is missing somehow, disabled birthdate compare so that it is feasible that authors get combined appropriately

    if (lhs.GetName() != rhs.GetName()) {
        return false;
    }
    
    return true;
}


bool rtl::operator!=(const Author& lhs, const Author& rhs) {
    return !operator==(lhs, rhs);
}

//sort by last word in name then by birthdate
bool rtl::operator<(const Author& lhs, const Author& rhs) {
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
        boost::posix_time::ptime lhspt = boost::posix_time::ptime_from_tm(lhstm);
        boost::posix_time::ptime rhspt = boost::posix_time::ptime_from_tm(rhstm);
        
        if (lhspt < rhspt) { return true; }
        else if (rhspt > lhspt) { return false; }
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

