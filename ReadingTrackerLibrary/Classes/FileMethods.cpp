//
//  FileMethods.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#include "FileMethods.hpp"

bool rtl::InMemoryContainers::SaveJson(std::string input, std::fstream& saveFile) {
    //check if file exists/is locked by another process
    if(!saveFile.good()) {
        saveFile.close();
        return false;
    };
    
    saveFile << input << std::endl;
    
    return true;
}

std::vector<std::shared_ptr<rtl::ReadBook>> rtl::InMemoryContainers::GetMasterReadBooks() {
    return this->readBookVector;
}

void rtl::InMemoryContainers::AddMasterReadBooks(std::vector<std::shared_ptr<rtl::ReadBook>> newReadBookVector) {
    this->AddMasterBooks(newReadBookVector); //add readbook to book vector as well (will be discarded if it already exists
    this->readBookVector.insert(std::end(readBookVector), std::begin(newReadBookVector), std::end(newReadBookVector));
    rtl::SortUnique(this->readBookVector);
    return;
}

void rtl::InMemoryContainers::AddMasterReadBooks(std::shared_ptr<rtl::ReadBook> newReadBook) {
    this->AddMasterBooks(newReadBook); //add readbook to book vector as well (will be discarded if it already exists
    this->readBookVector.push_back(newReadBook);
    rtl::SortUnique(this->readBookVector);
    return;
}

std::vector<std::shared_ptr<rtl::Book>> rtl::InMemoryContainers::GetMasterBooks() {
    return this->bookVector;
}

void rtl::InMemoryContainers::AddMasterBooks(std::vector<std::shared_ptr<rtl::ReadBook>> newReadBookVector) {
    for (auto x : newReadBookVector) {
        this->bookVector.push_back(x);
    }
    rtl::SortUnique(this->bookVector);
    return;
}

void rtl::InMemoryContainers::AddMasterBooks(std::vector<std::shared_ptr<rtl::Book>> newBookVector) {
    this->AddMasterAuthors(newBookVector);
    this->bookVector.insert(std::end(this->bookVector), std::begin(newBookVector), std::end(newBookVector));
    rtl::SortUnique(this->bookVector);
    return;
}

void rtl::InMemoryContainers::AddMasterBooks(std::shared_ptr<rtl::Book> newBook) {
    this->AddMasterAuthors(newBook);
    this->bookVector.push_back(newBook);
    rtl::SortUnique(this->bookVector);
    return;
}

std::vector<std::shared_ptr<rtl::Author>> rtl::InMemoryContainers::GetMasterAuthors() {
    return this->authorVector;
}

void rtl::InMemoryContainers::AddMasterAuthors(std::vector<std::shared_ptr<rtl::Author>> newAuthorVector) {
    this->authorVector.insert(std::end(this->authorVector), std::begin(newAuthorVector), std::end(newAuthorVector));
    rtl::SortUnique(this->authorVector);
    return;
}

void rtl::InMemoryContainers::AddMasterAuthors(std::shared_ptr<rtl::Author> newAuthor) {
    this->authorVector.push_back(newAuthor);
    rtl::SortUnique(this->authorVector);
    return;
}

void rtl::InMemoryContainers::AddMasterAuthors(std::shared_ptr<rtl::Book> newBook) {
    for (std::string x : newBook->GetAuthors()) {
        //TODO: get author birth date
        auto newAuthor = std::make_shared<rtl::Author>(x, rtl::jan2038, std::vector<std::shared_ptr<rtl::Book>>{newBook});
        this->authorVector.push_back(newAuthor);
        rtl::SortUnique(this->authorVector);
    }
    return;
}

void rtl::InMemoryContainers::AddMasterAuthors(std::vector<std::shared_ptr<rtl::Book>> newBookVector) {
    for (auto newBook : newBookVector) {
        for (std::string x : newBook->GetAuthors()) {
            //TODO: retrieve author birth date
            auto newAuthor = std::make_shared<rtl::Author>(x, rtl::jan2038, newBookVector);
            this->authorVector.push_back(newAuthor);
        }
    }
    rtl::SortUnique(this->authorVector);
    return;
}

