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
#include <nlohmann/json.hpp>
#include <set>
#include "Author.hpp"
#include <curl/curl.h>

//TODO: #include "ReadBook.hpp" see Author.hpp includes

namespace rtl {

    //TODO: should these two structs be here or the queries spun into their own file
    struct wikiDataValues {
        bool success = true;
        std::string oclc = "";
        std::string title = "";
        std::string series = "";
        std::string author = "";
        std::string publisher = "";
        boost::gregorian::date datePublished;
    };

    struct openLibraryValues {
        bool success = true;
        std::string oclc = "";
        std::string author = "";
        std::string title = "";
    };

    class InMemoryContainers {
    public:
        
        std::vector<std::shared_ptr<rtl::ReadBook>> getMasterReadBooks();
        void addMasterReadBooks(std::vector<std::shared_ptr<rtl::ReadBook>> newReadBookVector);
        void addMasterReadBooks(std::shared_ptr<rtl::ReadBook> newReadBook);
        
        std::vector<std::shared_ptr<rtl::Book>> getMasterBooks();
        void addMasterBooks(std::vector<std::shared_ptr<rtl::Book>> newBookVector);
        void addMasterBooks(std::shared_ptr<rtl::Book> newBook);
        
        std::vector<std::shared_ptr<rtl::Author>> getMasterAuthors();
        void addMasterAuthors(std::vector<std::shared_ptr<rtl::Author>> newAuthorVector);
        void addMasterAuthors(std::shared_ptr<rtl::Author> newAuthor);
        void addMasterAuthors(std::shared_ptr<rtl::Book> newBook);
        void addMasterAuthors(std::vector<std::shared_ptr<rtl::Book>> newBookVector);
        
        bool saveInMemoryToFile(std::string filePath);
        bool loadInMemoryFromFile(std::string filePath);
        void clearAll();
        
        static InMemoryContainers& getInstance() {
            static InMemoryContainers instance;
            return instance;
        }
        
    private:
        //only for adding books when vector addMasterReadBooks is called
        void addMasterBooks(std::vector<std::shared_ptr<rtl::ReadBook>> newReadBookVector);
        
        InMemoryContainers() = default;
        ~InMemoryContainers() = default;
        InMemoryContainers(InMemoryContainers const&) = delete;
        void operator=(InMemoryContainers const&) = delete;
        
        
        std::vector<std::shared_ptr<rtl::ReadBook>> readBookVector;
        std::vector<std::shared_ptr<rtl::Book>> bookVector;
        std::vector<std::shared_ptr<rtl::Author>> authorVector;
    };

    rtl::openLibraryValues queryBookByIdentifier(std::string identifier, std::string identifierNum);
    rtl::wikiDataValues queryBookByTitle(std::string title);
    template <typename T>
    void sortUnique(std::vector<T>& input); //TODO: this shouldn't be declared here but everytime I try to move it to a util header I break everything
    bool saveJson(std::vector<nlohmann::json> input, std::fstream& filePath);
    std::vector<std::shared_ptr<rtl::ReadBook>> loadReadingList(std::string filePath);
    rtl::ReadBook convertJsonToReadBook(nlohmann::json json);
    std::shared_ptr<rtl::Book> convertJsonToBookPtr(nlohmann::json json);
    std::shared_ptr<rtl::ReadBook> convertJsonToReadBookPtr(nlohmann::json json);
    std::shared_ptr<rtl::Author> convertJsonToAuthorPtr(nlohmann::json json);
    std::string& rightTrim(std::string& input);
    std::string& leftTrim(std::string& input);
    std::string& trim(std::string& input);

}

#endif /* FileMethods_hpp */
