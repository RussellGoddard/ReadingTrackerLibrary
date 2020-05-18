//
//  ServerMethods.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 4/11/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef ServerMethods_hpp
#define ServerMethods_hpp

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
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

#include <aws/dynamodb/model/DeleteTableRequest.h>

#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/CreateTableRequest.h>
#include <aws/dynamodb/model/KeySchemaElement.h>
#include <aws/dynamodb/model/ProvisionedThroughput.h>
#include <aws/dynamodb/model/ScalarAttributeType.h>

#include <aws/dynamodb/model/TransactWriteItemsRequest.h>

// turn the warnings back on
#pragma GCC diagnostic pop


namespace rtl {

    class ServerMethods {
    public:
        bool testDyanamodb(std::vector<std::shared_ptr<rtl::Book>> input); //TODO: delete this, just for experimentation
        
        bool AddBook(std::shared_ptr<rtl::Book> input);
        bool AddBook(std::vector<std::shared_ptr<rtl::Book>> input);
        std::vector<std::shared_ptr<rtl::Book>> LoadBooks();
        bool AddReadBook(std::shared_ptr<rtl::ReadBook> input);
        bool AddReadBook(std::vector<std::shared_ptr<rtl::ReadBook>> input);
        std::vector<std::shared_ptr<rtl::ReadBook>> LoadReadBooks();
        bool AddAuthor(std::shared_ptr<rtl::Author> input);
        bool AddAuthor(std::vector<std::shared_ptr<rtl::Author>> input);
        std::vector<std::shared_ptr<rtl::Author>> LoadAuthors();
        
        bool ClearTables();
        
        static ServerMethods& GetInstance(bool isDev);
    private:
        bool ClearTable(std::string tableName);
        bool CreateTable(std::string tableName, std::string partitionKey, std::string sortKey = "");
        void SetClientConfig();
        
        Aws::Client::ClientConfiguration clientConfig;
        std::string booksTableName = "Books";
        std::string readbooksTableName = "ReadBooks";
        std::string authorsTableName = "Authors";
        
        ServerMethods(bool isDev);
        ServerMethods() = delete;
        ~ServerMethods();
        ServerMethods(ServerMethods const&) = delete;
        void operator=(ServerMethods const&) = delete;
    };
}

#endif /* ServerMethods_hpp */
