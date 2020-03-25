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

//TODO: better break up tests
- (void)testBookGetAndSet {
    rtl::Book testBook("testAuthor", "testTitle");
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
    rtl::Book testBook("testAuthor", "testTitle");
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
    rtl::Book testBook("testAuthor", "testTitle");
    time_t testTimeInitial = 1199163600; //Tuesday, January 1, 2008 12:00:00 AM GMT -5
    testBook.SetPublishDate(testTimeInitial);
    XCTAssert(testTimeInitial == testBook.GetPublishDateAsTimeT());
    time_t testTime = 1199165003; //Tuesday, January 1, 2008 12:23:23 AM GMT -5
    testBook.SetPublishDate(testTime);
    XCTAssert(testTimeInitial == testBook.GetPublishDateAsTimeT());
}

- (void)testSetPageCount {
    rtl::Book testBook("testAuthor", "testTitle");
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
    rtl::Book testBook("testAuthor", "testTitle");
    rtl::Genre newGenre = rtl::Genre::western;
    testBook.SetGenre(newGenre);
    XCTAssert(newGenre == testBook.GetGenre());
}

- (void)testBookEquals {
    rtl::Book testBook("testAuthor", "testTitle");
    testBook.SetSeries("testSeries");
    testBook.SetPublisher("testPublisher");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(10);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("testAuthor", "testTitle");
    testBook2.SetSeries("testSeries");
    testBook2.SetPublisher("testPublisher");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(10);
    testBook2.SetPublishDate("1990-Dec-01");
    
    XCTAssert(testBook == testBook2);
}

- (void)testBookNotEquals {
    rtl::Book testBook("testAuthor", "testTitle");
    testBook.SetSeries("testSeries");
    testBook.SetPublisher("testPublisher");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(10);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("testAuthor2", "testTitle2");
    testBook2.SetSeries("testSeries2");
    testBook2.SetPublisher("testPublisher2");
    testBook2.SetGenre("western");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook != testBook2);
}

- (void)testBookLessThan {
    rtl::Book testBook("a", "a");
    testBook.SetSeries("a");
    testBook.SetPublisher("a");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(100);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("b", "b");
    testBook2.SetSeries("b");
    testBook2.SetPublisher("a");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook < testBook2);

    rtl::Book testBook3("a", "b");
    testBook3.SetSeries("b");
    testBook3.SetPublisher("a");
    testBook3.SetGenre("fantasy");
    testBook3.SetPageCount(100);
    testBook3.SetPublishDate("1991-Dec-01");
    XCTAssert(testBook < testBook3);
    
    testBook3.SetSeries("a");
    XCTAssert(testBook < testBook3);
    
    testBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook < testBook3);
    
    rtl::Book testBook4("a", "a");
    testBook4.SetSeries("a");
    testBook4.SetPublisher("a");
    testBook4.SetPublishDate("1990-Dec-01");
    testBook4.SetGenre("western");
    testBook4.SetPageCount(110);
    XCTAssert(!(testBook < testBook4));
}

- (void)testBookLessEqualsThan {
    rtl::Book testBook("a", "a");
    testBook.SetSeries("a");
    testBook.SetPublisher("a");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(100);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("b", "b");
    testBook2.SetSeries("b");
    testBook2.SetPublisher("a");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook <= testBook2);

    rtl::Book testBook3("b", "b");
    testBook3.SetSeries("b");
    testBook3.SetPublisher("a");
    testBook3.SetGenre("fantasy");
    testBook3.SetPageCount(100);
    testBook3.SetPublishDate("1991-Dec-01");
    XCTAssert(testBook <= testBook3);
    
    testBook3.SetSeries("a");
    XCTAssert(testBook <= testBook3);
    
    testBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook <= testBook3);
    
    rtl::Book testBook4("a", "a");
    testBook4.SetSeries("a");
    testBook4.SetPublisher("a");
    testBook4.SetPublishDate("1990-Dec-01");
    testBook4.SetGenre("western");
    testBook4.SetPageCount(110);
    XCTAssert(testBook <= testBook4);
}

