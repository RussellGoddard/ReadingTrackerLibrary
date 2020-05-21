//
//  ServerMethods.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 4/11/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "ServerMethods.hpp"

bool rtl::ServerMethods::testDyanamodb(std::vector<std::shared_ptr<rtl::Book>> input) {
    bool isSuccess = true;
    
    for (auto x : input) {
        isSuccess = std::min(this->AddBook(x), isSuccess);
    }
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::TransactWriteItemsRequest test;
    Aws::DynamoDB::Model::TransactWriteItem test2;
    
    
    for (auto x : input) {
        Aws::DynamoDB::Model::Put test3;
        Aws::DynamoDB::Model::AttributeValue bookId;
        bookId.SetS(Aws::String(x->GetBookId()));
        test3.AddItem("bookId", bookId);

        Aws::DynamoDB::Model::AttributeValue author;
        Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> authors;
        for (auto x : x->GetAuthors()) {
            authors.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
        }
        author.SetL(authors);
        test3.AddItem("author", author);
         
        Aws::DynamoDB::Model::AttributeValue isbn;
        Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> isbns;
        for (auto x : x->GetIsbn()) {
            isbns.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
        }
        isbn.SetL(isbns);
        test3.AddItem("isbn", isbn);
         
        Aws::DynamoDB::Model::AttributeValue oclc;
        Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> oclcs;
        for (auto x : x->GetOclc()) {
            oclcs.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
        }
        oclc.SetL(oclcs);
        test3.AddItem("oclc", oclc);
         
        Aws::DynamoDB::Model::AttributeValue authorId;
        Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> authorIds;
        for (auto x : x->GetAuthorId()) {
            authorIds.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
        }
        authorId.SetL(authorIds);
        test3.AddItem("authorId", authorId);
         
        Aws::DynamoDB::Model::AttributeValue title;
        title.SetS(Aws::String(x->GetTitle()));
        test3.AddItem("title", title);
         
        Aws::DynamoDB::Model::AttributeValue series;
        series.SetS(Aws::String(x->GetSeries()));
        test3.AddItem("series", series);
         
        Aws::DynamoDB::Model::AttributeValue publisher;
        publisher.SetS(Aws::String(x->GetPublisher()));
        test3.AddItem("publisher", publisher);
         
        Aws::DynamoDB::Model::AttributeValue genre;
        genre.SetS(Aws::String(x->PrintGenre()));
        test3.AddItem("genre", genre);
         
        Aws::DynamoDB::Model::AttributeValue pageCount;
        pageCount.SetN(x->GetPageCount());
        test3.AddItem("pageCount", pageCount);
         
        Aws::DynamoDB::Model::AttributeValue publishDate;
        publishDate.SetS(Aws::String(x->PrintPublishDate()));
        test3.AddItem("publishDate", publishDate);
        
        test2.SetPut(test3);
    }
    
    test.AddTransactItems(test2);
    
    const Aws::DynamoDB::Model::TransactWriteItemsOutcome test4 = dynamoClient.TransactWriteItems(test);
    
    return test4.IsSuccess();
}

bool rtl::ServerMethods::AddBook(std::vector<std::shared_ptr<rtl::Book>> input) {
    bool isSuccess = true;
    
    for (auto x : input) {
        isSuccess = std::min(this->AddBook(x), isSuccess);
    }

    return isSuccess;
}

