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

- (void)test_GetAuthor_ReturnInitializedAuthor {
    std::string author = "testAuthor";
    rtl::Book testBook(author, "testTitle");
    
    XCTAssert(testBook.GetAuthors().size() == 1);
    XCTAssert(testBook.GetAuthors().at(0) == author);
}

- (void)test_GetTitle_ReturnInitializedTitle {
    std::string title = "testTitle";
    rtl::Book testBook("testAuthor", title);
    
    XCTAssert(testBook.GetTitle() == title);
}

- (void)test_SetAndGetSeries_ReturnPassedString {
    std::string series = "testSeries";
    rtl::Book testBook("testAuthor", "testTitle");
    
    //SetSeries returns a bool based on success
    XCTAssert(testBook.SetSeries(series));
    
    XCTAssert(testBook.GetSeries() == series);
}

- (void)test_SetAndGetPublisher_ReturnPassedString {
    std::string publisher = "testPublisher";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetPublisher(publisher) == true);
    
    XCTAssert(testBook.GetPublisher() == publisher);
}

- (void)test_SetAndGetPageCountInt_ReturnInt {
    int pageCount = 1;
    rtl::Book testBook("testAuthor", "testTitle");
    
    //SetPageCount returns a bool based on success
    XCTAssert(testBook.SetPageCount(pageCount));
    
    XCTAssert(testBook.GetPageCount() == pageCount);
}

- (void)test_SetPageCountInt_PassNegativeInt_ReturnFalse {
    int pageCount = -1;
    rtl::Book testBook("testAuthor", "testTitle");
    
    //SetPageCount returns a bool based on success
    XCTAssert(!testBook.SetPageCount(pageCount));
}

- (void)test_SetAndGetPageCountChar_ReturnInt {
    char pageCount = '9';
    rtl::Book testBook("testAuthor", "testTitle");
    
    //SetPageCount returns a bool based on success
    XCTAssert(testBook.SetPageCount(pageCount));
    
    XCTAssert(testBook.GetPageCount() == 9);
}

- (void)test_SetPageCountChar_PassAlpha_ReturnFalse {
    char pageCount = 'a';
    rtl::Book testBook("testAuthor", "testTitle");
    
    //SetPageCount returns a bool based on success
    XCTAssert(!testBook.SetPageCount(pageCount));
}

- (void)test_SetPageCountString_ReturnInt {
    std::string pageCount = "100";
    rtl::Book testBook("testAuthor", "testTitle");
    
    //SetPageCount returns a bool based on success
    XCTAssert(testBook.SetPageCount(pageCount));
    
    XCTAssert(testBook.GetPageCount() == 100);
}

- (void)test_SetPageCountString_PassNegativeNumber_ReturnFalse {
    std::string pageCount = "-10";
    rtl::Book testBook("testAuthor", "testTitle");
    
    //SetPageCount returns a bool based on success
    XCTAssert(!testBook.SetPageCount(pageCount));
}

- (void)test_SetPageCountString_PassAlpha_ReturnFalse {
    std::string pageCount = "abc";
    rtl::Book testBook("testAuthor", "testTitle");
    
    //SetPageCount returns a bool based on success
    XCTAssert(!testBook.SetPageCount(pageCount));
}

- (void)test_SetAndGetGenre_ReturnPassedGenre {
    rtl::Book testBook("testAuthor", "testTitle");
    rtl::Genre newGenre = rtl::Genre::western;
    XCTAssert(testBook.SetGenre(newGenre));
    XCTAssert(testBook.GetGenre() == newGenre);
}

- (void)test_SetGenreString_ReturnPassedGenreAsString {
    rtl::Book testBook("testAuthor", "testTitle");
    std::string newGenre = "western";
    XCTAssert(testBook.SetGenre(newGenre));
    XCTAssert(testBook.PrintGenre() == newGenre);
}

