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
#include "Book.hpp"

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
        int testDyanamodb(int argc, std::vector<std::string> argv);
        
        std::vector<rtl::Book> LoadBooks();
        
        static ServerMethods& GetInstance();
    private:
        
        Aws::Client::ClientConfiguration clientConfig;
        
        void SetClientConfig();
        
        ServerMethods();
        ~ServerMethods();
        ServerMethods(ServerMethods const&) = delete;
        void operator=(ServerMethods const&) = delete;
    };
}

#endif /* ServerMethods_hpp */
