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
    rtl::InMemoryContainers& testContainer = rtl::InMemoryContainers::GetInstance();
    testContainer.ClearAll();
}

- (void)testReadBookVector {
    rtl::ReadBook testReadBook1(1);
    testReadBook1.SetAuthor("a");
    testReadBook1.SetTitle("a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(1);
    testReadBook2.SetAuthor("b");
    testReadBook2.SetTitle("b");
    testReadBook2.SetSeries("b");
    testReadBook2.SetPublisher("b");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("1990-Dec-01");
    testReadBook2.SetRating(4);
    testReadBook2.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook3(1);
    testReadBook3.SetAuthor("a");
    testReadBook3.SetTitle("a");
    testReadBook3.SetSeries("a");
    testReadBook3.SetPublisher("a");
    testReadBook3.SetGenre("fantasy");
    testReadBook3.SetPageCount(100);
    testReadBook3.SetPublishDate("1990-Dec-01");
    testReadBook3.SetRating(4);
    testReadBook3.SetDateRead("1993-Mar-25");
    
    std::shared_ptr<rtl::ReadBook> testPtrReadBook1 = std::make_shared<rtl::ReadBook>(testReadBook1);
    std::shared_ptr<rtl::ReadBook> testPtrReadBook2 = std::make_shared<rtl::ReadBook>(testReadBook2);
    std::shared_ptr<rtl::ReadBook> testPtrReadBook3 = std::make_shared<rtl::ReadBook>(testReadBook3);
    std::vector<std::shared_ptr<rtl::ReadBook>> testReadBooks;
    testReadBooks.push_back(testPtrReadBook1);
    testReadBooks.push_back(testPtrReadBook2);
    testReadBooks.push_back(testPtrReadBook3);
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::GetInstance();
    
    testContainers.AddMasterReadBooks(testPtrReadBook1);
    
    XCTAssert(testContainers.GetMasterReadBooks().size() == 1);
    XCTAssert(testContainers.GetMasterReadBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainers.GetMasterBooks().size() == 1);
    XCTAssert(testContainers.GetMasterBooks().at(0) == testPtrReadBook1);
    
    testContainers.AddMasterReadBooks(testReadBooks);
    
    XCTAssert(testContainers.GetMasterReadBooks().size() == 2);
    XCTAssert(testContainers.GetMasterReadBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainers.GetMasterReadBooks().at(1) == testPtrReadBook2);
    XCTAssert(testContainers.GetMasterBooks().size() == 2);
    XCTAssert(testContainers.GetMasterBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainers.GetMasterBooks().at(1) == testPtrReadBook2);
}

- (void)testBookVector {
    rtl::Book testBook1;
    testBook1.SetAuthor("testAuthor");
    testBook1.SetTitle("testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.SetAuthor("testAuthor2");
    testBook2.SetTitle("testTitle2");
    testBook2.SetSeries("testSeries2");
    testBook2.SetPublisher("testPublisher2");
    testBook2.SetGenre("western");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    rtl::Book testBook3;
    testBook3.SetAuthor("testAuthor");
    testBook3.SetTitle("testTitle");
    testBook3.SetSeries("testSeries");
    testBook3.SetPublisher("testPublisher");
    testBook3.SetGenre("fantasy");
    testBook3.SetPageCount(10);
    testBook3.SetPublishDate("1990-Dec-01");
    
    std::shared_ptr<rtl::Book> testPtrBook1 = std::make_shared<rtl::Book>(testBook1);
    std::shared_ptr<rtl::Book> testPtrBook2 = std::make_shared<rtl::Book>(testBook2);
    std::shared_ptr<rtl::Book> testPtrBook3 = std::make_shared<rtl::Book>(testBook3);
    std::vector<std::shared_ptr<rtl::Book>> testBooks;
    testBooks.push_back(testPtrBook1);
    testBooks.push_back(testPtrBook2);
    testBooks.push_back(testPtrBook3);
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::GetInstance();
    
    testContainers.AddMasterBooks(testPtrBook1);
    
    XCTAssert(testContainers.GetMasterBooks().size() == 1);
    XCTAssert(testContainers.GetMasterBooks().at(0) == testPtrBook1);
    
    testContainers.AddMasterBooks(testBooks);
    
    XCTAssert(testContainers.GetMasterBooks().size() == 2);
    XCTAssert(testContainers.GetMasterBooks().at(0) == testPtrBook1);
    XCTAssert(testContainers.GetMasterBooks().at(1) == testPtrBook2);
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
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::GetInstance();
    
    testContainers.AddMasterAuthors(testPtrAuthor1);
    
    XCTAssert(testContainers.GetMasterAuthors().size() == 1);
    XCTAssert(testContainers.GetMasterAuthors().at(0) == testPtrAuthor1);
    
    testContainers.AddMasterAuthors(testAuthors);
    
    XCTAssert(testContainers.GetMasterAuthors().size() == 2);
    XCTAssert(testContainers.GetMasterAuthors().at(0) == testPtrAuthor1);
    XCTAssert(testContainers.GetMasterAuthors().at(1) == testPtrAuthor2);
}

- (void)testAddMasterAuthorsPassedBook {
    rtl::Book testBook1;
    testBook1.SetAuthor("testAuthor1");
    testBook1.SetTitle("testTitle1");
    testBook1.SetSeries("testSeries1");
    testBook1.SetPublisher("testPublisher1");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(1);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.SetAuthor("testAuthor2");
    testBook2.SetTitle("testTitle2");
    testBook2.SetSeries("testSeries2");
    testBook2.SetPublisher("testPublisher2");
    testBook2.SetGenre("western");
    testBook2.SetPageCount(20);
    testBook2.SetPublishDate("1991-Dec-01");
    
    rtl::Book testBook3;
    testBook3.SetAuthor("testAuthor1");
    testBook3.SetTitle("testTitle1");
    testBook3.SetSeries("testSeries1");
    testBook3.SetPublisher("testPublisher1");
    testBook3.SetGenre("fantasy");
    testBook3.SetPageCount(1);
    testBook3.SetPublishDate("1990-Dec-01");
    
    std::shared_ptr<rtl::Book> testPtrBook1 = std::make_shared<rtl::Book>(testBook1);
    std::shared_ptr<rtl::Book> testPtrBook2 = std::make_shared<rtl::Book>(testBook2);
    std::shared_ptr<rtl::Book> testPtrBook3 = std::make_shared<rtl::Book>(testBook3);
    std::vector<std::shared_ptr<rtl::Book>> testBooks;
    testBooks.push_back(testPtrBook1);
    testBooks.push_back(testPtrBook2);
    testBooks.push_back(testPtrBook3);
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::GetInstance();
    
    testContainers.AddMasterAuthors(testPtrBook1);
    
    XCTAssert(testContainers.GetMasterAuthors().size() == 1);
    XCTAssert(testContainers.GetMasterAuthors().at(0)->GetName() == "testAuthor1");
    
    testContainers.AddMasterAuthors(testBooks);
    
    XCTAssert(testContainers.GetMasterAuthors().size() == 2);
    XCTAssert(testContainers.GetMasterAuthors().at(0)->GetName() == "testAuthor1");
    XCTAssert(testContainers.GetMasterAuthors().at(1)->GetName() == "testAuthor2");
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
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::GetInstance();
    
    testContainers.AddMasterAuthors(testPtrAuthor1);
    testContainers.AddMasterAuthors(testPtrAuthor2);
    
    XCTAssert(testContainers.GetMasterAuthors().size() == 1);
    XCTAssert(testContainers.GetMasterAuthors().at(0)->GetBooksWritten().size() == 3);
    XCTAssert(testContainers.GetMasterAuthors().at(0)->GetBooksWritten().at(0) == books1.at(0));
    XCTAssert(testContainers.GetMasterAuthors().at(0)->GetBooksWritten().at(1) == books2.at(1));
    XCTAssert(testContainers.GetMasterAuthors().at(0)->GetBooksWritten().at(2) == books1.at(1));

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
    
    std::shared_ptr<rtl::Book> testPtrBook1 = rtl::ConvertJsonToBookPtr(jsonTest);
    
    XCTAssert(testPtrBook1->GetAuthor() == jsonTest["author"].get<std::string>());
    XCTAssert(testPtrBook1->PrintGenre() == jsonTest["genre"].get<std::string>());
    XCTAssert(testPtrBook1->GetPageCount() == jsonTest["pageCount"].get<int>());
    XCTAssert(testPtrBook1->GetPublisher() == jsonTest["publisher"].get<std::string>());
    XCTAssert(testPtrBook1->GetSeries() == jsonTest["series"].get<std::string>());
    XCTAssert(testPtrBook1->GetTitle() == jsonTest["title"].get<std::string>());
    XCTAssert(testPtrBook1->PrintPublishDate() == jsonTest["publishDate"].get<std::string>());
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
    
    std::shared_ptr<rtl::ReadBook> testPtrReadBook1 = rtl::ConvertJsonToReadBookPtr(jsonTest);
    
    XCTAssert(testPtrReadBook1->GetReaderId() == jsonTest["readerId"].get<int>());
    XCTAssert(testPtrReadBook1->GetAuthor() == jsonTest["author"].get<std::string>());
    XCTAssert(testPtrReadBook1->PrintGenre() == jsonTest["genre"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetPageCount() == jsonTest["pageCount"].get<int>());
    XCTAssert(testPtrReadBook1->GetPublisher() == jsonTest["publisher"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetSeries() == jsonTest["series"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetTitle() == jsonTest["title"].get<std::string>());
    XCTAssert(testPtrReadBook1->PrintPublishDate() == jsonTest["publishDate"].get<std::string>());
    XCTAssert(testPtrReadBook1->GetRating() == jsonTest["rating"].get<int>());
    XCTAssert(testPtrReadBook1->PrintDateRead() == jsonTest["dateRead"].get<std::string>());
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
    
    std::shared_ptr<rtl::Author> testPtrAuthor1 = rtl::ConvertJsonToAuthorPtr(jsonTest);
    
    XCTAssert(testPtrAuthor1->GetName() == jsonTest["name"].get<std::string>());
    XCTAssert(testPtrAuthor1->PrintDateBorn() == jsonTest["dateBorn"].get<std::string>());
    XCTAssert(testPtrAuthor1->GetBooksWritten().size() == jsonTest.at("booksWritten").size());
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
    
    rtl::ReadBook testReadBook1 = rtl::ConvertJsonToReadBook(jsonTest);
    
    XCTAssert(testReadBook1.GetReaderId() == jsonTest["readerId"].get<int>());
    XCTAssert(testReadBook1.GetAuthor() == jsonTest["author"].get<std::string>());
    XCTAssert(testReadBook1.PrintDateRead() == jsonTest["dateRead"].get<std::string>());
    XCTAssert(testReadBook1.PrintGenre() == jsonTest["genre"].get<std::string>());
    XCTAssert(testReadBook1.GetPageCount() == jsonTest["pageCount"].get<int>());
    XCTAssert(testReadBook1.GetPublisher() == jsonTest["publisher"].get<std::string>());
    XCTAssert(testReadBook1.GetRating() == jsonTest["rating"].get<int>());
    XCTAssert(testReadBook1.GetSeries() == jsonTest["series"].get<std::string>());
    XCTAssert(testReadBook1.GetTitle() == jsonTest["title"].get<std::string>());
    XCTAssert(testReadBook1.PrintPublishDate() == jsonTest["publishDate"].get<std::string>());
}

- (void)testSaveAndLoadInMemoryToFile {
    std::string testFilePath = "./testSaveFile.txt";
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::GetInstance();
    rtl::Book testBook1;
    testBook1.SetAuthor("testAuthor");
    testBook1.SetTitle("testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::ReadBook testReadBook1(1);
    testReadBook1.SetAuthor("a");
    testReadBook1.SetTitle("a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    std::vector<std::shared_ptr<rtl::Book>> testBookVector1;
    testBookVector1.push_back(std::make_shared<rtl::Book>(testBook1));
    testBookVector1.push_back(std::make_shared<rtl::Book>(testReadBook1));
    
    rtl::Author testAuthor1("testAuthor", "1990-Dec-01", testBookVector1);
    
    testContainers.AddMasterAuthors(std::make_shared<rtl::Author>(testAuthor1));
    testContainers.AddMasterBooks(std::make_shared<rtl::Book>(testBook1));
    testContainers.AddMasterReadBooks(std::make_shared<rtl::ReadBook>(testReadBook1));
    
    testContainers.SaveInMemoryToFile(testFilePath);
    testContainers.ClearAll();
    testContainers.LoadInMemoryFromFile(testFilePath);
    
    XCTAssert(testContainers.GetMasterBooks().size() == 2);
    XCTAssert(testContainers.GetMasterReadBooks().size() == 1);
    XCTAssert(testContainers.GetMasterAuthors().size() == 2);
    XCTAssert(testContainers.GetMasterAuthors().at(0)->GetBooksWritten().size() == 1);
    XCTAssert(testContainers.GetMasterAuthors().at(1)->GetBooksWritten().size() == 2);
    XCTAssert(*testContainers.GetMasterBooks().at(0) == testReadBook1);
    XCTAssert(*testContainers.GetMasterBooks().at(1) == testBook1);
    XCTAssert(*testContainers.GetMasterReadBooks().at(0) == testReadBook1);
    XCTAssert(testContainers.GetMasterAuthors().at(0)->GetName() == "a");
    XCTAssert(*testContainers.GetMasterAuthors().at(1) == testAuthor1);
    
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
    
    XCTAssert(rtl::Trim(test1) == "test1");
    XCTAssert(rtl::Trim(test2) == "test2");
    XCTAssert(rtl::Trim(test3) == "test3");
    XCTAssert(rtl::Trim(test4) == "test4");
    XCTAssert(rtl::Trim(test5) == "a  test5  b");
    XCTAssert(rtl::Trim(test6) == "test6");
    XCTAssert(rtl::Trim(test7) == "test7");
    XCTAssert(rtl::Trim(test8) == "test8");
    XCTAssert(rtl::Trim(test9) == "test9");
    XCTAssert(rtl::Trim(test10) == "test10           a");
    
}

- (void)testClearAll {
    rtl::Book testBook1;
    testBook1.SetAuthor("testAuthor");
    testBook1.SetTitle("testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::ReadBook testReadBook1(1);
    testReadBook1.SetAuthor("a");
    testReadBook1.SetTitle("a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::Author testAuthor1("test author", "1990-Dec-01");
    
    rtl::InMemoryContainers& testContainer = rtl::InMemoryContainers::GetInstance();
    
    testContainer.AddMasterAuthors(std::make_shared<rtl::Author>(testAuthor1));
    testContainer.AddMasterReadBooks(std::make_shared<rtl::ReadBook>(testReadBook1));
    testContainer.AddMasterBooks(std::make_shared<rtl::Book>(testBook1));
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 3);
    XCTAssert(testContainer.GetMasterBooks().size() == 2);
    XCTAssert(testContainer.GetMasterReadBooks().size() == 1);
    
    testContainer.ClearAll();
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 0);
    XCTAssert(testContainer.GetMasterBooks().size() == 0);
    XCTAssert(testContainer.GetMasterReadBooks().size() == 0);
}

- (void)testQueryBookByIdentifier {
    rtl::OpenLibraryValues testQuery;
    
    testQuery = rtl::QueryBookByIdentifier("ISBN", "0812511816");
    XCTAssert(testQuery.success);
    XCTAssert(testQuery.oclc == "22671036");
    XCTAssert(testQuery.title == "The eye of the world");
    XCTAssert(testQuery.author == "Robert Jordan");
    
    testQuery = rtl::QueryBookByIdentifier("oclc", "861961500");
    XCTAssert(testQuery.success);
    XCTAssert(testQuery.oclc == "861961500");
    XCTAssert(testQuery.title == "The Girl with the Dragon Tattoo");
    XCTAssert(testQuery.author == "Stieg Larsson");
}

- (void)testQueryBookByTitle {
    
    rtl::WikiDataValues newQuery = rtl::QueryBookByTitle("The Eye of the World");
    
    XCTAssert(newQuery.success == true);
    XCTAssert(newQuery.author == "Robert Jordan");
    XCTAssert(newQuery.oclc == "19723327");
    XCTAssert(newQuery.series == "The Wheel of Time");
    XCTAssert(newQuery.title == "The Eye of the World");
    XCTAssert(newQuery.publisher == "Tor Publishing");
}

@end
