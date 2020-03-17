//
//  testReadingTrackerLibrary.mm
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/7/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "Book.hpp"

@interface testClassBook : XCTestCase

@end

@implementation testClassBook

- (void)setUp {

}

- (void)tearDown {

}

- (void)testBookGetAndSet {
    rtl::Book testBook;
    testBook.SetAuthor("testAuthor");
    testBook.SetTitle("testTitle");
    testBook.SetSeries("testSeries");
    testBook.SetPublisher("testPublisher");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(10);
    testBook.SetPublishDate("1990-12-01");
    XCTAssert(testBook.GetAuthor() == "testAuthor");
    XCTAssert(testBook.GetTitle() == "testTitle");
    XCTAssert(testBook.GetSeries() == "testSeries");
    XCTAssert(testBook.GetPublisher() == "testPublisher");
    XCTAssert(testBook.PrintGenre() == "fantasy");
    XCTAssert(testBook.GetPageCount() == 10);
    XCTAssert(testBook.PrintPublishDate() == "1990-Dec-01");
}

- (void)testSetPublishedDateString {
    rtl::Book testBook;
    XCTAssert(testBook.SetPublishDate("2008 1 01"));
    XCTAssert(testBook.PrintPublishDate() == "2008-Jan-01");
    XCTAssert(testBook.SetPublishDate("2001-Feb-28"));
    XCTAssert(testBook.PrintPublishDate() == "2001-Feb-28");
    XCTAssert(testBook.SetPublishDate("2008-Feb-29"));
    XCTAssert(testBook.PrintPublishDate() == "2008-Feb-29");
    XCTAssert(testBook.SetPublishDate("2017-Mar-13"));
    XCTAssert(testBook.PrintPublishDate() == "2017-Mar-13");
    XCTAssert(testBook.SetPublishDate("1950-April-02"));
    XCTAssert(testBook.PrintPublishDate() == "1950-Apr-02");
    XCTAssert(testBook.SetPublishDate("2010-May-31"));
    XCTAssert(testBook.PrintPublishDate() == "2010-May-31");
    XCTAssert(testBook.SetPublishDate("1910-Jun-22"));
    XCTAssert(testBook.PrintPublishDate() == "1910-Jun-22");
    XCTAssert(testBook.SetPublishDate("2020-07-30"));
    XCTAssert(testBook.PrintPublishDate() == "2020-Jul-30");
    XCTAssert(testBook.SetPublishDate("2000/Aug/13"));
    XCTAssert(testBook.PrintPublishDate() == "2000-Aug-13");
    XCTAssert(testBook.SetPublishDate("2013-9-28"));
    XCTAssert(testBook.PrintPublishDate() == "2013-Sep-28");
    XCTAssert(testBook.SetPublishDate("2002-Oct-31"));
    XCTAssert(testBook.PrintPublishDate() == "2002-Oct-31");
    XCTAssert(testBook.SetPublishDate("1990-Nov-15"));
    XCTAssert(testBook.PrintPublishDate() == "1990-Nov-15");
    XCTAssert(testBook.SetPublishDate("1999-Dec-25"));
    XCTAssert(testBook.PrintPublishDate() == "1999-Dec-25");
    XCTAssert(testBook.SetPublishDate("1890-Dec-01"));
    XCTAssert(testBook.PrintPublishDate() == "1890-Dec-01");
    
    XCTAssert(!testBook.SetPublishDate("Dec-ab-1980"));
    XCTAssert(!testBook.SetPublishDate(""));
    XCTAssert(!testBook.SetPublishDate("too short"));
    XCTAssert(!testBook.SetPublishDate("really long invalid string"));
    XCTAssert(!testBook.SetPublishDate("1990-Not-13"));
    XCTAssert(!testBook.SetPublishDate("AAA-01-asdf"));
    XCTAssert(!testBook.SetPublishDate("2001/Feb/29"));
    XCTAssert(!testBook.SetPublishDate("AAA 01 1980"));
    XCTAssert(!testBook.SetPublishDate("Dec-01-1980"));
}

- (void)testSetPublishDateTimeT {
    rtl::Book testBook;
    time_t testTimeInitial = 1199163600; //Tuesday, January 1, 2008 12:00:00 AM GMT -5
    testBook.SetPublishDate(testTimeInitial);
    XCTAssert(testTimeInitial == testBook.GetPublishDateAsTimeT());
    time_t testTime = 1199165003; //Tuesday, January 1, 2008 12:23:23 AM GMT -5
    testBook.SetPublishDate(testTime);
    XCTAssert(testTimeInitial == testBook.GetPublishDateAsTimeT());
}

