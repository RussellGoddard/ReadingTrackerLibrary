//
//  FileMethods.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#ifndef FileMethods_hpp
#define FileMethods_hpp

#include <curl/curl.h>
#include <fstream>
#include <functional>
#include <future>
#include <memory>
#include <set>
#include <utility>
#include "Author.hpp"
#include "HelperFunctions.hpp"
#include "JsonFunctions.hpp"


//TODO: #include "ReadBook.hpp" see Author.hpp includes

namespace rtl {
    //TODO: should these two structs be here or the queries spun into their own file
    struct WikiDataValues {
        bool success = true;
        std::string isbn = "";
        std::string oclc = "";
        std::string title = "";
        std::string series = "";
        std::string author = "";
        std::string publisher = "";
        boost::gregorian::date datePublished;
    };

    struct OpenLibraryValues {
        bool success = true;
        //TODO: support vectors for isbn and oclc
        //TODO: page number
        //std::string isbn = "";
        //std::string oclc = "";
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
        bool SaveJson(std::string input, std::fstream& filePath);
        
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
}

#endif /* FileMethods_hpp */
