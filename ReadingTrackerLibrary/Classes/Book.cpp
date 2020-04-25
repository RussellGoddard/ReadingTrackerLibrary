//
//  Book.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#include "Book.hpp"

std::vector<std::string> rtl::Book::GetAuthors() const {
    return this->authors;
}

std::string rtl::Book::GetAuthorsString() const {
    std::string returnStr;
    std::string delim = "";
    bool isFirstAuthor = true;
    for (std::string x : this->authors) {
        returnStr += delim;
        returnStr += x;
        if (isFirstAuthor) {
            delim = ", ";
            isFirstAuthor = false;
        }
    }
    
    return returnStr;
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

std::vector<std::string> rtl::Book::GetAuthorId() const {
    return this->authorId;
}

std::string rtl::Book::GetAuthorIdString() const {
    std::string returnStr;
    std::string delim = "";
    bool isFirstId = true;
    for (std::string x : this->GetAuthorId()) {
        returnStr += delim;
        returnStr += x;
        if (isFirstId) {
            delim = ", ";
            isFirstId = false;
        }
    }
    
    return returnStr;
}

std::string rtl::Book::GetBookId() const {
    return this->bookId;
}

tm rtl::Book::GetPublishDate() const {
    return this->publishDate;
}

boost::posix_time::ptime rtl::Book::GetPublishDateAsPosixTime() {
    return boost::posix_time::ptime_from_tm(this->publishDate);
}

std::string rtl::Book::PrintPublishDate() const {
    auto returnDate = boost::gregorian::date_from_tm(this->publishDate);
    return boost::gregorian::to_simple_string(returnDate);
}

bool rtl::Book::AddAuthor(std::string author) {
    rtl::Book::RemoveNonPrint(author);
    if (author.empty()) {
        return false;
    }

    this->authors.push_back(author);
    return true;
}

bool rtl::Book::SetTitle(std::string title) {
    rtl::Book::RemoveNonPrint(title);
    if (title.empty()) {
        return false;
    }
    
    this->title = title;
    return true;
}

bool rtl::Book::SetSeries(std::string series) {
    rtl::Book::RemoveNonPrint(series);
    if (series.empty()) {
        return false;
    }
    
    this->series = series;
    return true;
}

bool rtl::Book::SetPublisher(std::string publisher) {
    rtl::Book::RemoveNonPrint(publisher);
    if (publisher.empty()) {
        return false;
    }
    this->publisher = publisher;
    return true;
}

bool rtl::Book::SetPageCount(int pageCount) {
    //books can only have positive page counts, if it isn't mark as -1 as error
    if (pageCount <= 0) {
        return false;
    }
    this->pageCount = pageCount;
    return true;
}

//pageCount can't be changed by character, keep whatever is in there before
bool rtl::Book::SetPageCount(char pageCount) {
    int newPageCount = -1;
    std::stringstream sstream;
    
    sstream << pageCount;
    sstream >> newPageCount;
    
    //if newPageCount == 0 then failed to convert to an integer or the pageCount passed was zero which is invalid
    if (newPageCount <= 0) {
        return false;
    }
    this->pageCount = newPageCount;
    
    return true;
}

//will attempt a stoi if it fails set pageCount to -1
bool rtl::Book::SetPageCount(std::string pageCount) {
    try {
        int newPageCount = std::stoi(pageCount);
        //pageCount cannot be less than 1, if it is don't change anything
        if (newPageCount <= 0) {
            return false;
        }
        
        this->pageCount = newPageCount;
    } catch (std::invalid_argument ex) {
        std::string exceptionMessage = ex.what();
        exceptionMessage += " input pageCount: " + pageCount;
        BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        return false;
    }
    
    return true;
}

bool rtl::Book::SetGenre(Genre genre) {
    if (genre == rtl::Genre::genreNotSet) {
        return false;
    }
    this->genre = genre;
    return true;
}

bool rtl::Book::SetGenre(std::string genre) {
    rtl::Book::RemoveNonPrint(genre);
    if (genre.empty()) {
        return false;
    }
    
    rtl::Genre newGenre = ConvertStringToGenre(genre);
    
    if (newGenre == rtl::Genre::genreNotSet) {
        return false;
    }
    
    this->genre = newGenre;
    return true;
}

bool rtl::Book::SetPublishDate(boost::posix_time::ptime publishDate) {
    this->publishDate = boost::posix_time::to_tm(publishDate);
    return true;
}

bool rtl::Book::SetPublishDate(std::string publishDate) {
    rtl::Book::RemoveNonPrint(publishDate);
    if (publishDate.empty()) {
        return false;
    }
    
    try {
        auto d = boost::gregorian::from_string(publishDate);
        this->publishDate = boost::gregorian::to_tm(d);
    } catch (std::exception& ex) {
        std::string exceptionMessage = ex.what();
        exceptionMessage += " input publishDate: " + publishDate;
        BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        return false;
    }
    
    return true;
}

//TODO: oclc validation
bool rtl::Book::AddOclc(std::string oclc) {
    rtl::Book::RemoveNonPrint(oclc);
    if (oclc.empty()) {
        return false;
    }
    
    this->oclcVector.push_back(oclc);
    return true;
}

//TODO: better validation of ISBN
bool rtl::Book::AddIsbn(std::string isbn) {
    rtl::Book::RemoveNonPrint(isbn);
    if (isbn.empty()) {
        return false;
    }
    
    auto isbnEnd = std::remove_if(std::begin(isbn), std::end(isbn), [&](auto x){ return (x == '-'); });
    isbn.erase(isbnEnd, isbn.end());
    for (auto x : isbn) {
        if (!std::isdigit(x)) {
            BOOST_LOG_TRIVIAL(warning) << "isbn did not contain all digits";
            return false;
        }
    }
    this->isbnVector.push_back(isbn);
    return true;
}

rtl::SetsPtr rtl::Book::GetUpdateFunction(std::string input) {
    //TODO: make case insensitive
    //TODO: prompt user to make new book if they want to change author or title
    if (input == this->kAuthor) { return nullptr; }
    else if (input == this->kAuthorId) { return nullptr; }
    else if (input == this->title) { return nullptr; }
    else if (input == this->kBookId) { return nullptr; }
    else if (input == this->kSeries) { return static_cast<rtl::SetsPtr>(&rtl::Book::SetSeries); }
    else if (input == this->kGenre) { return static_cast<rtl::SetsPtr>(&rtl::Book::SetGenre); }
    else if (input == this->kPageCount) { return static_cast<rtl::SetsPtr>(&rtl::Book::SetPageCount); }
    else if (input == this->kPublisher) { return static_cast<rtl::SetsPtr>(&rtl::Book::SetPublisher); }
    else if (input == this->kPublishDate) { return static_cast<rtl::SetsPtr>(&rtl::Book::SetPublishDate); }
    else if (input == this->kIsbn) { return static_cast<rtl::SetsPtr>(&rtl::Book::AddIsbn); }
    else if (input == this->kOclc) { return static_cast<rtl::SetsPtr>(&rtl::Book::AddOclc); }
    else { return nullptr; }
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
        returnString += "\"";
        returnString += oclcVector.at(i);
        returnString += "\"";
        if (i < oclcVector.size() - 1) {
            returnString += ",";
        }
    }
    returnString += R"(],"author":[)";
    std::vector<std::string> authorVector = this->GetAuthors();
    for (int i = 0; i < authorVector.size(); ++i) {
        returnString += "\"";
        returnString += authorVector.at(i);
        returnString += "\"";
        if (i < authorVector.size() - 1) {
            returnString += ",";
        }
    }
    returnString += R"(],"authorId":[)";
    std::vector<std::string> authorIdVector = this->GetAuthorId();
    for (int i = 0; i < authorIdVector.size(); ++i) {
        returnString += "\"";
        returnString += authorIdVector.at(i);
        returnString += "\"";
        if (i < authorIdVector.size() - 1) {
            returnString += ",";
        }
    }
    returnString += R"(],"title":")" + this->GetTitle();
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
    std::string authorsConcat = "";
    bool isFirstAuthor = true;
    std::string delim = "";
    for (std::string x : this->GetAuthors()) {
        authorsConcat += delim;
        authorsConcat += x;
        if (isFirstAuthor) {
            delim = ", ";
            isFirstAuthor = false;
        }
    }
    
    returnStr.width(kWidthAuthor);
    returnStr << std::left << authorsConcat.substr(0, kWidthAuthor - 1);
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
    returnStr << std::setw(15) << this->kTitle + ": " << std::setw(65) << this->GetTitle().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kBookId + ": " << std::setw(65) << this->GetBookId().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kAuthor + ": " << std::setw(65) << this->GetAuthorsString().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kAuthorId + ": " << std::setw(65) << this->GetAuthorIdString().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kSeries + ": " << std::setw(65) << this->GetSeries().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kGenre + ": " << std::setw(65) << this->PrintGenre().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kPageCount + ": " << std::setw(65) << std::to_string(this->GetPageCount()).substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kPublisher + ": " << std::setw(65) << this->GetPublisher().substr(0, 65) << std::endl;
    returnStr << std::setw(15) << this->kPublishDate + ": " << std::setw(65) << this->PrintPublishDate().substr(0, 65) << std::endl;
    
    returnStr << std::setw(15) << this->kIsbn + ": ";
    std::string seperator = "";
    std::string isbnString = "";
    for (auto x : this->GetIsbn()) {
        isbnString += seperator + x;
        seperator = ", ";
    }
    returnStr << std::setw(65) << isbnString.substr(0, 65) << std::endl;
    seperator = "";
    
    returnStr << std::setw(15) << this->kOclc + ": ";
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

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, boost::posix_time::ptime publishDate) {
    if (!this->AddAuthor(author)) {
        throw std::invalid_argument("author cannot be empty");
    }
    if (!this->SetTitle(title)) {
        throw std::invalid_argument("title cannot be empty");
    }
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(genre);
    this->SetPublishDate(publishDate);
    for (auto x : this->authors) {
        this->authorId.push_back(this->GenerateId(x));
    }
    this->bookId = this->GenerateId(this->GetAuthorsString() + ' ' + this->GetTitle());
    
    return;
}

