//
//  Book.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "Book.hpp"

rtl::Genre rtl::ConvertStringToGenre(std::string genre) {
    rtl::Genre returnGenre;
    
    if (genre == "detective") { returnGenre = rtl::detective; }
    else if (genre == "dystopia") { returnGenre = rtl::dystopia; }
    else if (genre == "fantasy") { returnGenre = rtl::fantasy; }
    else if (genre == "mystery") { returnGenre = rtl::mystery; }
    else if (genre == "romance") { returnGenre = rtl::romance; }
    else if (genre == "science fiction" || genre == "sci fi") { returnGenre = rtl::scienceFiction; }
    else if (genre == "thriller") { returnGenre = rtl::thriller; }
    else if (genre == "western") { returnGenre = rtl::western; }
    else { returnGenre = rtl::genreNotSet; }
    return returnGenre;
}

std::string rtl::ConvertGenreToString(rtl::Genre genre) {
    std::string returnString;
    switch(genre) {
        case rtl::detective:
            returnString = "detective";
            break;
        case rtl::dystopia:
            returnString = "dystopia";
            break;
        case rtl::fantasy:
            returnString = "fantasy";
            break;
        case rtl::mystery:
            returnString = "mystery";
            break;
        case rtl::romance:
            returnString = "romance";
            break;
        case rtl::scienceFiction:
            returnString = "science fiction";
            break;
        case rtl::thriller:
            returnString = "thriller";
            break;
        case rtl::western:
            returnString = "western";
            break;
        case rtl::genreNotSet: //fall through to default
        default:
            returnString = "genre not set";
            break;
    }
    
    return returnString;
}

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

std::string rtl::Book::GetBookId() const {
    return this->bookId;
}

std::string rtl::Book::PrintJson() const {
    std::string returnString = R"({"bookId":")" + this->GetBookId();
    returnString += R"(","isbn":[)";
    for (int i = 0; i < this->isbnVector.size(); ++i) {
        returnString += R"(")";
        returnString += isbnVector.at(i);
        returnString += R"(")";
        if (i < this->isbnVector.size() - 1) {
            returnString += R"(,)";
        }
    }
    returnString += R"(],"oclc":[)";
    for (int i = 0; i < this->oclcVector.size(); ++i) {
        returnString += R"(")";
        returnString += oclcVector.at(i);
        returnString += R"(")";
        if (i < this->oclcVector.size() - 1) {
            returnString += R"(,)";
        }
    }
    returnString += R"(],"author":")" + this->GetAuthor();
    returnString += R"(","title":")" + this->GetTitle();
    returnString += R"(","series":")" + this->GetSeries();
    returnString += R"(","publisher":")" + this->GetPublisher();
    returnString += R"(","genre":")" + this->PrintGenre();
    returnString += R"(","pageCount":)" + std::to_string(this->GetPageCount());
    returnString += R"(,"publishDate":")" + this->PrintPublishDate();
    returnString += R"("})";
    return returnString;
}

//Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541
std::string rtl::Book::PrintCommandLine() const {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(Book::kWidthAuthor);
    returnStr << std::left << this->GetAuthor().substr(0, Book::kWidthAuthor - 1);
    returnStr.width(Book::kWidthTitle);
    returnStr << std::left << this->GetTitle().substr(0, Book::kWidthTitle - 1);
    returnStr.width(Book::kWidthSeries);
    returnStr << std::left << this->GetSeries().substr(0, Book::kWidthSeries - 1);
    returnStr.width(Book::kWidthPage);
    returnStr << std::left << std::to_string(this->GetPageCount()).substr(0, Book::kWidthPage);
    
    return returnStr.str();
}

//Author              Title                              Series              Pages
std::string rtl::Book::PrintCommandLineHeaders() {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(Book::kWidthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(Book::kWidthTitle);
    returnStr << std::left << "Title";
    returnStr.width(Book::kWidthSeries);
    returnStr << std::left << "Series";
    returnStr.width(Book::kWidthPage);
    returnStr << std::left << "Pages";
    
    return returnStr.str();
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
    this->bookId = rtl::GenerateId(this->GetAuthor() + ' ' + this->GetTitle());
}

bool rtl::operator==(const rtl::Book& lhs, const rtl::Book& rhs) {
    if (lhs.PrintJson() == rhs.PrintJson()) {
        return true;
    }
    
    return false;
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

//TODO: introduce something to handle ints larger than long long (boost?)
std::string rtl::GenerateId(const std::string& input) {
    //input is supposed to be clean/validated before this function
    //split string by word
    //toupper each word
    //convert each word to int * length of word + 13 for each word already done
    //add each int together
    //convert answer to hexadecimal string
    //return string
    
    std::vector<std::string> items;
    std::string token = "";
    std::stringstream ss(input);
    while (std::getline(ss, token, ' ')) {
        items.push_back(std::move(token));
    }
    
    unsigned long long id = 1;
    int adder = 13;
    for (std::string x : items) {
        std::transform(std::begin(x), std::end(x), std::begin(x), ::toupper);
        unsigned long long word = 0;
        for (char y : x) {
            word += y;
        }
        word *= x.size();
        word += adder;
        adder += 13;
        id *= word;
    }
    
    ss.str(std::string());
    ss.clear();
    ss << std::hex <<  id;
    
    return ss.str();
}
