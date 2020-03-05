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
    testReadBook.setDateRead("Jan 01 2008");
    XCTAssert("Jan 01 2008" == testReadBook.printDateRead());
    testReadBook.setDateRead("Feb 29 2001");
    XCTAssert("Mar 01 2001" == testReadBook.printDateRead());
    testReadBook.setDateRead("Feb 29 2008");
    XCTAssert("Feb 29 2008" == testReadBook.printDateRead());
    testReadBook.setDateRead("Feb 29 2008");
    XCTAssert("Feb 29 2008" == testReadBook.printDateRead());
    testReadBook.setDateRead("Mar 13 2017");
    XCTAssert("Mar 13 2017" == testReadBook.printDateRead());
    testReadBook.setDateRead("Apr 02 1950");
    XCTAssert("Apr 02 1950" == testReadBook.printDateRead());
    testReadBook.setDateRead("May 31 2010");
    XCTAssert("May 31 2010" == testReadBook.printDateRead());
    testReadBook.setDateRead("Jun 22 1910");
    XCTAssert("Jun 22 1910" == testReadBook.printDateRead());
    testReadBook.setDateRead("Jul 30 2020");
    XCTAssert("Jul 30 2020" == testReadBook.printDateRead());
    testReadBook.setDateRead("Aug 13 2000");
    XCTAssert("Aug 13 2000" == testReadBook.printDateRead());
    testReadBook.setDateRead("Sep 28 2013");
    XCTAssert("Sep 28 2013" == testReadBook.printDateRead());
    testReadBook.setDateRead("Oct 31 2002");
    XCTAssert("Oct 31 2002" == testReadBook.printDateRead());
    testReadBook.setDateRead("Nov 15 1990");
    XCTAssert("Nov 15 1990" == testReadBook.printDateRead());
    testReadBook.setDateRead("Nov 32 2000");
    XCTAssert("Dec 02 2000" == testReadBook.printDateRead());
    testReadBook.setDateRead("Dec 25 1999");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    testReadBook.setDateRead("Not 13 1990");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    testReadBook.setDateRead("really long invalid string");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    testReadBook.setDateRead("too short");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    testReadBook.setDateRead("");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    
    testReadBook.setDateRead("AAA 01 1980");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    
    testReadBook.setDateRead("Dec -1 1980");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    
    testReadBook.setDateRead("Dec 01 1890");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    
    testReadBook.setDateRead("Dec ab 1980");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
    
    testReadBook.setDateRead("AAA 01 asdf");
    XCTAssert("Dec 25 1999" == testReadBook.printDateRead());
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
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar 25 1993");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("a");
    testReadBook2.setTitle("a");
    testReadBook2.setSeries("a");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec 01 1990");
    testReadBook2.setRating(4);
    testReadBook2.setDateRead("Mar 25 1993");
    
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
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar 25 1993");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec 01 1991");
    testReadBook2.setRating(5);
    testReadBook2.setDateRead("Mar 26 1993");
    
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
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar 25 1993");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec 01 1991");
    testReadBook2.setRating(5);
    testReadBook2.setDateRead("Mar 26 1993");
    
    XCTAssert(testReadBook1 < testReadBook2);

    testReadBook2.setAuthor("a");
    XCTAssert(testReadBook1 < testReadBook2);
    
    testReadBook2.setSeries("a");
    XCTAssert(testReadBook1 < testReadBook2);
    
    
    testReadBook2.setPublishDate("Dec 01 1990");
    XCTAssert(testReadBook1 < testReadBook2);
    
    testReadBook2.setGenre("western");
    testReadBook2.setPageCount(110);
    testReadBook2.setTitle("a");
    XCTAssert(testReadBook1 < testReadBook2);
    
    testReadBook2.setDateRead("Mar 25 1993");
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
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setDateRead("Mar 25 1993");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec 01 1991");
    testReadBook2.setDateRead("Mar 26 1993");
    
    XCTAssert(testReadBook1 <= testReadBook2);

    testReadBook2.setAuthor("a");
    XCTAssert(testReadBook1 <= testReadBook2);
    
    testReadBook2.setSeries("a");
    XCTAssert(testReadBook1 <= testReadBook2);
    
    testReadBook2.setPublishDate("Dec 01 1990");
    XCTAssert(testReadBook1 <= testReadBook2);
    
    testReadBook2.setGenre("western");
    testReadBook2.setPageCount(110);
    testReadBook2.setTitle("a");
    XCTAssert(testReadBook1 <= testReadBook2);
    
    testReadBook2.setDateRead("Mar 25 1993");
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
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setDateRead("Mar 25 1993");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec 01 1991");
    testReadBook2.setDateRead("Mar 26 1993");
    
    XCTAssert(testReadBook2 > testReadBook1);

    testReadBook2.setAuthor("a");
    XCTAssert(testReadBook2 > testReadBook1);
    
    testReadBook2.setSeries("a");
    XCTAssert(testReadBook2 > testReadBook1);
    
    testReadBook2.setPublishDate("Dec 01 1990");
    XCTAssert(testReadBook2 > testReadBook1);
    
    testReadBook2.setGenre("western");
    testReadBook2.setPageCount(110);
    testReadBook2.setTitle("a");
    XCTAssert(testReadBook2 > testReadBook1);
    
    testReadBook2.setDateRead("Mar 25 1993");
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
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setDateRead("Mar 25 1993");
    
    rtl::ReadBook testReadBook2(testReaderId);
    testReadBook2.setAuthor("b");
    testReadBook2.setTitle("b");
    testReadBook2.setSeries("b");
    testReadBook2.setPublisher("a");
    testReadBook2.setGenre("fantasy");
    testReadBook2.setPageCount(100);
    testReadBook2.setPublishDate("Dec 01 1991");
    testReadBook2.setDateRead("Mar 26 1993");
    
    XCTAssert(testReadBook2 >= testReadBook1);

    testReadBook2.setAuthor("a");
    XCTAssert(testReadBook2 >= testReadBook1);
    
    testReadBook2.setSeries("a");
    XCTAssert(testReadBook2 >= testReadBook1);
    
    testReadBook2.setPublishDate("Dec 01 1990");
    XCTAssert(testReadBook2 >= testReadBook1);
    
    testReadBook2.setGenre("western");
    testReadBook2.setPageCount(110);
    testReadBook2.setTitle("a");
    XCTAssert(testReadBook2 >= testReadBook1);
    
    testReadBook2.setDateRead("Mar 25 1993");
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
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setDateRead("Mar 25 1993");
    testReadBook1.setRating(4);
    
    std::string jsonString = R"({"author":"a","title":"a","series":"a","publisher":"a","genre":"fantasy","pageCount":100,"publishDate":"Dec 01 1990","rating":4,"dateRead":"Mar 25 1993","readerId":1})";
    
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
    rtl::ReadBook testConstructor3(456, newBook, 1, "Feb 11 1913");
    XCTAssert(testConstructor3.getAuthor() == "testAuthor");
    XCTAssert(testConstructor3.getTitle() == "testTitle");
    XCTAssert(testConstructor3.getSeries() == "testSeries");
    XCTAssert(testConstructor3.getPublisher() == "testPublisher");
    XCTAssert(testConstructor3.getPageCount() == 111);
    XCTAssert(testConstructor3.getGenre() == rtl::fantasy);
    XCTAssert(testConstructor3.getPublishDateAsTimeT() == 1199163600);
    XCTAssert(testConstructor3.getRating() == 1);
    XCTAssert(testConstructor3.printDateRead() == "Feb 11 1913" );
    
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
    rtl::ReadBook testConstructor4(-1234567890, "testAuthor4", "testTitle4", "testSeries4", "testPublisher4", 444, "mystery", "Aug 13 1972", 4, "Nov 14 2019");
    XCTAssert(testConstructor4.getAuthor() == "testAuthor4");
    XCTAssert(testConstructor4.getTitle() == "testTitle4");
    XCTAssert(testConstructor4.getSeries() == "testSeries4");
    XCTAssert(testConstructor4.getPublisher() == "testPublisher4");
    XCTAssert(testConstructor4.getPageCount() == 444);
    XCTAssert(testConstructor4.printGenre() == "mystery");
    XCTAssert(testConstructor4.printPublishDate() == "Aug 13 1972");
    XCTAssert(testConstructor4.getRating() == 4);
    XCTAssert(testConstructor4.printDateRead() == "Nov 14 2019");
}

- (void)testPrintColumnHeaders {
    std::string testStr = "Author              Title                              Pages Date Read    Rating";
    
    XCTAssert(rtl::ReadBook::printCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLine {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         541   Sep 13 2019  9     ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    480   Nov 19 2019  9     ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 70212 Oct 27 2019  8     ";

    rtl::ReadBook bookMist(123, "Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "Jul 17 2006", 9, "Sep 13 2019");
    rtl::ReadBook bookGirl(123, "Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "Aug 01 2005", 9, "Nov 19 2019");
    rtl::ReadBook bookWidth(123, "Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "Jan 15 1990", 8, "Oct 27 2019");
    
    XCTAssert(bookMist.printCommandLine() == testMist);
    XCTAssert(bookGirl.printCommandLine() == testGirl);
    XCTAssert(bookWidth.printCommandLine() == testWidth);
}

@end