rtl::Book::Book(std::vector<std::string> author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, boost::posix_time::ptime publishDate) {
    for (auto x : author) {
        if (!this->AddAuthor(x)) {
            throw std::invalid_argument("author cannot be empty");
        }
    }
    if (!this->SetTitle(title)) {
        throw std::invalid_argument("title cannot be empty");
    }
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(genre);
    this->SetPublishDate(publishDate);
    for (auto x : this->authors) {
        this->authorId.push_back(this->GenerateId(x));
    }
    this->bookId = this->GenerateId(this->GetAuthorsString() + ' ' + this->GetTitle());
    
    return;
}

rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate) {
    if (!this->AddAuthor(author)) {
        throw std::invalid_argument("author cannot be empty");
    }
    if (!this->SetTitle(title)) {
        throw std::invalid_argument("title cannot be empty");
    }
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(genre);
    this->SetPublishDate(publishDate);
    for (auto x : this->authors) {
        this->authorId.push_back(this->GenerateId(x));
    }
    this->bookId = this->GenerateId(this->GetAuthorsString() + ' ' + this->GetTitle());
}

rtl::Book::Book(std::vector<std::string> authors, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::vector<std::string> isbn, std::vector<std::string> oclc) {
    for (auto x : authors) {
        if (!this->AddAuthor(x)) {
            throw std::invalid_argument("author cannot be empty");
        }
    }
    if (!this->SetTitle(title)) {
        throw std::invalid_argument("title cannot be empty");
    }
    this->SetSeries(series);
    this->SetPublisher(publisher);
    this->SetPageCount(pageCount);
    this->SetGenre(ConvertStringToGenre(genre));
    this->SetPublishDate(publishDate);
    for (auto x : isbn) {
        this->AddIsbn(x);
    }
    for (auto x : oclc) {
        this->AddOclc(x);
    }
    for (auto x : this->authors) {
        this->authorId.push_back(this->GenerateId(x));
    }
    this->bookId = this->GenerateId(this->GetAuthorsString() + ' ' + this->GetTitle());
}

