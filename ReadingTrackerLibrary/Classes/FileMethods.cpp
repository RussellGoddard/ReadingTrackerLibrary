//
//  FileMethods.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#include "FileMethods.hpp"

std::string& rtl::leftTrim(std::string& input) {
  auto it2 =  std::find_if(input.begin(), input.end(), [](char ch){ return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(input.begin(), it2);
  return input;
}

std::string& rtl::rightTrim(std::string& input)
{
  auto it1 = std::find_if(input.rbegin(), input.rend(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(it1.base(), input.end());
  return input;
}

std::string& rtl::trim(std::string& str)
{
   return rtl::leftTrim(rtl::rightTrim(str));
}

bool rtl::saveJson(std::vector<nlohmann::json> input, std::fstream& saveFile) {
    //check if file exists/is locked by another process
    if(!saveFile.good()) {
        saveFile.close();
        return false;
    };
    
    for (auto x : input) {
        saveFile << x << std::endl;
    }
    
    return true;
}

rtl::ReadBook rtl::convertJsonToReadBook(nlohmann::json json) {
    
    int readerId = json["readerId"].get<int>();
    std::string author = json["author"].get<std::string>();
    std::string title = json["title"].get<std::string>();
    std::string series = json["series"].get<std::string>();
    std::string publisher = json["publisher"].get<std::string>();
    int pageCount = json["pageCount"].get<int>();
    std::string genre = json["genre"].get<std::string>();
    std::string publishDate = json["publishDate"].get<std::string>();
    int rating = json["rating"].get<int>();
    std::string time = json["dateRead"].get<std::string>();
    
    return rtl::ReadBook(readerId, author, title, series, publisher, pageCount, genre, publishDate, rating, time);
}

std::shared_ptr<rtl::Book> rtl::convertJsonToBookPtr(nlohmann::json json) {
    std::string author = json["author"].get<std::string>();
    std::string title = json["title"].get<std::string>();
    std::string series = json["series"].get<std::string>();
    std::string publisher = json["publisher"].get<std::string>();
    int pageCount = json["pageCount"].get<int>();
    std::string genre = json["genre"].get<std::string>();
    std::string publishDate = json["publishDate"].get<std::string>();
    
    std::shared_ptr<rtl::Book> newBook = std::make_shared<rtl::Book>(author, title, series, publisher, pageCount, genre, publishDate);
    
    return newBook;
}

std::shared_ptr<rtl::ReadBook> rtl::convertJsonToReadBookPtr(nlohmann::json json) {
    
    int readerId = json["readerId"].get<int>();
    std::string author = json["author"].get<std::string>();
    std::string title = json["title"].get<std::string>();
    std::string series = json["series"].get<std::string>();
    std::string publisher = json["publisher"].get<std::string>();
    int pageCount = json["pageCount"].get<int>();
    std::string genre = json["genre"].get<std::string>();
    std::string publishDate = json["publishDate"].get<std::string>();
    int rating = json["rating"].get<int>();
    std::string time = json["dateRead"].get<std::string>();
    
    std::shared_ptr<rtl::ReadBook> newReadBook = std::make_shared<rtl::ReadBook>(readerId, author, title, series, publisher, pageCount, genre, publishDate, rating, time);
    
    return newReadBook;
}

std::shared_ptr<rtl::Author> rtl::convertJsonToAuthorPtr(nlohmann::json json) {
    std::string name = json["name"].get<std::string>();
    std::string dateBorn = json["dateBorn"].get<std::string>();
    std::vector<std::shared_ptr<rtl::Book>> booksWritten;
    for (auto x : json.at("booksWritten")) {
        booksWritten.push_back(rtl::convertJsonToBookPtr(x));
    }
    
    std::shared_ptr<rtl::Author> newAuthor = std::make_shared<rtl::Author>(name, dateBorn, booksWritten);
    
    return newAuthor;
}

std::vector<std::shared_ptr<rtl::ReadBook>> rtl::InMemoryContainers::getMasterReadBooks() {
    return this->readBookVector;
}

void rtl::InMemoryContainers::addMasterReadBooks(std::vector<std::shared_ptr<rtl::ReadBook>> newReadBookVector) {
    this->addMasterBooks(newReadBookVector); //add readbook to book vector as well (will be discarded if it already exists
    this->readBookVector.insert(std::end(readBookVector), std::begin(newReadBookVector), std::end(newReadBookVector));
    rtl::sortUnique(this->readBookVector);
    return;
}

void rtl::InMemoryContainers::addMasterReadBooks(std::shared_ptr<rtl::ReadBook> newReadBook) {
    this->addMasterBooks(newReadBook); //add readbook to book vector as well (will be discarded if it already exists
    this->readBookVector.push_back(newReadBook);
    rtl::sortUnique(this->readBookVector);
    return;
}

std::vector<std::shared_ptr<rtl::Book>> rtl::InMemoryContainers::getMasterBooks() {
    return this->bookVector;
}

void rtl::InMemoryContainers::addMasterBooks(std::vector<std::shared_ptr<rtl::ReadBook>> newReadBookVector) {
    for (auto x : newReadBookVector) {
        this->bookVector.push_back(x);
    }
    rtl::sortUnique(this->bookVector);
    return;
}

void rtl::InMemoryContainers::addMasterBooks(std::vector<std::shared_ptr<rtl::Book>> newBookVector) {
    this->addMasterAuthors(newBookVector);
    this->bookVector.insert(std::end(this->bookVector), std::begin(newBookVector), std::end(newBookVector));
    rtl::sortUnique(this->bookVector);
    return;
}

void rtl::InMemoryContainers::addMasterBooks(std::shared_ptr<rtl::Book> newBook) {
    this->addMasterAuthors(newBook);
    this->bookVector.push_back(newBook);
    rtl::sortUnique(this->bookVector);
    return;
}

std::vector<std::shared_ptr<rtl::Author>> rtl::InMemoryContainers::getMasterAuthors() {
    return this->authorVector;
}

void rtl::InMemoryContainers::addMasterAuthors(std::vector<std::shared_ptr<rtl::Author>> newAuthorVector) {
    this->authorVector.insert(std::end(this->authorVector), std::begin(newAuthorVector), std::end(newAuthorVector));
    rtl::sortUnique(this->authorVector);
    return;
}

void rtl::InMemoryContainers::addMasterAuthors(std::shared_ptr<rtl::Author> newAuthor) {
    this->authorVector.push_back(newAuthor);
    rtl::sortUnique(this->authorVector);
    return;
}

void rtl::InMemoryContainers::addMasterAuthors(std::shared_ptr<rtl::Book> newBook) {
    if (newBook->getAuthor() != "") {
        std::shared_ptr<rtl::Author> newAuthor = std::make_shared<rtl::Author>(newBook->getAuthor(), rtl::jan2038, newBook);
        this->authorVector.push_back(newAuthor);
        rtl::sortUnique(this->authorVector);
    }
    return;
}

void rtl::InMemoryContainers::addMasterAuthors(std::vector<std::shared_ptr<rtl::Book>> newBookVector) {
    for (auto x : newBookVector) {
        if (x->getAuthor() != "") {
            std::shared_ptr<rtl::Author> newAuthor = std::make_shared<rtl::Author>(x->getAuthor(), rtl::jan2038, newBookVector);
            this->authorVector.push_back(newAuthor);
        }
    }
    rtl::sortUnique(this->authorVector);
    return;
}

void rtl::InMemoryContainers::clearAll() {
    this->readBookVector.clear();
    this->authorVector.clear();
    this->bookVector.clear();
    
    return;
}

//TODO: this whole thing will probably look stupid to me in 6 months 
//had issue with std::unique not actually removing items even with custom comparator
//forced to make my own
template <typename T>
void uniqueVector(std::vector<T>& input) {
    int index = 1;
    
    while (index < input.size()) {
        if (*input.at(index - 1) == *input.at(index)) {
            input.erase(std::begin(input) + index);
        }
        else {
            ++index;
        }
    }
    
    return;
}

template <>
void uniqueVector(std::vector<std::shared_ptr<rtl::Author>>& input) {
    int index = 1;
    
    while (index < input.size()) {
        if (*input.at(index - 1) == *input.at(index)) {
            //if authors are the same combine unique books
            input.at(index - 1)->addBookWritten(input.at(index)->getBooksWritten());
            
            input.erase(std::begin(input) + index);
        }
        else {
            ++index;
        }
    }
    
    return;
}

template <typename T>
bool sortPointers(T lhs, T rhs) {
    return *lhs < *rhs;
}

template <typename T>
void rtl::sortUnique(std::vector<T>& input) {
    
    std::sort(std::begin(input), std::end(input), sortPointers<T>);
    uniqueVector(input);
    
    return;
}

//TODO: investigate a way to remove for loops
bool rtl::InMemoryContainers::saveInMemoryToFile(std::string filePath) {
    bool successfulSave = true;
    std::vector<nlohmann::json> bookJson;
    std::vector<nlohmann::json> readBookJson;
    std::vector<nlohmann::json> authorJson;
    
    for (auto x : this->getMasterBooks()) {
        bookJson.push_back(nlohmann::json::parse(x->printJson()));
    }
    
    for (auto x : this->getMasterReadBooks()) {
        readBookJson.push_back(nlohmann::json::parse(x->printJson()));
    }
    
    for (auto x : this->getMasterAuthors()) {
        authorJson.push_back(nlohmann::json::parse(x->printJson()));
    }
    
    
    std::fstream saveFile;
    saveFile.open(filePath, std::fstream::out);
    if(!saveFile.good()) {
        saveFile.close();
        return false;
    };
    
    if (successfulSave) {
        saveFile << "*[*\n";
        successfulSave = rtl::saveJson(bookJson, saveFile);
    }
    if (successfulSave) {
        saveFile << "*]*\n*[*\n";
        successfulSave = rtl::saveJson(readBookJson, saveFile);
    }
    if (successfulSave) {
        saveFile << "*]*\n*[*\n";
        successfulSave = rtl::saveJson(authorJson, saveFile);
    }
    if (successfulSave) {
        saveFile << "*]*";
        saveFile.close();
    }
    
    return successfulSave;
}

bool rtl::InMemoryContainers::loadInMemoryFromFile(std::string filePath) {
    bool successfulLoad = true;
    int trackLoad = 0;
    std::fstream loadFile;
    std::string line;
    loadFile.open(filePath, std::fstream::in);
    if(!loadFile.good()) {
        loadFile.close();
        return false;
    };
    
    //verify that first line is "*[*"
    std::getline(loadFile, line);
    if (line != "*[*") {
        loadFile.close();
        return false;
    }
    
    while(std::getline(loadFile, line)) {
        if (line == "*[*") {
            continue;
        }
        else if (line == "*]*") {
            ++trackLoad;
        }
        else {
            switch(trackLoad) {
                //book
                case 0 : {
                    this->addMasterBooks(rtl::convertJsonToBookPtr(nlohmann::json::parse(line)));
                    break;
                }
                //readbook
                case 1 : {
                    this->addMasterReadBooks(rtl::convertJsonToReadBookPtr(nlohmann::json::parse(line)));
                    break;
                }
                //author
                case 2 : {
                    this->addMasterAuthors(rtl::convertJsonToAuthorPtr(nlohmann::json::parse(line)));
                    break;
                }
                default : {
                    loadFile.close();
                    return false;
                }
            }
        }
    }
    
    //currently only books, readBooks, and authors supported so trackLoad should end at 3
    if (trackLoad != 3) {
        loadFile.close();
        return false;
    }
    
    if (successfulLoad) {
        loadFile.close();
    }
    
    return successfulLoad;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

//TODO: move this?
bool isDigit(char c) {
    return  std::isdigit(c);
}

//queries the open library for info based on given OCLC or ISBN (10 or 13 digit)
bool rtl::queryBookByIdentifier(std::string identifier, std::string identifierNum, std::vector<std::pair<std::string, std::string>>& getValues) {
    
    //validation checks
    if (rtl::trim(identifier).empty() || rtl::trim(identifierNum).empty()) {
        //TODO: log the error
        return false;
    }
    
    std::transform(std::begin(identifier), std::end(identifier), std::begin(identifier), ::toupper);
    
    if (identifier != "OCLC" && identifier != "ISBN") {
        //TODO: log the error
        return false;
    }
    
    std::remove_if(std::begin(identifierNum), std::end(identifierNum), [](const char& element)
    {
        return !std::isdigit(element); //remove anything not 0-9
    });
    
    if (identifierNum.empty()) {
        return false;
    }
    
    std::string combinedIdentifier = identifier + ':' + identifierNum;
    std::string curlUrl = "https://openlibrary.org/api/books?bibkeys=" + combinedIdentifier + "&jscmd=data&format=json";
    
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, curlUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        nlohmann::json openLibJson = nlohmann::json::parse(readBuffer);
        
        for (auto& x : getValues) {
            if (x.first == "oclc") {
                x.second = openLibJson[combinedIdentifier]["identifiers"][x.first].at(0).get<std::string>();
            }
            else if (x.first == "authors") {
                //TODO: figure out multiple authors
                x.second = openLibJson[combinedIdentifier][x.first].at(0)["name"].get<std::string>();
            }
            else {
                x.second = openLibJson[combinedIdentifier][x.first].get<std::string>();
            }
        }
    }
    
    return true;
}


//TODO: curl query very fragile due to requiring exact capitalization figure out better way (might have to move google books)
bool rtl::queryBookByTitle(std::string title, std::vector<std::pair<std::string, std::string>>& getValues) {
    
    //validation check
    if (rtl::trim(title).empty()) {
        return false;
    }
    
    std::transform(std::begin(title), std::end(title), std::begin(title), [](const char& element)
    {
        return std::isspace(element) ? '_' : element; //replace all whitespace with _
    });
    
    std::string curlUrl = "https://www.wikidata.org/w/api.php?action=wbgetentities&format=json&sites=enwiki&titles=" + title + "&props=descriptions%7Cclaims&languages=en";
    
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, curlUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        nlohmann::json wikiDataJson = nlohmann::json::parse(readBuffer);
        
        std::cout << wikiDataJson << std::endl;
        
        std::string objectId = wikiDataJson["entities"].begin().key();

        //datePublish: P577
        //"time": "+1990-01-15T00:00:00Z",
        boost::gregorian::date datePublished = boost::gregorian::from_string(wikiDataJson["entities"][objectId]["claims"]["P577"].at(0)["mainsnak"]["datavalue"]["value"]["time"].get<std::string>().substr(1, 10));
        
        std::cout << boost::gregorian::to_simple_string(datePublished) << std::endl;
        
        for (auto& x : wikiDataJson["entities"][objectId]["claims"]["P577"].at(0)["mainsnak"]["datavalue"]["value"]["time"].items())
        {
            std::cout << "key: " << x.key() << ", value: " << x.value() << '\n';
        }
        
        //for (auto& x : getValues) {
        //}
    }
    
    return true;
}