void rtl::InMemoryContainers::ClearAll() {
    this->readBookVector.clear();
    this->authorVector.clear();
    this->bookVector.clear();
    
    return;
}

bool rtl::InMemoryContainers::SaveInMemoryToFile(std::string filePath) {
    
    std::fstream saveFile;
    saveFile.open(filePath, std::fstream::out);
    if(!saveFile.good()) {
        saveFile.close();
        return false;
    };
    
    bool successfulSave = true;
    if (successfulSave) {
        saveFile << "*[*\n";
        for (auto x : this->GetMasterBooks()) {
            if(!this->SaveJson(x->PrintJson(), saveFile)) {
                //if any SaveJson fails stop trying
                break;
            }
        }
    }
    if (successfulSave) {
        saveFile << "*]*\n*[*\n";
        for (auto x : this->GetMasterReadBooks()) {
            if(!this->SaveJson(x->PrintJson(), saveFile)) {
                //if any SaveJson fails stop trying
                break;
            }
        }
    }
    if (successfulSave) {
        saveFile << "*]*\n*[*\n";
        for (auto x : this->GetMasterAuthors()) {
            if(!this->SaveJson(x->PrintJson(), saveFile)) {
                //if any SaveJson fails stop trying
                break;
            }
        }
    }
    if (successfulSave) {
        saveFile << "*]*";
        saveFile.close();
    }
    
    return successfulSave;
}

bool rtl::InMemoryContainers::LoadInMemoryFromFile(std::string filePath) {
    std::fstream loadFile;
    loadFile.open(filePath, std::fstream::in);
    if(!loadFile.good()) {
        loadFile.close();
        return false;
    };
    
    int trackLoad = 0;
    std::string line;
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
                    try {
                        this->AddMasterBooks(rtl::ConvertJsonToBookPtr(nlohmann::json::parse(line)));
                    }
                    catch (nlohmann::json::exception& ex) {
                        std::string exceptionMessage = ex.what();
                        exceptionMessage += " exception attempting CovertJsonToBookPtr on: " + line;
                        BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
                    }
                    break;
                }
                //readbook
                case 1 : {
                    try {
                        this->AddMasterReadBooks(rtl::ConvertJsonToReadBookPtr(nlohmann::json::parse(line)));
                    }
                    catch (nlohmann::json::exception& ex) {
                        std::string exceptionMessage = ex.what();
                        exceptionMessage += " exception attempting CovertJsonToReadBookPtr on: " + line;
                        BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
                    }
                    break;
                }
                //author
                case 2 : {
                    try {
                        this->AddMasterAuthors(rtl::ConvertJsonToAuthorPtr(nlohmann::json::parse(line)));
                    }
                    catch (nlohmann::json::exception& ex) {
                        std::string exceptionMessage = ex.what();
                        exceptionMessage += " exception attempting CovertJsonToAuthorPtr on: " + line;
                        BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
                    }
                    break;
                }
                default : {
                    loadFile.close();
                    return false;
                }
            }
        }
    }
    
    loadFile.close();
    
    //currently only books, readBooks, and authors supported so trackLoad should end at 3
    if (trackLoad != 3) {
        return false;
    }
    
    return true;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool QueryByCurl(std::string curlUrl, std::string& readBuffer) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, curlUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return true;
    }
    
    return false;
}

