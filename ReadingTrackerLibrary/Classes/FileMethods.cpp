//
//  FileMethods.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#include "FileMethods.hpp"

std::string& rtl::LeftTrim(std::string& input) {
  auto it2 =  std::find_if(input.begin(), input.end(), [](char ch){ return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(input.begin(), it2);
  return input;
}

std::string& rtl::RightTrim(std::string& input) {
  auto it1 = std::find_if(input.rbegin(), input.rend(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(it1.base(), input.end());
  return input;
}

std::string& rtl::Trim(std::string& str) {
   return rtl::LeftTrim(rtl::RightTrim(str));
}

bool rtl::SaveJson(std::vector<nlohmann::json> input, std::fstream& saveFile) {
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
        return ReadBook(-1);
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
        
        return std::make_shared<rtl::Book>(author, title, series, publisher, pageCount, genre, publishDate);
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
        std::string time = json["dateRead"].get<std::string>();
        
        return std::make_shared<rtl::ReadBook>(readerId, author, title, series, publisher, pageCount, genre, publishDate, rating, time);;
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
    if (newBook->GetAuthor() != "") {
        auto newAuthor = std::make_shared<rtl::Author>(newBook->GetAuthor(), rtl::jan2038, newBook);
        this->authorVector.push_back(newAuthor);
        rtl::SortUnique(this->authorVector);
    }
    return;
}

void rtl::InMemoryContainers::AddMasterAuthors(std::vector<std::shared_ptr<rtl::Book>> newBookVector) {
    for (auto x : newBookVector) {
        if (x->GetAuthor() != "") {
            auto newAuthor = std::make_shared<rtl::Author>(x->GetAuthor(), rtl::jan2038, newBookVector);
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
            input.at(index - 1)->AddBookWritten(input.at(index)->GetBooksWritten());
            
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
void rtl::SortUnique(std::vector<T>& input) {
    std::sort(std::begin(input), std::end(input), sortPointers<T>);
    uniqueVector(input);
    
    return;
}

//TODO: investigate a way to remove for loops
bool rtl::InMemoryContainers::SaveInMemoryToFile(std::string filePath) {
    std::vector<nlohmann::json> bookJson;
    std::vector<nlohmann::json> readBookJson;
    std::vector<nlohmann::json> authorJson;
    
    try {
        for (auto x : this->GetMasterBooks()) {
            bookJson.push_back(nlohmann::json::parse(x->PrintJson()));
        }
    }
    catch (nlohmann::json::exception& ex) {
        //TODO: Log this exception
        std::cout << "error parsing masterBooks" << std::endl;
        std::cout << ex.what() << std::endl;
    }
    
    try {
        for (auto x : this->GetMasterReadBooks()) {
            readBookJson.push_back(nlohmann::json::parse(x->PrintJson()));
        }
    }
    catch (nlohmann::json::exception& ex) {
        //TODO: Log this exception
        std::cout << "error parsing masterReadBooks" << std::endl;
        std::cout << ex.what() << std::endl;
    }
      
    try {
        for (auto x : this->GetMasterAuthors()) {
            authorJson.push_back(nlohmann::json::parse(x->PrintJson()));
        }
    }
    catch (nlohmann::json::exception& ex) {
        //TODO: Log this exception
        std::cout << "error parsing masterAuthors" << std::endl;
        std::cout << ex.what() << std::endl;
    }
    
    
    std::fstream saveFile;
    saveFile.open(filePath, std::fstream::out);
    if(!saveFile.good()) {
        saveFile.close();
        return false;
    };
    
    bool successfulSave = true;
    if (successfulSave) {
        saveFile << "*[*\n";
        successfulSave = rtl::SaveJson(bookJson, saveFile);
    }
    if (successfulSave) {
        saveFile << "*]*\n*[*\n";
        successfulSave = rtl::SaveJson(readBookJson, saveFile);
    }
    if (successfulSave) {
        saveFile << "*]*\n*[*\n";
        successfulSave = rtl::SaveJson(authorJson, saveFile);
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
                        //TODO: Log this exception
                        std::cout << "error parsing masterBooks" << std::endl;
                        std::cout << ex.what() << std::endl;
                    }
                    break;
                }
                //readbook
                case 1 : {
                    try {
                        this->AddMasterReadBooks(rtl::ConvertJsonToReadBookPtr(nlohmann::json::parse(line)));
                    }
                    catch (nlohmann::json::exception& ex) {
                        //TODO: Log this exception
                        std::cout << "error parsing masterReadBooks" << std::endl;
                        std::cout << ex.what() << std::endl;
                    }
                    break;
                }
                //author
                case 2 : {
                    try {
                        this->AddMasterAuthors(rtl::ConvertJsonToAuthorPtr(nlohmann::json::parse(line)));
                    }
                    catch (nlohmann::json::exception& ex) {
                        //TODO: Log this exception
                        std::cout << "error parsing masterAuthors" << std::endl;
                        std::cout << ex.what() << std::endl;
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
    if (rtl::Trim(identifier).empty() || rtl::Trim(identifierNum).empty()) {
        //TODO: log the error
        newLibraryValues.success = false;
        return newLibraryValues;
    }
    
    std::transform(std::begin(identifier), std::end(identifier), std::begin(identifier), ::toupper);
    
    if (identifier != "OCLC" && identifier != "ISBN") {
        //TODO: log the error
        newLibraryValues.success = false;
        return newLibraryValues;
    }
    
    identifierNum.erase(std::remove_if(std::begin(identifierNum), std::end(identifierNum), [](char c){ return !std::isdigit(c); }), identifierNum.end()); //remove all non digits
    
    
    if (identifierNum.empty()) {
        //TODO: log that this happened
        newLibraryValues.success = false;
        return newLibraryValues;
    }
    
    std::string combinedIdentifier = identifier + ':' + identifierNum;
    std::string curlUrl = "https://openlibrary.org/api/books?bibkeys=" + combinedIdentifier + "&jscmd=data&format=json";
    
    std::string readBuffer;
    
    if (!QueryByCurl(curlUrl, readBuffer)) {
        //TODO: log that this happened
        newLibraryValues.success = false;
        return newLibraryValues;
    }
        
    try {
        nlohmann::json openLibJson = nlohmann::json::parse(readBuffer);
    
        //oclc
        newLibraryValues.oclc = openLibJson[combinedIdentifier]["identifiers"]["oclc"].at(0).get<std::string>();
        
        //author
        //TODO: figure out multiple authors
        newLibraryValues.author = openLibJson[combinedIdentifier]["authors"].at(0)["name"].get<std::string>();
        
        //title
        newLibraryValues.title = openLibJson[combinedIdentifier]["title"].get<std::string>();
    }
    catch (nlohmann::json::exception& ex) {
        //TODO: Log this exception
        std::cout << ex.what() << std::endl;
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
        //TODO: log error
        newDataValues.success = false;
        return newDataValues;
    }
    
    std::transform(std::begin(title), std::end(title), std::begin(title), [](const char& element) {
        return std::isspace(element) ? '_' : element; //replace all whitespace with _
    });
    
    std::string curlUrl = "https://www.wikidata.org/w/api.php?action=wbgetentities&format=json&sites=enwiki&titles=" + title + "&props=descriptions%7Cclaims&languages=en";
    
    std::string readBuffer;
    if (!QueryByCurl(curlUrl, readBuffer)) {
        //TODO: log that this happened
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
        //TODO: log error
        std::cout << ex.what() << std::endl;
        newDataValues.success = false;
        return newDataValues;
    }
    
    //TODO: figure out how to test lambda belows try/catches without disabling this if block
    if (objectId == "-1") {
        //TODO: log error
        std::cout << "No object returned" << std::endl;
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
            //TODO: log error
            std::cout << ex.what() << std::endl;
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
            }
            success = true;
        }
        catch (nlohmann::json::exception& ex) {
            //TODO: log error
            std::cout << ex.what() << std::endl;
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
            }
            success = true;
        }
        catch (nlohmann::json::exception& ex) {
            //TODO: log error
            std::cout << ex.what() << std::endl;
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
            }
            success = true;
        }
        catch (nlohmann::json::exception& ex) {
            //TODO: log error
            std::cout << ex.what() << std::endl;
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
            //TODO: log error
            std::cout << ex.what() << std::endl;
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
            //TODO: log error
            newDataValues.success = false;
            std::cout << ex.what() << std::endl;
        }
        return success;
    }, wikiDataJson, objectId, std::ref(newDataValues));
    
    newDataValues.success = boolTitle.get() && boolSeries.get() && boolAuthor.get() && boolPublisher.get() && boolOclc.get();
    
    return newDataValues;
}