- (void)testSetPageCount {
    rtl::Book testBook;
    testBook.SetPageCount(-10);
    XCTAssert(-1 == testBook.GetPageCount());
    testBook.SetPageCount('1');
    XCTAssert(1 == testBook.GetPageCount());
    testBook.SetPageCount('Z');
    XCTAssert(1 == testBook.GetPageCount());
    testBook.SetPageCount("15");
    XCTAssert(15 == testBook.GetPageCount());
    testBook.SetPageCount("a");
    XCTAssert(15 == testBook.GetPageCount());
    testBook.SetPageCount("-100");
    XCTAssert(15 == testBook.GetPageCount());
}

- (void)testGetGenre {
    rtl::Book testBook;
    rtl::Genre newGenre = rtl::western;
    testBook.SetGenre(newGenre);
    XCTAssert(newGenre == testBook.GetGenre());
}

- (void)testPrintJson {
    rtl::Book testBook;
    testBook.SetAuthor("testAuthor");
    testBook.SetTitle("testTitle");
    testBook.SetSeries("testSeries");
    testBook.SetPublisher("testPublisher");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(10);
    testBook.SetPublishDate("1990-Dec-01");
    
    std::string answer = R"({"author":"testAuthor","title":"testTitle","series":"testSeries","publisher":"testPublisher","genre":"fantasy","pageCount":10,"publishDate":"1990-Dec-01"})";
    XCTAssert(answer == testBook.PrintJson());
}

- (void)testPrintGenre {
    rtl::Book testBook;
    testBook.SetGenre("detective");
    XCTAssert(testBook.PrintGenre() == "detective");
    testBook.SetGenre("dystopia");
    XCTAssert(testBook.PrintGenre() == "dystopia");
    testBook.SetGenre("fantasy");
    XCTAssert(testBook.PrintGenre() == "fantasy");
    testBook.SetGenre("mystery");
    XCTAssert(testBook.PrintGenre() == "mystery");
    testBook.SetGenre("romance");
    XCTAssert(testBook.PrintGenre() == "romance");
    testBook.SetGenre("science fiction");
    XCTAssert(testBook.PrintGenre() == "science fiction");
    testBook.SetGenre("thriller");
    XCTAssert(testBook.PrintGenre() == "thriller");
    testBook.SetGenre("western");
    XCTAssert(testBook.PrintGenre() == "western");
    testBook.SetGenre("sci fi");
    XCTAssert(testBook.PrintGenre() == "science fiction");
    testBook.SetGenre("pickle");
    XCTAssert(testBook.PrintGenre() == "genre not set");
}

- (void)testBookEquals {
    rtl::Book testBook;
    testBook.SetAuthor("testAuthor");
    testBook.SetTitle("testTitle");
    testBook.SetSeries("testSeries");
    testBook.SetPublisher("testPublisher");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(10);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.SetAuthor("testAuthor");
    testBook2.SetTitle("testTitle");
    testBook2.SetSeries("testSeries");
    testBook2.SetPublisher("testPublisher");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(10);
    testBook2.SetPublishDate("1990-Dec-01");
    
    XCTAssert(testBook == testBook2);
}

- (void)testBookNotEquals {
    rtl::Book testBook;
    testBook.SetAuthor("testAuthor");
    testBook.SetTitle("testTitle");
    testBook.SetSeries("testSeries");
    testBook.SetPublisher("testPublisher");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(10);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.SetAuthor("testAuthor2");
    testBook2.SetTitle("testTitle2");
    testBook2.SetSeries("testSeries2");
    testBook2.SetPublisher("testPublisher2");
    testBook2.SetGenre("western");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook != testBook2);
}

- (void)testBookLessThan {
    rtl::Book testBook;
    testBook.SetAuthor("a");
    testBook.SetTitle("a");
    testBook.SetSeries("a");
    testBook.SetPublisher("a");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(100);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.SetAuthor("b");
    testBook2.SetTitle("b");
    testBook2.SetSeries("b");
    testBook2.SetPublisher("a");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook < testBook2);

    testBook2.SetAuthor("a");
    XCTAssert(testBook < testBook2);
    
    testBook2.SetSeries("a");
    XCTAssert(testBook < testBook2);
    
    testBook2.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook < testBook2);
    
    testBook2.SetGenre("western");
    testBook2.SetPageCount(110);
    testBook2.SetTitle("a");
    XCTAssert(!(testBook < testBook2));
}

- (void)testBookLessEqualsThan {
    rtl::Book testBook;
    testBook.SetAuthor("a");
    testBook.SetTitle("a");
    testBook.SetSeries("a");
    testBook.SetPublisher("a");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(100);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.SetAuthor("b");
    testBook2.SetTitle("b");
    testBook2.SetSeries("b");
    testBook2.SetPublisher("a");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook <= testBook2);

    testBook2.SetAuthor("a");
    XCTAssert(testBook <= testBook2);
    
    testBook2.SetSeries("a");
    XCTAssert(testBook <= testBook2);
    
    testBook2.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook <= testBook2);
    
    testBook2.SetGenre("western");
    testBook2.SetPageCount(110);
    testBook2.SetTitle("a");
    XCTAssert(testBook <= testBook2);
}

