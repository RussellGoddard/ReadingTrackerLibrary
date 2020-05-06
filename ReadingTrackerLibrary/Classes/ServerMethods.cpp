//
//  ServerMethods.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 4/11/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "ServerMethods.hpp"

int rtl::ServerMethods::testDyanamodb(int argc, std::vector<std::string> argv) {
    
    std::cout << "Your DynamoDB Tables:" << std::endl;
    
    // snippet-start:[dynamodb.cpp.list_tables.code]
    std::cout << clientConfig.region << std::endl;
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

    Aws::DynamoDB::Model::ListTablesRequest ltr;
    ltr.SetLimit(50);
    do
    {
        const Aws::DynamoDB::Model::ListTablesOutcome& lto = dynamoClient.ListTables(ltr);
        if (!lto.IsSuccess())
        {
            std::cout << "Error: " << lto.GetError().GetMessage() << std::endl;
            return 1;
        }
        for (const auto& s : lto.GetResult().GetTableNames())
            std::cout << s << std::endl;
        ltr.SetExclusiveStartTableName(lto.GetResult().GetLastEvaluatedTableName());
    } while (!ltr.GetExclusiveStartTableName().empty());
    // snippet-end:[dynamodb.cpp.list_tables.code]
    
    // snippet-start:[dynamodb.cpp.put_item.code]

    Aws::DynamoDB::Model::PutItemRequest pir;
    pir.SetTableName("Books");

    Aws::DynamoDB::Model::AttributeValue bookId;
    bookId.SetS("1c5fdaf7109aa47ef2");
    pir.AddItem("BookId", bookId);

    //TODO: should be a aws list
    Aws::DynamoDB::Model::AttributeValue author;
    author.SetS("Brandon Sanderson");
    pir.AddItem("Author", author);
    
    //TODO: should be aws list
    Aws::DynamoDB::Model::AttributeValue isbn;
    isbn.SetS("9780765311788");
    pir.AddItem("ISBN", isbn);
    
    //TODO: should be aws list
    Aws::DynamoDB::Model::AttributeValue oclc;
    oclc.SetS("62342185");
    pir.AddItem("OCLC", oclc);
    
    //TODO: should be aws list
    Aws::DynamoDB::Model::AttributeValue authorId;
    authorId.SetS("1567187");
    pir.AddItem("AuthorId", authorId);
    
    Aws::DynamoDB::Model::AttributeValue title;
    title.SetS("Mistborn: The Final Empire");
    pir.AddItem("Title", title);
    
    Aws::DynamoDB::Model::AttributeValue series;
    series.SetS("Mistborn");
    pir.AddItem("Series", series);
    
    Aws::DynamoDB::Model::AttributeValue publisher;
    publisher.SetS("Tor Books");
    pir.AddItem("Publisher", publisher);
    
    Aws::DynamoDB::Model::AttributeValue genre;
    genre.SetS("fantasy");
    pir.AddItem("Genre", genre);
    
    Aws::DynamoDB::Model::AttributeValue pageCount;
    pageCount.SetN("541");
    pir.AddItem("Page Count", pageCount);
    
    Aws::DynamoDB::Model::AttributeValue publishDate;
    publishDate.SetS("2006-Jul-17");
    pir.AddItem("Publish Date", publishDate);
    
    const Aws::DynamoDB::Model::PutItemOutcome result = dynamoClient.PutItem(pir);
    if (!result.IsSuccess())
    {
        std::cout << result.GetError().GetMessage() << std::endl;
        return 1;
    }
    std::cout << "Done!" << std::endl;
    // snippet-end:[dynamodb.cpp.put_item.code]

    return 0;
}

std::vector<rtl::Book> rtl::ServerMethods::LoadBooks() {
    //TODO: support pagination
    std::vector<rtl::Book> returnVector;
    
    Aws::DynamoDB::Model::ScanRequest scanRequest;
    scanRequest.WithTableName("Books");
    
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::ScanOutcome scanOutcome = dynamoClient.Scan(scanRequest);
    
    if (scanOutcome.IsSuccess()) {
        auto items = scanOutcome.GetResult().GetItems();
        for (auto x : items) {
            std::cout << x.find("Author")->first << std::endl;
            std::cout << x.find("Author")->second.GetS() << std::endl;
            /*
             Book(std::vector<std::string> authors, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::vector<std::string> isbn = {}, std::vector<std::string> oclc = {})
             */
            
            //TODO: support multiple ISBN and OCLC
            
            rtl::Book newBook({x.find("Author")->second.GetS().c_str()}, x.find("Title")->second.GetS().c_str(), x.find("Series")->second.GetS().c_str(), x.find("Publisher")->second.GetS().c_str(), std::stoi(x.find("Page Count")->second.GetN().c_str()), x.find("Genre")->second.GetS().c_str(), x.find("Publish Date")->second.GetS().c_str(), {x.find("ISBN")->second.GetS().c_str()}, {x.find("OCLC")->second.GetS().c_str()});
            
            returnVector.push_back(newBook);
        }
    }
    else {
        std::cout << scanOutcome.GetError() << std::endl;
    }
    
    
    return returnVector;
}

void rtl::ServerMethods::SetClientConfig() {
    this->clientConfig.scheme = Aws::Http::Scheme::HTTPS;
    this->clientConfig.region = "us-east-2";
}

rtl::ServerMethods& rtl::ServerMethods::GetInstance() {
    static ServerMethods instance;
    return instance;
}

rtl::ServerMethods::ServerMethods() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    SetClientConfig();
}

rtl::ServerMethods::~ServerMethods() {
   Aws::SDKOptions options;
   Aws::ShutdownAPI(options);
}
