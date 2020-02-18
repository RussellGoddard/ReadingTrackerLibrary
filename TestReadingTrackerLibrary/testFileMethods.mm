//
//  testFileMethods.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/24/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <filesystem>
#include <vector>
#include "FileMethods.hpp"

@interface testFileMethods : XCTestCase

@end

@implementation testFileMethods

- (void)setUp {
}

- (void)tearDown {
    InMemoryContainers& testContainer = InMemoryContainers::getInstance();
    testContainer.clearAll();
}
//figure out how to test FileMethods TO DO
- (void)testReadBookVector {
    ReadBook testReadBook1;
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar 25 1993");
    
    ReadBook testReadBook2;
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("b");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec 01 1990");
    testReadBook2.setRating(4);
    testReadBook2.setDateRead("Mar 25 1993");
    
    ReadBook testReadBook3;
    testReadBook3.setAuthor("a");
    testReadBook3.setTitle("a");
    testReadBook3.setSeries("a");
    testReadBook3.setPublisher("a");
    testReadBook3.setGenre("fantasy");
    testReadBook3.setPageCount(100);
    testReadBook3.setPublishDate("Dec 01 1990");
    testReadBook3.setRating(4);
    testReadBook3.setDateRead("Mar 25 1993");
    
    std::shared_ptr<ReadBook> testPtrReadBook1 = std::make_shared<ReadBook>(testReadBook1);
    std::shared_ptr<ReadBook> testPtrReadBook2 = std::make_shared<ReadBook>(testReadBook2);
    std::shared_ptr<ReadBook> testPtrReadBook3 = std::make_shared<ReadBook>(testReadBook3);
    std::vector<std::shared_ptr<ReadBook>> testReadBooks;
    testReadBooks.push_back(testPtrReadBook1);
    testReadBooks.push_back(testPtrReadBook2);
    testReadBooks.push_back(testPtrReadBook3);
    
    InMemoryContainers& testContainers = InMemoryContainers::getInstance();
    
    testContainers.addMasterReadBooks(testPtrReadBook1);
    
    XCTAssert(testContainers.getMasterReadBooks().size() == 1);
    XCTAssert(testContainers.getMasterReadBooks().at(0) == testPtrReadBook1);
    
    testContainers.addMasterReadBooks(testReadBooks);
    
    XCTAssert(testContainers.getMasterReadBooks().size() == 2);
    XCTAssert(testContainers.getMasterReadBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainers.getMasterReadBooks().at(1) == testPtrReadBook2);
}

- (void)testBookVector {
    Book testBook1;
    testBook1.setAuthor("testAuthor");
    testBook1.setTitle("testTitle");
    testBook1.setSeries("testSeries");
    testBook1.setPublisher("testPublisher");
    testBook1.setGenre("fantasy");
    testBook1.setPageCount(10);
    testBook1.setPublishDate("Dec 01 1990");
    
    Book testBook2;
    testBook2.setAuthor("testAuthor2");
    testBook2.setTitle("testTitle2");
    testBook2.setSeries("testSeries2");
    testBook2.setPublisher("testPublisher2");
    testBook2.setGenre("western");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("Dec 01 1991");
    
    Book testBook3;
    testBook3.setAuthor("testAuthor");
    testBook3.setTitle("testTitle");
    testBook3.setSeries("testSeries");
    testBook3.setPublisher("testPublisher");
    testBook3.setGenre("fantasy");
    testBook3.setPageCount(10);
    testBook3.setPublishDate("Dec 01 1990");
    
    std::shared_ptr<Book> testPtrBook1 = std::make_shared<Book>(testBook1);
    std::shared_ptr<Book> testPtrBook2 = std::make_shared<Book>(testBook2);
    std::shared_ptr<Book> testPtrBook3 = std::make_shared<Book>(testBook3);
    std::vector<std::shared_ptr<Book>> testBooks;
    testBooks.push_back(testPtrBook1);
    testBooks.push_back(testPtrBook2);
    testBooks.push_back(testPtrBook3);
    
    InMemoryContainers& testContainers = InMemoryContainers::getInstance();
    
    testContainers.addMasterBooks(testPtrBook1);
    
    XCTAssert(testContainers.getMasterBooks().size() == 1);
    XCTAssert(testContainers.getMasterBooks().at(0) == testPtrBook1);
    
    testContainers.addMasterBooks(testBooks);
    
    XCTAssert(testContainers.getMasterBooks().size() == 2);
    XCTAssert(testContainers.getMasterBooks().at(0) == testPtrBook1);
    XCTAssert(testContainers.getMasterBooks().at(1) == testPtrBook2);
}

