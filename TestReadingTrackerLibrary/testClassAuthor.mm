//
//  testClassAuthor.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/15/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "Author.hpp"
#include "Book.hpp"

@interface testClassAuthor : XCTestCase

@end

@implementation testClassAuthor

std::vector<std::shared_ptr<rtl::Book>> bookCollection;
std::shared_ptr<rtl::Book> testBook1;
std::shared_ptr<rtl::Book> testBook2;

- (void)setUp {
    testBook1 = std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 11, "fantasy", "1992-Nov-11");
    testBook2 = std::make_shared<rtl::Book>("testA", "testT", "testS", "testP", 22, "western", "1999-Nov-13");
    bookCollection.push_back(testBook1);
    bookCollection.push_back(testBook2);
}

- (void)tearDown {
    bookCollection.clear();
}

- (void)testSetName {
    rtl::Author testAuthor("testAuthor");
    XCTAssert(testAuthor.GetName() == "testAuthor");
    testAuthor.SetName("pickle");
    XCTAssert(testAuthor.GetName() == "pickle");
}

- (void)testSetDateBorn {
    rtl::Author testAuthor("testAuthor");
    time_t testValue = 1573862400;
    testAuthor.SetDateBorn(testValue);
    tm initialTm = *std::gmtime(&testValue);
    tm testTm = testAuthor.GetDateBorn();
    
    XCTAssert(std::mktime(&initialTm) == std::mktime(&testTm));
    XCTAssert(testAuthor.GetDateBornTimeT() == 1573880400);
    XCTAssert(testAuthor.PrintDateBorn() == "2019-Nov-16");
    
    XCTAssert(testAuthor.SetDateBorn("1990-Dec-08"));
    XCTAssert(testAuthor.PrintDateBorn() == "1990-Dec-08");
    
    XCTAssert(testAuthor.SetDateBorn("1890-Dec-01"));
    XCTAssert(testAuthor.PrintDateBorn() == "1890-Dec-01");
    
    XCTAssert(testAuthor.SetDateBorn("1990-Dec-01"));
    XCTAssert(testAuthor.GetDateBornTimeT() == 660027600);
    XCTAssert(testAuthor.PrintDateBorn() == "1990-Dec-01");
    
    XCTAssert(!testAuthor.SetDateBorn("Dec-ab-2000"));
    XCTAssert(!testAuthor.SetDateBorn("invalid string"));
    XCTAssert(!testAuthor.SetDateBorn("AAA 01 3453"));
    
    
}

- (void)testAddBook {    
    rtl::Author newAuthor("testAuthor");
    std::shared_ptr<rtl::Book> testBook = std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 111, rtl::fantasy, "Nov-11-1992");
    
    XCTAssert(newAuthor.GetBooksWritten().empty());
    
    newAuthor.AddBookWritten(testBook);
    
    XCTAssert(newAuthor.GetBooksWritten().size() == 1);
    XCTAssert(newAuthor.GetBooksWritten().at(0) == testBook);
}

- (void)testAddBooks {
    rtl::Author newAuthor("testAuthors");
    
    XCTAssert(newAuthor.GetBooksWritten().empty());
    
    newAuthor.AddBookWritten(bookCollection);
    
    XCTAssert(newAuthor.GetBooksWritten().size() == 2);
    XCTAssert(newAuthor.GetBooksWritten().at(0) == testBook2);
    XCTAssert(newAuthor.GetBooksWritten().at(1) == testBook1);
}

- (void)testAuthorConstructor {
    
    //Author(std::string name, time_t dateBorn = std::time(0), std::vector<std::shared_ptr<Book>> booksWritten = {});
    rtl::Author testAuthor1("testAuthor1", 660027600);
    XCTAssert(testAuthor1.GetName() == "testAuthor1");
    XCTAssert(testAuthor1.GetDateBornTimeT() == 660027600);
    XCTAssert(testAuthor1.GetBooksWritten().size() == 0);
    XCTAssert(testAuthor1.GetAuthorId() == "23f9");
    
    //Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
    rtl::Author testAuthor2("testAuthor2", "1990-Dec-01", bookCollection);
    XCTAssert(testAuthor2.GetName() == "testAuthor2");
    XCTAssert(testAuthor2.PrintDateBorn() == "1990-Dec-01");
    XCTAssert(testAuthor2.GetBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor2.GetBooksWritten().size() == 2);
    XCTAssert(testAuthor2.GetBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor2.GetBooksWritten().at(1) == testBook1);
    XCTAssert(testAuthor2.GetAuthorId() == "2404");
    
    //Author::Author(std::string name, time_t dateBorn, std::shared_ptr<Book> bookWritten)
    rtl::Author testAuthor3("testAuthor3", 660027600, testBook1);
    XCTAssert(testAuthor3.GetName() == "testAuthor3");
    XCTAssert(testAuthor3.GetDateBornTimeT() == 660027600);
    XCTAssert(testAuthor3.GetBooksWritten().size() == 1);
    XCTAssert(testAuthor3.GetBooksWritten().at(0) == testBook1);
    XCTAssert(testAuthor3.GetAuthorId() == "240f");
}