//queries the open library for info based on given OCLC or ISBN (10 or 13 digit)
rtl::OpenLibraryValues rtl::QueryBookByIdentifier(std::string identifier, std::string identifierNum) {
    rtl::OpenLibraryValues newLibraryValues;
    
    //validation checks
    //remove all nondigits from indentifierNum
    identifierNum.erase(std::remove_if(std::begin(identifierNum), std::end(identifierNum), [](char c){ return !std::isdigit(c); }), identifierNum.end());
    
    if (rtl::Trim(identifier).empty() || rtl::Trim(identifierNum).empty()) {
        BOOST_LOG_TRIVIAL(error) << "identifier and identifierNum cannot be empty";
        newLibraryValues.success = false;
        return newLibraryValues;
    }
    
    std::transform(std::begin(identifier), std::end(identifier), std::begin(identifier), ::toupper);
    
    if (identifier != "OCLC" && identifier != "ISBN") {
        BOOST_LOG_TRIVIAL(error) << "identifier was not OCLC or ISBN";
        newLibraryValues.success = false;
        return newLibraryValues;
    }
    
    std::string combinedIdentifier = identifier + ':' + identifierNum;
    std::string curlUrl = "https://openlibrary.org/api/books?bibkeys=" + combinedIdentifier + "&jscmd=data&format=json";
    
    std::string readBuffer;
    
    if (!QueryByCurl(curlUrl, readBuffer)) {
        BOOST_LOG_TRIVIAL(error) << "curl failed to initialize";
        newLibraryValues.success = false;
        return newLibraryValues;
    }
        
    try {
        nlohmann::json openLibJson = nlohmann::json::parse(readBuffer);
        
        //author
        for (auto x : openLibJson[combinedIdentifier]["authors"].items()) {
            newLibraryValues.authors.push_back(x.value()["name"].get<std::string>());
        }
        
        //title
        newLibraryValues.title = openLibJson[combinedIdentifier]["title"].get<std::string>();
        
        //isbn 10
        if (openLibJson[combinedIdentifier]["identifiers"].contains("isbn_10")) {
            std::vector<std::string> newIsbn = openLibJson[combinedIdentifier]["identifiers"]["isbn_10"].get<std::vector<std::string>>();
            newLibraryValues.isbn.insert(std::end(newLibraryValues.isbn), std::begin(newIsbn), std::end(newIsbn));
        }
        
        //isbn 13
        if (openLibJson[combinedIdentifier]["identifiers"].contains("isbn_13")) {
            std::vector<std::string> newIsbn = openLibJson[combinedIdentifier]["identifiers"]["isbn_13"].get<std::vector<std::string>>();
            newLibraryValues.isbn.insert(std::end(newLibraryValues.isbn), std::begin(newIsbn), std::end(newIsbn));
        }
        
        //oclc
        if (openLibJson[combinedIdentifier]["identifiers"].contains("oclc")) {
            newLibraryValues.oclc = openLibJson[combinedIdentifier]["identifiers"]["oclc"].get<std::vector<std::string>>();
        }
    }
    catch (nlohmann::json::exception& ex) {
        std::string exceptionMessage = ex.what();
        exceptionMessage += " failed to find author from openlibrary in: " + readBuffer;
        BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        newLibraryValues.success = false;
        return newLibraryValues;
    }
    
    return newLibraryValues;
}

