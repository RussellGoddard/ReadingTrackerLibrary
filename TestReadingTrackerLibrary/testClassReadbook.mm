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

- (void)test_SetDateRead_PassPosixTime_GetPassedPosixTime {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testReadBook.SetDateRead(boost::date_time::min_date_time));
    XCTAssert(testReadBook.GetDateReadAsPosixTime() == boost::date_time::min_date_time);
}

- (void)test_SetReadDate_PassStringSpaceDelim_PrintPassedDate {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testReadBook.SetDateRead("2008 1 01"));
    XCTAssert(testReadBook.PrintDateRead() == "2008-Jan-01");
}

- (void)test_SetReadDate_PassStringHyphenDelim_PrintPassedDate {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testReadBook.SetDateRead("2001-Feb-28"));
    XCTAssert(testReadBook.PrintDateRead() == "2001-Feb-28");
}

- (void)test_SetReadDate_PassLeapYearFeb29_PrintPassedDate {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testReadBook.SetDateRead("2008-Feb-29"));
    XCTAssert(testReadBook.PrintDateRead() == "2008-Feb-29");
}

- (void)test_SetReadDate_PassDateBefore1900_PrintPassedDate {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testReadBook.SetDateRead("1890-Dec-01"));
    XCTAssert(testReadBook.PrintDateRead() == "1890-Dec-01");
}

- (void)test_SetReadDate_PassInvalidFormatDate_ReturnFalse {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testReadBook.SetDateRead("Dec-ab-1980"));
}

- (void)test_SetReadDate_PassEmptyString_ReturnFalse {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testReadBook.SetDateRead(""));
}

- (void)test_SetReadDate_PassNotLeapYearFeb29_ReturnFalse {
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testReadBook.SetDateRead("2001-Feb-29"));
}

- (void)test_SetRating_PassIntLessThanZero_ReturnFalse {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testRating.SetRating(-1));
}

- (void)test_SetRating_PassInt1_GetInt1 {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testRating.SetRating(1));
    XCTAssert(testRating.GetRating() == 1);
}

- (void)test_SetRating_PassInt10_GetInt10 {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testRating.SetRating(10));
    XCTAssert(testRating.GetRating() == 10);
}

- (void)test_SetRating_PassValueGreaterThan10_ReturnFalse {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testRating.SetRating(11));
}

- (void)test_SetRating_PassChar9_GetInt9 {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(testRating.SetRating('9'));
    XCTAssert(testRating.GetRating() == 9);
}

- (void)test_SetRating_PassInvalidChar_ReturnFalse {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testRating.SetRating('a'));
}

- (void)test_SetRating_PassString2_GetInt2 {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");\
    XCTAssert(testRating.SetRating("2"));
    XCTAssert(testRating.GetRating() == 2);
}

- (void)test_SetRating_PassInvalidString_ReturnFalse {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testRating.SetRating("z4"));
}

- (void)test_SetRating_PassStringLessThanOne_ReturnFalse {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testRating.SetRating("-20"));
}

- (void)test_SetRating_PassStringGreaterThanTen_ReturnFalse {
    rtl::ReadBook testRating(testReaderId, "testAuthor", "testTitle");
    XCTAssert(!testRating.SetRating("12"));
}