- (void)testBookGreaterThan {
    rtl::Book testBook;
    testBook.SetAuthor("a");
    testBook.SetTitle("a");
    testBook.SetSeries("a");
    testBook.SetPublisher("a");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(100);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.SetAuthor("b");
    testBook2.SetTitle("b");
    testBook2.SetSeries("b");
    testBook2.SetPublisher("a");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook2 > testBook);

    testBook2.SetAuthor("a");
    XCTAssert(testBook2 > testBook);
    
    testBook2.SetSeries("a");
    XCTAssert(testBook2 > testBook);
    
    testBook2.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook2 > testBook);
    
    testBook2.SetGenre("western");
    testBook2.SetPageCount(110);
    testBook2.SetTitle("a");
    XCTAssert(!(testBook2 > testBook));
}

- (void)testBookGreaterEqualsThan {
    rtl::Book testBook;
    testBook.SetAuthor("a");
    testBook.SetTitle("a");
    testBook.SetSeries("a");
    testBook.SetPublisher("a");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(100);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.SetAuthor("b");
    testBook2.SetTitle("b");
    testBook2.SetSeries("b");
    testBook2.SetPublisher("a");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook2 >= testBook);

    testBook2.SetAuthor("a");
    XCTAssert(testBook2 >= testBook);
    
    testBook2.SetSeries("a");
    XCTAssert(testBook2 >= testBook);
    
    testBook2.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook2 >= testBook);
    
    testBook2.SetGenre("western");
    testBook2.SetPageCount(110);
    testBook2.SetTitle("a");
    XCTAssert(testBook2 >= testBook);
}

- (void)testBookConstructor {
    rtl::Book testBook;
    //Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, time_t publishDate = std::time(0));
    rtl::Book testBookConstructor("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::romance, 1199163600);
    XCTAssert("testAuthor" == testBookConstructor.GetAuthor());
    XCTAssert("testTitle" == testBookConstructor.GetTitle());
    XCTAssert("testSeries" == testBookConstructor.GetSeries());
    XCTAssert("testPublisher" == testBookConstructor.GetPublisher());
    XCTAssert(1111 == testBookConstructor.GetPageCount());
    XCTAssert(rtl::romance == testBookConstructor.GetGenre());
    XCTAssert(1199163600 == testBookConstructor.GetPublishDateAsTimeT());
    
    //Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate);
    rtl::Book testBookConstructor2("testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 2222, "thriller", "1991-Nov-16");
    XCTAssert("testAuthor2" == testBookConstructor2.GetAuthor());
    XCTAssert("testTitle2" == testBookConstructor2.GetTitle());
    XCTAssert("testSeries2" == testBookConstructor2.GetSeries());
    XCTAssert("testPublisher2" == testBookConstructor2.GetPublisher());
    XCTAssert(2222 == testBookConstructor2.GetPageCount());
    XCTAssert(rtl::thriller == testBookConstructor2.GetGenre());
    XCTAssert("1991-Nov-16" == testBookConstructor2.PrintPublishDate());
}

- (void)testPrintColumnHeaders {
    std::string testStr = "Author              Title                              Series              Pages";
    
    XCTAssert(rtl::Book::PrintCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLine {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541  ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    Millennium          480  ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 The Wheel of Time12 70212";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15");
    
    XCTAssert(bookMist.PrintCommandLine() == testMist);
    XCTAssert(bookGirl.PrintCommandLine() == testGirl);
    XCTAssert(bookWidth.PrintCommandLine() == testWidth);
}

- (void)testAddandGetOclc {
    rtl::Book testBook;
    std::string testString = "1234";
                              
    testBook.AddOclc(testString);
    
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == testString);
}

- (void)testAddandGetIsbn {
    rtl::Book testBook;
    std::string testString = "1234567890";
    
    testBook.AddIsbn(testString);
    
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == testString);
}

- (void)testGenerateId {
    std::string test1 = "test input";
    std::string test2 = "input test";
    std::string test3 = "Robert Jordan";
    std::string test4 = "robert jordan";
    std::string test5 = "robertjordan";
    std::string test6 = "Robert Jordan The Eye of the World";
    std::string test7 = "Robert Jordan The Path of Daggers";
    
    XCTAssert(rtl::GenerateId(test1) == "27f8e2");
    XCTAssert(rtl::GenerateId(test2) == "281d72");
    XCTAssert(rtl::GenerateId(test3) == "72d2ce");
    XCTAssert(rtl::GenerateId(test4) == "72d2ce");
    XCTAssert(rtl::GenerateId(test5) == "2a9d");
    XCTAssert(rtl::GenerateId(test6) == "b0cf3cbc95a4b81c");
    XCTAssert(rtl::GenerateId(test7) == "7bc75959ace9d2a0");
}

@end
