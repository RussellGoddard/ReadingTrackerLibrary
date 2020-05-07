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

bool rtl::ServerMethods::AddBook(std::shared_ptr<rtl::Book> input) {
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    
    Aws::DynamoDB::Model::PutItemRequest pir;
    pir.SetTableName("Books");

    Aws::DynamoDB::Model::AttributeValue bookId;
    bookId.SetS(Aws::String(input->GetBookId()));
    pir.AddItem("BookId", bookId);

    Aws::DynamoDB::Model::AttributeValue author;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> authors;
    for (auto x : input->GetAuthors()) {
        authors.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
    }
    author.SetL(authors);
    pir.AddItem("Authors", author);
    
    Aws::DynamoDB::Model::AttributeValue isbn;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> isbns;
    for (auto x : input->GetIsbn()) {
        isbns.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
    }
    isbn.SetL(isbns);
    pir.AddItem("ISBN", isbn);
    
    Aws::DynamoDB::Model::AttributeValue oclc;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> oclcs;
    for (auto x : input->GetOclc()) {
        oclcs.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
    }
    oclc.SetL(oclcs);
    pir.AddItem("OCLC", oclc);
    
    Aws::DynamoDB::Model::AttributeValue authorId;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> authorIds;
    for (auto x : input->GetAuthorId()) {
        authorIds.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
    }
    authorId.SetL(authorIds);
    pir.AddItem("AuthorId", authorId);
    
    Aws::DynamoDB::Model::AttributeValue title;
    title.SetS(Aws::String(input->GetTitle()));
    pir.AddItem("Title", title);
    
    Aws::DynamoDB::Model::AttributeValue series;
    series.SetS(Aws::String(input->GetSeries()));
    pir.AddItem("Series", series);
    
    Aws::DynamoDB::Model::AttributeValue publisher;
    publisher.SetS(Aws::String(input->GetPublisher()));
    pir.AddItem("Publisher", publisher);
    
    Aws::DynamoDB::Model::AttributeValue genre;
    genre.SetS(Aws::String(input->PrintGenre()));
    pir.AddItem("Genre", genre);
    
    Aws::DynamoDB::Model::AttributeValue pageCount;
    pageCount.SetN(input->GetPageCount());
    pir.AddItem("Page Count", pageCount);
    
    Aws::DynamoDB::Model::AttributeValue publishDate;
    publishDate.SetS(Aws::String(input->PrintPublishDate()));
    pir.AddItem("Publish Date", publishDate);
    
    const Aws::DynamoDB::Model::PutItemOutcome result = dynamoClient.PutItem(pir);
    if (!result.IsSuccess())
    {
        BOOST_LOG_TRIVIAL(warning) << result.GetError().GetMessage();
        return false;
    }
    return true;
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
            
            std::vector<std::string> allAuthors;
            for (auto y : x.find("Authors")->second.GetL()) {
                allAuthors.push_back(y->GetS().c_str());
            }
            
            std::vector<std::string> allIsbn;
            for (auto y : x.find("ISBN")->second.GetL()) {
                allIsbn.push_back(y->GetS().c_str());
            }
            
            std::vector<std::string> allOclc;
            for (auto y : x.find("OCLC")->second.GetL()) {
                allOclc.push_back(y->GetS().c_str());
            }
            
            rtl::Book newBook(allAuthors, x.find("Title")->second.GetS().c_str(), x.find("Series")->second.GetS().c_str(), x.find("Publisher")->second.GetS().c_str(), std::stoi(x.find("Page Count")->second.GetN().c_str()), x.find("Genre")->second.GetS().c_str(), x.find("Publish Date")->second.GetS().c_str(), allIsbn, allOclc);
            
            returnVector.push_back(newBook);
        }
    }
    else {
        //TODO: should this always return empty vector?
        BOOST_LOG_TRIVIAL(warning) << scanOutcome.GetError();
        returnVector.clear();
        return returnVector;
    }
    
    
    return returnVector;
}

void rtl::ServerMethods::SetClientConfig() {
    this->clientConfig.scheme = Aws::Http::Scheme::HTTPS;
    this->clientConfig.region = "us-east-2";
    
    return;
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
