//
//  testClassReadbook.mm
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/13/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "ReadBook.hpp"

@interface testClassReadbook : XCTestCase

@end

@implementation testClassReadbook

int testReaderId = 1;

- (void)setUp {
    
}

- (void)tearDown {
}

- (void)testSetReadDateTimeT {
    rtl::ReadBook testReadBook(testReaderId);
    time_t testTimeInitial = 1199163600; //Tuesday, January 1, 2008 12:00:00 AM GMT -5
    testReadBook.setDateRead(testTimeInitial);
    XCTAssert(testTimeInitial == testReadBook.getDateReadAsTimeT());
    time_t testTime = 1199165003; //Tuesday, January 1, 2008 12:23:23 AM GMT -5
    testReadBook.setPublishDate(testTime);
    XCTAssert(testTimeInitial == testReadBook.getDateReadAsTimeT());
}

- (void)testSetReadDateString {
    rtl::ReadBook testReadBook(testReaderId);
    XCTAssert(testReadBook.setDateRead("2008 1 01"));
    XCTAssert(testReadBook.printDateRead() == "2008-Jan-01");
    XCTAssert(testReadBook.setDateRead("2001-Feb-28"));
    XCTAssert(testReadBook.printDateRead() == "2001-Feb-28");
    XCTAssert(testReadBook.setDateRead("2008-Feb-29"));
    XCTAssert(testReadBook.printDateRead() == "2008-Feb-29");
    XCTAssert(testReadBook.setDateRead("2017-Mar-13"));
    XCTAssert(testReadBook.printDateRead() == "2017-Mar-13");
    XCTAssert(testReadBook.setDateRead("1950-April-02"));
    XCTAssert(testReadBook.printDateRead() == "1950-Apr-02");
    XCTAssert(testReadBook.setDateRead("2010-May-31"));
    XCTAssert(testReadBook.printDateRead() == "2010-May-31");
    XCTAssert(testReadBook.setDateRead("1910-Jun-22"));
    XCTAssert(testReadBook.printDateRead() == "1910-Jun-22");
    XCTAssert(testReadBook.setDateRead("2020-07-30"));
    XCTAssert(testReadBook.printDateRead() == "2020-Jul-30");
    XCTAssert(testReadBook.setDateRead("2000/Aug/13"));
    XCTAssert(testReadBook.printDateRead() == "2000-Aug-13");
    XCTAssert(testReadBook.setDateRead("2013-9-28"));
    XCTAssert(testReadBook.printDateRead() == "2013-Sep-28");
    XCTAssert(testReadBook.setDateRead("2002-Oct-31"));
    XCTAssert(testReadBook.printDateRead() == "2002-Oct-31");
    XCTAssert(testReadBook.setDateRead("1990-Nov-15"));
    XCTAssert(testReadBook.printDateRead() == "1990-Nov-15");
    XCTAssert(testReadBook.setDateRead("1999-Dec-25"));
    XCTAssert(testReadBook.printDateRead() == "1999-Dec-25");
    XCTAssert(testReadBook.setDateRead("1890-Dec-01"));
    XCTAssert(testReadBook.printDateRead() == "1890-Dec-01");
    
    XCTAssert(!testReadBook.setDateRead("Dec-ab-1980"));
    XCTAssert(!testReadBook.setDateRead(""));
    XCTAssert(!testReadBook.setDateRead("too short"));
    XCTAssert(!testReadBook.setDateRead("really long invalid string"));
    XCTAssert(!testReadBook.setDateRead("1990-Not-13"));
    XCTAssert(!testReadBook.setDateRead("AAA-01-asdf"));
    XCTAssert(!testReadBook.setDateRead("2001/Feb/29"));
    XCTAssert(!testReadBook.setDateRead("AAA 01 1980"));
    XCTAssert(!testReadBook.setDateRead("Dec-01-1980"));
}

- (void)testSetRating {
    rtl::ReadBook testRating(testReaderId);
    testRating.setRating(-1);
    XCTAssert(1 == testRating.getRating());
    testRating.setRating(1);
    XCTAssert(1 == testRating.getRating());
    testRating.setRating(10);
    XCTAssert(10 == testRating.getRating());
    testRating.setRating(11);
    XCTAssert(10 == testRating.getRating());
    testRating.setRating('9');
    XCTAssert(9 == testRating.getRating());
    testRating.setRating('a');
    XCTAssert(9 == testRating.getRating());
    testRating.setRating("2");
    XCTAssert(2 == testRating.getRating());
    testRating.setRating("z4");
    XCTAssert(2 == testRating.getRating());
    testRating.setRating("-20");
    XCTAssert(2 == testRating.getRating());
}


