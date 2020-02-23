//
//  FileMethods.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#ifndef FileMethods_hpp
#define FileMethods_hpp

#include <fstream>
#include <memory>
#include <set>
#include <nlohmann/json.hpp>
#include "Author.hpp"
//#include "ReadBook.hpp" see Author.hpp includes TO DO

class InMemoryContainers {
public:
    
    std::vector<std::shared_ptr<ReadBook>> getMasterReadBooks();
    void addMasterReadBooks(std::vector<std::shared_ptr<ReadBook>> newReadBookVector);
    void addMasterReadBooks(std::shared_ptr<ReadBook> newReadBook);
    
    std::vector<std::shared_ptr<Book>> getMasterBooks();
    void addMasterBooks(std::vector<std::shared_ptr<Book>> newBookVector);
    void addMasterBooks(std::shared_ptr<Book> newBook);
    
    std::vector<std::shared_ptr<Author>> getMasterAuthors();
    void addMasterAuthors(std::vector<std::shared_ptr<Author>> newAuthorVector);
    void addMasterAuthors(std::shared_ptr<Author> newAuthor);
    
    bool saveInMemoryToFile(std::string filePath);
    bool loadInMemoryFromFile(std::string filePath);
    void clearAll();
    
    static InMemoryContainers& getInstance() {
        static InMemoryContainers instance;
        return instance;
    }
    
private:
    //only for adding books when vector addMasterReadBooks is called
    void addMasterBooks(std::vector<std::shared_ptr<ReadBook>> newReadBookVector);
    
    InMemoryContainers() = default;
    ~InMemoryContainers() = default;
    InMemoryContainers(InMemoryContainers const&) = delete;
    void operator=(InMemoryContainers const&) = delete;
    
    
    std::vector<std::shared_ptr<ReadBook>> readBookVector;
    std::vector<std::shared_ptr<Book>> bookVector;
    std::vector<std::shared_ptr<Author>> authorVector;
};

template <typename T>
void sortUnique(std::vector<T>& input); //this shouldn't be declared here but everytime I try to move it to a util header I break everything TO DO
bool saveJson(nlohmann::json input, std::string filePath);
bool saveJson(std::vector<nlohmann::json> input, std::string filePath);
std::vector<std::shared_ptr<ReadBook>> loadReadingList(std::string filePath);
ReadBook convertJsonToReadBook(nlohmann::json json);
std::shared_ptr<Book> convertJsonToBookPtr(nlohmann::json json);
std::shared_ptr<ReadBook> convertJsonToReadBookPtr(nlohmann::json json);
std::shared_ptr<Author> convertJsonToAuthorPtr(nlohmann::json json);
std::string& rightTrim(std::string& input);
std::string& leftTrim(std::string& input);
std::string& trim(std::string& input);

#endif /* FileMethods_hpp */
