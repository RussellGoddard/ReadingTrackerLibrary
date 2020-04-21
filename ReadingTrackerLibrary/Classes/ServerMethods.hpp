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
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/CreateTableRequest.h>
#include <aws/dynamodb/model/KeySchemaElement.h>
#include <aws/dynamodb/model/ProvisionedThroughput.h>
#include <aws/dynamodb/model/ScalarAttributeType.h>
#include <iostream>




int testDyanamodb(int argc, char** argv);

#endif /* ServerMethods_hpp */
