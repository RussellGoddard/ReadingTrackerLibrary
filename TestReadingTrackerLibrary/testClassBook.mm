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
    testBook.setAuthor("testAuthor");
    testBook.setTitle("testTitle");
    testBook.setSeries("testSeries");
    testBook.setPublisher("testPublisher");
    testBook.setGenre("fantasy");
    testBook.setPageCount(10);
    testBook.setPublishDate("1990-12-01");
    XCTAssert(testBook.getAuthor() == "testAuthor");
    XCTAssert(testBook.getTitle() == "testTitle");
    XCTAssert(testBook.getSeries() == "testSeries");
    XCTAssert(testBook.getPublisher() == "testPublisher");
    XCTAssert(testBook.printGenre() == "fantasy");
    XCTAssert(testBook.getPageCount() == 10);
    XCTAssert(testBook.printPublishDate() == "1990-Dec-01");
}

- (void)testSetPublishedDateString {
    rtl::Book testBook;
    XCTAssert(testBook.setPublishDate("2008 1 01"));
    XCTAssert(testBook.printPublishDate() == "2008-Jan-01");
    XCTAssert(testBook.setPublishDate("2001-Feb-28"));
    XCTAssert(testBook.printPublishDate() == "2001-Feb-28");
    XCTAssert(testBook.setPublishDate("2008-Feb-29"));
    XCTAssert(testBook.printPublishDate() == "2008-Feb-29");
    XCTAssert(testBook.setPublishDate("2017-Mar-13"));
    XCTAssert(testBook.printPublishDate() == "2017-Mar-13");
    XCTAssert(testBook.setPublishDate("1950-April-02"));
    XCTAssert(testBook.printPublishDate() == "1950-Apr-02");
    XCTAssert(testBook.setPublishDate("2010-May-31"));
    XCTAssert(testBook.printPublishDate() == "2010-May-31");
    XCTAssert(testBook.setPublishDate("1910-Jun-22"));
    XCTAssert(testBook.printPublishDate() == "1910-Jun-22");
    XCTAssert(testBook.setPublishDate("2020-07-30"));
    XCTAssert(testBook.printPublishDate() == "2020-Jul-30");
    XCTAssert(testBook.setPublishDate("2000/Aug/13"));
    XCTAssert(testBook.printPublishDate() == "2000-Aug-13");
    XCTAssert(testBook.setPublishDate("2013-9-28"));
    XCTAssert(testBook.printPublishDate() == "2013-Sep-28");
    XCTAssert(testBook.setPublishDate("2002-Oct-31"));
    XCTAssert(testBook.printPublishDate() == "2002-Oct-31");
    XCTAssert(testBook.setPublishDate("1990-Nov-15"));
    XCTAssert(testBook.printPublishDate() == "1990-Nov-15");
    XCTAssert(testBook.setPublishDate("1999-Dec-25"));
    XCTAssert(testBook.printPublishDate() == "1999-Dec-25");
    XCTAssert(testBook.setPublishDate("1890-Dec-01"));
    XCTAssert(testBook.printPublishDate() == "1890-Dec-01");
    
    XCTAssert(!testBook.setPublishDate("Dec-ab-1980"));
    XCTAssert(!testBook.setPublishDate(""));
    XCTAssert(!testBook.setPublishDate("too short"));
    XCTAssert(!testBook.setPublishDate("really long invalid string"));
    XCTAssert(!testBook.setPublishDate("1990-Not-13"));
    XCTAssert(!testBook.setPublishDate("AAA-01-asdf"));
    XCTAssert(!testBook.setPublishDate("2001/Feb/29"));
    XCTAssert(!testBook.setPublishDate("AAA 01 1980"));
    XCTAssert(!testBook.setPublishDate("Dec-01-1980"));
}

- (void)testSetPublishDateTimeT {
    rtl::Book testBook;
    time_t testTimeInitial = 1199163600; //Tuesday, January 1, 2008 12:00:00 AM GMT -5
    testBook.setPublishDate(testTimeInitial);
    XCTAssert(testTimeInitial == testBook.getPublishDateAsTimeT());
    time_t testTime = 1199165003; //Tuesday, January 1, 2008 12:23:23 AM GMT -5
    testBook.setPublishDate(testTime);
    XCTAssert(testTimeInitial == testBook.getPublishDateAsTimeT());
}

- (void)testSetPageCount {
    rtl::Book testBook;
    testBook.setPageCount(-10);
    XCTAssert(-1 == testBook.getPageCount());
    testBook.setPageCount('1');
    XCTAssert(1 == testBook.getPageCount());
    testBook.setPageCount('Z');
    XCTAssert(1 == testBook.getPageCount());
    testBook.setPageCount("15");
    XCTAssert(15 == testBook.getPageCount());
    testBook.setPageCount("a");
    XCTAssert(15 == testBook.getPageCount());
    testBook.setPageCount("-100");
    XCTAssert(15 == testBook.getPageCount());
}

