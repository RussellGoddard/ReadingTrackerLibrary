//
//  Book.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "Book.hpp"

std::string rtl::Book::GetAuthor() const {
    return this->author;
}

std::string rtl::Book::GetTitle() const {
    return this->title;
}

std::string rtl::Book::GetSeries() const {
    return series;
}

int rtl::Book::GetPageCount() const {
    return pageCount;
}

std::string rtl::Book::GetPublisher() const {
    return this->publisher;
}

rtl::Genre rtl::Book::GetGenre() const {
    return genre;
}

std::string rtl::Book::PrintGenre() const {
    return ConvertGenreToString(this->genre);
}

std::vector<std::string> rtl::Book::GetOclc() const {
    return this->oclcVector;
}

std::vector<std::string> rtl::Book::GetIsbn() const {
    return this->isbnVector;
}

std::string rtl::Book::GetAuthorId() const {
    return this->authorId;
}

std::string rtl::Book::GetBookId() const {
    return this->bookId;
}

tm rtl::Book::GetPublishDate() const {
    return this->publishDate;
}

time_t rtl::Book::GetPublishDateAsTimeT() {
    return std::mktime(&this->publishDate);
}

std::string rtl::Book::PrintPublishDate() const {
    auto returnDate = boost::gregorian::date_from_tm(this->publishDate);
    return boost::gregorian::to_simple_string(returnDate);
}

void rtl::Book::SetSeries(std::string series) {
    this->series = series;
    return;
}

void rtl::Book::SetPublisher(std::string publisher) {
    this->publisher = publisher;
    return;
}

void rtl::Book::SetPageCount(int pageCount) {
    //books can only have positive page counts, if it isn't mark as -1 as error
    if (pageCount <= 0) {
        pageCount = -1;
    }
    this->pageCount = pageCount;
    return;
}

//pageCount can't be changed by character, keep whatever is in there before
void rtl::Book::SetPageCount(char pageCount) {
    int newPageCount = -1;
    std::stringstream sstream;
    
    sstream << pageCount;
    sstream >> newPageCount;
    
    //if newPageCount == 0 then failed to convert to an integer or the pageCount passed was zero which is invalid
    if (newPageCount <= 0) {
        return;
    }
    this->pageCount = newPageCount;
    
    return;
}

//will attempt a stoi if it fails set pageCount to -1
void rtl::Book::SetPageCount(std::string pageCount) {
    try {
        int newPageCount = std::stoi(pageCount);
        //pageCount cannot be less than 1, if it is don't change anything
        if (newPageCount <= 0) {
            return;
        }
        
        this->pageCount = newPageCount;
    } catch (std::invalid_argument) {
        //TODO: Log error
        //keep pageCount what it was
    }
    
    return;
}

void rtl::Book::SetGenre(Genre genre) {
    this->genre = genre;
    return;
}

void rtl::Book::SetGenre(std::string genre) {
    this->genre = ConvertStringToGenre(genre);
    return;
}

void rtl::Book::SetPublishDate(time_t publishDate) {
    this->publishDate = *std::gmtime(&publishDate);
    this->publishDate.tm_sec = 0;
    this->publishDate.tm_min = 0;
    this->publishDate.tm_hour = 0;
    this->publishDate.tm_wday = 0;
    this->publishDate.tm_isdst = 0;
    this->publishDate.tm_gmtoff = 0;
    this->publishDate.tm_zone = nullptr;
    
    return;
}

bool rtl::Book::SetPublishDate(std::string publishDate) {
    try {
        auto d = boost::gregorian::from_string(publishDate);
        this->publishDate = boost::gregorian::to_tm(d);
    } catch (std::exception& ex) {
        //TODO: log error
        return false;
    }
    
    return true;
}

void rtl::Book::AddOclc(std::string oclc) {
    this->oclcVector.push_back(oclc);
    return;
}

