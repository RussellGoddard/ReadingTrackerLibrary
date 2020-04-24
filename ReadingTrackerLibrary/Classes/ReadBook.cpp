//
//  ReadBook.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "ReadBook.hpp"

//TODO: validation
bool rtl::ReadBook::SetDateRead(boost::posix_time::ptime time) {
    this->dateRead = boost::posix_time::to_tm(time);
    
    return true;
}

bool rtl::ReadBook::SetDateRead(std::string time) {
    rtl::ReadBook::RemoveNonPrint(time);
    if (time.empty()) {
        return false;
    }
    
    try {
        auto d = boost::gregorian::from_string(time);
        this->dateRead = boost::gregorian::to_tm(d);
    } catch (std::exception& ex) {
        std::string exceptionMessage = ex.what();
        exceptionMessage += " failed to convert " + time + " to boost::gregorian::date";
        BOOST_LOG_TRIVIAL(error) << exceptionMessage;
        return false;
    }
    
    return true;
}

//1-10 rating scale
bool rtl::ReadBook::SetRating(int rating) {
    if (rating < 1 || rating > 10) {
        return false;
    }
    this->rating = rating;
    
    return true;
}

//will result in rating being set to 0
bool rtl::ReadBook::SetRating(char rating) {
    int newRating = -1;
    std::stringstream sstream;
    
    sstream << rating;
    sstream >> newRating;
    
    //if rating == 0 then failed to convert to an integer or the rating passed was zero which is invalid
    if (newRating >= 1 && newRating <= 10) {
        this->rating = newRating;
        return true;
    }
    
    return false;
}

//will attempt a stoi if it fails set rating to 0
bool rtl::ReadBook::SetRating(std::string rating) {
    rtl::ReadBook::RemoveNonPrint(rating);
    if (rating.empty()) {
        return false;
    }
    
    try {
        int newRating = std::stoi(rating);
        //rating cannot be less than 1 or greater than 10, if it is don't change anything
        if (newRating < 1 || newRating > 10) {
            BOOST_LOG_TRIVIAL(info) << "rating must be between 1 and 10 inclusive, input: " + rating;
            return false;
        }
        
        this->rating = newRating;
    } catch (std::invalid_argument ex) {
        std::string exceptionMessage = ex.what();
        exceptionMessage += " failed to convert to int, input: " + rating;
        BOOST_LOG_TRIVIAL(error) << exceptionMessage;
        return false;
    }
    
    return true;
}

tm rtl::ReadBook::GetDateRead() const {
    return this->dateRead;
}

boost::posix_time::ptime rtl::ReadBook::GetDateReadAsPosixTime() {
    return boost::posix_time::ptime_from_tm(this->dateRead);;
}

std::string rtl::ReadBook::PrintDateRead() const {
    try {
        auto returnDate = boost::gregorian::date_from_tm(this->dateRead);
        return boost::gregorian::to_simple_string(returnDate);
    }
    catch (std::exception ex) {
        std::string exceptionMessage = ex.what();
        exceptionMessage += " failed to convert this struct tm to boost::gregorian::date";
        BOOST_LOG_TRIVIAL(error) << exceptionMessage;
        return "";
    }
}

int rtl::ReadBook::GetRating() const {
    return this->rating;
}

int rtl::ReadBook::GetReaderId() const {
    return this->readerId;
}

rtl::SetsPtr rtl::ReadBook::GetUpdateFunction(std::string input) {
    SetsPtr returnPtr = this->Book::GetUpdateFunction(input);
    
    if (returnPtr == nullptr) {
        if (input == this->kReaderId) { return nullptr; }
        else if (input == this->kRating) { return static_cast<rtl::SetsPtr>(&rtl::ReadBook::SetRating); }
        else if (input == this->kDateRead) { return static_cast<rtl::SetsPtr>(&rtl::ReadBook::SetDateRead); }
    }
    
    return returnPtr;
}

std::string rtl::ReadBook::PrintJson() const {
    std::string returnString;
    
    returnString = this->Book::PrintJson();
    returnString.pop_back(); //remove ending bracket
    
    //append ReadBook variables
    returnString += R"(,"rating":)" + std::to_string(this->GetRating()) + R"(,"dateRead":")" + this->PrintDateRead() + R"(","readerId":)" + std::to_string(this->GetReaderId()) + R"(})";
    
    return returnString;
    
}

std::string rtl::ReadBook::PrintSimple() const {
    //Brandon Sanderson   Mistborn: The Final Empire         541   Sep 13 2019  9
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kWidthAuthor);
    returnStr << std::left << this->GetAuthorsString().substr(0, kWidthAuthor - 1);
    returnStr.width(kWidthTitle);
    returnStr << std::left << this->GetTitle().substr(0, kWidthTitle - 1);
    returnStr.width(kWidthPage);
    returnStr << std::left << std::to_string(this->GetPageCount()).substr(0, kWidthPage - 1);
    returnStr.width(kWidthDateRead);
    returnStr << std::left << this->PrintDateRead().substr(0, kWidthDateRead - 1);
    returnStr.width(kWidthRating);
    returnStr << std::left << std::to_string(this->GetRating()).substr(0, kWidthRating - 1);
    
    return returnStr.str();
}

