//
//  testJsonHelper.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 3/21/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "JsonFunctions.hpp"

@interface testJsonHelper : XCTestCase

@end

@implementation testJsonHelper

- (void)setUp {
}

- (void)tearDown {
}

- (void)testConvertJsonToBookPtr {
    nlohmann::json jsonTestPass = R"(
      {
        "author":"Robert Jordan",
        "genre":"fantasy",
        "pageCount":684,
        "publisher":"Tor Books",
        "series":"The Wheel of Time",
        "title":"The Fires of Heaven",
        "publishDate":"1992-Sep-15",
        "isbn":["1234567890","1234567890abc"],
        "oclc":["123456"]
      }
    )"_json;
    
    std::shared_ptr<rtl::Book> testPtrBook1 = rtl::ConvertJsonToBookPtr(jsonTestPass);
    
    XCTAssert(testPtrBook1->GetAuthor() == jsonTestPass["author"].get<std::string>());
    XCTAssert(testPtrBook1->PrintGenre() == jsonTestPass["genre"].get<std::string>());
    XCTAssert(testPtrBook1->GetPageCount() == jsonTestPass["pageCount"].get<int>());
    XCTAssert(testPtrBook1->GetPublisher() == jsonTestPass["publisher"].get<std::string>());
    XCTAssert(testPtrBook1->GetSeries() == jsonTestPass["series"].get<std::string>());
    XCTAssert(testPtrBook1->GetTitle() == jsonTestPass["title"].get<std::string>());
    XCTAssert(testPtrBook1->PrintPublishDate() == jsonTestPass["publishDate"].get<std::string>());
    XCTAssert(testPtrBook1->GetIsbn().size() == 2);
    XCTAssert(testPtrBook1->GetIsbn().at(0) == "1234567890");
    XCTAssert(testPtrBook1->GetIsbn().at(1) == "1234567890abc");
    XCTAssert(testPtrBook1->GetOclc().size() == 1);
    XCTAssert(testPtrBook1->GetOclc().at(0) == "123456");
    
    nlohmann::json jsonTestFail = R"(
      {
        "a":"Robert Jordan",
        "g":"fantasy",
        "p":684,
        "p":"Tor Books",
        "s":"The Wheel of Time",
        "t":"The Fires of Heaven",
        "p":"1992-Sep-15"
      }
    )"_json;
    
    XCTAssert(rtl::ConvertJsonToBookPtr(jsonTestFail) == nullptr);
}

