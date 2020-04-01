//
//  JsonFunctions.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/21/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "JsonFunctions.hpp"

std::shared_ptr<rtl::Book> rtl::ConvertJsonToBookPtr(nlohmann::json json) {
    try {
        std::string author = json["author"].get<std::string>();
        std::string title = json["title"].get<std::string>();
        std::string series = json["series"].get<std::string>();
        std::string publisher = json["publisher"].get<std::string>();
        int pageCount = json["pageCount"].get<int>();
        std::string genre = json["genre"].get<std::string>();
        std::string publishDate = json["publishDate"].get<std::string>();
        std::vector<std::string> isbnVector = json["isbn"];
        std::vector<std::string> oclcVector = json["oclc"];
        
        return std::make_shared<rtl::Book>(author, title, series, publisher, pageCount, genre, publishDate, isbnVector, oclcVector);
    }
    catch (nlohmann::json::exception& ex) {
        //TODO: log this exception, figure out better return when exception happens
        std::cout << ex.what() << std::endl;
        return nullptr;
    }
}

std::shared_ptr<rtl::ReadBook> rtl::ConvertJsonToReadBookPtr(nlohmann::json json) {
    try {
        int readerId = json["readerId"].get<int>();
        std::string author = json["author"].get<std::string>();
        std::string title = json["title"].get<std::string>();
        std::string series = json["series"].get<std::string>();
        std::string publisher = json["publisher"].get<std::string>();
        int pageCount = json["pageCount"].get<int>();
        std::string genre = json["genre"].get<std::string>();
        std::string publishDate = json["publishDate"].get<std::string>();
        int rating = json["rating"].get<int>();
        std::string dateRead = json["dateRead"].get<std::string>();
        std::vector<std::string> isbnVector = json["isbn"];
        std::vector<std::string> oclcVector = json["oclc"];
        
        return std::make_shared<rtl::ReadBook>(readerId, rtl::Book(author, title, series, publisher, pageCount, genre, publishDate, isbnVector, oclcVector), rating, dateRead);;
    }
    catch (nlohmann::json::exception& ex) {
        //TODO: log this exception, figure out better return when exception happens
        std::cout << ex.what() << std::endl;
        return nullptr;
    }
}

std::shared_ptr<rtl::Author> rtl::ConvertJsonToAuthorPtr(nlohmann::json json) {
    try {
        std::string name = json["name"].get<std::string>();
        std::string dateBorn = json["dateBorn"].get<std::string>();
        std::vector<std::shared_ptr<rtl::Book>> booksWritten;
        for (auto x : json.at("booksWritten")) {
            booksWritten.push_back(rtl::ConvertJsonToBookPtr(x));
        }
        
        return std::make_shared<rtl::Author>(name, dateBorn, booksWritten);
    }
    catch (nlohmann::json::exception& ex) {
        //TODO: log this exception, figure out better return when exception happens
        std::cout << ex.what() << std::endl;
        return nullptr;
    }
}
