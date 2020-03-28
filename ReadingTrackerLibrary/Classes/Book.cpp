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
    //TODO: more validation ISBN
    auto isbnEnd = std::remove_if(std::begin(isbn), std::end(isbn), [&](auto x){
        return (x == '-');
    });
    isbn.erase(isbnEnd, isbn.end());
    for (auto x : isbn) {
        if (!std::isdigit(x)) {
            //TODO: log this
            return;
        }
    }
    this->isbnVector.push_back(isbn);
    return;
}

rtl::SetsPtr rtl::Book::GetUpdateFunction(std::string input) {
    //TODO: implement this
    SetsPtr returnPtr = nullptr;
    
    return returnPtr;
}

std::string rtl::Book::PrintJson() const {
    std::string returnString = R"({"bookId":")" + this->GetBookId();
    
    returnString += R"(","isbn":[)";
    std::vector<std::string> isbnVector = this->GetIsbn();
    for (int i = 0; i < isbnVector.size(); ++i) {
        returnString += R"(")";
        returnString += isbnVector.at(i);
        returnString += R"(")";
        if (i < isbnVector.size() - 1) {
            returnString += R"(,)";
        }
    }
    
    returnString += R"(],"oclc":[)";
    std::vector<std::string> oclcVector = this->GetOclc();
    for (int i = 0; i < oclcVector.size(); ++i) {
        returnString += R"(")";
        returnString += oclcVector.at(i);
        returnString += R"(")";
        if (i < oclcVector.size() - 1) {
            returnString += R"(,)";
        }
    }
    returnString += R"(],"author":")" + this->GetAuthor();
    returnString += R"(","authorId":")" + this->GetAuthorId();
    returnString += R"(","title":")" + this->GetTitle();
    returnString += R"(","series":")" + this->GetSeries();
    returnString += R"(","publisher":")" + this->GetPublisher();
    returnString += R"(","genre":")" + this->PrintGenre();
    returnString += R"(","pageCount":)" + std::to_string(this->GetPageCount());
    returnString += R"(,"publishDate":")" + this->PrintPublishDate();
    returnString += R"("})";
    return returnString;
    
}

std::string rtl::Book::PrintSimple() const {
    //Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kWidthAuthor);
    returnStr << std::left << this->GetAuthor().substr(0, kWidthAuthor - 1);
    returnStr.width(kWidthTitle);
    returnStr << std::left << this->GetTitle().substr(0, kWidthTitle - 1);
    returnStr.width(kWidthSeries);
    returnStr << std::left << this->GetSeries().substr(0, kWidthSeries - 1);
    returnStr.width(kWidthPage);
    returnStr << std::left << std::to_string(this->GetPageCount()).substr(0, kWidthPage);
    
    return returnStr.str();
}

std::string rtl::Book::PrintDetailed() const {
    /*
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
    returnStr << std::setw(15) << "Title: " << std::setw(65) << this->GetTitle().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "BookId: " << std::setw(65) << this->GetBookId().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Author Name: " << std::setw(65) << this->GetAuthor().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "AuthorId: " << std::setw(65) << this->GetAuthorId().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Series: " << std::setw(65) << this->GetSeries().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Genre: " << std::setw(65) << this->PrintGenre().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Page Count: " << std::setw(65) << std::to_string(this->GetPageCount()).substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Publisher: " << std::setw(65) << this->GetPublisher().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << "Publish Date: " << std::setw(65) << this->PrintPublishDate().substr(0, 65) << std::endl;
    
    returnStr << std::setw(15) << "ISBN: ";
    std::string seperator = "";
    std::string isbnString = "";
    for (auto x : this->GetIsbn()) {
        isbnString += seperator + x;
        seperator = ", ";
    }
    returnStr << std::setw(65) << isbnString.substr(0, 65) << std::endl;
    seperator = "";
    
    returnStr << std::setw(15) << "OCLC: ";
    std::string oclcString = "";
    for (auto x : this->GetOclc()) {
        oclcString += seperator + x;
        seperator = ", ";
    }
    returnStr << std::setw(65) << oclcString.substr(0, 65) << std::endl;
    seperator = "";
    
    return returnStr.str();
}

std::string rtl::Book::PrintHeader() const {
    //Author              Title                              Series              Pages
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(kWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(kWidthTitle);
    returnStr << std::left << "Title";
    returnStr.width(kWidthSeries);
    returnStr << std::left << "Series";
    returnStr.width(kWidthPage);
    returnStr << std::left << "Pages";
    
    return returnStr.str();
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, time_t publishDate) {
    this->author = author;
    this->title = title;
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(genre);
    this->SetPublishDate(publishDate);
    this->authorId = this->GenerateId(this->GetAuthor());
    this->bookId = this->GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
    
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
    this->authorId = this->GenerateId(this->GetAuthor());
    this->bookId = this->GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
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
    this->authorId = this->GenerateId(this->GetAuthor());
    this->bookId = this->GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
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
    this->authorId = this->GenerateId(this->GetAuthor());
    this->bookId = this->GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
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