- (void)testAuthorVector {
    Author testAuthor1("test author", "Dec 01 1990");
    Author testAuthor2("test buthor", "Dec 03 1990");
    Author testAuthor3("test author", "Dec 01 1990");
    
    std::shared_ptr<Author> testPtrAuthor1 = std::make_shared<Author>(testAuthor1);
    std::shared_ptr<Author> testPtrAuthor2 = std::make_shared<Author>(testAuthor2);
    std::shared_ptr<Author> testPtrAuthor3 = std::make_shared<Author>(testAuthor3);
    std::vector<std::shared_ptr<Author>> testAuthors;
    testAuthors.push_back(testPtrAuthor1);
    testAuthors.push_back(testPtrAuthor2);
    testAuthors.push_back(testPtrAuthor3);
    
    InMemoryContainers& testContainers = InMemoryContainers::getInstance();
    
    testContainers.addMasterAuthors(testPtrAuthor1);
    
    XCTAssert(testContainers.getMasterAuthors().size() == 1);
    XCTAssert(testContainers.getMasterAuthors().at(0) == testPtrAuthor1);
    
    testContainers.addMasterAuthors(testAuthors);
    
    XCTAssert(testContainers.getMasterAuthors().size() == 2);
    XCTAssert(testContainers.getMasterAuthors().at(0) == testPtrAuthor1);
    XCTAssert(testContainers.getMasterAuthors().at(1) == testPtrAuthor2);
}

- (void)testAuthorMergeBooksWhenSameAuthor {
    
    std::vector<std::shared_ptr<Book>> books1;
    std::vector<std::shared_ptr<Book>> books2;
    
    books1.push_back(std::make_shared<Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, romance, 1199163600));
    books1.push_back(std::make_shared<Book>("testAuthor", "testTitle3", "testSeries3", "testPublisher3", 3333, romance, 1199163600));
    books2.push_back(std::make_shared<Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, romance, 1199163600));
    books2.push_back(std::make_shared<Book>("testAuthor", "testTitle2", "testSeries2", "testPublisher2", 2222, romance, 1199163600));
    
    std::shared_ptr<Author> testPtrAuthor1 = std::make_shared<Author>("testAuthor", "Dec 01 1990", books1);
    std::shared_ptr<Author> testPtrAuthor2 = std::make_shared<Author>("testAuthor", "Dec 01 1990", books2);
    
    InMemoryContainers& testContainers = InMemoryContainers::getInstance();
    
    testContainers.addMasterAuthors(testPtrAuthor1);
    testContainers.addMasterAuthors(testPtrAuthor2);
    
    XCTAssert(testContainers.getMasterAuthors().size() == 1);
    XCTAssert(testContainers.getMasterAuthors().at(0)->getBooksWritten().size() == 3);
    XCTAssert(testContainers.getMasterAuthors().at(0)->getBooksWritten().at(0) == books1.at(0));
    XCTAssert(testContainers.getMasterAuthors().at(0)->getBooksWritten().at(1) == books2.at(1));
    XCTAssert(testContainers.getMasterAuthors().at(0)->getBooksWritten().at(2) == books1.at(1));

}

