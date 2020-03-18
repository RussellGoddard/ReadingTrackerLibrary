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
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    time_t testTimeInitial = 1199163600; //Tuesday, January 1, 2008 12:00:00 AM GMT -5
    testReadBook.SetDateRead(testTimeInitial);
    XCTAssert(testTimeInitial == testReadBook.GetDateReadAsTimeT());
    time_t testTime = 1199165003; //Tuesday, January 1, 2008 12:23:23 AM GMT -5
    testReadBook.SetPublishDate(testTime);
    XCTAssert(testTimeInitial == testReadBook.GetDateReadAsTimeT());
}

- (void)testSetReadDateString {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testReadBook.SetDateRead("2008 1 01"));
    XCTAssert(testReadBook.PrintDateRead() == "2008-Jan-01");
    XCTAssert(testReadBook.SetDateRead("2001-Feb-28"));
    XCTAssert(testReadBook.PrintDateRead() == "2001-Feb-28");
    XCTAssert(testReadBook.SetDateRead("2008-Feb-29"));
    XCTAssert(testReadBook.PrintDateRead() == "2008-Feb-29");
    XCTAssert(testReadBook.SetDateRead("2017-Mar-13"));
    XCTAssert(testReadBook.PrintDateRead() == "2017-Mar-13");
    XCTAssert(testReadBook.SetDateRead("1950-April-02"));
    XCTAssert(testReadBook.PrintDateRead() == "1950-Apr-02");
    XCTAssert(testReadBook.SetDateRead("2010-May-31"));
    XCTAssert(testReadBook.PrintDateRead() == "2010-May-31");
    XCTAssert(testReadBook.SetDateRead("1910-Jun-22"));
    XCTAssert(testReadBook.PrintDateRead() == "1910-Jun-22");
    XCTAssert(testReadBook.SetDateRead("2020-07-30"));
    XCTAssert(testReadBook.PrintDateRead() == "2020-Jul-30");
    XCTAssert(testReadBook.SetDateRead("2000/Aug/13"));
    XCTAssert(testReadBook.PrintDateRead() == "2000-Aug-13");
    XCTAssert(testReadBook.SetDateRead("2013-9-28"));
    XCTAssert(testReadBook.PrintDateRead() == "2013-Sep-28");
    XCTAssert(testReadBook.SetDateRead("2002-Oct-31"));
    XCTAssert(testReadBook.PrintDateRead() == "2002-Oct-31");
    XCTAssert(testReadBook.SetDateRead("1990-Nov-15"));
    XCTAssert(testReadBook.PrintDateRead() == "1990-Nov-15");
    XCTAssert(testReadBook.SetDateRead("1999-Dec-25"));
    XCTAssert(testReadBook.PrintDateRead() == "1999-Dec-25");
    XCTAssert(testReadBook.SetDateRead("1890-Dec-01"));
    XCTAssert(testReadBook.PrintDateRead() == "1890-Dec-01");
    
    XCTAssert(!testReadBook.SetDateRead("Dec-ab-1980"));
    XCTAssert(!testReadBook.SetDateRead(""));
    XCTAssert(!testReadBook.SetDateRead("too short"));
    XCTAssert(!testReadBook.SetDateRead("really long invalid string"));
    XCTAssert(!testReadBook.SetDateRead("1990-Not-13"));
    XCTAssert(!testReadBook.SetDateRead("AAA-01-asdf"));
    XCTAssert(!testReadBook.SetDateRead("2001/Feb/29"));
    XCTAssert(!testReadBook.SetDateRead("AAA 01 1980"));
    XCTAssert(!testReadBook.SetDateRead("Dec-01-1980"));
}

- (void)testSetRating {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    testRating.SetRating(-1);
    XCTAssert(1 == testRating.GetRating());
    testRating.SetRating(1);
    XCTAssert(1 == testRating.GetRating());
    testRating.SetRating(10);
    XCTAssert(10 == testRating.GetRating());
    testRating.SetRating(11);
    XCTAssert(10 == testRating.GetRating());
    testRating.SetRating('9');
    XCTAssert(9 == testRating.GetRating());
    testRating.SetRating('a');
    XCTAssert(9 == testRating.GetRating());
    testRating.SetRating("2");
    XCTAssert(2 == testRating.GetRating());
    testRating.SetRating("z4");
    XCTAssert(2 == testRating.GetRating());
    testRating.SetRating("-20");
    XCTAssert(2 == testRating.GetRating());
}


