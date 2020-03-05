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
    testBook.setPublishDate("Dec 01 1990");
    XCTAssert("testAuthor" == testBook.getAuthor());
    XCTAssert("testTitle" == testBook.getTitle());
    XCTAssert("testSeries" == testBook.getSeries());
    XCTAssert("testPublisher" == testBook.getPublisher());
    XCTAssert("fantasy" == testBook.printGenre());
    XCTAssert(10 == testBook.getPageCount());
    XCTAssert("Dec 01 1990" == testBook.printPublishDate());
}

- (void)testSetPublishedDateString {
    rtl::Book testBook;
    testBook.setPublishDate("Jan 01 2008");
    XCTAssert("Jan 01 2008" == testBook.printPublishDate());
    testBook.setPublishDate("Feb 29 2001");
    XCTAssert("Mar 01 2001" == testBook.printPublishDate());
    testBook.setPublishDate("Feb 29 2008");
    XCTAssert("Feb 29 2008" == testBook.printPublishDate());
    testBook.setPublishDate("Feb 29 2008");
    XCTAssert("Feb 29 2008" == testBook.printPublishDate());
    testBook.setPublishDate("Mar 13 2017");
    XCTAssert("Mar 13 2017" == testBook.printPublishDate());
    testBook.setPublishDate("Apr 02 1950");
    XCTAssert("Apr 02 1950" == testBook.printPublishDate());
    testBook.setPublishDate("May 31 2010");
    XCTAssert("May 31 2010" == testBook.printPublishDate());
    testBook.setPublishDate("Jun 22 1910");
    XCTAssert("Jun 22 1910" == testBook.printPublishDate());
    testBook.setPublishDate("Jul 30 2020");
    XCTAssert("Jul 30 2020" == testBook.printPublishDate());
    testBook.setPublishDate("Aug 13 2000");
    XCTAssert("Aug 13 2000" == testBook.printPublishDate());
    testBook.setPublishDate("Sep 28 2013");
    XCTAssert("Sep 28 2013" == testBook.printPublishDate());
    testBook.setPublishDate("Oct 31 2002");
    XCTAssert("Oct 31 2002" == testBook.printPublishDate());
    testBook.setPublishDate("Nov 15 1990");
    XCTAssert("Nov 15 1990" == testBook.printPublishDate());
    testBook.setPublishDate("Nov 32 2000");
    XCTAssert("Dec 02 2000" == testBook.printPublishDate());
    testBook.setPublishDate("Dec 25 1999");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    testBook.setPublishDate("Not 13 1990");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    testBook.setPublishDate("really long invalid string");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    testBook.setPublishDate("too short");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    testBook.setPublishDate("");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    
    testBook.setPublishDate("AAA 01 1980");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    
    testBook.setPublishDate("Dec -1 1980");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    
    testBook.setPublishDate("Dec 01 1890");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    
    testBook.setPublishDate("Dec ab 1980");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
    
    testBook.setPublishDate("AAA 01 asdf");
    XCTAssert("Dec 25 1999" == testBook.printPublishDate());
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
    testBook.setPublishDate("Dec 01 1990");
    
    std::string answer = R"({"author":"testAuthor","title":"testTitle","series":"testSeries","publisher":"testPublisher","genre":"fantasy","pageCount":10,"publishDate":"Dec 01 1990"})";
    XCTAssert(answer == testBook.printJson());
}

- (void)testPrintGenre {
    rtl::Book testBook;
    testBook.setGenre("detective");
    XCTAssert("detective" == testBook.printGenre());
    testBook.setGenre("dystopia");
    XCTAssert("dystopia" == testBook.printGenre());
    testBook.setGenre("fantasy");
    XCTAssert("fantasy" == testBook.printGenre());
    testBook.setGenre("mystery");
    XCTAssert("mystery" == testBook.printGenre());
    testBook.setGenre("romance");
    XCTAssert("romance" == testBook.printGenre());
    testBook.setGenre("science fiction");
    XCTAssert("science fiction" == testBook.printGenre());
    testBook.setGenre("thriller");
    XCTAssert("thriller" == testBook.printGenre());
    testBook.setGenre("western");
    XCTAssert("western" == testBook.printGenre());
    testBook.setGenre("sci fi");
    XCTAssert("science fiction" == testBook.printGenre());
    testBook.setGenre("pickle");
    XCTAssert("genre not set" == testBook.printGenre());
}