- (void)testConvertJsonToBookPtr {
    nlohmann::json jsonTest = R"(
      {
        "author":"Robert Jordan",
        "genre":"fantasy",
        "pageCount":684,
        "publisher":"Tor Books",
        "series":"The Wheel of Time",
        "title":"The Fires of Heaven",
        "publishDate":"Sep 15 1992"
      }
    )"_json;
    
    std::shared_ptr<Book> testPtrBook1 = convertJsonToBookPtr(jsonTest);
    
    XCTAssert(testPtrBook1->getAuthor() == jsonTest["author"].get<std::string>());
    XCTAssert(testPtrBook1->printGenre() == jsonTest["genre"].get<std::string>());
    XCTAssert(testPtrBook1->getPageCount() == jsonTest["pageCount"].get<int>());
    XCTAssert(testPtrBook1->getPublisher() == jsonTest["publisher"].get<std::string>());
    XCTAssert(testPtrBook1->getSeries() == jsonTest["series"].get<std::string>());
    XCTAssert(testPtrBook1->getTitle() == jsonTest["title"].get<std::string>());
    XCTAssert(testPtrBook1->printPublishDate() == jsonTest["publishDate"].get<std::string>());
}

- (void)testConvertJsonToReadBookPtr {
    
    nlohmann::json jsonTest = R"(
      {
        "author":"Robert Jordan",
        "dateRead":"Jan 29 2020",
        "genre":"fantasy",
        "pageCount":684,
        "publisher":"Tor Books",
        "series":"The Wheel of Time",
        "title":"The Fires of Heaven",
        "publishDate":"Sep 15 1992",
        "rating":9,
        "dateRead":"Sep 25 1993"
      }
    )"_json;
    
    std::shared_ptr<ReadBook> testPtrReadBook1 = convertJsonToReadBookPtr(jsonTest);
    
    XCTAssert(testPtrReadBook1->getAuthor() == jsonTest["author"].get<std::string>());
    XCTAssert(testPtrReadBook1->printGenre() == jsonTest["genre"].get<std::string>());
    XCTAssert(testPtrReadBook1->getPageCount() == jsonTest["pageCount"].get<int>());
    XCTAssert(testPtrReadBook1->getPublisher() == jsonTest["publisher"].get<std::string>());
    XCTAssert(testPtrReadBook1->getSeries() == jsonTest["series"].get<std::string>());
    XCTAssert(testPtrReadBook1->getTitle() == jsonTest["title"].get<std::string>());
    XCTAssert(testPtrReadBook1->printPublishDate() == jsonTest["publishDate"].get<std::string>());
    XCTAssert(testPtrReadBook1->getRating() == jsonTest["rating"].get<int>());
    XCTAssert(testPtrReadBook1->printDateRead() == jsonTest["dateRead"].get<std::string>());
}

- (void)testConvertJsonToAuthorPtr {
    nlohmann::json jsonTest = R"(
      {
          "name": "3rd",
          "dateBorn": "Apr 01 2000",
          "booksWritten": [{
              "author": "testAuthor1",
              "title": "testTitle1",
              "series": "testSeries1",
              "publisher": "testPublisher1",
              "genre": "fantasy",
              "pageCount": 1,
              "publishDate": "Oct 15 1978"
          }, {
              "author": "testAuthor2",
              "title": "testTitle2",
              "series": "testSeries2",
              "publisher": "testPublisher2",
              "genre": "western",
              "pageCount": 22,
              "publishDate": "Apr 25 1983"
          }]
      }
    )"_json;
    
    std::shared_ptr<Author> testPtrAuthor1 = convertJsonToAuthorPtr(jsonTest);
    
    XCTAssert(testPtrAuthor1->getName() == jsonTest["name"].get<std::string>());
    XCTAssert(testPtrAuthor1->printDateBorn() == jsonTest["dateBorn"].get<std::string>());
    XCTAssert(testPtrAuthor1->getBooksWritten().size() == jsonTest.at("booksWritten").size());
}