- (void)testBookGreaterThan {
    rtl::Book testBook("a", "a");
    testBook.SetSeries("a");
    testBook.SetPublisher("a");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(100);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("b", "b");
    testBook2.SetSeries("b");
    testBook2.SetPublisher("a");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook2 > testBook);

    rtl::Book testBook3("a", "b");
    testBook3.SetSeries("b");
    testBook3.SetPublisher("a");
    testBook3.SetGenre("fantasy");
    testBook3.SetPageCount(100);
    testBook3.SetPublishDate("1991-Dec-01");
    XCTAssert(testBook3 > testBook);
    
    testBook3.SetSeries("a");
    XCTAssert(testBook3 > testBook);
    
    testBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook3 > testBook);
    
    rtl::Book testBook4("a", "a");
    testBook4.SetSeries("a");
    testBook4.SetPublisher("a");
    testBook4.SetGenre("fantasy");
    testBook4.SetPageCount(100);
    testBook4.SetPublishDate("1990-Dec-01");
    testBook4.SetGenre("western");
    testBook4.SetPageCount(110);
    XCTAssert(!(testBook4 > testBook));
}

- (void)testBookGreaterEqualsThan {
    rtl::Book testBook("a", "a");
    testBook.SetSeries("a");
    testBook.SetPublisher("a");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(100);
    testBook.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("b", "b");
    testBook2.SetSeries("b");
    testBook2.SetPublisher("a");
    testBook2.SetGenre("fantasy");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    XCTAssert(testBook2 >= testBook);

    rtl::Book testBook3("a", "b");
    testBook3.SetSeries("b");
    testBook3.SetPublisher("a");
    testBook3.SetGenre("fantasy");
    testBook3.SetPageCount(100);
    testBook3.SetPublishDate("1991-Dec-01");
    XCTAssert(testBook3 >= testBook);
    
    testBook3.SetSeries("a");
    XCTAssert(testBook3 >= testBook);
    
    testBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook3 >= testBook);
    
    rtl::Book testBook4("a", "a");
    testBook4.SetSeries("a");
    testBook4.SetPublisher("a");
    testBook4.SetPublishDate("1990-Dec-01");
    testBook4.SetGenre("western");
    testBook4.SetPageCount(110);
    XCTAssert(testBook2 >= testBook);
}

- (void)testPrintGenre {
    rtl::Book testBook("testAuthor", "testTitle");
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
    testBook.SetGenre("technical");
    XCTAssert(testBook.PrintGenre() == "technical");
    testBook.SetGenre("nonfiction");
    XCTAssert(testBook.PrintGenre() == "non-fiction");
    testBook.SetGenre("non-fiction");
    XCTAssert(testBook.PrintGenre() == "non-fiction");
    testBook.SetGenre("pickle");
    XCTAssert(testBook.PrintGenre() == "genre not set");
}