- (void)testConvertJsonToReadBookPtr {
    
    nlohmann::json jsonTestPass = R"(
      {
        "readerId":123,
        "author":"Robert Jordan",
        "isbn":[],
        "oclc":["123456"],
        "dateRead":"2020-Jan-29",
        "genre":"fantasy",
        "pageCount":684,
        "publisher":"Tor Books",
        "series":"The Wheel of Time",
        "title":"The Fires of Heaven",
        "publishDate":"1992-Sep-15",
        "rating":9,
        "dateRead":"1993-Sep-25"
      }
    )"_json;
    
    std::shared_ptr<rtl::ReadBook> testPtrReadBook1 = rtl::ConvertJsonToReadBookPtr(jsonTestPass);
    
    XCTAssert(testPtrReadBook1->GetReaderId() == jsonTestPass["readerId"].get<int>());
    XCTAssert(testPtrReadBook1->GetAuthor() == jsonTestPass["author"].get<std::string>());
    XCTAssert(testPtrReadBook1->PrintGenre() == jsonTestPass["genre"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetPageCount() == jsonTestPass["pageCount"].get<int>());
    XCTAssert(testPtrReadBook1->GetPublisher() == jsonTestPass["publisher"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetSeries() == jsonTestPass["series"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetTitle() == jsonTestPass["title"].get<std::string>());
    XCTAssert(testPtrReadBook1->PrintPublishDate() == jsonTestPass["publishDate"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetRating() == jsonTestPass["rating"].get<int>());
    XCTAssert(testPtrReadBook1->PrintDateRead() == jsonTestPass["dateRead"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetIsbn().size() == jsonTestPass["isbn"].size());
    XCTAssert(testPtrReadBook1->GetIsbn().size() == 0);
    XCTAssert(testPtrReadBook1->GetOclc().size() == jsonTestPass["oclc"].size());
    XCTAssert(testPtrReadBook1->GetOclc()[0] == jsonTestPass["oclc"][0]);
    
    
    
    nlohmann::json jsonTestFail = R"(
      {
        "r":123,
        "a":"Robert Jordan",
        "dateRead":"2020-Jan-29",
        "genre":"fantasy",
        "pageCount":684,
        "publisher":"Tor Books",
        "series":"The Wheel of Time",
        "title":"The Fires of Heaven",
        "publishDate":"1992-Sep-15",
        "rating":9,
        "dateRead":"1993-Sep-25"
      }
    )"_json;
    
    XCTAssert(rtl::ConvertJsonToReadBookPtr(jsonTestFail) == nullptr);
}

- (void)testConvertJsonToAuthorPtr {
    nlohmann::json jsonTestPass = R"(
      {
          "name": "3rd",
          "dateBorn": "2000-Apr-01",
          "booksWritten": [{
              "isbn":["1234567890"],
              "oclc":["123456"],
              "author": "testAuthor1",
              "title": "testTitle1",
              "series": "testSeries1",
              "publisher": "testPublisher1",
              "genre": "fantasy",
              "pageCount": 1,
              "publishDate": "1978-Oct-15"
          }, {
              "isbn":["1234567890abc"],
              "oclc":[],
              "author": "testAuthor2",
              "title": "testTitle2",
              "series": "testSeries2",
              "publisher": "testPublisher2",
              "genre": "western",
              "pageCount": 22,
              "publishDate": "1983-Apr-25"
          }]
      }
    )"_json;
    
    std::shared_ptr<rtl::Author> testPtrAuthor1 = rtl::ConvertJsonToAuthorPtr(jsonTestPass);
    
    XCTAssert(testPtrAuthor1->GetName() == jsonTestPass["name"].get<std::string>());
    XCTAssert(testPtrAuthor1->PrintDateBorn() == jsonTestPass["dateBorn"].get<std::string>());
    XCTAssert(testPtrAuthor1->GetBooksWritten().size() == jsonTestPass.at("booksWritten").size());

    nlohmann::json jsonTestFail = R"(
      {
          "n": "3rd",
          "dBorn": "2000-Apr-01",
          "booksWritten": [{
              "author": "testAuthor1",
              "title": "testTitle1",
              "series": "testSeries1",
              "publisher": "testPublisher1",
              "genre": "fantasy",
              "pageCount": 1,
              "publishDate": "1978-Oct-15"
          }, {
              "author": "testAuthor2",
              "title": "testTitle2",
              "series": "testSeries2",
              "publisher": "testPublisher2",
              "genre": "western",
              "pageCount": 22,
              "publishDate": "1983-Apr-25"
          }]
      }
    )"_json;
    
    XCTAssert(rtl::ConvertJsonToAuthorPtr(jsonTestFail) == nullptr);
}

- (void)testConvertJsonToReadBook {
    nlohmann::json jsonTestPass = R"(
      {
        "readerId":456,
        "author":"Robert Jordan",
        "dateRead":"2020-Jan-29",
        "genre":"fantasy",
        "pageCount":684,
        "publisher":"Tor Books",
        "rating":9,
        "series":"The Wheel of Time",
        "title":"The Fires of Heaven",
        "publishDate":"1992-Sep-15"
      }
    )"_json;
    
    rtl::ReadBook testReadBook1 = rtl::ConvertJsonToReadBook(jsonTestPass);
    
    XCTAssert(testReadBook1.GetReaderId() == jsonTestPass["readerId"].get<int>());
    XCTAssert(testReadBook1.GetAuthor() == jsonTestPass["author"].get<std::string>());
    XCTAssert(testReadBook1.PrintDateRead() == jsonTestPass["dateRead"].get<std::string>());
    XCTAssert(testReadBook1.PrintGenre() == jsonTestPass["genre"].get<std::string>());
    XCTAssert(testReadBook1.GetPageCount() == jsonTestPass["pageCount"].get<int>());
    XCTAssert(testReadBook1.GetPublisher() == jsonTestPass["publisher"].get<std::string>());
    XCTAssert(testReadBook1.GetRating() == jsonTestPass["rating"].get<int>());
    XCTAssert(testReadBook1.GetSeries() == jsonTestPass["series"].get<std::string>());
    XCTAssert(testReadBook1.GetTitle() == jsonTestPass["title"].get<std::string>());
    XCTAssert(testReadBook1.PrintPublishDate() == jsonTestPass["publishDate"].get<std::string>());
    
    nlohmann::json jsonTestFail = R"(
      {
        "r":456,
        "hor":"Robert Jordan",
        "dateRead":"2020-Jan-29",
        "genre":"fantasy",
        "pageCount":684,
        "publisher":"Tor Books",
        "rating":9,
        "series":"The Wheel of Time",
        "title":"The Fires of Heaven",
        "publishDate":"1992-Sep-15"
      }
    )"_json;
    
    XCTAssert(rtl::ConvertJsonToReadBook(jsonTestFail).GetReaderId() == -1);
}