- (void)testGetGenre {
    rtl::Book testBook;
    rtl::Genre newGenre = rtl::western;
    testBook.setGenre(newGenre);
    XCTAssert(newGenre == testBook.getGenre());
}

- (void)testPrintJson {
    rtl::Book testBook;
    testBook.setAuthor("testAuthor");
    testBook.setTitle("testTitle");
    testBook.setSeries("testSeries");
    testBook.setPublisher("testPublisher");
    testBook.setGenre("fantasy");
    testBook.setPageCount(10);
    testBook.setPublishDate("1990-Dec-01");
    
    std::string answer = R"({"author":"testAuthor","title":"testTitle","series":"testSeries","publisher":"testPublisher","genre":"fantasy","pageCount":10,"publishDate":"1990-Dec-01"})";
    XCTAssert(answer == testBook.printJson());
}

- (void)testPrintGenre {
    rtl::Book testBook;
    testBook.setGenre("detective");
    XCTAssert(testBook.printGenre() == "detective");
    testBook.setGenre("dystopia");
    XCTAssert(testBook.printGenre() == "dystopia");
    testBook.setGenre("fantasy");
    XCTAssert(testBook.printGenre() == "fantasy");
    testBook.setGenre("mystery");
    XCTAssert(testBook.printGenre() == "mystery");
    testBook.setGenre("romance");
    XCTAssert(testBook.printGenre() == "romance");
    testBook.setGenre("science fiction");
    XCTAssert(testBook.printGenre() == "science fiction");
    testBook.setGenre("thriller");
    XCTAssert(testBook.printGenre() == "thriller");
    testBook.setGenre("western");
    XCTAssert(testBook.printGenre() == "western");
    testBook.setGenre("sci fi");
    XCTAssert(testBook.printGenre() == "science fiction");
    testBook.setGenre("pickle");
    XCTAssert(testBook.printGenre() == "genre not set");
}

- (void)testBookEquals {
    rtl::Book testBook;
    testBook.setAuthor("testAuthor");
    testBook.setTitle("testTitle");
    testBook.setSeries("testSeries");
    testBook.setPublisher("testPublisher");
    testBook.setGenre("fantasy");
    testBook.setPageCount(10);
    testBook.setPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.setAuthor("testAuthor");
    testBook2.setTitle("testTitle");
    testBook2.setSeries("testSeries");
    testBook2.setPublisher("testPublisher");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(10);
    testBook2.setPublishDate("1990-Dec-01");
    
    XCTAssert(testBook == testBook2);
}

- (void)testBookNotEquals {
    rtl::Book testBook;
    testBook.setAuthor("testAuthor");
    testBook.setTitle("testTitle");
    testBook.setSeries("testSeries");
    testBook.setPublisher("testPublisher");
    testBook.setGenre("fantasy");
    testBook.setPageCount(10);
    testBook.setPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.setAuthor("testAuthor2");
    testBook2.setTitle("testTitle2");
    testBook2.setSeries("testSeries2");
    testBook2.setPublisher("testPublisher2");
    testBook2.setGenre("western");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("1991-Dec-01");
    
    XCTAssert(testBook != testBook2);
}

- (void)testBookLessThan {
    rtl::Book testBook;
    testBook.setAuthor("a");
    testBook.setTitle("a");
    testBook.setSeries("a");
    testBook.setPublisher("a");
    testBook.setGenre("fantasy");
    testBook.setPageCount(100);
    testBook.setPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.setAuthor("b");
    testBook2.setTitle("b");
    testBook2.setSeries("b");
    testBook2.setPublisher("a");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("1991-Dec-01");
    
    XCTAssert(testBook < testBook2);

    testBook2.setAuthor("a");
    XCTAssert(testBook < testBook2);
    
    testBook2.setSeries("a");
    XCTAssert(testBook < testBook2);
    
    testBook2.setPublishDate("1990-Dec-01");
    XCTAssert(testBook < testBook2);
    
    testBook2.setGenre("western");
    testBook2.setPageCount(110);
    testBook2.setTitle("a");
    XCTAssert(!(testBook < testBook2));
}