std::string rtl::ReadBook::PrintDetailed() const {
    /*
     std::string readerId
     std::string rating
     tm dateRead
     std::string title;
     std::string bookId;
     std::string author;
     std::string authorId;
     std::string series;
     Genre genre;
     int pageCount;
     std::string publisher;
     tm publishDate;
     std::vector<std::string> isbnVector;
     std::vector<std::string> oclcVector;
     */
    
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr << std::left;
    returnStr << this->Book::PrintDetailed();
    returnStr << std::setw(15) << this->kReaderId + ": " << std::setw(65) << this->GetReaderId() << std::endl;
    returnStr << std::setw(15) << this->kRating + ": " << std::setw(65) << this->GetRating() << std::endl;
    returnStr << std::setw(15) << this->kDateRead + ": " << std::setw(65) << this->PrintDateRead() << std::endl;
    
    return returnStr.str();
}

std::string rtl::ReadBook::PrintHeader() const {
    //Author              Title                              Pages Date Read    Rating
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(kWidthTitle);
    returnStr << std::left << "Title";
    returnStr.width(kWidthPage);
    returnStr << std::left << "Pages";
    returnStr.width(kWidthDateRead);
    returnStr << std::left << "Date Read";
    returnStr.width(kWidthRating);
    returnStr << std::left << "Rate";
    
    return returnStr.str();
}

rtl::ReadBook::ReadBook(int readerId, Book book, int rating, boost::posix_time::ptime dateRead) : Book(book) {
    this->readerId = readerId;
    this->SetDateRead(dateRead);
    this->SetRating(rating);
}

rtl::ReadBook::ReadBook(int readerId, Book book, int rating, std::string dateRead) : Book(book) {
    this->readerId = readerId;
    this->SetDateRead(dateRead);
    this->SetRating(rating);
}


rtl::ReadBook::ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, rtl::Genre genre, boost::posix_time::ptime publishDate, int rating, boost::posix_time::ptime dateRead) : Book(author, title, series, publisher, pageCount, genre, publishDate) {
    this->readerId = readerId;
    this->SetDateRead(dateRead);
    this->SetRating(rating);
}

rtl::ReadBook::ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead) : Book({author}, title, series, publisher, pageCount, genre, publishDate) {
    this->readerId = readerId;
    this->SetDateRead(dateRead);
    this->SetRating(rating);
}
    
bool rtl::operator==(const ReadBook& lhs, const ReadBook& rhs) {
    if (!(static_cast<const Book&>(lhs) == static_cast<const Book&>(rhs))) { return false; }
    if (!(lhs.GetReaderId() == rhs.GetReaderId())) { return false; }
    if (!(lhs.PrintDateRead() == rhs.PrintDateRead())) { return false; }
    if (!(lhs.GetRating() == rhs.GetRating())) { return false; }
    
    return true;
}

bool rtl::operator!=(const ReadBook& lhs, const ReadBook& rhs) {
    return !operator==(lhs, rhs);
}

bool rtl::operator<(const ReadBook& lhs, const ReadBook& rhs) {
    //TODO: see if this can be simplified
    //sort by Book comparison then by dateRead
    
    if (lhs.GetAuthors() < rhs.GetAuthors()) { return true; }
    else if (lhs.GetAuthors() > rhs.GetAuthors()) { return false; }
    else {
        if (lhs.GetSeries() < rhs.GetSeries()) { return true; }
        else if (lhs.GetSeries() > rhs.GetSeries()) { return false; }
        else {
            tm lhstm = lhs.GetPublishDate();
            tm rhstm = rhs.GetPublishDate();;
            boost::posix_time::ptime lhspt = boost::posix_time::ptime_from_tm(lhstm);
            boost::posix_time::ptime rhspt = boost::posix_time::ptime_from_tm(rhstm);
            
            if (lhspt < rhspt) { return true; }
            else if (lhspt > rhspt) { return false; }
            else {
                if (lhs.GetTitle() < rhs.GetTitle()) { return true; }
                else if (lhs.GetTitle() > rhs.GetTitle()) { return false; }
                else {
                    lhstm = lhs.GetDateRead();
                    lhspt = boost::posix_time::ptime_from_tm(lhstm);
                    rhstm = rhs.GetDateRead();
                    rhspt = boost::posix_time::ptime_from_tm(rhstm);
                    
                    if (lhspt < rhspt) { return true; }
                    else if (rhspt > lhspt) { return false; }
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