- (void)testPrintJsonReadBook {
    rtl::ReadBook testReadBook1(1, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetDateRead("1993-Mar-25");
    testReadBook1.SetRating(4);
    
    std::string jsonString = R"({"bookId":"1bba","isbn":[],"oclc":[],"author":"a","authorId":"4e","title":"a","series":"a","publisher":"a","genre":"fantasy","pageCount":100,"publishDate":"1990-Dec-01","rating":4,"dateRead":"1993-Mar-25","readerId":1})";
    
    XCTAssert(rtl::PrintJson(std::make_shared<rtl::ReadBook>(testReadBook1)) == jsonString);
}


- (void)testPrintJsonAuthor {
    std::shared_ptr<rtl::Book> testBook1 = std::make_shared<rtl::Book>("3rd", "testTitle1", "testSeries1", "testPublisher1", 1, rtl::fantasy, "1992-Nov-11");
    std::shared_ptr<rtl::Book> testBook2 = std::make_shared<rtl::Book>("3rd", "testTitle2", "testSeries2", "testPublisher2", 22, rtl::western, "2020-Nov-11");
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "2001-Nov-12");
    rtl::Author testAuthor3("3rd", "2000-Apr-01");
    testAuthor3.AddBookWritten(testBook1);
    testAuthor3.AddBookWritten(testBook2);
    
    XCTAssert(rtl::PrintJson(std::make_shared<rtl::Author>(testAuthor1)) == R"({"authorId":"4e","name":"a","dateBorn":"1990-Dec-01","booksWritten":[]})");
    XCTAssert(rtl::PrintJson(std::make_shared<rtl::Author>(testAuthor2)) == R"({"authorId":"4f","name":"b","dateBorn":"2001-Nov-12","booksWritten":[]})");
    XCTAssert(rtl::PrintJson(std::make_shared<rtl::Author>(testAuthor3)) == R"({"authorId":"268","name":"3rd","dateBorn":"2000-Apr-01","booksWritten":[{"bookId":"4735c0","isbn":[],"oclc":[],"author":"3rd","authorId":"268","title":"testTitle1","series":"testSeries1","publisher":"testPublisher1","genre":"fantasy","pageCount":1,"publishDate":"1992-Nov-11"},{"bookId":"474dd0","isbn":[],"oclc":[],"author":"3rd","authorId":"268","title":"testTitle2","series":"testSeries2","publisher":"testPublisher2","genre":"western","pageCount":22,"publishDate":"2020-Nov-11"}]})");
}

- (void)testPrintJsonBook {
    rtl::Book testBook("testAuthor", "testTitle");
    testBook.AddIsbn("1234567890");
    testBook.AddIsbn("1234567890abc");
    testBook.AddOclc("123456");
    testBook.SetSeries("testSeries");
    testBook.SetPublisher("testPublisher");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(10);
    testBook.SetPublishDate("1990-Dec-01");
    
    std::string answer = R"({"bookId":"2ff6b24","isbn":["1234567890","1234567890abc"],"oclc":["123456"],"author":"testAuthor","authorId":"1ecb","title":"testTitle","series":"testSeries","publisher":"testPublisher","genre":"fantasy","pageCount":10,"publishDate":"1990-Dec-01"})";
    XCTAssert(rtl::PrintJson(std::make_shared<rtl::Book>(testBook)) == answer);
}

@end
