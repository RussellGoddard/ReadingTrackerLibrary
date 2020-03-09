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
    rtl::InMemoryContainers& testContainer = rtl::InMemoryContainers::getInstance();
    testContainer.clearAll();
}

- (void)testReadBookVector {
    rtl::ReadBook testReadBook1(1);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("1990-Dec-01");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(1);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("b");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("1990-Dec-01");
    testReadBook2.setRating(4);
    testReadBook2.setDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook3(1);
    testReadBook3.setAuthor("a");
    testReadBook3.setTitle("a");
    testReadBook3.setSeries("a");
    testReadBook3.setPublisher("a");
    testReadBook3.setGenre("fantasy");
    testReadBook3.setPageCount(100);
    testReadBook3.setPublishDate("1990-Dec-01");
    testReadBook3.setRating(4);
    testReadBook3.setDateRead("1993-Mar-25");
    
    std::shared_ptr<rtl::ReadBook> testPtrReadBook1 = std::make_shared<rtl::ReadBook>(testReadBook1);
    std::shared_ptr<rtl::ReadBook> testPtrReadBook2 = std::make_shared<rtl::ReadBook>(testReadBook2);
    std::shared_ptr<rtl::ReadBook> testPtrReadBook3 = std::make_shared<rtl::ReadBook>(testReadBook3);
    std::vector<std::shared_ptr<rtl::ReadBook>> testReadBooks;
    testReadBooks.push_back(testPtrReadBook1);
    testReadBooks.push_back(testPtrReadBook2);
    testReadBooks.push_back(testPtrReadBook3);
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::getInstance();
    
    testContainers.addMasterReadBooks(testPtrReadBook1);
    
    XCTAssert(testContainers.getMasterReadBooks().size() == 1);
    XCTAssert(testContainers.getMasterReadBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainers.getMasterBooks().size() == 1);
    XCTAssert(testContainers.getMasterBooks().at(0) == testPtrReadBook1);
    
    testContainers.addMasterReadBooks(testReadBooks);
    
    XCTAssert(testContainers.getMasterReadBooks().size() == 2);
    XCTAssert(testContainers.getMasterReadBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainers.getMasterReadBooks().at(1) == testPtrReadBook2);
    XCTAssert(testContainers.getMasterBooks().size() == 2);
    XCTAssert(testContainers.getMasterBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainers.getMasterBooks().at(1) == testPtrReadBook2);
}

- (void)testBookVector {
    rtl::Book testBook1;
    testBook1.setAuthor("testAuthor");
    testBook1.setTitle("testTitle");
    testBook1.setSeries("testSeries");
    testBook1.setPublisher("testPublisher");
    testBook1.setGenre("fantasy");
    testBook1.setPageCount(10);
    testBook1.setPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.setAuthor("testAuthor2");
    testBook2.setTitle("testTitle2");
    testBook2.setSeries("testSeries2");
    testBook2.setPublisher("testPublisher2");
    testBook2.setGenre("western");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("1991-Dec-01");
    
    rtl::Book testBook3;
    testBook3.setAuthor("testAuthor");
    testBook3.setTitle("testTitle");
    testBook3.setSeries("testSeries");
    testBook3.setPublisher("testPublisher");
    testBook3.setGenre("fantasy");
    testBook3.setPageCount(10);
    testBook3.setPublishDate("1990-Dec-01");
    
    std::shared_ptr<rtl::Book> testPtrBook1 = std::make_shared<rtl::Book>(testBook1);
    std::shared_ptr<rtl::Book> testPtrBook2 = std::make_shared<rtl::Book>(testBook2);
    std::shared_ptr<rtl::Book> testPtrBook3 = std::make_shared<rtl::Book>(testBook3);
    std::vector<std::shared_ptr<rtl::Book>> testBooks;
    testBooks.push_back(testPtrBook1);
    testBooks.push_back(testPtrBook2);
    testBooks.push_back(testPtrBook3);
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::getInstance();
    
    testContainers.addMasterBooks(testPtrBook1);
    
    XCTAssert(testContainers.getMasterBooks().size() == 1);
    XCTAssert(testContainers.getMasterBooks().at(0) == testPtrBook1);
    
    testContainers.addMasterBooks(testBooks);
    
    XCTAssert(testContainers.getMasterBooks().size() == 2);
    XCTAssert(testContainers.getMasterBooks().at(0) == testPtrBook1);
    XCTAssert(testContainers.getMasterBooks().at(1) == testPtrBook2);
}