- (void)testBookConstructor {
    //Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, time_t publishDate = std::time(0));
    rtl::Book testBookConstructor("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::Genre::romance, 1199163600);
    XCTAssert(testBookConstructor.GetAuthor() == "testAuthor");
    XCTAssert(testBookConstructor.GetTitle() == "testTitle");
    XCTAssert(testBookConstructor.GetSeries() == "testSeries");
    XCTAssert(testBookConstructor.GetPublisher() == "testPublisher");
    XCTAssert(testBookConstructor.GetPageCount() == 1111);
    XCTAssert(testBookConstructor.GetGenre() == rtl::Genre::romance);
    XCTAssert(testBookConstructor.GetPublishDateAsTimeT() == 1199163600);
    XCTAssert(testBookConstructor.GetBookId() == "2ff6b24");
    XCTAssert(testBookConstructor.GetAuthorId() == "1ecb");
    
    //Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate);
    rtl::Book testBookConstructor2("testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 2222, "thriller", "1991-Nov-16");
    XCTAssert(testBookConstructor2.GetAuthor() == "testAuthor2");
    XCTAssert(testBookConstructor2.GetTitle() == "testTitle2");
    XCTAssert(testBookConstructor2.GetSeries() == "testSeries2");
    XCTAssert(testBookConstructor2.GetPublisher() == "testPublisher2");
    XCTAssert(testBookConstructor2.GetPageCount() == 2222);
    XCTAssert(testBookConstructor2.GetGenre() == rtl::Genre::thriller);
    XCTAssert(testBookConstructor2.PrintPublishDate() == "1991-Nov-16");
    XCTAssert(testBookConstructor2.GetBookId() == "42b3e88");
    XCTAssert(testBookConstructor2.GetAuthorId() == "2404");
    
    //Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate);
    rtl::Book testBookConstructor3("testAuthor3", "testTitle3", "testSeries3", "testPublisher3", 333, rtl::Genre::scienceFiction, "1995-Oct-03");
    XCTAssert(testBookConstructor3.GetAuthor() == "testAuthor3");
    XCTAssert(testBookConstructor3.GetTitle() == "testTitle3");
    XCTAssert(testBookConstructor3.GetSeries() == "testSeries3");
    XCTAssert(testBookConstructor3.GetPublisher() == "testPublisher3");
    XCTAssert(testBookConstructor3.GetPageCount() == 333);
    XCTAssert(testBookConstructor3.GetGenre() == rtl::Genre::scienceFiction);
    XCTAssert(testBookConstructor3.PrintPublishDate() == "1995-Oct-03");
    XCTAssert(testBookConstructor3.GetBookId() == "42ded14");
    XCTAssert(testBookConstructor3.GetAuthorId() == "240f");
    
    //rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::string isbn, std::string oclc)
    rtl::Book testBookConstructor4("testAuthor4", "testTitle4", "testSeries4", "testPublisher4", 4444, "fantasy", "1969-Oct-31", std::vector<std::string>{"1234567890", "1234567890abc"}, std::vector<std::string>{"123456"});
    XCTAssert(testBookConstructor4.GetAuthor() == "testAuthor4");
    XCTAssert(testBookConstructor4.GetTitle() == "testTitle4");
    XCTAssert(testBookConstructor4.GetSeries() == "testSeries4");
    XCTAssert(testBookConstructor4.GetPublisher() == "testPublisher4");
    XCTAssert(testBookConstructor4.GetPageCount() == 4444);
    XCTAssert(testBookConstructor4.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testBookConstructor4.PrintPublishDate() == "1969-Oct-31");
    XCTAssert(testBookConstructor4.GetIsbn().size() == 2);
    XCTAssert(testBookConstructor4.GetIsbn().at(0) == "1234567890");
    XCTAssert(testBookConstructor4.GetIsbn().at(1) == "1234567890abc");
    XCTAssert(testBookConstructor4.GetOclc().size() == 1);
    XCTAssert(testBookConstructor4.GetOclc().at(0) == "123456");
    XCTAssert(testBookConstructor4.GetAuthorId() == "241a");
}

- (void)testAddandGetOclc {
    rtl::Book testBook("testAuthor", "testTitle");
    std::string testString = "1234";
                              
    testBook.AddOclc(testString);
    
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == testString);
}

- (void)testAddandGetIsbn {
    rtl::Book testBook("testAuthor", "testTitle");
    std::string testString = "1234567890";
    std::string testString2 = "123-4567-890-12";
    std::string answerString2 = "123456789012";
    
    testBook.AddIsbn(testString);
    
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == testString);
    
    testBook.AddIsbn("asdgbadf213");
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == testString);
    
    testBook.AddIsbn(testString2);
    XCTAssert(testBook.GetIsbn().size() == 2);
    XCTAssert(testBook.GetIsbn().at(0) == testString);
    XCTAssert(testBook.GetIsbn().at(1) == answerString2);
}