- (void)test_SetGenreString_PassInvalidGenre_ReturnFalse {
    rtl::Book testBook("testAuthor", "testTitle");
    std::string newGenre = "asdasdasdf";
    XCTAssert(!testBook.SetGenre(newGenre));
}

- (void)test_SetAndGetPublishDate_PassYYYYMMDD_ReturnYYYYMMMDD {
    rtl::Book testBook("testAuthor", "testTitle");
    XCTAssert(testBook.SetPublishDate("1990-12-01"));
    XCTAssert(testBook.PrintPublishDate() == "1990-Dec-01");
}

- (void)test_SetPublishDate_PassSpaceAsDelim_ReturnYYYYMMMDD {
    rtl::Book testBook("testAuthor", "testTitle");
    XCTAssert(testBook.SetPublishDate("2008 1 01"));
    XCTAssert(testBook.PrintPublishDate() == "2008-Jan-01");
}

- (void)test_SetPublishDate_PassInvalidCharacters_ReturnFaslse {
    rtl::Book testBook("testAuthor", "testTitle");
    XCTAssert(!testBook.SetPublishDate("1980-Dec-ab"));
}

- (void)test_SetPublishDate_PassInvalidDate_ReturnFalse {
    rtl::Book testBook("testAuthor", "testTitle");
    XCTAssert(!testBook.SetPublishDate("2001-Feb-29"));
}

- (void)test_SetPublishDate_PassPosixTime_ReturnPosixTime {
    rtl::Book testBook("testAuthor", "testTitle");
    XCTAssert(testBook.SetPublishDate(boost::date_time::min_date_time));
    XCTAssert(testBook.GetPublishDateAsPosixTime() == boost::posix_time::ptime(boost::date_time::min_date_time));
}

- (void)test_OperatorEquals {
    rtl::Book testBook({"testAuthor", "testAuthor2"}, "testTitle", "testSeries", "testPublisher", 10, rtl::Genre::fantasy, "1990-Dec-01");
    
    rtl::Book testBook2({"testAuthor", "testAuthor2"}, "testTitle", "testSeries", "testPublisher", 10, rtl::Genre::fantasy, "1990-Dec-01");
    
    XCTAssert(testBook == testBook2);
}

- (void)test_OperatorNotEquals {
    rtl::Book testBook({"testAuthor"}, "testTitle", "testSeries", "testPublisher", 10, rtl::Genre::fantasy, "1990-Dec-01");
    
    rtl::Book testBook2({"testAuthor2"}, "testTitle2", "testSeries2", "testPublisher2", 100, rtl::Genre::western, "1991-Dec-01");
    
    XCTAssert(testBook != testBook2);
}

- (void)test_OperatorLessThan {
    rtl::Book testBook("authorA", "titleA", "seriesA", "publisherA", 100, rtl::Genre::fantasy, "1990-Dec-01");
    
    rtl::Book testBook2("authorB", "titleB", "seriesB", "publisherA", 100, rtl::Genre::fantasy, "1990-Dec-01");
    
    XCTAssert(testBook < testBook2);

    rtl::Book testBook3("authorA", "titleB", "seriesB", "publisherA", 100, rtl::Genre::fantasy, "1991-Dec-01");
    XCTAssert(testBook < testBook3);
    
    testBook3.SetSeries("seriesA");
    XCTAssert(testBook < testBook3);
    
    testBook3.SetPublishDate("1990-Dec-01");
    XCTAssert(testBook < testBook3);
    
    rtl::Book testBook4("authorA", "titleA", "seriesA", "publisherA", 110, rtl::Genre::western, "1990-Dec-01");
    XCTAssert(!(testBook < testBook4));
}

