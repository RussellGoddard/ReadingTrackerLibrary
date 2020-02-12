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

std::vector<std::shared_ptr<Book>> bookCollection;
std::shared_ptr<Book> testBook1;
std::shared_ptr<Book> testBook2;

- (void)setUp {
    testBook1 = std::make_shared<Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 11, fantasy, "Nov 11 1992");
    testBook2 = std::make_shared<Book>("testA", "testT", "testS", "testP", 22, western, "Nov 13 1999");
    bookCollection.push_back(testBook1);
    bookCollection.push_back(testBook2);
}

- (void)tearDown {
    bookCollection.clear();
}

- (void)testSetName {
    Author testAuthor("testAuthor");
    XCTAssert("testAuthor" == testAuthor.getName());
    testAuthor.setName("pickle");
    XCTAssert("pickle" == testAuthor.getName());
}

- (void)testSetDateBorn {
    Author testAuthor("testAuthor");
    time_t testValue = 1573862400;
    testAuthor.setDateBorn(testValue);
    tm initialTm = *std::gmtime(&testValue);
    tm testTm = testAuthor.getDateBorn();
    
    XCTAssert(std::mktime(&initialTm) == std::mktime(&testTm));
    XCTAssert(1573880400 == testAuthor.getDateBornTimeT());
    XCTAssert("Nov 16 2019" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("Dec ab 2000");
    XCTAssert("Nov 16 2019" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("Dec -8 1990");
    XCTAssert("Nov 16 2019" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("Dec 01 1890");
    XCTAssert("Nov 16 2019" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("Dec 01 1990");
    XCTAssert(660045600 == testAuthor.getDateBornTimeT());
    XCTAssert("Dec 01 1990" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("invalid string");
    XCTAssert("Dec 01 1990" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("AAA 01 3453");
    XCTAssert("Dec 01 1990" == testAuthor.printDateBorn());
    
    
}

- (void)testAddBook {    
    Author newAuthor("testAuthor");
    std::shared_ptr<Book> testBook = std::make_shared<Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 111, fantasy, "Nov 11 1992");
    
    XCTAssert(true == newAuthor.getBooksWritten().empty());
    
    newAuthor.addBookWritten(testBook);
    
    XCTAssert(1 == newAuthor.getBooksWritten().size());
    XCTAssert(testBook == newAuthor.getBooksWritten().at(0));
}

- (void)testAddBooks {
    Author newAuthor("testAuthors");
    
    XCTAssert(newAuthor.getBooksWritten().empty());
    
    newAuthor.addBookWritten(bookCollection);
    
    XCTAssert(2 == newAuthor.getBooksWritten().size());
    XCTAssert(testBook1 = newAuthor.getBooksWritten().at(0));
    XCTAssert(testBook2 = newAuthor.getBooksWritten().at(1));
}

- (void)testAuthorConstructor {
    //Author(std::string name, time_t dateBorn = std::time(0), std::vector<std::shared_ptr<Book>> booksWritten = {});
    Author testAuthor1("testAuthor1", 660027600);
    XCTAssert("testAuthor1" == testAuthor1.getName());
    XCTAssert(660027600 == testAuthor1.getDateBornTimeT());
    XCTAssert(0 == testAuthor1.getBooksWritten().size());
    
    //Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
    Author testAuthor2("testAuthor2", "Dec 01 1990", bookCollection);
    XCTAssert("testAuthor2" == testAuthor2.getName());
    XCTAssert("Dec 01 1990" == testAuthor2.printDateBorn());
    XCTAssert(2 == testAuthor2.getBooksWritten().size());
    XCTAssert(testBook1 == testAuthor2.getBooksWritten().at(0));
}

- (void)testEquals {
    Author testAuthor1("testAuthor1", "Dec 01 1990");
    Author testAuthor2("testAuthor1", "Dec 01 1990");
    
    XCTAssert(testAuthor1 == testAuthor2);
}

- (void)testNotEquals {
    Author testAuthor1("testAuthor1", "Dec 01 1990");
    Author testAuthor2("testAuthor2", "Dec 01 1990");
    
    XCTAssert(testAuthor1 != testAuthor2);
}

- (void)testLessThan {
    Author testAuthor1("a", "Dec 01 1990");
    Author testAuthor2("b", "Dec 01 1990");
    
    XCTAssert(testAuthor1 < testAuthor2);
    
    testAuthor1.setName("chris test");
    
    XCTAssert(testAuthor2 < testAuthor1);
    
    testAuthor2.setName("Laura Winner");
    
    XCTAssert(testAuthor1 < testAuthor2);
    
    testAuthor1.setName("a");
    testAuthor2.setName("a");
    testAuthor1.setDateBorn("Dec 02 1990");
    
    XCTAssert(testAuthor2 < testAuthor1);
}

- (void)testLessThanEquals {
    Author testAuthor1("a", "Dec 01 1990");
    Author testAuthor2("b", "Dec 01 1990");
    
    XCTAssert(testAuthor1 <= testAuthor2);
    
    testAuthor1.setName("chris test");
    
    XCTAssert(testAuthor2 <= testAuthor1);
    
    testAuthor2.setName("Laura Winner");
    
    XCTAssert(testAuthor1 <= testAuthor2);
    
    testAuthor1.setName("a");
    testAuthor2.setName("a");
    
    XCTAssert(testAuthor2 <= testAuthor1);
    
    testAuthor2.setDateBorn("Dec 02 1990");
    
    XCTAssert(testAuthor1 <= testAuthor2);
}

- (void)testGreaterThan {
    Author testAuthor1("a", "Dec 01 1990");
    Author testAuthor2("b", "Dec 01 1990");
    
    XCTAssert(testAuthor2 > testAuthor1);
    
    testAuthor1.setName("chris test");
    
    XCTAssert(testAuthor1 > testAuthor2);
    
    testAuthor2.setName("Laura Winner");
    
    XCTAssert(testAuthor2 > testAuthor1);
    
    testAuthor1.setName("a");
    testAuthor2.setName("a");
    testAuthor1.setDateBorn("Dec 02 1990");
    
    XCTAssert(testAuthor1 > testAuthor2);
}

- (void)testGreaterThanEquals {
    Author testAuthor1("a", "Dec 01 1990");
    Author testAuthor2("b", "Dec 01 1990");
    
    XCTAssert(testAuthor2 >= testAuthor1);
    
    testAuthor1.setName("chris test");
    
    XCTAssert(testAuthor1 >= testAuthor2);
    
    testAuthor2.setName("Laura Winner");
    
    XCTAssert(testAuthor2 >= testAuthor1);
    
    testAuthor1.setName("a");
    testAuthor2.setName("a");
    
    XCTAssert(testAuthor1 >= testAuthor2);
    
    testAuthor2.setDateBorn("Dec 02 1990");
    
    XCTAssert(testAuthor2 >= testAuthor1);
}

@end
