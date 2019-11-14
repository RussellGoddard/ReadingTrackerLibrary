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
        return false;
    };
    
    for (auto x : input) {
        saveFile << x << std::endl;
    }
    
    saveFile.close();
    return true;
}

std::vector<json> loadReadingList(std::string filePath) {
    std::vector<json> returnVector;
    std::string line;
    std::fstream loadFile;
    loadFile.open(filePath, std::fstream::in);
    
    //check if file exists/is locked by another process
    if (!loadFile.good()) {
        return returnVector; //empty vector is returned
    }
    
    while(std::getline(loadFile, line)) { //while there is a new json object to get
        json newReadBook = json::parse(line); //convert the string into json
        returnVector.push_back(newReadBook); //add json object to collection
    }
    
    loadFile.close();
    return returnVector;
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