- (void)testReadBookEquals {
    rtl::ReadBook testReadBook1(testReaderId);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec-01-1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar-25-1993");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("a");
    testReadBook2.setTitle("a");
    testReadBook2.setSeries("a");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec-01-1990");
    testReadBook2.setRating(4);
    testReadBook2.setDateRead("Mar-25-1993");
    
    XCTAssert(testReadBook1 == testReadBook2);
}

- (void)testReadBookNotEquals {
    rtl::ReadBook testReadBook1(testReaderId);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec-01-1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar-25-1993");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec-01-1991");
    testReadBook2.setRating(5);
    testReadBook2.setDateRead("Mar-26-1993");
    
    XCTAssert(testReadBook1 != testReadBook2);
}

- (void)testReadBookLessThan {
    rtl::ReadBook testReadBook1(testReaderId);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("1990-Dec-01");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("1991-Dec-01");
    testReadBook2.setRating(5);
    testReadBook2.setDateRead("1993-Mar-26");
    
    XCTAssert(testReadBook1 < testReadBook2);

    testReadBook2.setAuthor("a");
    XCTAssert(testReadBook1 < testReadBook2);
    
    testReadBook2.setSeries("a");
    XCTAssert(testReadBook1 < testReadBook2);
    
    
    testReadBook2.setPublishDate("1990-Dec-01");
    XCTAssert(testReadBook1 < testReadBook2);
    
    testReadBook2.setGenre("western");
    testReadBook2.setPageCount(110);
    testReadBook2.setTitle("a");
    XCTAssert(testReadBook1 < testReadBook2);
    
    testReadBook2.setDateRead("1993-Mar-25");
    XCTAssert(!(testReadBook2 < testReadBook1));
}

- (void)testReadBookLessEqualsThan {
    rtl::ReadBook testReadBook1(testReaderId);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("1990-Dec-01");
    testReadBook1.setDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("1991-Dec-01");
    testReadBook2.setDateRead("1993-Mar-26");
    
    XCTAssert(testReadBook1 <= testReadBook2);

    testReadBook2.setAuthor("a");
    XCTAssert(testReadBook1 <= testReadBook2);
    
    testReadBook2.setSeries("a");
    XCTAssert(testReadBook1 <= testReadBook2);
    
    testReadBook2.setPublishDate("1990-Dec-01");
    XCTAssert(testReadBook1 <= testReadBook2);
    
    testReadBook2.setGenre("western");
    testReadBook2.setPageCount(110);
    testReadBook2.setTitle("a");
    XCTAssert(testReadBook1 <= testReadBook2);
    
    testReadBook2.setDateRead("1993-Mar-25");
    XCTAssert(testReadBook2 <= testReadBook1);
}

- (void)testReadBookGreaterThan {
    rtl::ReadBook testReadBook1(testReaderId);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("1990-Dec-01");
    testReadBook1.setDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("1991-Dec-01");
    testReadBook2.setDateRead("1993-Mar-26");
    
    XCTAssert(testReadBook2 > testReadBook1);

    testReadBook2.setAuthor("a");
    XCTAssert(testReadBook2 > testReadBook1);
    
    testReadBook2.setSeries("a");
    XCTAssert(testReadBook2 > testReadBook1);
    
    testReadBook2.setPublishDate("1990-Dec-01");
    XCTAssert(testReadBook2 > testReadBook1);
    
    testReadBook2.setGenre("western");
    testReadBook2.setPageCount(110);
    testReadBook2.setTitle("a");
    XCTAssert(testReadBook2 > testReadBook1);
    
    testReadBook2.setDateRead("1993-Mar-25");
    XCTAssert(!(testReadBook1 > testReadBook2));
}

- (void)testReadBookGreaterEqualsThan {
    rtl::ReadBook testReadBook1(testReaderId);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("1990-Dec-01");
    testReadBook1.setDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("1991-Dec-01");
    testReadBook2.setDateRead("1993-Mar-26");
    
    XCTAssert(testReadBook2 >= testReadBook1);

    testReadBook2.setAuthor("a");
    XCTAssert(testReadBook2 >= testReadBook1);
    
    testReadBook2.setSeries("a");
    XCTAssert(testReadBook2 >= testReadBook1);
    
    testReadBook2.setPublishDate("1990-Dec-01");
    XCTAssert(testReadBook2 >= testReadBook1);
    
    testReadBook2.setGenre("western");
    testReadBook2.setPageCount(110);
    testReadBook2.setTitle("a");
    XCTAssert(testReadBook2 >= testReadBook1);
    
    testReadBook2.setDateRead("1993-Mar-25");
    XCTAssert(testReadBook2 >= testReadBook1);
}