- (void)testReadBookEquals {
    rtl::ReadBook testReadBook1(testReaderId, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("Dec-01-1990");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("Mar-25-1993");
    
    rtl::ReadBook testReadBook2(testReaderId, "a", "a");
    testReadBook2.SetSeries("a");
    testReadBook2.SetPublisher("a");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("Dec-01-1990");
    testReadBook2.SetRating(4);
    testReadBook2.SetDateRead("Mar-25-1993");
    
    XCTAssert(testReadBook1 == testReadBook2);
}

- (void)testReadBookNotEquals {
    rtl::ReadBook testReadBook1(testReaderId, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("Dec-01-1990");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("Mar-25-1993");
    
    rtl::ReadBook testReadBook2(testReaderId, "b", "b");
    testReadBook2.SetSeries("b");
    testReadBook2.SetPublisher("a");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("Dec-01-1991");
    testReadBook2.SetRating(5);
    testReadBook2.SetDateRead("Mar-26-1993");
    
    XCTAssert(testReadBook1 != testReadBook2);
}

- (void)testReadBookLessThan {
    rtl::ReadBook testReadBook1(testReaderId, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "b", "b");
    testReadBook2.SetSeries("b");
    testReadBook2.SetPublisher("a");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("1991-Dec-01");
    testReadBook2.SetRating(5);
    testReadBook2.SetDateRead("1993-Mar-26");
    
    XCTAssert(testReadBook1 < testReadBook2);

    rtl::ReadBook testReadBook3(testReaderId, "a", "b");
    testReadBook3.SetSeries("b");
    testReadBook3.SetPublisher("a");
    testReadBook3.SetGenre("fantasy");
    testReadBook3.SetPageCount(100);
    testReadBook3.SetPublishDate("1991-Dec-01");
    testReadBook3.SetRating(5);
    testReadBook3.SetDateRead("1993-Mar-26");
    XCTAssert(testReadBook1 < testReadBook2);
    
    testReadBook3.SetSeries("a");
    XCTAssert(testReadBook1 < testReadBook3);
    
    
    testReadBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testReadBook1 < testReadBook3);
    
    rtl::ReadBook testReadBook4(testReaderId, "a", "a");
    testReadBook4.SetSeries("a");
    testReadBook4.SetPublisher("a");
    testReadBook4.SetPublishDate("1990-Dec-01");
    testReadBook4.SetRating(5);
    testReadBook4.SetDateRead("1993-Mar-26");
    testReadBook4.SetGenre("western");
    testReadBook4.SetPageCount(110);
    XCTAssert(testReadBook1 < testReadBook4);
    
    testReadBook4.SetDateRead("1993-Mar-25");
    XCTAssert(!(testReadBook4 < testReadBook1));
}

- (void)testReadBookLessEqualsThan {
    rtl::ReadBook testReadBook1(testReaderId, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "b", "b");
    testReadBook2.SetSeries("b");
    testReadBook2.SetPublisher("a");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("1991-Dec-01");
    testReadBook2.SetDateRead("1993-Mar-26");
    
    XCTAssert(testReadBook1 <= testReadBook2);

    rtl::ReadBook testReadBook3(testReaderId, "a", "b");
    testReadBook3.SetSeries("b");
    testReadBook3.SetPublisher("a");
    testReadBook3.SetGenre("fantasy");
    testReadBook3.SetPageCount(100);
    testReadBook3.SetPublishDate("1991-Dec-01");
    testReadBook3.SetDateRead("1993-Mar-26");
    XCTAssert(testReadBook1 <= testReadBook3);
    
    testReadBook3.SetSeries("a");
    XCTAssert(testReadBook1 <= testReadBook3);
    
    testReadBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testReadBook1 <= testReadBook3);
    
    rtl::ReadBook testReadBook4(testReaderId, "a", "a");
    testReadBook4.SetSeries("a");
    testReadBook4.SetPublisher("a");
    testReadBook4.SetPublishDate("1990-Dec-01");
    testReadBook4.SetDateRead("1993-Mar-26");
    testReadBook4.SetGenre("western");
    testReadBook4.SetPageCount(110);
    XCTAssert(testReadBook1 <= testReadBook4);
    
    testReadBook4.SetDateRead("1993-Mar-25");
    XCTAssert(testReadBook4 <= testReadBook1);
}