bool rtl::ServerMethods::AddBook(std::shared_ptr<rtl::Book> input) {
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    
    Aws::DynamoDB::Model::PutItemRequest pir;
    pir.SetTableName(Aws::String(this->booksTableName));

    Aws::DynamoDB::Model::AttributeValue bookId;
    bookId.SetS(Aws::String(input->GetBookId()));
    pir.AddItem("bookId", bookId);

    Aws::DynamoDB::Model::AttributeValue author;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> authors;
    for (auto x : input->GetAuthors()) {
        authors.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
    }
    author.SetL(authors);
    pir.AddItem("author", author);
    
    Aws::DynamoDB::Model::AttributeValue isbn;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> isbns;
    for (auto x : input->GetIsbn()) {
        isbns.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
    }
    isbn.SetL(isbns);
    pir.AddItem("isbn", isbn);
    
    Aws::DynamoDB::Model::AttributeValue oclc;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> oclcs;
    for (auto x : input->GetOclc()) {
        oclcs.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
    }
    oclc.SetL(oclcs);
    pir.AddItem("oclc", oclc);
    
    Aws::DynamoDB::Model::AttributeValue authorId;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> authorIds;
    for (auto x : input->GetAuthorId()) {
        authorIds.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadBook", Aws::String(x)));
    }
    authorId.SetL(authorIds);
    pir.AddItem("authorId", authorId);
    
    Aws::DynamoDB::Model::AttributeValue title;
    title.SetS(Aws::String(input->GetTitle()));
    pir.AddItem("title", title);
    
    Aws::DynamoDB::Model::AttributeValue series;
    series.SetS(Aws::String(input->GetSeries()));
    pir.AddItem("series", series);
    
    Aws::DynamoDB::Model::AttributeValue publisher;
    publisher.SetS(Aws::String(input->GetPublisher()));
    pir.AddItem("publisher", publisher);
    
    Aws::DynamoDB::Model::AttributeValue genre;
    genre.SetS(Aws::String(input->PrintGenre()));
    pir.AddItem("genre", genre);
    
    Aws::DynamoDB::Model::AttributeValue pageCount;
    pageCount.SetN(input->GetPageCount());
    pir.AddItem("pageCount", pageCount);
    
    Aws::DynamoDB::Model::AttributeValue publishDate;
    publishDate.SetS(Aws::String(input->PrintPublishDate()));
    pir.AddItem("publishDate", publishDate);
    
    const Aws::DynamoDB::Model::PutItemOutcome result = dynamoClient.PutItem(pir);
    if (!result.IsSuccess())
    {
        BOOST_LOG_TRIVIAL(warning) << result.GetError().GetMessage();
        return false;
    }
    return true;
}

std::vector<std::shared_ptr<rtl::Book>> rtl::ServerMethods::LoadBooks() {
    //TODO: support pagination
    std::vector<std::shared_ptr<rtl::Book>> returnVector;
    
    Aws::DynamoDB::Model::ScanRequest scanRequest;
    scanRequest.WithTableName(Aws::String(this->booksTableName));
    
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::ScanOutcome scanOutcome = dynamoClient.Scan(scanRequest);
    
    if (scanOutcome.IsSuccess()) {
        auto items = scanOutcome.GetResult().GetItems();
        for (auto x : items) {
            
            std::vector<std::string> allAuthors;
            for (auto y : x.find("author")->second.GetL()) {
                allAuthors.push_back(y->GetS().c_str());
            }
            
            std::vector<std::string> allIsbn;
            for (auto y : x.find("isbn")->second.GetL()) {
                allIsbn.push_back(y->GetS().c_str());
            }
            
            std::vector<std::string> allOclc;
            for (auto y : x.find("oclc")->second.GetL()) {
                allOclc.push_back(y->GetS().c_str());
            }
            
            rtl::Book newBook(allAuthors, x.find("title")->second.GetS().c_str(), x.find("series")->second.GetS().c_str(), x.find("publisher")->second.GetS().c_str(), std::stoi(x.find("pageCount")->second.GetN().c_str()), x.find("genre")->second.GetS().c_str(), x.find("publishDate")->second.GetS().c_str(), allIsbn, allOclc);
            
            returnVector.push_back(std::make_shared<rtl::Book>(newBook));
        }
    }
    else {
        //TODO: should this always return empty vector?
        BOOST_LOG_TRIVIAL(warning) << scanOutcome.GetError();
        returnVector.clear();
        return returnVector;
    }
    
    rtl::InMemoryContainers& inMemoryContainer = rtl::InMemoryContainers::GetInstance();
    inMemoryContainer.AddMasterBooks(returnVector);
    
    return returnVector;
}

