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

- (void)test_ConvertJsonToBookPtr_PassJson_ReturnSharedPtrToBook {
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
}

- (void)test_ConvertJsonToBookPtr_PassInvalid_ReturnNullptr {
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

- (void)test_ConvertJsonToReadBookPtr_PassJson_ReturnSharedPtrReadBook {
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
}
    
- (void)test_ConvertJsonToReadBookPtr_PassInvalid_ReturnNullptr {
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

- (void)test_ConvertJsonToAuthorPtr_PassJson_ReturnSharedPtrAuthor {
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
}

- (void)test_ConvertJsonToAuthorPtr_PassInvalid_ReturnNullptr {
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

@end
