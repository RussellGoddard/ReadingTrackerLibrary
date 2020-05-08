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

//TODO: LoadBooks should put books in FileMethods
std::vector<rtl::Book> rtl::ServerMethods::LoadBooks() {
    //TODO: support pagination
    std::vector<rtl::Book> returnVector;
    
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

//TODO: LoadReadBooks should put readbooks in FileMethods
std::vector<rtl::ReadBook> rtl::ServerMethods::LoadReadBooks() {
    //TODO: support pagination
    std::vector<rtl::ReadBook> returnVector;
    
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
            
            returnVector.push_back(newReadBook);
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

//TODO: LoadAuthors should put authors in FileMethods
std::vector<rtl::Author> rtl::ServerMethods::LoadAuthors() {
    //TODO: support pagination
    std::vector<rtl::Author> returnVector;
    
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
            
            returnVector.push_back(newAuthor);
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