bool rtl::ServerMethods::AddReadBook(std::shared_ptr<rtl::ReadBook> input) {
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    
    Aws::DynamoDB::Model::PutItemRequest pir;
    pir.SetTableName(Aws::String(this->readbooksTableName));

    Aws::DynamoDB::Model::AttributeValue bookId;
    bookId.SetS(Aws::String(input->GetBookId()));
    pir.AddItem("bookId", bookId);

    Aws::DynamoDB::Model::AttributeValue author;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> authors;
    for (auto x : input->GetAuthors()) {
        authors.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadReadBook", Aws::String(x)));
    }
    author.SetL(authors);
    pir.AddItem("author", author);
    
    Aws::DynamoDB::Model::AttributeValue isbn;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> isbns;
    for (auto x : input->GetIsbn()) {
        isbns.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadReadBook", Aws::String(x)));
    }
    isbn.SetL(isbns);
    pir.AddItem("isbn", isbn);
    
    Aws::DynamoDB::Model::AttributeValue oclc;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> oclcs;
    for (auto x : input->GetOclc()) {
        oclcs.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadReadBook", Aws::String(x)));
    }
    oclc.SetL(oclcs);
    pir.AddItem("oclc", oclc);
    
    Aws::DynamoDB::Model::AttributeValue authorId;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> authorIds;
    for (auto x : input->GetAuthorId()) {
        authorIds.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadReadBook", Aws::String(x)));
    }
    authorId.SetL(authorIds);
    pir.AddItem("authorId", authorId);
    
    Aws::DynamoDB::Model::AttributeValue title;
    title.SetS(Aws::String(input->GetTitle()));
    pir.AddItem("title", title);
    
    Aws::DynamoDB::Model::AttributeValue series;
    series.SetS(Aws::String(input->GetSeries()));
    pir.AddItem("series", series);
    
    Aws::DynamoDB::Model::AttributeValue publisher;
    publisher.SetS(Aws::String(input->GetPublisher()));
    pir.AddItem("publisher", publisher);
    
    Aws::DynamoDB::Model::AttributeValue genre;
    genre.SetS(Aws::String(input->PrintGenre()));
    pir.AddItem("genre", genre);
    
    Aws::DynamoDB::Model::AttributeValue pageCount;
    pageCount.SetN(input->GetPageCount());
    pir.AddItem("pageCount", pageCount);
    
    Aws::DynamoDB::Model::AttributeValue publishDate;
    publishDate.SetS(Aws::String(input->PrintPublishDate()));
    pir.AddItem("publishDate", publishDate);
    
    Aws::DynamoDB::Model::AttributeValue readerId;
    readerId.SetS(Aws::String(input->GetReaderId()));
    pir.AddItem("readerId", readerId);
    
    Aws::DynamoDB::Model::AttributeValue rating;
    rating.SetN(input->GetRating());
    pir.AddItem("rating", rating);
    
    Aws::DynamoDB::Model::AttributeValue dateRead;
    dateRead.SetS(Aws::String(input->PrintDateRead()));
    pir.AddItem("dateRead", dateRead);
    
    const Aws::DynamoDB::Model::PutItemOutcome result = dynamoClient.PutItem(pir);
    if (!result.IsSuccess())
    {
        BOOST_LOG_TRIVIAL(warning) << result.GetError().GetMessage();
        return false;
    }
    return true;
}

bool rtl::ServerMethods::AddReadBook(std::vector<std::shared_ptr<rtl::ReadBook>> input) {
    bool isSuccess = true;
    
    for (auto x : input) {
        isSuccess = std::min(this->AddReadBook(x), isSuccess);
    }
    
    return isSuccess;
}

std::vector<std::shared_ptr<rtl::ReadBook>> rtl::ServerMethods::LoadReadBooks() {
    //TODO: support pagination
    std::vector<std::shared_ptr<rtl::ReadBook>> returnVector;
    
    Aws::DynamoDB::Model::ScanRequest scanRequest;
    scanRequest.WithTableName(Aws::String(this->readbooksTableName));
    
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::ScanOutcome scanOutcome = dynamoClient.Scan(scanRequest);
    
    if (scanOutcome.IsSuccess()) {
        auto items = scanOutcome.GetResult().GetItems();
        for (auto x : items) {
            
            std::vector<std::string> allAuthors;
            for (auto y : x.find("author")->second.GetL()) {
                allAuthors.push_back(y->GetS().c_str());
            }
            
            std::vector<std::string> allIsbn;
            for (auto y : x.find("isbn")->second.GetL()) {
                allIsbn.push_back(y->GetS().c_str());
            }
            
            std::vector<std::string> allOclc;
            for (auto y : x.find("oclc")->second.GetL()) {
                allOclc.push_back(y->GetS().c_str());
            }
            
            rtl::Book newBook(allAuthors, x.find("title")->second.GetS().c_str(), x.find("series")->second.GetS().c_str(), x.find("publisher")->second.GetS().c_str(), std::stoi(x.find("pageCount")->second.GetN().c_str()), x.find("genre")->second.GetS().c_str(), x.find("publishDate")->second.GetS().c_str(), allIsbn, allOclc);
            
            rtl::ReadBook newReadBook(x.find("readerId")->second.GetS().c_str(), newBook, std::stoi(x.find("rating")->second.GetN().c_str()), x.find("dateRead")->second.GetS().c_str());
            
            returnVector.push_back(std::make_shared<rtl::ReadBook>(newReadBook));
        }
    }
    else {
        //TODO: should this always return empty vector?
        BOOST_LOG_TRIVIAL(warning) << scanOutcome.GetError();
        returnVector.clear();
        return returnVector;
    }
    
    rtl::InMemoryContainers& inMemoryContainer = rtl::InMemoryContainers::GetInstance();
    inMemoryContainer.AddMasterReadBooks(returnVector);
    
    return returnVector;
}