- (void)test_OperatorLessThanOrEquals {
    rtl::Book testBook("authorA", "titleA", "seriesA", "publisherA", 100, rtl::Genre::fantasy, "1990-Dec-01");
    
    rtl::Book testBook2("authorB", "titleB", "seriesB", "publisherA", 100, rtl::Genre::fantasy, "1991-Dec-01");
    XCTAssert(testBook <= testBook2);

    rtl::Book testBook3("authorB", "titleB", "seriesB", "publisherA", 100, rtl::Genre::fantasy, "1991-Dec-01");
    XCTAssert(testBook <= testBook3);
    
    XCTAssert(testBook3.SetSeries("seriesA"));
    XCTAssert(testBook <= testBook3);
    
    XCTAssert(testBook3.SetPublishDate("1990-Dec-01"));
    XCTAssert(testBook <= testBook3);
    
    rtl::Book testBook4("authorA", "titleA", "seriesA", "publisherA", 110, rtl::Genre::western, "1990-Dec-01");
    XCTAssert(testBook <= testBook4);
}

- (void)test_OperatorGreaterThan {
    rtl::Book testBook("authorA", "titleA", "seriesA", "publisherA", 100, rtl::Genre::fantasy, "1990-Dec-01");
    
    rtl::Book testBook2("authorB", "titleB", "seriesB", "publisherA", 100, rtl::Genre::fantasy, "1991-Dec-01");
    XCTAssert(testBook2 > testBook);

    rtl::Book testBook3("authorA", "titleB", "seriesB", "publisherA", 100, rtl::Genre::fantasy, "1991-Dec-01");
    XCTAssert(testBook3 > testBook);
    
    XCTAssert(testBook3.SetSeries("seriesA"));
    XCTAssert(testBook3 > testBook);
    
    XCTAssert(testBook3.SetPublishDate("1990-Dec-01"));
    XCTAssert(testBook3 > testBook);
    
    rtl::Book testBook4("authorA", "titleA", "seriesA", "publisherA", 100, rtl::Genre::western, "1990-Dec-01");
    XCTAssert(!(testBook4 > testBook));
}

- (void)test_OperatorGreaterThanOrEquals {
    rtl::Book testBook("authorA", "titleA", "seriesA", "publisherA", 100, rtl::Genre::fantasy, "1990-Dec-01");
    
    rtl::Book testBook2("authorB", "titleB", "seriesB", "publisherA", 100, rtl::Genre::fantasy, "1991-Dec-01");
    XCTAssert(testBook2 >= testBook);

    rtl::Book testBook3("authorA", "titleB", "seriesB", "publisherA", 100, rtl::Genre::fantasy, "1991-Dec-01");
    XCTAssert(testBook3 >= testBook);
    
    XCTAssert(testBook3.SetSeries("seriesA"));
    XCTAssert(testBook3 >= testBook);
    
    XCTAssert(testBook3.SetPublishDate("1990-Dec-01"));
    XCTAssert(testBook3 >= testBook);
    
    rtl::Book testBook4("authorA", "titleA", "seriesA", "publisherA", 110, rtl::Genre::western, "1990-Dec-01");
    XCTAssert(testBook2 >= testBook);
}

