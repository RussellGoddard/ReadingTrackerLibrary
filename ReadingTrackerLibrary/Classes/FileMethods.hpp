//
//  FileMethods.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#ifndef FileMethods_hpp
#define FileMethods_hpp

#include <fstream>
#include <functional>
#include <future>
#include <memory>
#include <nlohmann/json.hpp>
#include <set>
#include "Author.hpp"
#include <curl/curl.h>

//TODO: #include "ReadBook.hpp" see Author.hpp includes

namespace rtl {

    //TODO: should these two structs be here or the queries spun into their own file
    struct WikiDataValues {
        bool success = true;
        std::string oclc = "";
        std::string title = "";
        std::string series = "";
        std::string author = "";
        std::string publisher = "";
        boost::gregorian::date datePublished;
    };

    struct OpenLibraryValues {
        bool success = true;
        std::string oclc = "";
        std::string author = "";
        std::string title = "";
    };

    class InMemoryContainers {
    public:
        std::vector<std::shared_ptr<rtl::ReadBook>> GetMasterReadBooks();
        void AddMasterReadBooks(std::vector<std::shared_ptr<rtl::ReadBook>> newReadBookVector);
        void AddMasterReadBooks(std::shared_ptr<rtl::ReadBook> newReadBook);
        
        std::vector<std::shared_ptr<rtl::Book>> GetMasterBooks();
        void AddMasterBooks(std::vector<std::shared_ptr<rtl::Book>> newBookVector);
        void AddMasterBooks(std::shared_ptr<rtl::Book> newBook);
        
        std::vector<std::shared_ptr<rtl::Author>> GetMasterAuthors();
        void AddMasterAuthors(std::vector<std::shared_ptr<rtl::Author>> newAuthorVector);
        void AddMasterAuthors(std::shared_ptr<rtl::Author> newAuthor);
        void AddMasterAuthors(std::shared_ptr<rtl::Book> newBook);
        void AddMasterAuthors(std::vector<std::shared_ptr<rtl::Book>> newBookVector);
        
        bool SaveInMemoryToFile(std::string filePath);
        bool LoadInMemoryFromFile(std::string filePath);
        void ClearAll();
        
        static InMemoryContainers& GetInstance() {
            static InMemoryContainers instance;
            return instance;
        }
        
    private:
        //only for adding books when vector addMasterReadBooks is called
        void AddMasterBooks(std::vector<std::shared_ptr<rtl::ReadBook>> newReadBookVector);
        
        InMemoryContainers() = default;
        ~InMemoryContainers() = default;
        InMemoryContainers(InMemoryContainers const&) = delete;
        void operator=(InMemoryContainers const&) = delete;
        
        
        std::vector<std::shared_ptr<rtl::ReadBook>> readBookVector;
        std::vector<std::shared_ptr<rtl::Book>> bookVector;
        std::vector<std::shared_ptr<rtl::Author>> authorVector;
    };

    rtl::OpenLibraryValues QueryBookByIdentifier(std::string identifier, std::string identifierNum);
    rtl::WikiDataValues QueryBookByTitle(std::string title);
    template <typename T>
    void SortUnique(std::vector<T>& input); //TODO: this shouldn't be declared here but everytime I try to move it to a util header I break everything
    bool SaveJson(std::vector<nlohmann::json> input, std::fstream& filePath);
    std::vector<std::shared_ptr<rtl::ReadBook>> LoadReadingList(std::string filePath);
    rtl::ReadBook ConvertJsonToReadBook(nlohmann::json json);
    std::shared_ptr<rtl::Book> ConvertJsonToBookPtr(nlohmann::json json);
    std::shared_ptr<rtl::ReadBook> ConvertJsonToReadBookPtr(nlohmann::json json);
    std::shared_ptr<rtl::Author> ConvertJsonToAuthorPtr(nlohmann::json json);
    std::string& RightTrim(std::string& input);
    std::string& LeftTrim(std::string& input);
    std::string& Trim(std::string& input);

}

#endif /* FileMethods_hpp */
