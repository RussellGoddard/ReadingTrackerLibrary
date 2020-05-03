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

// turn off the specific warning
#pragma GCC diagnostic ignored "-Wdocumentation"



// turn the warnings back on
#pragma GCC diagnostic pop

#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/ListTablesRequest.h>
#include <aws/dynamodb/model/ListTablesResult.h>

#include <aws/dynamodb/model/DeleteTableRequest.h>
#include <iostream>

namespace rtl {

    class ServerMethods {
    public:
        int testDyanamodb(int argc, std::vector<std::string> argv);
        
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
