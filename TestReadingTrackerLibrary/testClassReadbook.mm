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

ReadBook testReadBook;

- (void)setUp {
}

- (void)tearDown {
}

- (void)testSetReadDateTimeT {
    time_t testTimeInitial = 1199163600; //Tuesday, January 1, 2008 12:00:00 AM GMT -5
    testReadBook.setDateRead(testTimeInitial);
    XCTAssert(testTimeInitial == testReadBook.getDateReadAsTimeT());
    time_t testTime = 1199165003; //Tuesday, January 1, 2008 12:23:23 AM GMT -5
    testReadBook.setPublishDate(testTime);
    XCTAssert(testTimeInitial == testReadBook.getDateReadAsTimeT());
}

- (void)testSetReadDateString {
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
    testReadBook.setRating(-1);
    XCTAssert(1 == testReadBook.getRating());
    testReadBook.setRating(1);
    XCTAssert(1 == testReadBook.getRating());
    testReadBook.setRating(10);
    XCTAssert(10 == testReadBook.getRating());
    testReadBook.setRating(11);
    XCTAssert(10 == testReadBook.getRating());
    testReadBook.setRating('9');
    XCTAssert(9 == testReadBook.getRating());
    testReadBook.setRating('a');
    XCTAssert(9 == testReadBook.getRating());
    testReadBook.setRating("2");
    XCTAssert(2 == testReadBook.getRating());
    testReadBook.setRating("z4");
    XCTAssert(2 == testReadBook.getRating());
    testReadBook.setRating("-20");
    XCTAssert(2 == testReadBook.getRating());
}


- (void)testReadBookEquals {
    ReadBook testReadBook1;
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar 25 1993");
    
    ReadBook testReadBook2;
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
    ReadBook testReadBook1;
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar 25 1993");
    
    ReadBook testReadBook2;
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
    ReadBook testReadBook1;
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setRating(4);
    testReadBook1.setDateRead("Mar 25 1993");
    
    ReadBook testReadBook2;
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
    ReadBook testReadBook1;
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setDateRead("Mar 25 1993");
    
    ReadBook testReadBook2;
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
    ReadBook testReadBook1;
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setDateRead("Mar 25 1993");
    
    ReadBook testReadBook2;
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
    ReadBook testReadBook1;
    testReadBook1.setAuthor("a");
    testReadBook1.setTitle("a");
    testReadBook1.setSeries("a");
    testReadBook1.setPublisher("a");
    testReadBook1.setGenre("fantasy");
    testReadBook1.setPageCount(100);
    testReadBook1.setPublishDate("Dec 01 1990");
    testReadBook1.setDateRead("Mar 25 1993");
    
    ReadBook testReadBook2;
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

- (void)testConstructors {
    
    Book newBook("testAuthor", "testTitle", "testSeries", "testPublisher", 111, fantasy, 1199163600);
    ReadBook testConstructor(newBook, 9, 1199163600);
    XCTAssert("testAuthor" == testConstructor.getAuthor());
    XCTAssert("testTitle" == testConstructor.getTitle());
    XCTAssert("testSeries" == testConstructor.getSeries());
    XCTAssert("testPublisher" == testConstructor.getPublisher());
    XCTAssert(111 == testConstructor.getPageCount());
    XCTAssert(fantasy == testConstructor.getGenre());
    XCTAssert(1199163600 == testConstructor.getPublishDateAsTimeT());
    XCTAssert(9 == testConstructor.getRating());
    XCTAssert(1199163600 == testConstructor.getDateReadAsTimeT());
    
    //ReadBook(Book book, int rating, std::string dateRead);
    ReadBook testConstructor3(newBook, 1, "Feb 11 1913");
    XCTAssert("testAuthor" == testConstructor3.getAuthor());
    XCTAssert("testTitle" == testConstructor3.getTitle());
    XCTAssert("testSeries" == testConstructor3.getSeries());
    XCTAssert("testPublisher" == testConstructor3.getPublisher());
    XCTAssert(111 == testConstructor3.getPageCount());
    XCTAssert(fantasy == testConstructor3.getGenre());
    XCTAssert(1199163600 == testConstructor3.getPublishDateAsTimeT());
    XCTAssert(1 == testConstructor3.getRating());
    XCTAssert("Feb 11 1913" == testConstructor3.printDateRead());
    
    //ReadBook(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, int rating = 0, time_t time = std::time(0));
    ReadBook testConstructor2("testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 222, western, 1199181600, 8, 1199181600);
    XCTAssert("testAuthor2" == testConstructor2.getAuthor());
    XCTAssert("testTitle2" == testConstructor2.getTitle());
    XCTAssert("testSeries2" == testConstructor2.getSeries());
    XCTAssert("testPublisher2" == testConstructor2.getPublisher());
    XCTAssert(222 == testConstructor2.getPageCount());
    XCTAssert(western == testConstructor2.getGenre());
    XCTAssert(1199163600 == testConstructor2.getPublishDateAsTimeT());
    XCTAssert(8 == testConstructor2.getRating());
    XCTAssert(1199163600 == testConstructor2.getDateReadAsTimeT());
    
    //ReadBook::ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead)
    ReadBook testConstructor4("testAuthor4", "testTitle4", "testSeries4", "testPublisher4", 444, "mystery", "Aug 13 1972", 4, "Nov 14 2019");
    XCTAssert("testAuthor4" == testConstructor4.getAuthor());
    XCTAssert("testTitle4" == testConstructor4.getTitle());
    XCTAssert("testSeries4" == testConstructor4.getSeries());
    XCTAssert("testPublisher4" == testConstructor4.getPublisher());
    XCTAssert(444 == testConstructor4.getPageCount());
    XCTAssert("mystery" == testConstructor4.printGenre());
    XCTAssert("Aug 13 1972" == testConstructor4.printPublishDate());
    XCTAssert(4 == testConstructor4.getRating());
    XCTAssert("Nov 14 2019" == testConstructor4.printDateRead());
}

@end