- (void)testPrintJson {
    rtl::ReadBook testReadBook1(testReaderId);
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("1990-Dec-01");
    testReadBook1.setDateRead("1993-Mar-25");
    testReadBook1.setRating(4);
    
    std::string jsonString = R"({"author":"a","title":"a","series":"a","publisher":"a","genre":"fantasy","pageCount":100,"publishDate":"1990-Dec-01","rating":4,"dateRead":"1993-Mar-25","readerId":1})";
    
    XCTAssert(testReadBook1.printJson() == jsonString);
}

- (void)testConstructors {
    
    rtl::Book newBook("testAuthor", "testTitle", "testSeries", "testPublisher", 111, rtl::fantasy, 1199163600);
    rtl::ReadBook testConstructor(2147483647, newBook, 9, 1199163600);
    XCTAssert(testConstructor.getReaderId() == 2147483647);
    XCTAssert(testConstructor.getAuthor() == "testAuthor");
    XCTAssert(testConstructor.getTitle() == "testTitle");
    XCTAssert(testConstructor.getSeries() == "testSeries");
    XCTAssert(testConstructor.getPublisher() == "testPublisher");
    XCTAssert(testConstructor.getPageCount() == 111);
    XCTAssert(testConstructor.getGenre() == rtl::fantasy);
    XCTAssert(testConstructor.getPublishDateAsTimeT() == 1199163600);
    XCTAssert(testConstructor.getRating() == 9);
    XCTAssert(testConstructor.getDateReadAsTimeT() == 1199163600);
    
    //ReadBook(Book book, int rating, std::string dateRead);
    rtl::ReadBook testConstructor3(456, newBook, 1, "1913-Feb-11");
    XCTAssert(testConstructor3.getAuthor() == "testAuthor");
    XCTAssert(testConstructor3.getTitle() == "testTitle");
    XCTAssert(testConstructor3.getSeries() == "testSeries");
    XCTAssert(testConstructor3.getPublisher() == "testPublisher");
    XCTAssert(testConstructor3.getPageCount() == 111);
    XCTAssert(testConstructor3.getGenre() == rtl::fantasy);
    XCTAssert(testConstructor3.getPublishDateAsTimeT() == 1199163600);
    XCTAssert(testConstructor3.getRating() == 1);
    XCTAssert(testConstructor3.printDateRead() == "1913-Feb-11" );
    
    //ReadBook(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, int rating = 0, time_t time = std::time(0));
    rtl::ReadBook testConstructor2(789, "testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 222, rtl::western, 1199181600, 8, 1199181600);
    XCTAssert(testConstructor2.getAuthor() == "testAuthor2");
    XCTAssert(testConstructor2.getTitle() == "testTitle2");
    XCTAssert(testConstructor2.getSeries() == "testSeries2");
    XCTAssert(testConstructor2.getPublisher() == "testPublisher2");
    XCTAssert(testConstructor2.getPageCount() == 222);
    XCTAssert(testConstructor2.getGenre() == rtl::western);
    XCTAssert(testConstructor2.getPublishDateAsTimeT() == 1199163600);
    XCTAssert(testConstructor2.getRating() == 8);
    XCTAssert(testConstructor2.getDateReadAsTimeT() == 1199163600);
    
    //ReadBook::ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead)
    rtl::ReadBook testConstructor4(-1234567890, "testAuthor4", "testTitle4", "testSeries4", "testPublisher4", 444, "mystery", "1972-Aug-13", 4, "2019-Nov-14");
    XCTAssert(testConstructor4.getAuthor() == "testAuthor4");
    XCTAssert(testConstructor4.getTitle() == "testTitle4");
    XCTAssert(testConstructor4.getSeries() == "testSeries4");
    XCTAssert(testConstructor4.getPublisher() == "testPublisher4");
    XCTAssert(testConstructor4.getPageCount() == 444);
    XCTAssert(testConstructor4.printGenre() == "mystery");
    XCTAssert(testConstructor4.printPublishDate() == "1972-Aug-13");
    XCTAssert(testConstructor4.getRating() == 4);
    XCTAssert(testConstructor4.printDateRead() == "2019-Nov-14");
}

- (void)testPrintColumnHeaders {
    std::string testStr = "Author              Title                              Pages Date Read    Rating";
    
    XCTAssert(rtl::ReadBook::printCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLine {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         541   2019-Sep-13  9     ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    480   2019-Nov-19  9     ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 70212 2019-Oct-27  8     ";

    rtl::ReadBook bookMist(123, "Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", 9, "2019-Sep-13");
    rtl::ReadBook bookGirl(123, "Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", 9, "2019-Nov-19");
    rtl::ReadBook bookWidth(123, "Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15", 8, "2019-Oct-27");
    
    XCTAssert(bookMist.printCommandLine() == testMist);
    XCTAssert(bookGirl.printCommandLine() == testGirl);
    XCTAssert(bookWidth.printCommandLine() == testWidth);
}

@end