- (void)test_DefaultConstructor {
    //Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, boost::posix_time::ptime publishDate = boost::posix_time::second_clock::universal_time());
    rtl::Book testBookConstructor("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::Genre::romance, boost::date_time::min_date_time);
    
    XCTAssert(testBookConstructor.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testBookConstructor.GetTitle() == "testTitle");
    XCTAssert(testBookConstructor.GetSeries() == "testSeries");
    XCTAssert(testBookConstructor.GetPublisher() == "testPublisher");
    XCTAssert(testBookConstructor.GetPageCount() == 1111);
    XCTAssert(testBookConstructor.GetGenre() == rtl::Genre::romance);
    XCTAssert(testBookConstructor.GetPublishDateAsPosixTime() == boost::date_time::min_date_time);
    XCTAssert(testBookConstructor.GetBookId() == "2ff6b24");
    XCTAssert(testBookConstructor.GetAuthorId().at(0) == "1ecb");
}

- (void)test_Constructor2 {
    //Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, boost::posix_time::ptime publishDate = boost::posix_time::second_clock::universal_time());
    rtl::Book testBookConstructor(std::vector<std::string> {"testAuthor1", "testAuthor2"}, "testTitle", "testSeries", "testPublisher", 1111, rtl::Genre::romance, boost::date_time::min_date_time);
    
    XCTAssert(testBookConstructor.GetAuthors().size() == 2);
    XCTAssert(testBookConstructor.GetAuthors().at(0) == "testAuthor1");
    XCTAssert(testBookConstructor.GetAuthors().at(1) == "testAuthor2");
    XCTAssert(testBookConstructor.GetTitle() == "testTitle");
    XCTAssert(testBookConstructor.GetSeries() == "testSeries");
    XCTAssert(testBookConstructor.GetPublisher() == "testPublisher");
    XCTAssert(testBookConstructor.GetPageCount() == 1111);
    XCTAssert(testBookConstructor.GetGenre() == rtl::Genre::romance);
    XCTAssert(testBookConstructor.GetPublishDateAsPosixTime() == boost::date_time::min_date_time);
    XCTAssert(testBookConstructor.GetBookId() == "914e89d635");
    XCTAssert(testBookConstructor.GetAuthorId().size() == 2);
    XCTAssert(testBookConstructor.GetAuthorId().at(0) == "23f9");
    XCTAssert(testBookConstructor.GetAuthorId().at(1) == "2404");
}

- (void)test_Constructor3 {
    //Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate);
    rtl::Book testBookConstructor3("testAuthor3", "testTitle3", "testSeries3", "testPublisher3", 333, rtl::Genre::scienceFiction, "1995-Oct-03");
    XCTAssert(testBookConstructor3.GetAuthors().at(0) == "testAuthor3");
    XCTAssert(testBookConstructor3.GetTitle() == "testTitle3");
    XCTAssert(testBookConstructor3.GetSeries() == "testSeries3");
    XCTAssert(testBookConstructor3.GetPublisher() == "testPublisher3");
    XCTAssert(testBookConstructor3.GetPageCount() == 333);
    XCTAssert(testBookConstructor3.GetGenre() == rtl::Genre::scienceFiction);
    XCTAssert(testBookConstructor3.PrintPublishDate() == "1995-Oct-03");
    XCTAssert(testBookConstructor3.GetBookId() == "42ded14");
    XCTAssert(testBookConstructor3.GetAuthorId().at(0) == "240f");
}

- (void)test_Constructor4 {
    //rtl::Book::Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::string isbn, std::string oclc)
    rtl::Book testBookConstructor4({"testAuthor4"}, "testTitle4", "testSeries4", "testPublisher4", 4444, "fantasy", "1969-Oct-31", std::vector<std::string>{"1234567890", "1234567890123"}, std::vector<std::string>{"123456"});
    XCTAssert(testBookConstructor4.GetAuthors().at(0) == "testAuthor4");
    XCTAssert(testBookConstructor4.GetTitle() == "testTitle4");
    XCTAssert(testBookConstructor4.GetSeries() == "testSeries4");
    XCTAssert(testBookConstructor4.GetPublisher() == "testPublisher4");
    XCTAssert(testBookConstructor4.GetPageCount() == 4444);
    XCTAssert(testBookConstructor4.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testBookConstructor4.PrintPublishDate() == "1969-Oct-31");
    XCTAssert(testBookConstructor4.GetIsbn().size() == 2);
    XCTAssert(testBookConstructor4.GetIsbn().at(0) == "1234567890");
    XCTAssert(testBookConstructor4.GetIsbn().at(1) == "1234567890123");
    XCTAssert(testBookConstructor4.GetOclc().size() == 1);
    XCTAssert(testBookConstructor4.GetOclc().at(0) == "123456");
    XCTAssert(testBookConstructor4.GetAuthorId().at(0) == "241a");
}

- (void)test_AddandGetOclc {
    rtl::Book testBook("testAuthor", "testTitle");
    std::string testString = "1234";
                              
    XCTAssert(testBook.AddOclc(testString));
    
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == testString);
}

