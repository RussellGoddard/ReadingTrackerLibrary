//
//  Book.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "Book.hpp"

//used for printCommandLine and printCommandLineHeaders
int widthAuthor = 20;
int widthTitle = 35;
int widthSeries = 20;
int widthPage = 5;

int rtl::convertAbbrMonthToInt(std::string month) {
    if (month == "Jan") {
        return 0;
    }
    else if (month == "Feb") {
        return 1;
    }
    else if (month == "Mar") {
        return 2;
    }
    else if (month == "Apr") {
        return 3;
    }
    else if (month == "May") {
        return 4;
    }
    else if (month == "Jun") {
        return 5;
    }
    else if (month == "Jul") {
        return 6;
    }
    else if (month == "Aug") {
        return 7;
    }
    else if (month == "Sep") {
        return 8;
    }
    else if (month == "Oct") {
        return 9;
    }
    else if (month == "Nov") {
        return 10;
    }
    else if (month == "Dec") {
        return 11;
    }
    return -1;
}

rtl::Genre rtl::convertStringToGenre(std::string genre) {
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

std::string rtl::convertGenreToString(rtl::Genre genre) {
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

std::string rtl::Book::getAuthor() const {
    return this->author;
}

std::string rtl::Book::getTitle() const {
    return this->title;
}

std::string rtl::Book::getSeries() const {
    return series;
}

int rtl::Book::getPageCount() const {
    return pageCount;
}

std::string rtl::Book::getPublisher() const {
    return this->publisher;
}

rtl::Genre rtl::Book::getGenre() const {
    return genre;
}

std::string rtl::Book::printGenre() const {
    return convertGenreToString(this->genre);
}

std::string rtl::Book::getOclc() const {
    return this->oclc;
}

std::string rtl::Book::printJson() const {
    std::string returnString = "test\"\"";
    returnString = R"({"author":")" + this->getAuthor() + R"(","title":")" + this->getTitle() + R"(","series":")" + this->getSeries() + R"(","publisher":")" + this->getPublisher() + R"(","genre":")" + this->printGenre() + R"(","pageCount":)" + std::to_string(this->getPageCount()) + R"(,"publishDate":")" + this->printPublishDate() + R"("})";
    return returnString;
}

//Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541
std::string rtl::Book::printCommandLine() const {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(widthAuthor);
    returnStr << std::left << this->getAuthor().substr(0, widthAuthor - 1);
    returnStr.width(widthTitle);
    returnStr << std::left << this->getTitle().substr(0, widthTitle - 1);
    returnStr.width(widthSeries);
    returnStr << std::left << this->getSeries().substr(0, widthSeries - 1);
    returnStr.width(widthPage);
    returnStr << std::left << std::to_string(this->getPageCount()).substr(0, widthPage);
    
    return returnStr.str();
}

//Author              Title                              Series              Pages
std::string rtl::Book::printCommandLineHeaders() {
    std::stringstream returnStr;
    returnStr.fill(' ');
    
    returnStr.width(widthAuthor);
    returnStr << std::left << "Author";
    returnStr.width(widthTitle);
    returnStr << std::left << "Title";
    returnStr.width(widthSeries);
    returnStr << std::left << "Series";
    returnStr.width(widthPage);
    returnStr << std::left << "Pages";
    
    return returnStr.str();
}

tm rtl::Book::getPublishDate() const {
    return this->publishDate;
}

time_t rtl::Book::getPublishDateAsTimeT() {
    return std::mktime(&this->publishDate);
}

std::string rtl::Book::printPublishDate() const {
    char buffer [50];
    std::strftime(buffer, 50, "%b %d %Y", &this->publishDate);
    return buffer;
}

void rtl::Book::setAuthor(std::string author) {
    this->author = author;
    
    return;
}

void rtl::Book::setTitle(std::string title) {
    this->title = title;
    
    return;
}

void rtl::Book::setSeries(std::string series) {
    this->series = series;
    
    return;
}

void rtl::Book::setPublisher(std::string publisher) {
    this->publisher = publisher;
    
    return;
}

void rtl::Book::setPageCount(int pageCount) {
    //books can only have positive page counts, if it isn't mark as -1 as error
    if (pageCount <= 0) {
        pageCount = -1;
    }
    
    this->pageCount = pageCount;
    
    return;
}

//pageCount can't be changed by character, keep whatever is in there before
void rtl::Book::setPageCount(char pageCount) {
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
void rtl::Book::setPageCount(std::string pageCount) {
    try {
        int newPageCount = std::stoi(pageCount);
        //pageCount cannot be less than 1, if it is don't change anything
        if (newPageCount <= 0) {
            return;
        }
        
        this->pageCount = newPageCount;
    } catch (std::invalid_argument) {
        //keep pageCount what it was
    }
    
    return;
}

void rtl::Book::setGenre(Genre genre) {
    this->genre = genre;
    
    return;
}

void rtl::Book::setGenre(std::string genre) {
    this->genre = convertStringToGenre(genre);
    
    return;
}

void rtl::Book::setPublishDate(time_t publishDate) {
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

void rtl::Book::setPublishDate(std::string publishDate) {
    if (publishDate.size() != 11) {
        return;
    }
    
    std::string month = publishDate.substr(0, 3);
    std::string day = publishDate.substr(4, 2);
    std::string year = publishDate.substr(7, 4);
    
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
    
    this->publishDate.tm_year = intYear;
    this->publishDate.tm_mon = intMonth;
    this->publishDate.tm_mday = intDay;
    this->publishDate.tm_sec = 0;
    this->publishDate.tm_min = 0;
    this->publishDate.tm_hour = 0;
    this->publishDate.tm_wday = 0;
    this->publishDate.tm_isdst = 0;
    this->publishDate.tm_gmtoff = 0;
    this->publishDate.tm_zone = nullptr;
    
    time_t validateTime = std::mktime(&this->publishDate);
    
    this->publishDate = *std::gmtime(&validateTime);

    return;
}

void rtl::Book::setOclc(std::string oclc) {
    this->oclc = oclc;
    
    return;
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, time_t publishDate) {
    this->setAuthor(author);
    this->setTitle(title);
    this->setSeries(series);
    this->setPublisher(publisher);
    this->setPageCount(pageCount);
    this->setGenre(genre);
    this->setPublishDate(publishDate);
    
    return;
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate) {
    this->setAuthor(author);
    this->setTitle(title);
    this->setSeries(series);
    this->setPublisher(publisher);
    this->setPageCount(pageCount);
    this->setGenre(genre);
    this->setPublishDate(publishDate);
    
    return;
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate) {
    this->setAuthor(author);
    this->setTitle(title);
    this->setSeries(series);
    this->setPublisher(publisher);
    this->setPageCount(pageCount);
    this->setGenre(convertStringToGenre(genre));
    this->setPublishDate(publishDate);
    
    return;
}

bool rtl::operator==(const rtl::Book& lhs, const rtl::Book& rhs) {
    if (lhs.printJson() == rhs.printJson()) {
        return true;
    }
    
    return false;
}

bool rtl::operator!=(const rtl::Book& lhs, const rtl::Book& rhs) {
    return !operator==(lhs, rhs);
}

bool rtl::operator<(const rtl::Book& lhs, const rtl::Book& rhs) {
    //see if this can be simplified TODO
    //sort by author -> series -> publish date -> title
    tm lhstm;
    tm rhstm;
    time_t lhstt;
    time_t rhstt;
    
    if (lhs.getAuthor() < rhs.getAuthor()) { return true; }
    else if (lhs.getAuthor() > rhs.getAuthor()) { return false; }
    else {
        if (lhs.getSeries() < rhs.getSeries()) { return true; }
        else if (lhs.getSeries() > rhs.getSeries()) { return false; }
        else {
            lhstm = lhs.getPublishDate();
            lhstt = std::mktime(&lhstm);
            rhstm = rhs.getPublishDate();
            rhstt = std::mktime(&rhstm);
            
            if (lhstt < rhstt) { return true; }
            else if (lhstt > rhstt) { return false; }
            else {
                if (lhs.getTitle() < rhs.getTitle()) { return true; }
                else if (lhs.getTitle() > rhs.getTitle()) { return false; }
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