- (void)testEquals {
    rtl::Author testAuthor1("testAuthor1", "1990-Dec-01");
    rtl::Author testAuthor2("testAuthor1", "1990-Dec-01");
    
    XCTAssert(testAuthor1 == testAuthor2);
}

- (void)testNotEquals {
    rtl::Author testAuthor1("testAuthor1", "1990-Dec-01");
    rtl::Author testAuthor2("testAuthor2", "1990-Dec-01");
    
    XCTAssert(testAuthor1 != testAuthor2);
}

- (void)testLessThan {
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "1990-Dec-01");
    
    XCTAssert(testAuthor1 < testAuthor2);
    
    testAuthor1.SetName("chris test");
    
    XCTAssert(testAuthor2 < testAuthor1);
    
    testAuthor2.SetName("Laura Winner");
    
    XCTAssert(testAuthor1 < testAuthor2);
    
    testAuthor1.SetName("a");
    testAuthor2.SetName("a");
    testAuthor1.SetDateBorn("1990-Dec-02");
    
    XCTAssert(testAuthor2 < testAuthor1);
}

- (void)testLessThanEquals {
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "1990-Dec-01");
    
    XCTAssert(testAuthor1 <= testAuthor2);
    
    testAuthor1.SetName("chris test");
    
    XCTAssert(testAuthor2 <= testAuthor1);
    
    testAuthor2.SetName("Laura Winner");
    
    XCTAssert(testAuthor1 <= testAuthor2);
    
    testAuthor1.SetName("a");
    testAuthor2.SetName("a");
    
    XCTAssert(testAuthor2 <= testAuthor1);
    
    testAuthor2.SetDateBorn("1990-Dec-02");
    
    XCTAssert(testAuthor1 <= testAuthor2);
}

- (void)testGreaterThan {
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "1990-Dec-01");
    
    XCTAssert(testAuthor2 > testAuthor1);
    
    testAuthor1.SetName("chris test");
    
    XCTAssert(testAuthor1 > testAuthor2);
    
    testAuthor2.SetName("Laura Winner");
    
    XCTAssert(testAuthor2 > testAuthor1);
    
    testAuthor1.SetName("a");
    testAuthor2.SetName("a");
    testAuthor1.SetDateBorn("1990-Dec-02");
    
    XCTAssert(testAuthor1 > testAuthor2);
}

- (void)testGreaterThanEquals {
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "1990-Dec-01");
    
    XCTAssert(testAuthor2 >= testAuthor1);
    
    testAuthor1.SetName("chris test");
    
    XCTAssert(testAuthor1 >= testAuthor2);
    
    testAuthor2.SetName("Laura Winner");
    
    XCTAssert(testAuthor2 >= testAuthor1);
    
    testAuthor1.SetName("a");
    testAuthor2.SetName("a");
    
    XCTAssert(testAuthor1 >= testAuthor2);
    
    testAuthor2.SetDateBorn("1990-Dec-02");
    
    XCTAssert(testAuthor2 >= testAuthor1);
}


- (void)testAuthorConstructors {
    //Author(std::string name, time_t dateBorn = std::time(&jan2038), std::vector<std::shared_ptr<Book>> booksWritten = {});
    //Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
    
    rtl::Author testAuthor("testName");
    XCTAssert(testAuthor.GetName() == "testName");
    XCTAssert(testAuthor.PrintDateBorn() == "2038-Jan-01");
    XCTAssert(testAuthor.GetBooksWritten().size() == 0);
    
    rtl::Author testAuthor2("testName2", "1990-Dec-01");
    XCTAssert(testAuthor2.GetName() == "testName2");
    XCTAssert(testAuthor2.PrintDateBorn() == "1990-Dec-01");
    XCTAssert(testAuthor2.GetBooksWritten().size() == 0);
    
    rtl::Author testAuthor3("testName3", "1975-Jun-02", bookCollection);
    XCTAssert(testAuthor3.GetName() == "testName3");
    XCTAssert(testAuthor3.PrintDateBorn() == "1975-Jun-02");
    XCTAssert(testAuthor3.GetBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor3.GetBooksWritten().size() == 2);
    XCTAssert(testAuthor3.GetBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor3.GetBooksWritten().at(1) == testBook1);
    
    rtl::Author testAuthor4("testName4", "1984-Aug-27");
    XCTAssert(testAuthor4.GetName() == "testName4");
    XCTAssert(testAuthor4.PrintDateBorn() == "1984-Aug-27");
    XCTAssert(testAuthor4.GetBooksWritten().size() == 0);
    
    rtl::Author testAuthor5("testName5", "2001-Feb-21", bookCollection);
    XCTAssert(testAuthor5.GetName() == "testName5");
    XCTAssert(testAuthor5.PrintDateBorn() == "2001-Feb-21");
    XCTAssert(testAuthor5.GetBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor5.GetBooksWritten().size() == 2);
    XCTAssert(testAuthor5.GetBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor5.GetBooksWritten().at(1) == testBook1);
}

@end