- (void)test_AddandGetIsbn_PassISBN10andISBN13_ReturnISBNVector {
    rtl::Book testBook("testAuthor", "testTitle");
    std::string testString = "1234567890";
    std::string testString2 = "123-4567-890-12";
    std::string answerString2 = "123456789012";
    
    XCTAssert(testBook.AddIsbn(testString));
    
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == testString);
    
    XCTAssert(!testBook.AddIsbn("asdgbadf213"));
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == testString);
    
    XCTAssert(testBook.AddIsbn(testString2));
    XCTAssert(testBook.GetIsbn().size() == 2);
    XCTAssert(testBook.GetIsbn().at(0) == testString);
    XCTAssert(testBook.GetIsbn().at(1) == answerString2);
}

- (void)test_PrintHeader {
    std::string testStr = "Author              Title                            Series             Pages";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.PrintHeader() == testStr);
}

- (void)test_PrintSimple {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire       Mistborn           541  ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo  Millennium         480  ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World123456789012 The Wheel of Time1 70212";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, rtl::Genre::fantasy, "2006-Jul-17");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, rtl::Genre::thriller, "2005-Aug-01");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, rtl::Genre::fantasy, "1990-Jan-15");
    
    XCTAssert(bookMist.PrintSimple() == testMist);
    XCTAssert(bookGirl.PrintSimple() == testGirl);
    XCTAssert(bookWidth.PrintSimple() == testWidth);
}

- (void)test_PrintDetailed {
    std::string testMist = "Title:         Mistborn: The Final Empire                                       \nBookId:        1c5fdaf7109aa47ef2                                               \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2006-Jul-17                                                      \nISBN:          9780765311788                                                    \nOCLC:          62342185                                                         \n";
    std::string testGirl = "Title:         The Girl with the Dragon Tattoo                                  \nBookId:        2c844f9a4aac31a8848f80                                           \nAuthor Name:   Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nSeries:        Millennium                                                       \nGenre:         thriller                                                         \nPage Count:    480                                                              \nPublisher:     Norstedts Förlag                                                \nPublish Date:  2005-Aug-01                                                      \nISBN:          9781847242532                                                    \nOCLC:          186764078                                                        \n";
    std::string testWidth = "Title:         The Eye of the World123456789012345678901234567890123456789012345\nBookId:        cfcbb4cef513c9c904bf8                                            \nAuthor Name:   Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nSeries:        The Wheel of Time123456789012345678901234567890123456789012345678\nGenre:         fantasy                                                          \nPage Count:    70212                                                            \nPublisher:     Tor Books12345678901234567890123456789012345678901234567890123456\nPublish Date:  1990-Jan-15                                                      \nISBN:          19723327, 1234567890, 1234567890, 1234567890, 1234567890, 1234567\nOCLC:          0312850093, 1234567890, 1234567890, 1234567890, 1234567890, 12345\n";
    
    rtl::Book bookMist({"Brandon Sanderson"}, "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", {"9780765311788"}, {"62342185"});
    rtl::Book bookGirl({"Stieg Larsson"}, "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", {"9781847242532"}, {"186764078"});
    rtl::Book bookWidth({"Robert Jordan123456789012345678901234567890123456789012345678901234567890"}, "The Eye of the World12345678901234567890123456789012345678901234567890", "The Wheel of Time12345678901234567890123456789012345678901234567890", "Tor Books123456789012345678901234567890123456789012345678901234567890", 70212, "fantasy", "1990-Jan-15", {"19723327", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"}, {"0312850093", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"});
    
    XCTAssert(bookMist.PrintDetailed() == testMist);
    XCTAssert(bookGirl.PrintDetailed() == testGirl);
    XCTAssert(bookWidth.PrintDetailed() == testWidth);
}