- (void)testReadBookGreaterThan {
    rtl::ReadBook testReadBook1(testReaderId, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "b", "b");
    testReadBook2.SetSeries("b");
    testReadBook2.SetPublisher("a");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("1991-Dec-01");
    testReadBook2.SetDateRead("1993-Mar-26");
    
    XCTAssert(testReadBook2 > testReadBook1);

    rtl::ReadBook testReadBook3(testReaderId, "a", "b");
    testReadBook3.SetSeries("b");
    testReadBook3.SetPublisher("a");
    testReadBook3.SetGenre("fantasy");
    testReadBook3.SetPageCount(100);
    testReadBook3.SetPublishDate("1991-Dec-01");
    testReadBook3.SetDateRead("1993-Mar-26");
    XCTAssert(testReadBook3 > testReadBook1);
    
    testReadBook3.SetSeries("a");
    XCTAssert(testReadBook3 > testReadBook1);
    
    testReadBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testReadBook3 > testReadBook1);
    
    rtl::ReadBook testReadBook4(testReaderId, "a", "a");
    testReadBook4.SetSeries("a");
    testReadBook4.SetPublisher("a");
    testReadBook4.SetPublishDate("1990-Dec-01");
    testReadBook4.SetDateRead("1993-Mar-26");
    testReadBook4.SetGenre("western");
    testReadBook4.SetPageCount(110);
    XCTAssert(testReadBook4 > testReadBook1);
    
    testReadBook4.SetDateRead("1993-Mar-25");
    XCTAssert(!(testReadBook1 > testReadBook4));
}

- (void)testReadBookGreaterEqualsThan {
    rtl::ReadBook testReadBook1(testReaderId, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "b", "b");
    testReadBook2.SetSeries("b");
    testReadBook2.SetPublisher("a");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("1991-Dec-01");
    testReadBook2.SetDateRead("1993-Mar-26");
    
    XCTAssert(testReadBook2 >= testReadBook1);

    rtl::ReadBook testReadBook3(testReaderId, "a", "b");
    testReadBook3.SetSeries("b");
    testReadBook3.SetPublisher("a");
    testReadBook3.SetGenre("fantasy");
    testReadBook3.SetPageCount(100);
    testReadBook3.SetPublishDate("1991-Dec-01");
    testReadBook3.SetDateRead("1993-Mar-26");
    XCTAssert(testReadBook3 >= testReadBook1);
    
    testReadBook3.SetSeries("a");
    XCTAssert(testReadBook3 >= testReadBook1);
    
    testReadBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testReadBook3 >= testReadBook1);
    
    rtl::ReadBook testReadBook4(testReaderId, "a", "a");
    testReadBook4.SetSeries("a");
    testReadBook4.SetPublisher("a");
    testReadBook4.SetPublishDate("1991-Dec-01");
    testReadBook4.SetDateRead("1993-Mar-26");
    testReadBook4.SetGenre("western");
    testReadBook4.SetPageCount(110);
    XCTAssert(testReadBook4 >= testReadBook1);
    
    testReadBook4.SetDateRead("1993-Mar-25");
    XCTAssert(testReadBook4 >= testReadBook1);
}

