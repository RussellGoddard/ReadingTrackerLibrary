//
//  FileMethods.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#include "FileMethods.hpp"

std::string& leftTrim(std::string& input) {
  auto it2 =  std::find_if(input.begin(), input.end(), [](char ch){ return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(input.begin(), it2);
  return input;
}

std::string& rightTrim(std::string& input)
{
  auto it1 = std::find_if(input.rbegin(), input.rend(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(it1.base(), input.end());
  return input;
}

std::string& trim(std::string& str)
{
   return leftTrim(rightTrim(str));
}

bool saveJson(std::vector<nlohmann::json> input, std::fstream& saveFile) {
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

ReadBook convertJsonToReadBook(nlohmann::json json) {
    
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
    
    return ReadBook(readerId, author, title, series, publisher, pageCount, genre, publishDate, rating, time);
}

std::shared_ptr<Book> convertJsonToBookPtr(nlohmann::json json) {
    std::string author = json["author"].get<std::string>();
    std::string title = json["title"].get<std::string>();
    std::string series = json["series"].get<std::string>();
    std::string publisher = json["publisher"].get<std::string>();
    int pageCount = json["pageCount"].get<int>();
    std::string genre = json["genre"].get<std::string>();
    std::string publishDate = json["publishDate"].get<std::string>();
    
    std::shared_ptr<Book> newBook = std::make_shared<Book>(author, title, series, publisher, pageCount, genre, publishDate);
    
    return newBook;
}

std::shared_ptr<ReadBook> convertJsonToReadBookPtr(nlohmann::json json) {
    
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
    
    std::shared_ptr<ReadBook> newReadBook = std::make_shared<ReadBook>(readerId, author, title, series, publisher, pageCount, genre, publishDate, rating, time);
    
    return newReadBook;
}

std::shared_ptr<Author> convertJsonToAuthorPtr(nlohmann::json json) {
    std::string name = json["name"].get<std::string>();
    std::string dateBorn = json["dateBorn"].get<std::string>();
    std::vector<std::shared_ptr<Book>> booksWritten;
    for (auto x : json.at("booksWritten")) {
        booksWritten.push_back(convertJsonToBookPtr(x));
    }
    
    std::shared_ptr<Author> newAuthor = std::make_shared<Author>(name, dateBorn, booksWritten);
    
    return newAuthor;
}

std::vector<std::shared_ptr<ReadBook>> InMemoryContainers::getMasterReadBooks() {
    return this->readBookVector;
}

void InMemoryContainers::addMasterReadBooks(std::vector<std::shared_ptr<ReadBook>> newReadBookVector) {
    this->addMasterBooks(newReadBookVector); //add readbook to book vector as well (will be discarded if it already exists
    this->readBookVector.insert(std::end(readBookVector), std::begin(newReadBookVector), std::end(newReadBookVector));
    sortUnique(this->readBookVector);
    return;
}

void InMemoryContainers::addMasterReadBooks(std::shared_ptr<ReadBook> newReadBook) {
    this->addMasterBooks(newReadBook); //add readbook to book vector as well (will be discarded if it already exists
    this->readBookVector.push_back(newReadBook);
    sortUnique(this->readBookVector);
    return;
}

std::vector<std::shared_ptr<Book>> InMemoryContainers::getMasterBooks() {
    return this->bookVector;
}

void InMemoryContainers::addMasterBooks(std::vector<std::shared_ptr<ReadBook>> newReadBookVector) {
    for (auto x : newReadBookVector) {
        this->bookVector.push_back(x);
    }
    sortUnique(this->bookVector);
    return;
}

void InMemoryContainers::addMasterBooks(std::vector<std::shared_ptr<Book>> newBookVector) {
    this->addMasterAuthors(newBookVector);
    this->bookVector.insert(std::end(this->bookVector), std::begin(newBookVector), std::end(newBookVector));
    sortUnique(this->bookVector);
    return;
}

void InMemoryContainers::addMasterBooks(std::shared_ptr<Book> newBook) {
    this->addMasterAuthors(newBook);
    this->bookVector.push_back(newBook);
    sortUnique(this->bookVector);
    return;
}

std::vector<std::shared_ptr<Author>> InMemoryContainers::getMasterAuthors() {
    return this->authorVector;
}

void InMemoryContainers::addMasterAuthors(std::vector<std::shared_ptr<Author>> newAuthorVector) {
    this->authorVector.insert(std::end(this->authorVector), std::begin(newAuthorVector), std::end(newAuthorVector));
    sortUnique(this->authorVector);
    return;
}

void InMemoryContainers::addMasterAuthors(std::shared_ptr<Author> newAuthor) {
    this->authorVector.push_back(newAuthor);
    sortUnique(this->authorVector);
    return;
}

void InMemoryContainers::addMasterAuthors(std::shared_ptr<Book> newBook) {
    if (newBook->getAuthor() != "") {
        std::shared_ptr<Author> newAuthor = std::make_shared<Author>(newBook->getAuthor(), jan2038, newBook);
        this->authorVector.push_back(newAuthor);
        sortUnique(this->authorVector);
    }
    return;
}

void InMemoryContainers::addMasterAuthors(std::vector<std::shared_ptr<Book>> newBookVector) {
    for (auto x : newBookVector) {
        if (x->getAuthor() != "") {
            std::shared_ptr<Author> newAuthor = std::make_shared<Author>(x->getAuthor(), jan2038, newBookVector);
            this->authorVector.push_back(newAuthor);
        }
    }
    sortUnique(this->authorVector);
    return;
}

void InMemoryContainers::clearAll() {
    this->readBookVector.clear();
    this->authorVector.clear();
    this->bookVector.clear();
    
    return;
}

//this whole thing will probably look stupid to me in 6 months TO DO
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
void uniqueVector(std::vector<std::shared_ptr<Author>>& input) {
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
void sortUnique(std::vector<T>& input) {
    
    std::sort(std::begin(input), std::end(input), sortPointers<T>);
    uniqueVector(input);
    
    return;
}

//TO DO investigate a way to remove for loops
bool InMemoryContainers::saveInMemoryToFile(std::string filePath) {
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
        successfulSave = saveJson(bookJson, saveFile);
    }
    if (successfulSave) {
        saveFile << "*]*\n*[*\n";
        successfulSave = saveJson(readBookJson, saveFile);
    }
    if (successfulSave) {
        saveFile << "*]*\n*[*\n";
        successfulSave = saveJson(authorJson, saveFile);
    }
    if (successfulSave) {
        saveFile << "*]*";
        saveFile.close();
    }
    
    return successfulSave;
}

bool InMemoryContainers::loadInMemoryFromFile(std::string filePath) {
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
                    this->addMasterBooks(convertJsonToBookPtr(nlohmann::json::parse(line)));
                    break;
                }
                //readbook
                case 1 : {
                    this->addMasterReadBooks(convertJsonToReadBookPtr(nlohmann::json::parse(line)));
                    break;
                }
                //author
                case 2 : {
                    this->addMasterAuthors(convertJsonToAuthorPtr(nlohmann::json::parse(line)));
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