void rtl::Book::AddIsbn(std::string isbn) {
    //TODO: validate ISBN
    this->isbnVector.push_back(isbn);
    return;
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, time_t publishDate) {
    this->author = author;
    this->title = title;
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(genre);
    this->SetPublishDate(publishDate);
    this->authorId = rtl::GenerateId(this->GetAuthor());
    this->bookId = rtl::GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
    
    return;
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate) {
    this->author = author;
    this->title = title;
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(genre);
    this->SetPublishDate(publishDate);
    this->authorId = rtl::GenerateId(this->GetAuthor());
    this->bookId = rtl::GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::string isbn, std::string oclc) {
    this->author = author;
    this->title = title;
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(ConvertStringToGenre(genre));
    this->SetPublishDate(publishDate);
    this->AddIsbn(isbn);
    this->AddOclc(oclc);
    this->authorId = rtl::GenerateId(this->GetAuthor());
    this->bookId = rtl::GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::vector<std::string> isbn, std::vector<std::string> oclc) {
    this->author = author;
    this->title = title;
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(ConvertStringToGenre(genre));
    this->SetPublishDate(publishDate);
    this->isbnVector = isbn;
    this->oclcVector = oclc;
    this->authorId = rtl::GenerateId(this->GetAuthor());
    this->bookId = rtl::GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
}

bool rtl::operator==(const rtl::Book& lhs, const rtl::Book& rhs) {
    if (!(lhs.GetAuthorId() == rhs.GetAuthorId())) { return false; }
    if (!(lhs.GetBookId() == rhs.GetBookId())) { return false; }
    if (!(lhs.GetIsbn() == rhs.GetIsbn())) { return false; }
    if (!(lhs.GetOclc() == rhs.GetOclc())) { return false; }
    if (!(lhs.GetAuthor() == rhs.GetAuthor())) { return false; }
    if (!(lhs.GetTitle() == rhs.GetTitle())) { return false; }
    if (!(lhs.GetPublisher() == rhs.GetPublisher())) { return false; }
    if (!(lhs.GetSeries() == rhs.GetSeries())) { return false; }
    if (!(lhs.GetGenre() == rhs.GetGenre())) { return false; }
    if (!(lhs.GetPageCount() == rhs.GetPageCount())) { return false; }
    if (!(lhs.PrintPublishDate() == rhs.PrintPublishDate())) { return false; }
    
    return true;
}

bool rtl::operator!=(const rtl::Book& lhs, const rtl::Book& rhs) {
    return !operator==(lhs, rhs);
}

bool rtl::operator<(const rtl::Book& lhs, const rtl::Book& rhs) {
    //TODO: see if this can be simplified 
    //sort by author -> series -> publish date -> title
    
    if (lhs.GetAuthor() < rhs.GetAuthor()) { return true; }
    else if (lhs.GetAuthor() > rhs.GetAuthor()) { return false; }
    else {
        if (lhs.GetSeries() < rhs.GetSeries()) { return true; }
        else if (lhs.GetSeries() > rhs.GetSeries()) { return false; }
        else {
            tm lhstm;
            tm rhstm;
            time_t lhstt;
            time_t rhstt;
            
            lhstm = lhs.GetPublishDate();
            lhstt = std::mktime(&lhstm);
            rhstm = rhs.GetPublishDate();
            rhstt = std::mktime(&rhstm);
            
            if (lhstt < rhstt) { return true; }
            else if (lhstt > rhstt) { return false; }
            else {
                if (lhs.GetTitle() < rhs.GetTitle()) { return true; }
                else if (lhs.GetTitle() > rhs.GetTitle()) { return false; }
            }
        }
    }
    
    return false;
}

bool rtl::operator>(const rtl::Book& lhs, const rtl::Book& rhs) {
    return operator<(rhs, lhs);
}

bool rtl::operator<=(const rtl::Book& lhs, const rtl::Book& rhs) {
    return !operator>(lhs, rhs);
}

bool rtl::operator>=(const rtl::Book& lhs, const rtl::Book& rhs) {
    return !operator<(lhs, rhs);
}