- (void)testBookLessEqualsThan {
    rtl::Book testBook;
    testBook.setAuthor("a");
    testBook.setTitle("a");
    testBook.setSeries("a");
    testBook.setPublisher("a");
    testBook.setGenre("fantasy");
    testBook.setPageCount(100);
    testBook.setPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.setAuthor("b");
    testBook2.setTitle("b");
    testBook2.setSeries("b");
    testBook2.setPublisher("a");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("1991-Dec-01");
    
    XCTAssert(testBook <= testBook2);

    testBook2.setAuthor("a");
    XCTAssert(testBook <= testBook2);
    
    testBook2.setSeries("a");
    XCTAssert(testBook <= testBook2);
    
    testBook2.setPublishDate("1990-Dec-01");
    XCTAssert(testBook <= testBook2);
    
    testBook2.setGenre("western");
    testBook2.setPageCount(110);
    testBook2.setTitle("a");
    XCTAssert(testBook <= testBook2);
}

- (void)testBookGreaterThan {
    rtl::Book testBook;
    testBook.setAuthor("a");
    testBook.setTitle("a");
    testBook.setSeries("a");
    testBook.setPublisher("a");
    testBook.setGenre("fantasy");
    testBook.setPageCount(100);
    testBook.setPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.setAuthor("b");
    testBook2.setTitle("b");
    testBook2.setSeries("b");
    testBook2.setPublisher("a");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("1991-Dec-01");
    
    XCTAssert(testBook2 > testBook);

    testBook2.setAuthor("a");
    XCTAssert(testBook2 > testBook);
    
    testBook2.setSeries("a");
    XCTAssert(testBook2 > testBook);
    
    testBook2.setPublishDate("1990-Dec-01");
    XCTAssert(testBook2 > testBook);
    
    testBook2.setGenre("western");
    testBook2.setPageCount(110);
    testBook2.setTitle("a");
    XCTAssert(!(testBook2 > testBook));
}

- (void)testBookGreaterEqualsThan {
    rtl::Book testBook;
    testBook.setAuthor("a");
    testBook.setTitle("a");
    testBook.setSeries("a");
    testBook.setPublisher("a");
    testBook.setGenre("fantasy");
    testBook.setPageCount(100);
    testBook.setPublishDate("1990-Dec-01");
    
    rtl::Book testBook2;
    testBook2.setAuthor("b");
    testBook2.setTitle("b");
    testBook2.setSeries("b");
    testBook2.setPublisher("a");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("1991-Dec-01");
    
    XCTAssert(testBook2 >= testBook);

    testBook2.setAuthor("a");
    XCTAssert(testBook2 >= testBook);
    
    testBook2.setSeries("a");
    XCTAssert(testBook2 >= testBook);
    
    testBook2.setPublishDate("1990-Dec-01");
    XCTAssert(testBook2 >= testBook);
    
    testBook2.setGenre("western");
    testBook2.setPageCount(110);
    testBook2.setTitle("a");
    XCTAssert(testBook2 >= testBook);
}

- (void)testBookConstructor {
    rtl::Book testBook;
    //Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, time_t publishDate = std::time(0));
    rtl::Book testBookConstructor("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::romance, 1199163600);
    XCTAssert("testAuthor" == testBookConstructor.getAuthor());
    XCTAssert("testTitle" == testBookConstructor.getTitle());
    XCTAssert("testSeries" == testBookConstructor.getSeries());
    XCTAssert("testPublisher" == testBookConstructor.getPublisher());
    XCTAssert(1111 == testBookConstructor.getPageCount());
    XCTAssert(rtl::romance == testBookConstructor.getGenre());
    XCTAssert(1199163600 == testBookConstructor.getPublishDateAsTimeT());
    
    //Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate);
    rtl::Book testBookConstructor2("testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 2222, "thriller", "1991-Nov-16");
    XCTAssert("testAuthor2" == testBookConstructor2.getAuthor());
    XCTAssert("testTitle2" == testBookConstructor2.getTitle());
    XCTAssert("testSeries2" == testBookConstructor2.getSeries());
    XCTAssert("testPublisher2" == testBookConstructor2.getPublisher());
    XCTAssert(2222 == testBookConstructor2.getPageCount());
    XCTAssert(rtl::thriller == testBookConstructor2.getGenre());
    XCTAssert("1991-Nov-16" == testBookConstructor2.printPublishDate());
}

- (void)testPrintColumnHeaders {
    std::string testStr = "Author              Title                              Series              Pages";
    
    XCTAssert(rtl::Book::printCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLine {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541  ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    Millennium          480  ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 The Wheel of Time12 70212";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15");
    
    XCTAssert(bookMist.printCommandLine() == testMist);
    XCTAssert(bookGirl.printCommandLine() == testGirl);
    XCTAssert(bookWidth.printCommandLine() == testWidth);
}

- (void)testSetandGetOclc {
    rtl::Book testBook;
    std::string testString = "1234";
                              
    testBook.setOclc(testString);
    
    XCTAssert(testBook.getOclc() == testString);
}

@end