- (void)test_PrintJson {
    //Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::vector<std::string> isbn, std::vector<std::string> oclc);
    rtl::Book testBook({"testAuthor"}, "testTitle", "testSeries", "testPublisher", 10, "fantasy", "1990-Dec-01", {"1234567890", "123456789012"}, {"123456"});
    
    std::string answer = R"({"bookId":"2ff6b24","isbn":["1234567890","123456789012"],"oclc":["123456"],"author":["testAuthor"],"authorId":["1ecb"],"title":"testTitle","series":"testSeries","publisher":"testPublisher","genre":"fantasy","pageCount":10,"publishDate":"1990-Dec-01"})";
    XCTAssert(testBook.PrintJson() == answer);
}

- (void)test_MultipleAuthors {
    rtl::Book testBook(std::vector<std::string> {"testAuthor1", "testAuthor2"}, "testTitle");
    
    XCTAssert(testBook.GetAuthors().size() == 2);
    XCTAssert(testBook.GetAuthors().at(0) == "testAuthor1");
    XCTAssert(testBook.GetAuthors().at(1) == "testAuthor2");
}

- (void)test_GetAuthorsString_ReturnAllAuthorsAsString {
    rtl::Book testBook(std::vector<std::string> {"test author1", "test author2"}, "testTitle");
    
    XCTAssert(testBook.GetAuthorsString() == "test author1, test author2");
}

- (void)test_GetUpdateFunction_PassStringSeries_ReturnPointerToSetSeries {
    rtl::Book testBook("testAuthor", "testTitle");
    
    rtl::SetsPtr returnFunction = testBook.GetUpdateFunction("Series");
    
    XCTAssert(returnFunction == &rtl::Book::SetSeries);
    
    XCTAssert(std::invoke(returnFunction, testBook, "newSeries"));
    XCTAssert(testBook.GetSeries() == "newSeries");
}

- (void)test_GetUpdateFunction_PassStringGenre_ReturnPointerToSetGenre {
    rtl::Book testBook("testAuthor", "testTitle");
    
    rtl::SetsPtr returnFunction = testBook.GetUpdateFunction("Genre");
    
    XCTAssert(returnFunction == static_cast<rtl::SetsPtr>(&rtl::Book::SetGenre));
    
    XCTAssert(std::invoke(returnFunction, testBook, "romance"));
    XCTAssert(testBook.GetGenre() == rtl::Genre::romance);
}

- (void)test_GetUpdateFunction_PassStringPageCount_ReturnPointerToSetPageCount {
    rtl::Book testBook("testAuthor", "testTitle");
    
    rtl::SetsPtr returnFunction = testBook.GetUpdateFunction("Page Count");
    
    XCTAssert(returnFunction == static_cast<rtl::SetsPtr>(&rtl::Book::SetPageCount));
    
    XCTAssert(std::invoke(returnFunction, testBook, "22"));
    XCTAssert(testBook.GetPageCount() == 22);
}

- (void)test_GetUpdateFunction_PassStringPublisher_ReturnPointerToSetPublisher {
    rtl::Book testBook("testAuthor", "testTitle");
    
    rtl::SetsPtr returnFunction = testBook.GetUpdateFunction("Publisher");
    
    XCTAssert(returnFunction == &rtl::Book::SetPublisher);
    
    XCTAssert(std::invoke(returnFunction, testBook, "newPub"));
    XCTAssert(testBook.GetPublisher() == "newPub");
}

