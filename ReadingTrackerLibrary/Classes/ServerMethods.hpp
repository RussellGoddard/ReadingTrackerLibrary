//
//  ServerMethods.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 4/11/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef ServerMethods_hpp
#define ServerMethods_hpp

#include <iostream>
#include <vector>
#include "Author.hpp"
#include "Book.hpp"
#include "FileMethods.hpp"
#include "JsonFunctions.hpp"
#include "ReadBook.hpp"

// turn off the specific warning
#pragma GCC diagnostic ignored "-Wcomma"
#pragma GCC diagnostic ignored "-Wdocumentation"

#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/ListTablesRequest.h>
#include <aws/dynamodb/model/ListTablesResult.h>

#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/PutItemRequest.h>
#include <aws/dynamodb/model/PutItemResult.h>

#include <aws/dynamodb/model/ScanRequest.h>

// turn the warnings back on
#pragma GCC diagnostic pop


namespace rtl {

    class ServerMethods {
    public:
        int testDyanamodb(int argc, std::vector<std::string> argv); //TODO: delete this, just for experimentation
        
        bool AddBook(std::shared_ptr<rtl::Book> input);
        std::vector<std::shared_ptr<rtl::Book>> LoadBooks();
        bool AddReadBook(std::shared_ptr<rtl::ReadBook> input);
        std::vector<std::shared_ptr<rtl::ReadBook>> LoadReadBooks();
        bool AddAuthor(std::shared_ptr<rtl::Author> input);
        std::vector<std::shared_ptr<rtl::Author>> LoadAuthors();
        
        static ServerMethods& GetInstance(bool isDev);
    private:
        
        Aws::Client::ClientConfiguration clientConfig;
        std::string booksTableName = "Books";
        std::string readbooksTableName = "ReadBooks";
        std::string authorsTableName = "Authors";
        
        void SetClientConfig();
        
        
        ServerMethods(bool isDev);
        ServerMethods() = delete;
        ~ServerMethods();
        ServerMethods(ServerMethods const&) = delete;
        void operator=(ServerMethods const&) = delete;
    };
}

#endif /* ServerMethods_hpp */
