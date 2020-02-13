//
//  FileMethods.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#include "FileMethods.hpp"

using namespace nlohmann;

bool saveReadingList(std::vector<json> input, std::string filePath) {
    std::fstream saveFile;
    saveFile.open(filePath, std::fstream::out);
    
    //check if file exists/is locked by another process
    if(!saveFile.good()) {
        saveFile.close();
        return false;
    };
    
    for (auto x : input) {
        saveFile << x << std::endl;
    }
    
    saveFile.close();
    return true;
}

std::vector<std::shared_ptr<ReadBook>> loadReadingList(std::string filePath) {
    InMemoryContainers& masterList = InMemoryContainers::getInstance();
    std::string line;
    std::fstream loadFile;
    loadFile.open(filePath, std::fstream::in);
    
    //check if file exists/is locked by another process
    if (!loadFile.good()) {
        loadFile.close();
        return std::vector<std::shared_ptr<ReadBook>>(); //empty vector is returned
    }
    
    while(std::getline(loadFile, line)) { //while there is a new json object to get
        json newReadBook = json::parse(line); //convert the string into json
        masterList.addMasterReadBooks(convertJsonToReadBookPtr(newReadBook)); //add json object to collection
    }
    
    loadFile.close();
    return masterList.getMasterReadBooks();
}

ReadBook convertJsonToReadBook(nlohmann::json json) {
    
    std::string author = json["author"].get<std::string>();
    std::string title = json["title"].get<std::string>();
    std::string series = json["series"].get<std::string>();
    std::string publisher = json["publisher"].get<std::string>();
    int pageCount = json["pageCount"].get<int>();
    std::string genre = json["genre"].get<std::string>();
    std::string publishDate = json["publishDate"].get<std::string>();
    int rating = json["rating"].get<int>();
    std::string time = json["dateRead"].get<std::string>();
    
    return ReadBook(author, title, series, publisher, pageCount, genre, publishDate, rating, time);
}

std::shared_ptr<ReadBook> convertJsonToReadBookPtr(nlohmann::json json) {
    
    std::string author = json["author"].get<std::string>();
    std::string title = json["title"].get<std::string>();
    std::string series = json["series"].get<std::string>();
    std::string publisher = json["publisher"].get<std::string>();
    int pageCount = json["pageCount"].get<int>();
    std::string genre = json["genre"].get<std::string>();
    std::string publishDate = json["publishDate"].get<std::string>();
    int rating = json["rating"].get<int>();
    std::string time = json["dateRead"].get<std::string>();
    
    std::shared_ptr<ReadBook> newReadBook = std::make_shared<ReadBook>(author, title, series, publisher, pageCount, genre, publishDate, rating, time);
    
    return newReadBook;
}

std::vector<std::shared_ptr<ReadBook>> InMemoryContainers::getMasterReadBooks() {
    return this->readBookVector;
}

void InMemoryContainers::addMasterReadBooks(std::vector<std::shared_ptr<ReadBook>> newReadBookVector) {
    this->readBookVector.insert(std::end(readBookVector), std::begin(newReadBookVector), std::end(newReadBookVector));
    sortUnique(this->readBookVector);
    return;
}

void InMemoryContainers::addMasterReadBooks(std::shared_ptr<ReadBook> newReadBook) {
    this->readBookVector.push_back(newReadBook);
    sortUnique(this->readBookVector);
    return;
}

std::vector<std::shared_ptr<Book>> InMemoryContainers::getMasterBooks() {
    return this->bookVector;
}

void InMemoryContainers::addMasterBooks(std::vector<std::shared_ptr<Book>> newBookVector) {
    this->bookVector.insert(std::end(this->bookVector), std::begin(newBookVector), std::end(newBookVector));
    sortUnique(this->bookVector);
    return;
}

void InMemoryContainers::addMasterBooks(std::shared_ptr<Book> newBook) {
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

