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
    testBook1 = std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 11, "fantasy", "Nov 11 1992");
    testBook2 = std::make_shared<rtl::Book>("testA", "testT", "testS", "testP", 22, "western", "Nov 13 1999");
    bookCollection.push_back(testBook1);
    bookCollection.push_back(testBook2);
}

- (void)tearDown {
    bookCollection.clear();
}

- (void)testSetName {
    rtl::Author testAuthor("testAuthor");
    XCTAssert(testAuthor.getName() == "testAuthor");
    testAuthor.setName("pickle");
    XCTAssert(testAuthor.getName() == "pickle");
}

- (void)testSetDateBorn {
    rtl::Author testAuthor("testAuthor");
    time_t testValue = 1573862400;
    testAuthor.setDateBorn(testValue);
    tm initialTm = *std::gmtime(&testValue);
    tm testTm = testAuthor.getDateBorn();
    
    XCTAssert(std::mktime(&initialTm) == std::mktime(&testTm));
    XCTAssert(testAuthor.getDateBornTimeT() == 1573880400);
    XCTAssert(testAuthor.printDateBorn() == "Nov 16 2019");
    
    testAuthor.setDateBorn("Dec ab 2000");
    XCTAssert(testAuthor.printDateBorn() == "Nov 16 2019");
    
    testAuthor.setDateBorn("Dec -8 1990");
    XCTAssert(testAuthor.printDateBorn() == "Nov 16 2019");
    
    testAuthor.setDateBorn("Dec 01 1890");
    XCTAssert(testAuthor.printDateBorn() == "Nov 16 2019");
    
    testAuthor.setDateBorn("Dec 01 1990");
    XCTAssert(testAuthor.getDateBornTimeT() == 660045600);
    XCTAssert(testAuthor.printDateBorn() == "Dec 01 1990");
    
    testAuthor.setDateBorn("invalid string");
    XCTAssert(testAuthor.printDateBorn() == "Dec 01 1990");
    
    testAuthor.setDateBorn("AAA 01 3453");
    XCTAssert(testAuthor.printDateBorn() == "Dec 01 1990");
    
    
}

- (void)testAddBook {    
    rtl::Author newAuthor("testAuthor");
    std::shared_ptr<rtl::Book> testBook = std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 111, rtl::fantasy, "Nov 11 1992");
    
    XCTAssert(newAuthor.getBooksWritten().empty());
    
    newAuthor.addBookWritten(testBook);
    
    XCTAssert(newAuthor.getBooksWritten().size() == 1);
    XCTAssert(newAuthor.getBooksWritten().at(0) == testBook);
}

- (void)testAddBooks {
    rtl::Author newAuthor("testAuthors");
    
    XCTAssert(newAuthor.getBooksWritten().empty());
    
    newAuthor.addBookWritten(bookCollection);
    
    XCTAssert(newAuthor.getBooksWritten().size() == 2);
    XCTAssert(newAuthor.getBooksWritten().at(0) == testBook2);
    XCTAssert(newAuthor.getBooksWritten().at(1) == testBook1);
}

- (void)testAuthorConstructor {
    
    //Author(std::string name, time_t dateBorn = std::time(0), std::vector<std::shared_ptr<Book>> booksWritten = {});
    rtl::Author testAuthor1("testAuthor1", 660027600);
    XCTAssert(testAuthor1.getName() == "testAuthor1");
    XCTAssert(testAuthor1.getDateBornTimeT() == 660027600);
    XCTAssert(testAuthor1.getBooksWritten().size() == 0);
    
    //Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
    rtl::Author testAuthor2("testAuthor2", "Dec 01 1990", bookCollection);
    XCTAssert(testAuthor2.getName() == "testAuthor2");
    XCTAssert(testAuthor2.printDateBorn() == "Dec 01 1990");
    XCTAssert(testAuthor2.getBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor2.getBooksWritten().size() == 2);
    XCTAssert(testAuthor2.getBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor2.getBooksWritten().at(1) == testBook1);
    
    //Author::Author(std::string name, time_t dateBorn, std::shared_ptr<Book> bookWritten)
    rtl::Author testAuthor3("testAuthor3", 660027600, testBook1);
    XCTAssert(testAuthor3.getName() == "testAuthor3");
    XCTAssert(testAuthor3.getDateBornTimeT() == 660027600);
    XCTAssert(testAuthor3.getBooksWritten().size() == 1);
    XCTAssert(testAuthor3.getBooksWritten().at(0) == testBook1);
}

- (void)testEquals {
    rtl::Author testAuthor1("testAuthor1", "Dec 01 1990");
    rtl::Author testAuthor2("testAuthor1", "Dec 01 1990");
    
    XCTAssert(testAuthor1 == testAuthor2);
}

- (void)testNotEquals {
    rtl::Author testAuthor1("testAuthor1", "Dec 01 1990");
    rtl::Author testAuthor2("testAuthor2", "Dec 01 1990");
    
    XCTAssert(testAuthor1 != testAuthor2);
}