- (void)testBookEquals {
    rtl::Book testBook;
    testBook.setAuthor("testAuthor");
    testBook.setTitle("testTitle");
    testBook.setSeries("testSeries");
    testBook.setPublisher("testPublisher");
    testBook.setGenre("fantasy");
    testBook.setPageCount(10);
    testBook.setPublishDate("Dec 01 1990");
    
    rtl::Book testBook2;
    testBook2.setAuthor("testAuthor");
    testBook2.setTitle("testTitle");
    testBook2.setSeries("testSeries");
    testBook2.setPublisher("testPublisher");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(10);
    testBook2.setPublishDate("Dec 01 1990");
    
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
    testBook.setPublishDate("Dec 01 1990");
    
    rtl::Book testBook2;
    testBook2.setAuthor("testAuthor2");
    testBook2.setTitle("testTitle2");
    testBook2.setSeries("testSeries2");
    testBook2.setPublisher("testPublisher2");
    testBook2.setGenre("western");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("Dec 01 1991");
    
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
    testBook.setPublishDate("Dec 01 1990");
    
    rtl::Book testBook2;
    testBook2.setAuthor("b");
    testBook2.setTitle("b");
    testBook2.setSeries("b");
    testBook2.setPublisher("a");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("Dec 01 1991");
    
    XCTAssert(testBook < testBook2);

    testBook2.setAuthor("a");
    XCTAssert(testBook < testBook2);
    
    testBook2.setSeries("a");
    XCTAssert(testBook < testBook2);
    
    testBook2.setPublishDate("Dec 01 1990");
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
    testBook.setPublishDate("Dec 01 1990");
    
    rtl::Book testBook2;
    testBook2.setAuthor("b");
    testBook2.setTitle("b");
    testBook2.setSeries("b");
    testBook2.setPublisher("a");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("Dec 01 1991");
    
    XCTAssert(testBook <= testBook2);

    testBook2.setAuthor("a");
    XCTAssert(testBook <= testBook2);
    
    testBook2.setSeries("a");
    XCTAssert(testBook <= testBook2);
    
    testBook2.setPublishDate("Dec 01 1990");
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
    testBook.setPublishDate("Dec 01 1990");
    
    rtl::Book testBook2;
    testBook2.setAuthor("b");
    testBook2.setTitle("b");
    testBook2.setSeries("b");
    testBook2.setPublisher("a");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("Dec 01 1991");
    
    XCTAssert(testBook2 > testBook);

    testBook2.setAuthor("a");
    XCTAssert(testBook2 > testBook);
    
    testBook2.setSeries("a");
    XCTAssert(testBook2 > testBook);
    
    testBook2.setPublishDate("Dec 01 1990");
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
    testBook.setPublishDate("Dec 01 1990");
    
    rtl::Book testBook2;
    testBook2.setAuthor("b");
    testBook2.setTitle("b");
    testBook2.setSeries("b");
    testBook2.setPublisher("a");
    testBook2.setGenre("fantasy");
    testBook2.setPageCount(100);
    testBook2.setPublishDate("Dec 01 1991");
    
    XCTAssert(testBook2 >= testBook);

    testBook2.setAuthor("a");
    XCTAssert(testBook2 >= testBook);
    
    testBook2.setSeries("a");
    XCTAssert(testBook2 >= testBook);
    
    testBook2.setPublishDate("Dec 01 1990");
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
    rtl::Book testBookConstructor2("testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 2222, "thriller", "Nov 16 1991");
    XCTAssert("testAuthor2" == testBookConstructor2.getAuthor());
    XCTAssert("testTitle2" == testBookConstructor2.getTitle());
    XCTAssert("testSeries2" == testBookConstructor2.getSeries());
    XCTAssert("testPublisher2" == testBookConstructor2.getPublisher());
    XCTAssert(2222 == testBookConstructor2.getPageCount());
    XCTAssert(rtl::thriller == testBookConstructor2.getGenre());
    XCTAssert("Nov 16 1991" == testBookConstructor2.printPublishDate());
}

- (void)testPrintColumnHeaders {
    std::string testStr = "Author              Title                              Series              Pages";
    
    XCTAssert(rtl::Book::printCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLine {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541  ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    Millennium          480  ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 The Wheel of Time12 70212";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "Jul 17 2006");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "Aug 01 2005");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "Jan 15 1990");
    
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