bool rtl::operator==(const rtl::Book& lhs, const rtl::Book& rhs) {
    if (!(lhs.GetAuthorId() == rhs.GetAuthorId())) { return false; }
    if (!(lhs.GetBookId() == rhs.GetBookId())) { return false; }
    if (!(lhs.GetIsbn() == rhs.GetIsbn())) { return false; }
    if (!(lhs.GetOclc() == rhs.GetOclc())) { return false; }
    if (!(lhs.GetAuthors() == rhs.GetAuthors())) { return false; }
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
    
    if (lhs.GetAuthors() < rhs.GetAuthors()) { return true; }
    else if (lhs.GetAuthors() > rhs.GetAuthors()) { return false; }
    else {
        if (lhs.GetSeries() < rhs.GetSeries()) { return true; }
        else if (lhs.GetSeries() > rhs.GetSeries()) { return false; }
        else {
            tm lhstm = lhs.GetPublishDate();
            tm rhstm = rhs.GetPublishDate();
            boost::posix_time::ptime lhspt = boost::posix_time::ptime_from_tm(lhstm);
            boost::posix_time::ptime rhspt = boost::posix_time::ptime_from_tm(rhstm);
            
            if (lhspt < rhspt) { return true; }
            else if (lhspt > rhspt) { return false; }
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