- (void)testLessThan {
    rtl::Author testAuthor1("a", "Dec 01 1990");
    rtl::Author testAuthor2("b", "Dec 01 1990");
    
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
    rtl::Author testAuthor1("a", "Dec 01 1990");
    rtl::Author testAuthor2("b", "Dec 01 1990");
    
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
    rtl::Author testAuthor1("a", "Dec 01 1990");
    rtl::Author testAuthor2("b", "Dec 01 1990");
    
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
    rtl::Author testAuthor1("a", "Dec 01 1990");
    rtl::Author testAuthor2("b", "Dec 01 1990");
    
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

- (void)testAuthorPrintJson {
    std::shared_ptr<rtl::Book> testBook1 = std::make_shared<rtl::Book>("testAuthor1", "testTitle1", "testSeries1", "testPublisher1", 1, rtl::fantasy, "Nov 11 1992");
    std::shared_ptr<rtl::Book> testBook2 = std::make_shared<rtl::Book>("testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 22, rtl::western, "Nov 11 2020");
    rtl::Author testAuthor1("a", "Dec 01 1990");
    rtl::Author testAuthor2("b", "Nov 12 2001");
    rtl::Author testAuthor3("3rd", "Apr 01 2000");
    testAuthor3.addBookWritten(testBook1);
    testAuthor3.addBookWritten(testBook2);
    
    XCTAssert(testAuthor1.printJson() == R"({"name":"a","dateBorn":"Dec 01 1990","booksWritten":[]})");
    XCTAssert(testAuthor2.printJson() == R"({"name":"b","dateBorn":"Nov 12 2001","booksWritten":[]})");
    XCTAssert(testAuthor3.printJson() == R"({"name":"3rd","dateBorn":"Apr 01 2000","booksWritten":[{"author":"testAuthor1","title":"testTitle1","series":"testSeries1","publisher":"testPublisher1","genre":"fantasy","pageCount":1,"publishDate":"Nov 11 1992"},{"author":"testAuthor2","title":"testTitle2","series":"testSeries2","publisher":"testPublisher2","genre":"western","pageCount":22,"publishDate":"Nov 11 2020"}]})");
}

- (void)testAuthorConstructors {
    //Author(std::string name, time_t dateBorn = std::time(&jan2038), std::vector<std::shared_ptr<Book>> booksWritten = {});
    //Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
    
    rtl::Author testAuthor("testName");
    XCTAssert(testAuthor.getName() == "testName");
    XCTAssert(testAuthor.printDateBorn() == "Jan 01 2038");
    XCTAssert(testAuthor.getBooksWritten().size() == 0);
    
    rtl::Author testAuthor2("testName2", "Dec 01 1990");
    XCTAssert(testAuthor2.getName() == "testName2");
    XCTAssert(testAuthor2.printDateBorn() == "Dec 01 1990");
    XCTAssert(testAuthor2.getBooksWritten().size() == 0);
    
    rtl::Author testAuthor3("testName3", "Jun 02 1975", bookCollection);
    XCTAssert(testAuthor3.getName() == "testName3");
    XCTAssert(testAuthor3.printDateBorn() == "Jun 02 1975");
    XCTAssert(testAuthor3.getBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor3.getBooksWritten().size() == 2);
    XCTAssert(testAuthor3.getBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor3.getBooksWritten().at(1) == testBook1);
    
    rtl::Author testAuthor4("testName4", "Aug 27 1984");
    XCTAssert(testAuthor4.getName() == "testName4");
    XCTAssert(testAuthor4.printDateBorn() == "Aug 27 1984");
    XCTAssert(testAuthor4.getBooksWritten().size() == 0);
    
    rtl::Author testAuthor5("testName5", "Feb 21 2001", bookCollection);
    XCTAssert(testAuthor5.getName() == "testName5");
    XCTAssert(testAuthor5.printDateBorn() == "Feb 21 2001");
    XCTAssert(testAuthor5.getBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor5.getBooksWritten().size() == 2);
    XCTAssert(testAuthor5.getBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor5.getBooksWritten().at(1) == testBook1);
}

- (void)testPrintColumnHeaders {
    std::string testStr = "Author              Date Born   Books Written                               Year";
    
    XCTAssert(rtl::Author::printCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLine {
    std::string testMist = "Brandon Sanderson   Dec 19 1975 Mistborn: The Final Empire                  2006\n                                Mistborn: The Well of Ascension             2007\n                                Mistborn: The Hero of Ages                  2008";
    std::string testGirl = "Stieg Larsson       Aug 15 1964 The Girl with the Dragon Tattoo             2005";
    std::string testWidth = "Robert Jordan123456 Oct 17 1948 The Eye of the World12345678901234567890123 1990";
    
    rtl::Book bookMist1("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "Jul 17 2006");
    rtl::Book bookMist2("Brandon Sanderson", "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 541, "fantasy", "Jul 17 2007");
    rtl::Book bookMist3("Brandon Sanderson", "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 541, "fantasy", "Jul 17 2008");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "Aug 01 2005");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World1234567890123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "Jan 15 1990");
    
    std::vector<std::shared_ptr<rtl::Book>> mistbornVector;
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist1));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist2));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist3));
    
    rtl::Author authorMist("Brandon Sanderson", "Dec 19 1975", mistbornVector);
    rtl::Author authorGirl("Stieg Larsson", "Aug 15 1964");
    authorGirl.addBookWritten(std::make_shared<rtl::Book>(bookGirl));
    rtl::Author authorWidth("Robert Jordan1234567");
    authorWidth.setDateBorn("Oct 17 1948");
    authorWidth.addBookWritten(std::make_shared<rtl::Book>(bookWidth));
    
    XCTAssert(authorMist.printCommandLine() == testMist);
    XCTAssert(authorGirl.printCommandLine() == testGirl);
    XCTAssert(authorWidth.printCommandLine() == testWidth);
}

@end