bool rtl::ServerMethods::AddAuthor(std::shared_ptr<rtl::Author> input) {
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    
    Aws::DynamoDB::Model::PutItemRequest pir;
    pir.SetTableName(Aws::String(this->authorsTableName));

    Aws::DynamoDB::Model::AttributeValue authorId;
    authorId.SetS(Aws::String(input->GetAuthorId()));
    pir.AddItem("authorId", authorId);

    Aws::DynamoDB::Model::AttributeValue name;
    name.SetS(Aws::String(input->GetName()));
    pir.AddItem("name", name);
    
    Aws::DynamoDB::Model::AttributeValue dateBorn;
    dateBorn.SetS(Aws::String(input->PrintDateBorn()));
    pir.AddItem("dateBorn", dateBorn);
    
    Aws::DynamoDB::Model::AttributeValue booksWritten;
    Aws::Vector<std::shared_ptr<Aws::DynamoDB::Model::AttributeValue>> books;
    for (auto x : input->GetBooksWritten()) {
        books.push_back(Aws::MakeShared<Aws::DynamoDB::Model::AttributeValue>("UploadAuthor", Aws::String(x->PrintJson())));
    }
    booksWritten.SetL(books);
    pir.AddItem("booksWritten", booksWritten);

    const Aws::DynamoDB::Model::PutItemOutcome result = dynamoClient.PutItem(pir);
    if (!result.IsSuccess())
    {
        BOOST_LOG_TRIVIAL(warning) << result.GetError().GetMessage();
        return false;
    }
    return true;
}

bool rtl::ServerMethods::AddAuthor(std::vector<std::shared_ptr<rtl::Author>> input) {
    bool isSuccess = true;
    
    for (auto x : input) {
        isSuccess = std::min(this->AddAuthor(x), isSuccess);
    }
    
    return isSuccess;
}

std::vector<std::shared_ptr<rtl::Author>> rtl::ServerMethods::LoadAuthors() {
    //TODO: support pagination
    std::vector<std::shared_ptr<rtl::Author>> returnVector;
    
    Aws::DynamoDB::Model::ScanRequest scanRequest;
    scanRequest.WithTableName(Aws::String(this->authorsTableName));
    
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::ScanOutcome scanOutcome = dynamoClient.Scan(scanRequest);
    
    if (scanOutcome.IsSuccess()) {
        auto items = scanOutcome.GetResult().GetItems();
        for (auto x : items) {
            
            std::vector<std::shared_ptr<rtl::Book>> booksWritten;
            for (auto y : x.find("booksWritten")->second.GetL()) {
                std::shared_ptr<rtl::Book> newBook = rtl::ConvertJsonToBookPtr(nlohmann::json::parse(y->GetS().c_str()));
                booksWritten.push_back(newBook);
            }

            rtl::Author newAuthor(x.find("name")->second.GetS().c_str(), x.find("dateBorn")->second.GetS().c_str(), booksWritten);
            
            returnVector.push_back(std::make_shared<rtl::Author>(newAuthor));
        }
    }
    else {
        //TODO: should this always return empty vector?
        BOOST_LOG_TRIVIAL(warning) << scanOutcome.GetError();
        returnVector.clear();
        return returnVector;
    }
    
    rtl::InMemoryContainers& inMemoryContainer = rtl::InMemoryContainers::GetInstance();
    inMemoryContainer.AddMasterAuthors(returnVector);
    
    return returnVector;
}