- (void)testAuthorVector {
    rtl::Author testAuthor1("test author", "1990-Dec-01");
    rtl::Author testAuthor2("test buthor", "1990-Dec-03");
    rtl::Author testAuthor3("test author", "1990-Dec-01");
    
    std::shared_ptr<rtl::Author> testPtrAuthor1 = std::make_shared<rtl::Author>(testAuthor1);
    std::shared_ptr<rtl::Author> testPtrAuthor2 = std::make_shared<rtl::Author>(testAuthor2);
    std::shared_ptr<rtl::Author> testPtrAuthor3 = std::make_shared<rtl::Author>(testAuthor3);
    std::vector<std::shared_ptr<rtl::Author>> testAuthors;
    testAuthors.push_back(testPtrAuthor1);
    testAuthors.push_back(testPtrAuthor2);
    testAuthors.push_back(testPtrAuthor3);
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::getInstance();
    
    testContainers.addMasterAuthors(testPtrAuthor1);
    
    XCTAssert(testContainers.getMasterAuthors().size() == 1);
    XCTAssert(testContainers.getMasterAuthors().at(0) == testPtrAuthor1);
    
    testContainers.addMasterAuthors(testAuthors);
    
    XCTAssert(testContainers.getMasterAuthors().size() == 2);
    XCTAssert(testContainers.getMasterAuthors().at(0) == testPtrAuthor1);
    XCTAssert(testContainers.getMasterAuthors().at(1) == testPtrAuthor2);
}

- (void)testAddMasterAuthorsPassedBook {
    rtl::Book testBook1;
    testBook1.setAuthor("testAuthor1");
    testBook1.setTitle("testTitle1");
    testBook1.setSeries("testSeries1");
    testBook1.setPublisher("testPublisher1");
    testBook1.setGenre("fantasy");
    testBook1.setPageCount(1);
    testBook1.setPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.setAuthor("testAuthor2");
    testBook2.setTitle("testTitle2");
    testBook2.setSeries("testSeries2");
    testBook2.setPublisher("testPublisher2");
    testBook2.setGenre("western");
    testBook2.setPageCount(20);
    testBook2.setPublishDate("1991-Dec-01");
    
    rtl::Book testBook3;
    testBook3.setAuthor("testAuthor1");
    testBook3.setTitle("testTitle1");
    testBook3.setSeries("testSeries1");
    testBook3.setPublisher("testPublisher1");
    testBook3.setGenre("fantasy");
    testBook3.setPageCount(1);
    testBook3.setPublishDate("1990-Dec-01");
    
    std::shared_ptr<rtl::Book> testPtrBook1 = std::make_shared<rtl::Book>(testBook1);
    std::shared_ptr<rtl::Book> testPtrBook2 = std::make_shared<rtl::Book>(testBook2);
    std::shared_ptr<rtl::Book> testPtrBook3 = std::make_shared<rtl::Book>(testBook3);
    std::vector<std::shared_ptr<rtl::Book>> testBooks;
    testBooks.push_back(testPtrBook1);
    testBooks.push_back(testPtrBook2);
    testBooks.push_back(testPtrBook3);
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::getInstance();
    
    testContainers.addMasterAuthors(testPtrBook1);
    
    XCTAssert(testContainers.getMasterAuthors().size() == 1);
    XCTAssert(testContainers.getMasterAuthors().at(0)->getName() == "testAuthor1");
    
    testContainers.addMasterAuthors(testBooks);
    
    XCTAssert(testContainers.getMasterAuthors().size() == 2);
    XCTAssert(testContainers.getMasterAuthors().at(0)->getName() == "testAuthor1");
    XCTAssert(testContainers.getMasterAuthors().at(1)->getName() == "testAuthor2");
}

