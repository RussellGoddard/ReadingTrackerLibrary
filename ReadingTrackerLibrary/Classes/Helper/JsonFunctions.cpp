//
//  JsonFunctions.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/21/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "JsonFunctions.hpp"

rtl::ReadBook rtl::ConvertJsonToReadBook(nlohmann::json json) {
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
        std::string time = json["dateRead"].get<std::string>();
        return rtl::ReadBook(readerId, author, title, series, publisher, pageCount, genre, publishDate, rating, time);
    }
    catch (nlohmann::json::exception& ex) {
        //TODO: log this exception, figure out better return when exception happens
        std::cout << ex.what() << std::endl;
        return ReadBook(-1, "", "");
    }
        
    
}

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

template <> std::string rtl::PrintJson(const std::shared_ptr<rtl::Author> input) {
    std::string returnString;
    returnString = R"({"authorId":")" + input->GetAuthorId() + R"(","name":")" + input->GetName() + R"(","dateBorn":")" + input->PrintDateBorn() + R"(","booksWritten":[)";
    for (std::shared_ptr<rtl::Book> x : input->GetBooksWritten()) {
        returnString += rtl::PrintJson(x);
        returnString += ',';
    }
    if (returnString.back() == ',') {
        returnString.pop_back();
    }
    returnString += R"(]})";
    
    return returnString;
}

template <> std::string rtl::PrintJson(const std::shared_ptr<rtl::Book> input) {
    std::string returnString = R"({"bookId":")" + input->GetBookId();
    
    returnString += R"(","isbn":[)";
    std::vector<std::string> isbnVector = input->GetIsbn();
    for (int i = 0; i < isbnVector.size(); ++i) {
        returnString += R"(")";
        returnString += isbnVector.at(i);
        returnString += R"(")";
        if (i < isbnVector.size() - 1) {
            returnString += R"(,)";
        }
    }
    
    returnString += R"(],"oclc":[)";
    std::vector<std::string> oclcVector = input->GetOclc();
    for (int i = 0; i < oclcVector.size(); ++i) {
        returnString += R"(")";
        returnString += oclcVector.at(i);
        returnString += R"(")";
        if (i < oclcVector.size() - 1) {
            returnString += R"(,)";
        }
    }
    returnString += R"(],"author":")" + input->GetAuthor();
    returnString += R"(","authorId":")" + input->GetAuthorId();
    returnString += R"(","title":")" + input->GetTitle();
    returnString += R"(","series":")" + input->GetSeries();
    returnString += R"(","publisher":")" + input->GetPublisher();
    returnString += R"(","genre":")" + input->PrintGenre();
    returnString += R"(","pageCount":)" + std::to_string(input->GetPageCount());
    returnString += R"(,"publishDate":")" + input->PrintPublishDate();
    returnString += R"("})";
    return returnString;
}

template<> std::string rtl::PrintJson(const std::shared_ptr<rtl::ReadBook> input) {
    std::string returnString;
    
    returnString = rtl::PrintJson(static_cast<const std::shared_ptr<rtl::Book>>(input)); //get Book as a JSON object
    returnString.pop_back(); //remove ending bracket
    
    //append ReadBook variables
    returnString += R"(,"rating":)" + std::to_string(input->GetRating()) + R"(,"dateRead":")" + input->PrintDateRead() + R"(","readerId":)" + std::to_string(input->GetReaderId()) + R"(})";
    
    return returnString;
}