bool rtl::ServerMethods::ClearTables() {
    if (this->booksTableName.find("Dev") != 0) {
        BOOST_LOG_TRIVIAL(info) << "ClearTables can only be performed on dev tables: " << this->booksTableName;
        return false;
    }
    else if (this->readbooksTableName.find("Dev") != 0) {
        BOOST_LOG_TRIVIAL(info) << "ClearTables can only be performed on dev tables: " << this->readbooksTableName;
        return false;
    }
    else if (this->authorsTableName.find("Dev") != 0) {
        BOOST_LOG_TRIVIAL(info) << "ClearTables can only be performed on dev tables: " << this->authorsTableName;
        return false;
    }
    
    bool isSuccess = false;
    if (ClearTable(this->booksTableName)) {
        isSuccess = std::max(CreateTable(this->booksTableName, "bookId"), isSuccess);
    }
    if (ClearTable(this->readbooksTableName)) {
        isSuccess = std::max(CreateTable(this->readbooksTableName, "readerId", "bookId"), isSuccess);
    }
    if (ClearTable(this->authorsTableName)) {
        isSuccess = std::max(CreateTable(this->authorsTableName, "authorId"), isSuccess);
    }
    
    return isSuccess;
}

bool rtl::ServerMethods::ClearTable(std::string tableName) {
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);

    Aws::DynamoDB::Model::DeleteTableRequest dtr;
    dtr.SetTableName(Aws::String(tableName));

    const Aws::DynamoDB::Model::DeleteTableOutcome& result = dynamoClient.DeleteTable(dtr);
    if (result.IsSuccess()) {
        return true;
    }
    else {
        BOOST_LOG_TRIVIAL(error) << "Failed to delete table: " << result.GetError().GetMessage();
        return false;
    }
}

bool rtl::ServerMethods::CreateTable(std::string tableName, std::string partitionKey, std::string sortKey) {
    
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::CreateTableRequest req;

    Aws::DynamoDB::Model::AttributeDefinition hashKey1, hashKey2;
    hashKey1.WithAttributeName(Aws::String(partitionKey)).WithAttributeType(Aws::DynamoDB::Model::ScalarAttributeType::S);
    req.AddAttributeDefinitions(hashKey1);
    if (sortKey != "") {
        hashKey2.WithAttributeName(Aws::String(sortKey)).WithAttributeType(Aws::DynamoDB::Model::ScalarAttributeType::S);
        req.AddAttributeDefinitions(hashKey2);
    }

    Aws::DynamoDB::Model::KeySchemaElement kse1, kse2;
    kse1.WithAttributeName(Aws::String(partitionKey)).WithKeyType(Aws::DynamoDB::Model::KeyType::HASH);
    req.AddKeySchema(kse1);
    if (sortKey != "") {
        kse2.WithAttributeName(Aws::String(sortKey)).WithKeyType(Aws::DynamoDB::Model::KeyType::RANGE);
        req.AddKeySchema(kse2);
    }
    
    Aws::DynamoDB::Model::ProvisionedThroughput thruput;
    thruput.WithReadCapacityUnits(5).WithWriteCapacityUnits(5);
    req.SetProvisionedThroughput(thruput);

    req.SetTableName(Aws::String(tableName));

    const Aws::DynamoDB::Model::CreateTableOutcome& result = dynamoClient.CreateTable(req);
    if (result.IsSuccess()) {
        return true;
    }
    else {
        BOOST_LOG_TRIVIAL(error) << "Failed to create table:" << result.GetError().GetMessage();
        return false;
    }
}

void rtl::ServerMethods::SetClientConfig() {
    this->clientConfig.scheme = Aws::Http::Scheme::HTTPS;
    this->clientConfig.region = "us-east-2";
    
    return;
}

rtl::ServerMethods& rtl::ServerMethods::GetInstance(bool isDev) {
    static ServerMethods instance(isDev);
    return instance;
}

rtl::ServerMethods::ServerMethods(bool isDev) {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    SetClientConfig();
    if (isDev) {
        this->booksTableName = "DevBooks";
        this->readbooksTableName = "DevReadBooks";
        this->authorsTableName = "DevAuthors";
    }
}

rtl::ServerMethods::~ServerMethods() {
   Aws::SDKOptions options;
   Aws::ShutdownAPI(options);
}