- (void)testPrintColumnHeader {
    std::string testStr = "Author              Title                            Series             Pages";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.PrintHeader() == testStr);
}

- (void)testPrintCommandLineSimpleBook {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire       Mistborn           541  ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo  Millennium         480  ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World123456789012 The Wheel of Time1 70212";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15");
    
    XCTAssert(bookMist.PrintSimple() == testMist);
    XCTAssert(bookGirl.PrintSimple() == testGirl);
    XCTAssert(bookWidth.PrintSimple() == testWidth);
}

- (void)testPrintCommandLineDetailedBook {
    std::string testMist = "Title:         Mistborn: The Final Empire                                       \nBookId:        1c5fdaf7109aa47ef2                                               \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2006-Jul-17                                                      \nISBN:          9780765311788                                                    \nOCLC:          62342185                                                         \n";
    std::string testGirl = "Title:         The Girl with the Dragon Tattoo                                  \nBookId:        2c844f9a4aac31a8848f80                                           \nAuthor Name:   Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nSeries:        Millennium                                                       \nGenre:         thriller                                                         \nPage Count:    480                                                              \nPublisher:     Norstedts Förlag                                                \nPublish Date:  2005-Aug-01                                                      \nISBN:          9781847242532                                                    \nOCLC:          186764078                                                        \n";
    std::string testWidth = "Title:         The Eye of the World123456789012345678901234567890123456789012345\nBookId:        cfcbb4cef513c9c904bf8                                            \nAuthor Name:   Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nSeries:        The Wheel of Time123456789012345678901234567890123456789012345678\nGenre:         fantasy                                                          \nPage Count:    70212                                                            \nPublisher:     Tor Books12345678901234567890123456789012345678901234567890123456\nPublish Date:  1990-Jan-15                                                      \nISBN:          19723327, 1234567890, 1234567890, 1234567890, 1234567890, 1234567\nOCLC:          0312850093, 1234567890, 1234567890, 1234567890, 1234567890, 12345\n";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", std::vector<std::string> {"9780765311788"}, std::vector<std::string> {"62342185"});
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", std::vector<std::string> {"9781847242532"}, std::vector<std::string> {"186764078"});
    rtl::Book bookWidth("Robert Jordan123456789012345678901234567890123456789012345678901234567890", "The Eye of the World12345678901234567890123456789012345678901234567890", "The Wheel of Time12345678901234567890123456789012345678901234567890", "Tor Books123456789012345678901234567890123456789012345678901234567890", 70212, "fantasy", "1990-Jan-15", std::vector<std::string> {"19723327", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"}, std::vector<std::string> {"0312850093", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"});
    
    XCTAssert(bookMist.PrintDetailed() == testMist);
    XCTAssert(bookGirl.PrintDetailed() == testGirl);
    XCTAssert(bookWidth.PrintDetailed() == testWidth);
}

- (void)testPrintJson {
    rtl::Book testBook("testAuthor", "testTitle");
    testBook.AddIsbn("1234567890");
    testBook.AddIsbn("123-45678-90-12");
    testBook.AddOclc("123456");
    testBook.SetSeries("testSeries");
    testBook.SetPublisher("testPublisher");
    testBook.SetGenre("fantasy");
    testBook.SetPageCount(10);
    testBook.SetPublishDate("1990-Dec-01");
    
    std::string answer = R"({"bookId":"2ff6b24","isbn":["1234567890","123456789012"],"oclc":["123456"],"author":"testAuthor","authorId":"1ecb","title":"testTitle","series":"testSeries","publisher":"testPublisher","genre":"fantasy","pageCount":10,"publishDate":"1990-Dec-01"})";
    XCTAssert(testBook.PrintJson() == answer);
}

@end