- (void)testConvertJsonToReadBook {
    nlohmann::json jsonTest = R"(
      {
        "author":"Robert Jordan",
        "dateRead":"Jan 29 2020",
        "genre":"fantasy",
        "pageCount":684,
        "publisher":"Tor Books",
        "rating":9,
        "series":"The Wheel of Time",
        "title":"The Fires of Heaven",
        "publishDate":"Sep 15 1992"
      }
    )"_json;
    
    ReadBook testReadBook1 = convertJsonToReadBook(jsonTest);
    
    XCTAssert(testReadBook1.getAuthor() == jsonTest["author"].get<std::string>());
    XCTAssert(testReadBook1.printDateRead() == jsonTest["dateRead"].get<std::string>());
    XCTAssert(testReadBook1.printGenre() == jsonTest["genre"].get<std::string>());
    XCTAssert(testReadBook1.getPageCount() == jsonTest["pageCount"].get<int>());
    XCTAssert(testReadBook1.getPublisher() == jsonTest["publisher"].get<std::string>());
    XCTAssert(testReadBook1.getRating() == jsonTest["rating"].get<int>());
    XCTAssert(testReadBook1.getSeries() == jsonTest["series"].get<std::string>());
    XCTAssert(testReadBook1.getTitle() == jsonTest["title"].get<std::string>());
    XCTAssert(testReadBook1.printPublishDate() == jsonTest["publishDate"].get<std::string>());
}

- (void)testSaveAndLoadInMemoryToFile {
    //std::string testFilePath = "./testSaveFile.txt";
    std::string testFilePath = "/Users/Frobu/Desktop/testFileSaveTest.txt";
    
    InMemoryContainers& testContainers = InMemoryContainers::getInstance();
    Book testBook1;
    testBook1.setAuthor("testAuthor");
    testBook1.setTitle("testTitle");
    testBook1.setSeries("testSeries");
    testBook1.setPublisher("testPublisher");
    testBook1.setGenre("fantasy");
    testBook1.setPageCount(10);
    testBook1.setPublishDate("Dec 01 1990");
    
    ReadBook testReadBook1;
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar 25 1993");
    
    std::vector<std::shared_ptr<Book>> testBookVector1;
    testBookVector1.push_back(std::make_shared<Book>(testBook1));
    testBookVector1.push_back(std::make_shared<Book>(testReadBook1));
    
    Author testAuthor1("testAuthor", "Dec 01 1990", testBookVector1);
    
    testContainers.addMasterAuthors(std::make_shared<Author>(testAuthor1));
    testContainers.addMasterBooks(std::make_shared<Book>(testBook1));
    testContainers.addMasterReadBooks(std::make_shared<ReadBook>(testReadBook1));
    
    testContainers.saveInMemoryToFile(testFilePath);
    testContainers.clearAll();
    testContainers.loadInMemoryFromFile(testFilePath);
    
    XCTAssert(testContainers.getMasterBooks().size() == 2);
    XCTAssert(testContainers.getMasterReadBooks().size() == 1);
    XCTAssert(testContainers.getMasterAuthors().size() == 1);
    XCTAssert(testContainers.getMasterAuthors().at(0)->getBooksWritten().size() == 2);
    XCTAssert(*testContainers.getMasterBooks().at(0) == testReadBook1);
    XCTAssert(*testContainers.getMasterBooks().at(1) == testBook1);
    XCTAssert(*testContainers.getMasterReadBooks().at(0) == testReadBook1);
    XCTAssert(*testContainers.getMasterAuthors().at(0) == testAuthor1);
    
    std::remove(testFilePath.c_str());
}

- (void)testTrim {
    
    std::string test1 = "test1";
    std::string test2 = "   test2";
    std::string test3 = "test3   ";
    std::string test4 = "   test4   ";
    std::string test5 = " a  test5  b";
    std::string test6 = "\ttest6";
    std::string test7 = "test7 \n";
    std::string test8 = "  \v  test8    ";
    std::string test9 = "\ftest9\f";
    std::string test10 = "\rtest10           a   ";
    
    XCTAssert(trim(test1) == "test1");
    XCTAssert(trim(test2) == "test2");
    XCTAssert(trim(test3) == "test3");
    XCTAssert(trim(test4) == "test4");
    XCTAssert(trim(test5) == "a  test5  b");
    XCTAssert(trim(test6) == "test6");
    XCTAssert(trim(test7) == "test7");
    XCTAssert(trim(test8) == "test8");
    XCTAssert(trim(test9) == "test9");
    XCTAssert(trim(test10) == "test10           a");
    
}

@end