- (void)test_ReadBookOperatorEquals_ReturnTrue {
    rtl::ReadBook testReadBook1(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 100, "fantasy", "1990-Dec-01", 4, "1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 100, "fantasy", "1990-Dec-01", 4, "1993-Mar-25");
    
    XCTAssert(testReadBook1 == testReadBook2);
}

- (void)test_ReadBookOperatorNotEquals_ReturnTrue {
    rtl::ReadBook testReadBook1(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 100, "fantasy", "1990-Dec-01", 4, "1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "authorB", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook1 != testReadBook2);
}

- (void)test_ReadBookOperatorLessThan_ReturnTrue {
    rtl::ReadBook testReadBook1(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 100, "fantasy", "1990-Dec-01", 4, "1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "authorB", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook1 < testReadBook2);

    rtl::ReadBook testReadBook3(testReaderId, "authorA", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook1 < testReadBook2);
    
    XCTAssert(testReadBook3.SetSeries("seriesA"));
    XCTAssert(testReadBook1 < testReadBook3);
    
    XCTAssert(testReadBook3.SetPublishDate("1990-Dec-01"));
    XCTAssert(testReadBook1 < testReadBook3);
    
    rtl::ReadBook testReadBook4(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 110, "western", "1990-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook1 < testReadBook4);
    
    XCTAssert(testReadBook4.SetDateRead("1993-Mar-25"));
    XCTAssert(!(testReadBook4 < testReadBook1));
}

- (void)test_ReadBookOperatorLessThanEquals_ReturnTrue {
    rtl::ReadBook testReadBook1(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 100, "fantasy", "1990-Dec-01", 4, "1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "authorB", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook1 <= testReadBook2);

    rtl::ReadBook testReadBook3(testReaderId, "authorA", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook1 <= testReadBook3);
    
    XCTAssert(testReadBook3.SetSeries("seriesA"));
    XCTAssert(testReadBook1 <= testReadBook3);
    
    XCTAssert(testReadBook3.SetPublishDate("1990-Dec-01"));
    XCTAssert(testReadBook1 <= testReadBook3);
    
    rtl::ReadBook testReadBook4(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 110, "western", "1990-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook1 <= testReadBook4);
    
    XCTAssert(testReadBook4.SetDateRead("1993-Mar-25"));
    XCTAssert(testReadBook4 <= testReadBook1);
}

- (void)test_ReadBookOperatorGreaterThan_ReturnTrue {
    rtl::ReadBook testReadBook1(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 100, "fantasy", "1990-Dec-01", 4, "1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "authorB", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook2 > testReadBook1);

    rtl::ReadBook testReadBook3(testReaderId, "authorA", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook3 > testReadBook1);
    
    XCTAssert(testReadBook3.SetSeries("seriesA"));
    XCTAssert(testReadBook3 > testReadBook1);
    
    XCTAssert(testReadBook3.SetPublishDate("1990-Dec-01"));
    XCTAssert(testReadBook3 > testReadBook1);
    
    rtl::ReadBook testReadBook4(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 110, "western", "1990-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook4 > testReadBook1);
    
    XCTAssert(testReadBook4.SetDateRead("1993-Mar-25"));
    XCTAssert(!(testReadBook1 > testReadBook4));
}

- (void)test_ReadBookOperatorGreaterThanEquals_ReturnTrue {
    rtl::ReadBook testReadBook1(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 100, "fantasy", "1990-Dec-01", 4, "1993-Mar-25");
    
    rtl::ReadBook testReadBook2(testReaderId, "authorB", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook2 >= testReadBook1);

    rtl::ReadBook testReadBook3(testReaderId, "authorA", "titleB", "seriesB", "publisherA", 100, "fantasy", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook3 >= testReadBook1);
    
    testReadBook3.SetSeries("seriesA");
    XCTAssert(testReadBook3 >= testReadBook1);
    
    testReadBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testReadBook3 >= testReadBook1);
    
    rtl::ReadBook testReadBook4(testReaderId, "authorA", "titleA", "seriesA", "publisherA", 110, "western", "1991-Dec-01", 5, "1993-Mar-26");
    XCTAssert(testReadBook4 >= testReadBook1);
    
    testReadBook4.SetDateRead("1993-Mar-25");
    XCTAssert(testReadBook4 >= testReadBook1);
}

- (void)test_Constructor1 {
    rtl::Book newBook("testAuthor", "testTitle", "testSeries", "testPublisher", 111, rtl::Genre::fantasy, boost::date_time::min_date_time);
    rtl::ReadBook testConstructor(2147483647, newBook, 9, boost::date_time::min_date_time);
    XCTAssert(testConstructor.GetReaderId() == 2147483647);
    XCTAssert(testConstructor.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testConstructor.GetTitle() == "testTitle");
    XCTAssert(testConstructor.GetSeries() == "testSeries");
    XCTAssert(testConstructor.GetPublisher() == "testPublisher");
    XCTAssert(testConstructor.GetPageCount() == 111);
    XCTAssert(testConstructor.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testConstructor.GetPublishDateAsPosixTime() == boost::date_time::min_date_time);
    XCTAssert(testConstructor.GetRating() == 9);
    XCTAssert(testConstructor.GetDateReadAsPosixTime() == boost::date_time::min_date_time);
    XCTAssert(testConstructor.GetBookId() == "2ff6b24");
}

- (void)test_Constructor2 {
    rtl::Book newBook("testAuthor", "testTitle", "testSeries", "testPublisher", 111, rtl::Genre::fantasy, boost::date_time::min_date_time);
    rtl::ReadBook testConstructor3(456, newBook, 1, "1913-Feb-11");
    XCTAssert(testConstructor3.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testConstructor3.GetTitle() == "testTitle");
    XCTAssert(testConstructor3.GetSeries() == "testSeries");
    XCTAssert(testConstructor3.GetPublisher() == "testPublisher");
    XCTAssert(testConstructor3.GetPageCount() == 111);
    XCTAssert(testConstructor3.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testConstructor3.GetPublishDateAsPosixTime() == boost::date_time::min_date_time);
    XCTAssert(testConstructor3.GetRating() == 1);
    XCTAssert(testConstructor3.PrintDateRead() == "1913-Feb-11" );
    XCTAssert(testConstructor3.GetBookId() == "2ff6b24");
}

- (void)test_ConstructorDefault {
    rtl::ReadBook testConstructor2(789, "testAuthor2", "testTitle2", "testSeries2", "testPublisher2", 222, rtl::Genre::western, boost::date_time::min_date_time, 8, boost::date_time::min_date_time);
    XCTAssert(testConstructor2.GetAuthors().at(0) == "testAuthor2");
    XCTAssert(testConstructor2.GetTitle() == "testTitle2");
    XCTAssert(testConstructor2.GetSeries() == "testSeries2");
    XCTAssert(testConstructor2.GetPublisher() == "testPublisher2");
    XCTAssert(testConstructor2.GetPageCount() == 222);
    XCTAssert(testConstructor2.GetGenre() == rtl::Genre::western);
    XCTAssert(testConstructor2.GetPublishDateAsPosixTime() == boost::date_time::min_date_time);
    XCTAssert(testConstructor2.GetRating() == 8);
    XCTAssert(testConstructor2.GetDateReadAsPosixTime() == boost::date_time::min_date_time);
    XCTAssert(testConstructor2.GetBookId() == "42b3e88");
}

- (void)test_Constructor4 {
    rtl::ReadBook testConstructor4(-1234567890, "testAuthor4", "testTitle4", "testSeries4", "testPublisher4", 444, "mystery", "1972-Aug-13", 4, "2019-Nov-14");
    XCTAssert(testConstructor4.GetAuthors().at(0) == "testAuthor4");
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

- (void)test_PrintHeader {
    std::string testStr = "Author              Title                             Pages Date Read    Rate";
    
    rtl::ReadBook testReadBook(testReaderId, "testAuthor", "testTitle");
    
    XCTAssert(testReadBook.PrintHeader() == testStr);
}

- (void)test_PrintSimple {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire        541   2019-Sep-13  9   ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo   480   2019-Nov-19  9   ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World1234567890123 70212 2019-Oct-27  8   ";

    rtl::ReadBook bookMist(123, "Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", 9, "2019-Sep-13");
    rtl::ReadBook bookGirl(123, "Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", 9, "2019-Nov-19");
    rtl::ReadBook bookWidth(123, "Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15", 8, "2019-Oct-27");
    
    XCTAssert(bookMist.PrintSimple() == testMist);
    XCTAssert(bookGirl.PrintSimple() == testGirl);
    XCTAssert(bookWidth.PrintSimple() == testWidth);
}

- (void)test_PrintDetailed {
    std::string testMist = "Title:         Mistborn: The Final Empire                                       \nBookId:        1c5fdaf7109aa47ef2                                               \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2006-Jul-17                                                      \nISBN:          9780765311788                                                    \nOCLC:          62342185                                                         \nReader ID:     123                                                              \nRating:        9                                                                \nDate Read:     2019-Sep-13                                                      \n";
    std::string testGirl = "Title:         The Girl with the Dragon Tattoo                                  \nBookId:        2c844f9a4aac31a8848f80                                           \nAuthor Name:   Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nSeries:        Millennium                                                       \nGenre:         thriller                                                         \nPage Count:    480                                                              \nPublisher:     Norstedts Förlag                                                \nPublish Date:  2005-Aug-01                                                      \nISBN:          9781847242532                                                    \nOCLC:          186764078                                                        \nReader ID:     123                                                              \nRating:        9                                                                \nDate Read:     2019-Nov-19                                                      \n";
    std::string testWidth = "Title:         The Eye of the World123456789012345678901234567890123456789012345\nBookId:        cfcbb4cef513c9c904bf8                                            \nAuthor Name:   Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nSeries:        The Wheel of Time123456789012345678901234567890123456789012345678\nGenre:         fantasy                                                          \nPage Count:    70212                                                            \nPublisher:     Tor Books12345678901234567890123456789012345678901234567890123456\nPublish Date:  1990-Jan-15                                                      \nISBN:          19723327, 1234567890, 1234567890, 1234567890, 1234567890, 1234567\nOCLC:          0312850093, 1234567890, 1234567890, 1234567890, 1234567890, 12345\nReader ID:     123                                                              \nRating:        8                                                                \nDate Read:     2019-Oct-27                                                      \n";
    
    rtl::Book bookMist({"Brandon Sanderson"}, "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", std::vector<std::string> {"9780765311788"}, std::vector<std::string> {"62342185"});
    rtl::Book bookGirl({"Stieg Larsson"}, "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", std::vector<std::string> {"9781847242532"}, std::vector<std::string> {"186764078"});
    rtl::Book bookWidth({"Robert Jordan123456789012345678901234567890123456789012345678901234567890"}, "The Eye of the World12345678901234567890123456789012345678901234567890", "The Wheel of Time12345678901234567890123456789012345678901234567890", "Tor Books123456789012345678901234567890123456789012345678901234567890", 70212, "fantasy", "1990-Jan-15", std::vector<std::string> {"19723327", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"}, std::vector<std::string> {"0312850093", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"});
    
    rtl::ReadBook readBookMist(123, bookMist, 9, "2019-Sep-13");
    rtl::ReadBook readBookGirl(123, bookGirl, 9, "2019-Nov-19");
    rtl::ReadBook readBookWidth(123, bookWidth, 8, "2019-Oct-27");
    
    XCTAssert(readBookMist.PrintDetailed() == testMist);
    XCTAssert(readBookGirl.PrintDetailed() == testGirl);
    XCTAssert(readBookWidth.PrintDetailed() == testWidth);
}

- (void)test_PrintJson {
    rtl::ReadBook testReadBook1(1, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetDateRead("1993-Mar-25");
    testReadBook1.SetRating(4);
    
    std::string jsonString = R"({"bookId":"1bba","isbn":[],"oclc":[],"author":["a"],"authorId":["4e"],"title":"a","series":"a","publisher":"a","genre":"fantasy","pageCount":100,"publishDate":"1990-Dec-01","rating":4,"dateRead":"1993-Mar-25","readerId":1})";
    
    XCTAssert(testReadBook1.PrintJson() == jsonString);
}

- (void)test_GetUpdateFunction_PassStringRating_ReturnPointerToSetRating {
    rtl::ReadBook testReadBook(123, "testAuthor", "testTitle");
    
    rtl::SetsPtr returnFunction = testReadBook.GetUpdateFunction("Rating");
    
    XCTAssert(returnFunction == static_cast<rtl::SetsPtr>(&rtl::ReadBook::SetRating));
    
    XCTAssert(std::invoke(returnFunction, testReadBook, "9"));
    XCTAssert(testReadBook.GetRating() == 9);
}

- (void)test_GetUpdateFunction_PassStringDateRead_ReturnPointerToSetDateRead {
    rtl::ReadBook testReadBook(123, "testAuthor", "testTitle");
    
    rtl::SetsPtr returnFunction = testReadBook.GetUpdateFunction("Date Read");
    
    XCTAssert(returnFunction == static_cast<rtl::SetsPtr>(&rtl::ReadBook::SetDateRead));
    
    XCTAssert(std::invoke(returnFunction, testReadBook, "2020-Apr-16"));
    XCTAssert(testReadBook.PrintDateRead() == "2020-Apr-16");
}

@end