- (void)testAuthorMergeBooksWhenSameAuthor {
    
    std::vector<std::shared_ptr<rtl::Book>> books1;
    std::vector<std::shared_ptr<rtl::Book>> books2;
    
    books1.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::romance, 1199163600));
    books1.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle3", "testSeries3", "testPublisher3", 3333, rtl::romance, 1199163600));
    books2.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::romance, 1199163600));
    books2.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle2", "testSeries2", "testPublisher2", 2222, rtl::romance, 1199163600));
    
    std::shared_ptr<rtl::Author> testPtrAuthor1 = std::make_shared<rtl::Author>("testAuthor", "1990-Dec-01", books1);
    std::shared_ptr<rtl::Author> testPtrAuthor2 = std::make_shared<rtl::Author>("testAuthor", "1990-Dec-01", books2);
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::getInstance();
    
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
        "publishDate":"1992-Sep-15"
      }
    )"_json;
    
    std::shared_ptr<rtl::Book> testPtrBook1 = rtl::convertJsonToBookPtr(jsonTest);
    
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
        "readerId":123,
        "author":"Robert Jordan",
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
    
    std::shared_ptr<rtl::ReadBook> testPtrReadBook1 = rtl::convertJsonToReadBookPtr(jsonTest);
    
    XCTAssert(testPtrReadBook1->getReaderId() == jsonTest["readerId"].get<int>());
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
          "dateBorn": "2000-Apr-01",
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
    
    std::shared_ptr<rtl::Author> testPtrAuthor1 = rtl::convertJsonToAuthorPtr(jsonTest);
    
    XCTAssert(testPtrAuthor1->getName() == jsonTest["name"].get<std::string>());
    XCTAssert(testPtrAuthor1->printDateBorn() == jsonTest["dateBorn"].get<std::string>());
    XCTAssert(testPtrAuthor1->getBooksWritten().size() == jsonTest.at("booksWritten").size());
}

- (void)testConvertJsonToReadBook {
    nlohmann::json jsonTest = R"(
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
    
    rtl::ReadBook testReadBook1 = rtl::convertJsonToReadBook(jsonTest);
    
    XCTAssert(testReadBook1.getReaderId() == jsonTest["readerId"].get<int>());
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
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::getInstance();
    rtl::Book testBook1;
    testBook1.setAuthor("testAuthor");
    testBook1.setTitle("testTitle");
    testBook1.setSeries("testSeries");
    testBook1.setPublisher("testPublisher");
    testBook1.setGenre("fantasy");
    testBook1.setPageCount(10);
    testBook1.setPublishDate("1990-Dec-01");
    
    rtl::ReadBook testReadBook1(1);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("1990-Dec-01");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("1993-Mar-25");
    
    std::vector<std::shared_ptr<rtl::Book>> testBookVector1;
    testBookVector1.push_back(std::make_shared<rtl::Book>(testBook1));
    testBookVector1.push_back(std::make_shared<rtl::Book>(testReadBook1));
    
    rtl::Author testAuthor1("testAuthor", "1990-Dec-01", testBookVector1);
    
    testContainers.addMasterAuthors(std::make_shared<rtl::Author>(testAuthor1));
    testContainers.addMasterBooks(std::make_shared<rtl::Book>(testBook1));
    testContainers.addMasterReadBooks(std::make_shared<rtl::ReadBook>(testReadBook1));
    
    testContainers.saveInMemoryToFile(testFilePath);
    testContainers.clearAll();
    testContainers.loadInMemoryFromFile(testFilePath);
    
    XCTAssert(testContainers.getMasterBooks().size() == 2);
    XCTAssert(testContainers.getMasterReadBooks().size() == 1);
    XCTAssert(testContainers.getMasterAuthors().size() == 2);
    XCTAssert(testContainers.getMasterAuthors().at(0)->getBooksWritten().size() == 1);
    XCTAssert(testContainers.getMasterAuthors().at(1)->getBooksWritten().size() == 2);
    XCTAssert(*testContainers.getMasterBooks().at(0) == testReadBook1);
    XCTAssert(*testContainers.getMasterBooks().at(1) == testBook1);
    XCTAssert(*testContainers.getMasterReadBooks().at(0) == testReadBook1);
    XCTAssert(testContainers.getMasterAuthors().at(0)->getName() == "a");
    XCTAssert(*testContainers.getMasterAuthors().at(1) == testAuthor1);
    
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
    
    XCTAssert(rtl::trim(test1) == "test1");
    XCTAssert(rtl::trim(test2) == "test2");
    XCTAssert(rtl::trim(test3) == "test3");
    XCTAssert(rtl::trim(test4) == "test4");
    XCTAssert(rtl::trim(test5) == "a  test5  b");
    XCTAssert(rtl::trim(test6) == "test6");
    XCTAssert(rtl::trim(test7) == "test7");
    XCTAssert(rtl::trim(test8) == "test8");
    XCTAssert(rtl::trim(test9) == "test9");
    XCTAssert(rtl::trim(test10) == "test10           a");
    
}

