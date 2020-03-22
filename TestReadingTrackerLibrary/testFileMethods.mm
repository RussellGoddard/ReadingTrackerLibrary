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
    rtl::ReadBook testReadBook1(1, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(1, "b", "b");
    testReadBook2.SetSeries("b");
    testReadBook2.SetPublisher("b");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("1990-Dec-01");
    testReadBook2.SetRating(4);
    testReadBook2.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook3(1, "a", "a");
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
    rtl::Book testBook1("testAuthor", "testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("testAuthor2", "testTitle2");
    testBook2.SetSeries("testSeries2");
    testBook2.SetPublisher("testPublisher2");
    testBook2.SetGenre("western");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    rtl::Book testBook3("testAuthor", "testTitle");
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
    rtl::Book testBook1("testAuthor1", "testTitle1");
    testBook1.SetSeries("testSeries1");
    testBook1.SetPublisher("testPublisher1");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(1);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("testAuthor2", "testTitle2");
    testBook2.SetSeries("testSeries2");
    testBook2.SetPublisher("testPublisher2");
    testBook2.SetGenre("western");
    testBook2.SetPageCount(20);
    testBook2.SetPublishDate("1991-Dec-01");
    
    rtl::Book testBook3("testAuthor1", "testTitle1");
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
    
    books1.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::Genre::romance, 1199163600));
    books1.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle3", "testSeries3", "testPublisher3", 3333, rtl::Genre::romance, 1199163600));
    books2.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::Genre::romance, 1199163600));
    books2.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle2", "testSeries2", "testPublisher2", 2222, rtl::Genre::romance, 1199163600));
    
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

- (void)testSaveAndLoadInMemoryToFile {
    std::string testFilePath = "./testSaveFile.txt";
    
    rtl::InMemoryContainers& testContainers = rtl::InMemoryContainers::GetInstance();
    rtl::Book testBook1("testAuthor", "testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::ReadBook testReadBook1(1, "a", "a");
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

- (void)testClearAll {
    rtl::Book testBook1("testAuthor", "testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::ReadBook testReadBook1(1, "a", "a");
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
    
    testQuery = rtl::QueryBookByIdentifier("ISBN", "08-1251181-6");
    XCTAssert(testQuery.success);
    XCTAssert(testQuery.oclc == "22671036");
    XCTAssert(testQuery.title == "The eye of the world");
    XCTAssert(testQuery.author == "Robert Jordan");
    
    testQuery = rtl::QueryBookByIdentifier("oclc", "861961500");
    XCTAssert(testQuery.success);
    XCTAssert(testQuery.oclc == "861961500");
    XCTAssert(testQuery.title == "The Girl with the Dragon Tattoo");
    XCTAssert(testQuery.author == "Stieg Larsson");
    
    XCTAssert(rtl::QueryBookByIdentifier(" ", "1234").success == false); //identifier can't be empty
    XCTAssert(rtl::QueryBookByIdentifier("OCLC", "  ").success == false); //identifierNum can't be empty
    XCTAssert(rtl::QueryBookByIdentifier("Babble", "1234").success == false); //identifier must be OCLC or ISBN
    XCTAssert(rtl::QueryBookByIdentifier("ISBN", "asdf").success == false); //identifierNum must not be empty after removing all non digits
    XCTAssert(rtl::QueryBookByIdentifier("ISBN", "123412351231234").success == false); //gibberish isbn
}

- (void)testQueryBookByTitle {
    
    rtl::WikiDataValues newQuery = rtl::QueryBookByTitle("The Eye of the World");
    
    XCTAssert(newQuery.success == true);
    XCTAssert(newQuery.author == "Robert Jordan");
    XCTAssert(newQuery.oclc == "19723327");
    XCTAssert(newQuery.series == "The Wheel of Time");
    XCTAssert(newQuery.title == "The Eye of the World");
    XCTAssert(newQuery.publisher == "Tor Publishing");
    
    newQuery = rtl::QueryBookByTitle("  "); //fails empty string check after trim
    
    XCTAssert(newQuery.success == false);
    
    newQuery = rtl::QueryBookByTitle("gibberishthatwonthaveapage"); //fails to retrieve an object
    
    XCTAssert(newQuery.success == false);
}


@end