//TODO: curl query very fragile due to requiring exact capitalization figure out better way (might have to move google books)
rtl::WikiDataValues rtl::QueryBookByTitle(std::string title) {
    rtl::WikiDataValues newDataValues;
    
    //validation check
    if (rtl::Trim(title).empty()) {
        BOOST_LOG_TRIVIAL(warning) << "title cannot be empty";
        newDataValues.success = false;
        return newDataValues;
    }
    
    std::transform(std::begin(title), std::end(title), std::begin(title), [](const char& element) {
        return std::isspace(element) ? '_' : element; //replace all whitespace with _
    });
    
    std::string curlUrl = "https://www.wikidata.org/w/api.php?action=wbgetentities&format=json&sites=enwiki&titles=" + title + "&props=descriptions%7Cclaims&languages=en";
    
    std::string readBuffer;
    if (!QueryByCurl(curlUrl, readBuffer)) {
        BOOST_LOG_TRIVIAL(error) << "curl failed to initialize";
        newDataValues.success = false;
        return newDataValues;
    }
    
    nlohmann::json wikiDataJson = nlohmann::json::value_t::null;
    std::string objectId = "";
    try {
        wikiDataJson = nlohmann::json::parse(readBuffer);
        objectId = wikiDataJson["entities"].begin().key();
    }
    catch (nlohmann::json::exception& ex) {
        std::string exceptionMessage = ex.what();
        exceptionMessage += " failed to parse: " + readBuffer;
        BOOST_LOG_TRIVIAL(error) << exceptionMessage;
        newDataValues.success = false;
        return newDataValues;
    }
    
    //TODO: figure out how to test lambda belows try/catches without disabling this if block
    if (objectId == "-1") {
        BOOST_LOG_TRIVIAL(warning) << "No object returned for title: " << title;
        newDataValues.success = false;
        return newDataValues;
    }
        
    std::future<bool> boolTitle = std::async([](const nlohmann::json& wikiDataJson, const std::string& objectId, WikiDataValues& newDataValues) {
        bool success = false;
        try {
            //title: P1476
            newDataValues.title = wikiDataJson.at("entities").at(objectId).at("claims").at("P1476").at(0).at("mainsnak").at("datavalue").at("value").at("text").get<std::string>();
            success = true;
        }
        catch (nlohmann::json::exception& ex) {
            std::string exceptionMessage = ex.what();
            exceptionMessage += " failed to retrieve title from: " + wikiDataJson.dump();
            BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        }
        return success;
    }, wikiDataJson, objectId, std::ref(newDataValues));
    
    std::future<bool> boolSeries = std::async([](const nlohmann::json& wikiDataJson, const std::string& objectId, WikiDataValues& newDataValues) {
        bool success = false;
        try {
            //series: P179 -> P1476
            std::string seriesId = wikiDataJson.at("entities").at(objectId).at("claims").at("P179").at(0).at("mainsnak").at("datavalue").at("value").at("id").get<std::string>();
            
            std::string seriesCurl = "https://www.wikidata.org/w/api.php?action=wbgetentities&format=json&ids=" + seriesId + "&sites=enwiki&props=claims&languages=en";
            
            std::string seriesBuffer = "";
            if (QueryByCurl(seriesCurl, seriesBuffer)) {
                auto wikiDataJsonSeries = nlohmann::json::parse(seriesBuffer);
                newDataValues.series = wikiDataJsonSeries.at("entities").at(seriesId).at("claims").at("P1476").at(0).at("mainsnak").at("datavalue").at("value").at("text").get<std::string>();
                success = true;
            }
        }
        catch (nlohmann::json::exception& ex) {
            std::string exceptionMessage = ex.what();
            exceptionMessage += " failed to retrieve series from: " + wikiDataJson.dump();
            BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        }
        return success;
    }, wikiDataJson, objectId, std::ref(newDataValues));
    
    std::future<bool> boolAuthor = std::async([](const nlohmann::json& wikiDataJson, const std::string& objectId, WikiDataValues& newDataValues) {
        bool success = false;
        try {
            //author: P50 -> P742
            std::string authorId = wikiDataJson.at("entities").at(objectId).at("claims").at("P50").at(0).at("mainsnak").at("datavalue").at("value").at("id").get<std::string>();
            
            std::string authorCurl = "https://www.wikidata.org/w/api.php?action=wbgetentities&format=json&ids=" + authorId + "&sites=enwiki&props=claims&languages=en";
            
            std::string authorBuffer = "";
            if (QueryByCurl(authorCurl, authorBuffer)) {
                auto wikiDataJsonAuthor = nlohmann::json::parse(authorBuffer);
                newDataValues.author = wikiDataJsonAuthor.at("entities").at(authorId).at("claims").at("P742").at(0).at("mainsnak").at("datavalue").at("value").get<std::string>();
                success = true;
            }
        }
        catch (nlohmann::json::exception& ex) {
            std::string exceptionMessage = ex.what();
            exceptionMessage += " failed to retrieve author from: " + wikiDataJson.dump();
            BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        }
        return success;
    }, wikiDataJson, objectId, std::ref(newDataValues));
    
    std::future<bool> boolPublisher = std::async([](const nlohmann::json& wikiDataJson, const std::string& objectId, WikiDataValues& newDataValues) {
        bool success = false;
        try {
            //publisher P123 -> query aliases for english name
            std::string publisherId = wikiDataJson.at("entities").at(objectId).at("claims").at("P123").at(0).at("mainsnak").at("datavalue").at("value").at("id").get<std::string>();
            
            std::string publisherCurl = "https://www.wikidata.org/w/api.php?action=wbgetentities&format=json&ids=" + publisherId + "&sites=enwiki&props=aliases&languages=en";
            
            std::string publisherBuffer = "";
            if (QueryByCurl(publisherCurl, publisherBuffer)) {
                auto wikiDataJsonPublisher = nlohmann::json::parse(publisherBuffer);
                newDataValues.publisher = wikiDataJsonPublisher.at("entities").at(publisherId).at("aliases").at("en").at(0).at("value").get<std::string>();
                success = true;
            }
        }
        catch (nlohmann::json::exception& ex) {
            std::string exceptionMessage = ex.what();
            exceptionMessage += " failed to retrieve publisher from: " + wikiDataJson.dump();
            BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        }
        return success;
    }, wikiDataJson, objectId, std::ref(newDataValues));
    
    std::future<bool> boolOclc = std::async([](const nlohmann::json& wikiDataJson, const std::string& objectId, WikiDataValues& newDataValues) {
        bool success = false;
        try {
            //oclc: P243
            newDataValues.oclc = wikiDataJson.at("entities").at(objectId).at("claims").at("P243").at(0).at("mainsnak").at("datavalue").at("value").get<std::string>();
            success = true;
        }
        catch (nlohmann::json::exception& ex) {
            std::string exceptionMessage = ex.what();
            exceptionMessage += " failed to retrieve oclc from: " + wikiDataJson.dump();
            BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        }
        return success;
    }, wikiDataJson, objectId, std::ref(newDataValues));
    
    std::future<bool> boolDatePublish = std::async([](const nlohmann::json& wikiDataJson, const std::string& objectId, WikiDataValues& newDataValues) {
        bool success = false;
        try {
            //datePublish: P577
            //"time": "+1990-01-15T00:00:00Z",
            newDataValues.datePublished = boost::gregorian::from_string(wikiDataJson.at("entities").at(objectId).at("claims").at("P577").at(0).at("mainsnak").at("datavalue").at("value").at("time").get<std::string>().substr(1, 10));
            success = true;
        }
        catch (nlohmann::json::exception& ex) {
            std::string exceptionMessage = ex.what();
            exceptionMessage += " failed to retrieve datePublish from: " + wikiDataJson.dump();
            BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        }
        return success;
    }, wikiDataJson, objectId, std::ref(newDataValues));
    
    std::future<bool> boolIsbn = std::async([](const nlohmann::json& wikiDataJson, const std::string& objectId, WikiDataValues& newDataValues) {
        bool success = false;
        try {
            //isbn: P212
            newDataValues.isbn = wikiDataJson.at("entities").at(objectId).at("claims").at("P212").at(0).at("mainsnak").at("datavalue").at("value").get<std::string>();
            success = true;
        }
        catch (nlohmann::json::exception& ex) {
            std::string exceptionMessage = ex.what();
            exceptionMessage += " failed to retrieve isbn from: " + wikiDataJson.dump();
            BOOST_LOG_TRIVIAL(warning) << exceptionMessage;
        }
        return success;
    }, wikiDataJson, objectId, std::ref(newDataValues));
    
    newDataValues.success = boolTitle.get() && boolSeries.get() && boolAuthor.get() && boolPublisher.get() && boolOclc.get() && boolIsbn.get();
    
    return newDataValues;
}