- (void)testPrintJson {
    rtl::ReadBook testReadBook1(testReaderId, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetDateRead("1993-Mar-25");
    testReadBook1.SetRating(4);
    
    std::string jsonString = R"({"bookId":"1bba","author":"a","title":"a","series":"a","publisher":"a","genre":"fantasy","pageCount":100,"publishDate":"1990-Dec-01","rating":4,"dateRead":"1993-Mar-25","readerId":1})";
    
    XCTAssert(testReadBook1.PrintJson() == jsonString);
}

- (void)testConstructors {
    
    rtl::Book newBook("testAuthor", "testTitle", "testSeries", "testPublisher", 111, rtl::fantasy, 1199163600);
    rtl::ReadBook testConstructor(2147483647, newBook, 9, 1199163600);
    XCTAssert(testConstructor.GetReaderId() == 2147483647);
    XCTAssert(testConstructor.GetAuthor() == "testAuthor");
    XCTAssert(testConstructor.GetTitle() == "testTitle");
    XCTAssert(testConstructor.GetSeries() == "testSeries");
    XCTAssert(testConstructor.GetPublisher() == "testPublisher");
    XCTAssert(testConstructor.GetPageCount() == 111);
    XCTAssert(testConstructor.GetGenre() == rtl::fantasy);
    XCTAssert(testConstructor.GetPublishDateAsTimeT() == 1199163600);
    XCTAssert(testConstructor.GetRating() == 9);
    XCTAssert(testConstructor.GetDateReadAsTimeT() == 1199163600);
    XCTAssert(testConstructor.GetBookId() == "2ff6b24");
    
    //ReadBook(Book book, int rating, std::string dateRead);
    rtl::ReadBook testConstructor3(456, newBook, 1, "1913-Feb-11");
    XCTAssert(testConstructor3.GetAuthor() == "testAuthor");
    XCTAssert(testConstructor3.GetTitle() == "testTitle");
    XCTAssert(testConstructor3.GetSeries() == "testSeries");
    XCTAssert(testConstructor3.GetPublisher() == "testPublisher");
    XCTAssert(testConstructor3.GetPageCount() == 111);
    XCTAssert(testConstructor3.GetGenre() == rtl::fantasy);
    XCTAssert(testConstructor3.GetPublishDateAsTimeT() == 1199163600);
    XCTAssert(testConstructor3.GetRating() == 1);
    XCTAssert(testConstructor3.PrintDateRead() == "1913-Feb-11" );
    XCTAssert(testConstructor3.GetBookId() == "2ff6b24");
    
    //ReadBook(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, int rating = 0, time_t time = std::time(0));
    rtl::ReadBook testConstructor2(789, "testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 222, rtl::western, 1199181600, 8, 1199181600);
    XCTAssert(testConstructor2.GetAuthor() == "testAuthor2");
    XCTAssert(testConstructor2.GetTitle() == "testTitle2");
    XCTAssert(testConstructor2.GetSeries() == "testSeries2");
    XCTAssert(testConstructor2.GetPublisher() == "testPublisher2");
    XCTAssert(testConstructor2.GetPageCount() == 222);
    XCTAssert(testConstructor2.GetGenre() == rtl::western);
    XCTAssert(testConstructor2.GetPublishDateAsTimeT() == 1199163600);
    XCTAssert(testConstructor2.GetRating() == 8);
    XCTAssert(testConstructor2.GetDateReadAsTimeT() == 1199163600);
    XCTAssert(testConstructor2.GetBookId() == "42b3e88");
    
    //ReadBook::ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead)
    rtl::ReadBook testConstructor4(-1234567890, "testAuthor4", "testTitle4", "testSeries4", "testPublisher4", 444, "mystery", "1972-Aug-13", 4, "2019-Nov-14");
    XCTAssert(testConstructor4.GetAuthor() == "testAuthor4");
    XCTAssert(testConstructor4.GetTitle() == "testTitle4");
    XCTAssert(testConstructor4.GetSeries() == "testSeries4");
    XCTAssert(testConstructor4.GetPublisher() == "testPublisher4");
    XCTAssert(testConstructor4.GetPageCount() == 444);
    XCTAssert(testConstructor4.PrintGenre() == "mystery");
    XCTAssert(testConstructor4.PrintPublishDate() == "1972-Aug-13");
    XCTAssert(testConstructor4.GetRating() == 4);
    XCTAssert(testConstructor4.PrintDateRead() == "2019-Nov-14");
    XCTAssert(testConstructor4.GetBookId() == "4309c7c");
}

- (void)testPrintColumnHeaders {
    std::string testStr = "Author              Title                              Pages Date Read    Rating";
    
    XCTAssert(rtl::ReadBook::PrintCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLine {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         541   2019-Sep-13  9     ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    480   2019-Nov-19  9     ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 70212 2019-Oct-27  8     ";

    rtl::ReadBook bookMist(123, "Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", 9, "2019-Sep-13");
    rtl::ReadBook bookGirl(123, "Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", 9, "2019-Nov-19");
    rtl::ReadBook bookWidth(123, "Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15", 8, "2019-Oct-27");
    
    XCTAssert(bookMist.PrintCommandLine() == testMist);
    XCTAssert(bookGirl.PrintCommandLine() == testGirl);
    XCTAssert(bookWidth.PrintCommandLine() == testWidth);
}

@end