- (void)test_GetUpdateFunction_PassStringPublishDate_ReturnPointerToSetPublishDate {
    rtl::Book testBook("testAuthor", "testTitle");
    
    rtl::SetsPtr returnFunction = testBook.GetUpdateFunction("Publish Date");
    
    XCTAssert(returnFunction == static_cast<rtl::SetsPtr>(&rtl::Book::SetPublishDate));
    
    XCTAssert(std::invoke(returnFunction, testBook, "2020-Apr-15"));
    XCTAssert(testBook.PrintPublishDate() == "2020-Apr-15");
}

- (void)test_GetUpdateFunction_PassStringIsbn_ReturnPointerToAddIsbn {
    rtl::Book testBook("testAuthor", "testTitle");

    rtl::SetsPtr returnFunction = testBook.GetUpdateFunction("ISBN");
    
    XCTAssert(returnFunction == &rtl::Book::AddIsbn);
    
    XCTAssert(std::invoke(returnFunction, testBook, "1234567890"));
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn()[0] == "1234567890");
}

- (void)test_GetUpdateFunction_PassStringOclc_ReturnPointerToAddOclc {
    rtl::Book testBook("testAuthor", "testTitle");

    rtl::SetsPtr returnFunction = testBook.GetUpdateFunction("OCLC");
    
    XCTAssert(returnFunction == &rtl::Book::AddOclc);
    
    XCTAssert(std::invoke(returnFunction, testBook, "123456"));
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc()[0] == "123456");
}

- (void)test_SetSeries_PassStringWithControlCharacters_ControlCharactersAreRemoved {
    std::string test = "\n\ntestSeries\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetSeries(test) == true);
    
    XCTAssert(testBook.GetSeries() == "testSeries");
}

- (void)test_SetSeries_PassStringOnlyWithControlCharacters_ReturnFalse {
    std::string test = "\n\n\t\t\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetSeries(test) == false);
}

- (void)test_SetPublisher_PassStringWithControlCharacters_ControlCharactersAreRemoved {
    std::string test = "\n\ntestPublisher\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetPublisher(test) == true);
    
    XCTAssert(testBook.GetPublisher() == "testPublisher");
}

- (void)test_SetPublisher_PassStringOnlyWithControlCharacters_ReturnFalse {
    std::string test = "\n\n\t\t\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetPublisher(test) == false);
}

- (void)test_SetGenre_PassStringWithControlCharacters_ControlCharactersAreRemoved {
    std::string test = "\n\nthriller\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetGenre(test) == true);
    
    XCTAssert(testBook.GetGenre() == rtl::Genre::thriller);
}

- (void)test_SetGenre_PassStringOnlyWithControlCharacters_ReturnFalse {
    std::string test = "\n\n\t\t\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetGenre(test) == false);
}

- (void)test_SetPublishDate_PassStringWithControlCharacters_ControlCharactersAreRemoved {
    std::string test = "\n\n1990-Apr-01\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetPublishDate(test) == true);
    
    XCTAssert(testBook.PrintPublishDate() == "1990-Apr-01");
}

- (void)test_SetPublishDate_PassStringOnlyWithControlCharacters_ReturnFalse {
    std::string test = "\n\n\t\t\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.SetPublishDate(test) == false);
}

- (void)test_SetOclc_PassStringWithControlCharacters_ControlCharactersAreRemoved {
    std::string test = "\n\n123456\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.AddOclc(test) == true);
    
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc()[0] == "123456");
}

- (void)test_SetOclc_PassStringOnlyWithControlCharacters_ReturnFalse {
    std::string test = "\n\n\t\t\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.AddOclc(test) == false);
}

- (void)test_SetIsbn_PassStringWithControlCharacters_ControlCharactersAreRemoved {
    std::string test = "\n\n1234567890\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.AddIsbn(test) == true);
    
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn()[0] == "1234567890");
}

- (void)test_SetIsbn_PassStringOnlyWithControlCharacters_ReturnFalse {
    std::string test = "\n\n\t\t\n";
    rtl::Book testBook("testAuthor", "testTitle");
    
    XCTAssert(testBook.AddIsbn(test) == false);
}

@end