- (void)testClearAll {
    rtl::Book testBook1;
    testBook1.setAuthor("testAuthor");
    testBook1.setTitle("testTitle");
    testBook1.setSeries("testSeries");
    testBook1.setPublisher("testPublisher");
    testBook1.setGenre("fantasy");
    testBook1.setPageCount(10);
    testBook1.setPublishDate("1990-Dec-01");
    
    rtl::ReadBook testReadBook1(1);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("1990-Dec-01");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("1993-Mar-25");
    
    rtl::Author testAuthor1("test author", "1990-Dec-01");
    
    rtl::InMemoryContainers& testContainer = rtl::InMemoryContainers::getInstance();
    
    testContainer.addMasterAuthors(std::make_shared<rtl::Author>(testAuthor1));
    testContainer.addMasterReadBooks(std::make_shared<rtl::ReadBook>(testReadBook1));
    testContainer.addMasterBooks(std::make_shared<rtl::Book>(testBook1));
    
    XCTAssert(testContainer.getMasterAuthors().size() == 3);
    XCTAssert(testContainer.getMasterBooks().size() == 2);
    XCTAssert(testContainer.getMasterReadBooks().size() == 1);
    
    testContainer.clearAll();
    
    XCTAssert(testContainer.getMasterAuthors().size() == 0);
    XCTAssert(testContainer.getMasterBooks().size() == 0);
    XCTAssert(testContainer.getMasterReadBooks().size() == 0);
}

- (void)testQueryBookByIdentifier {
    std::vector<std::pair<std::string, std::string>> test;
    test.push_back(std::make_pair("oclc", ""));
    test.push_back(std::make_pair("title", ""));
    test.push_back(std::make_pair("authors", ""));
    
    XCTAssert(rtl::queryBookByIdentifier("ISBN", "0812511816", test));
    XCTAssert(test.at(0).second == "22671036");
    XCTAssert(test.at(1).second == "The eye of the world");
    XCTAssert(test.at(2).second == "Robert Jordan");
    
    XCTAssert(rtl::queryBookByIdentifier("oclc", "861961500", test));
    XCTAssert(test.at(0).second == "861961500");
    XCTAssert(test.at(1).second == "The Girl with the Dragon Tattoo");
    XCTAssert(test.at(2).second == "Stieg Larsson");
}

- (void)testQueryBookByTitle {
    std::vector<std::pair<std::string, std::string>> test;
    
    rtl::queryBookByTitle("The Eye of the World", test);
    
    XCTAssert(false);
}

@end
