//
//  testClassAuthor.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/15/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "Author.hpp"
#include "Book.hpp"

@interface testClassAuthor : XCTestCase

@end

@implementation testClassAuthor

std::vector<std::shared_ptr<rtl::Book>> bookCollection;
std::shared_ptr<rtl::Book> testBook1;
std::shared_ptr<rtl::Book> testBook2;

- (void)setUp {
    testBook1 = std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 11, "fantasy", "1992-Nov-11");
    testBook2 = std::make_shared<rtl::Book>("testA", "testT", "testS", "testP", 22, "western", "1999-Nov-13");
    bookCollection.push_back(testBook1);
    bookCollection.push_back(testBook2);
}

- (void)tearDown {
    bookCollection.clear();
}

- (void)testSetName {
    rtl::Author testAuthor("testAuthor");
    XCTAssert(testAuthor.GetName() == "testAuthor");
    XCTAssert(testAuthor.SetName("pickle"));
    XCTAssert(testAuthor.GetName() == "pickle");
}

- (void)testSetDateBorn {
    rtl::Author testAuthor("testAuthor");
    time_t testValue = 1573862400;
    XCTAssert(testAuthor.SetDateBorn(testValue));
    tm initialTm = *std::gmtime(&testValue);
    tm testTm = testAuthor.GetDateBorn();
    
    XCTAssert(std::mktime(&initialTm) == std::mktime(&testTm));
    XCTAssert(testAuthor.GetDateBornTimeT() == 1573880400);
    XCTAssert(testAuthor.PrintDateBorn() == "2019-Nov-16");
    
    XCTAssert(testAuthor.SetDateBorn("1990-Dec-08"));
    XCTAssert(testAuthor.PrintDateBorn() == "1990-Dec-08");
    
    XCTAssert(testAuthor.SetDateBorn("1890-Dec-01"));
    XCTAssert(testAuthor.PrintDateBorn() == "1890-Dec-01");
    
    XCTAssert(testAuthor.SetDateBorn("1990-Dec-01"));
    XCTAssert(testAuthor.GetDateBornTimeT() == 660027600);
    XCTAssert(testAuthor.PrintDateBorn() == "1990-Dec-01");
    
    XCTAssert(!testAuthor.SetDateBorn("Dec-ab-2000"));
    XCTAssert(!testAuthor.SetDateBorn("invalid string"));
    XCTAssert(!testAuthor.SetDateBorn("AAA 01 3453"));
    
    
}

- (void)testAddBook {    
    rtl::Author newAuthor("testAuthor");
    std::shared_ptr<rtl::Book> testBook = std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 111, rtl::Genre::fantasy, "Nov-11-1992");
    
    XCTAssert(newAuthor.GetBooksWritten().empty());
    
    XCTAssert(newAuthor.AddBookWritten(testBook));
    
    XCTAssert(newAuthor.GetBooksWritten().size() == 1);
    XCTAssert(newAuthor.GetBooksWritten().at(0) == testBook);
}

- (void)testAddBooks {
    rtl::Author newAuthor("testAuthors");
    
    XCTAssert(newAuthor.GetBooksWritten().empty());
    
    XCTAssert(newAuthor.AddBookWritten(bookCollection));
    
    XCTAssert(newAuthor.GetBooksWritten().size() == 2);
    XCTAssert(newAuthor.GetBooksWritten().at(0) == testBook2);
    XCTAssert(newAuthor.GetBooksWritten().at(1) == testBook1);
}

- (void)testAuthorConstructor {
    
    //Author(std::string name, time_t dateBorn = std::time(0), std::vector<std::shared_ptr<Book>> booksWritten = {});
    rtl::Author testAuthor1("testAuthor1", 660027600);
    XCTAssert(testAuthor1.GetName() == "testAuthor1");
    XCTAssert(testAuthor1.GetDateBornTimeT() == 660027600);
    XCTAssert(testAuthor1.GetBooksWritten().size() == 0);
    XCTAssert(testAuthor1.GetAuthorId() == "23f9");
    
    //Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
    rtl::Author testAuthor2("testAuthor2", "1990-Dec-01", bookCollection);
    XCTAssert(testAuthor2.GetName() == "testAuthor2");
    XCTAssert(testAuthor2.PrintDateBorn() == "1990-Dec-01");
    XCTAssert(testAuthor2.GetBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor2.GetBooksWritten().size() == 2);
    XCTAssert(testAuthor2.GetBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor2.GetBooksWritten().at(1) == testBook1);
    XCTAssert(testAuthor2.GetAuthorId() == "2404");
    
    //Author::Author(std::string name, time_t dateBorn, std::shared_ptr<Book> bookWritten)
    rtl::Author testAuthor3("testAuthor3", 660027600, testBook1);
    XCTAssert(testAuthor3.GetName() == "testAuthor3");
    XCTAssert(testAuthor3.GetDateBornTimeT() == 660027600);
    XCTAssert(testAuthor3.GetBooksWritten().size() == 1);
    XCTAssert(testAuthor3.GetBooksWritten().at(0) == testBook1);
    XCTAssert(testAuthor3.GetAuthorId() == "240f");
}

- (void)testEquals {
    rtl::Author testAuthor1("testAuthor1", "1990-Dec-01");
    rtl::Author testAuthor2("testAuthor1", "1990-Dec-01");
    
    XCTAssert(testAuthor1 == testAuthor2);
}

- (void)testNotEquals {
    rtl::Author testAuthor1("testAuthor1", "1990-Dec-01");
    rtl::Author testAuthor2("testAuthor2", "1990-Dec-01");
    
    XCTAssert(testAuthor1 != testAuthor2);
}

- (void)testLessThan {
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "1990-Dec-01");
    
    XCTAssert(testAuthor1 < testAuthor2);
    
    testAuthor1.SetName("chris test");
    
    XCTAssert(testAuthor2 < testAuthor1);
    
    testAuthor2.SetName("Laura Winner");
    
    XCTAssert(testAuthor1 < testAuthor2);
    
    testAuthor1.SetName("a");
    testAuthor2.SetName("a");
    testAuthor1.SetDateBorn("1990-Dec-02");
    
    XCTAssert(testAuthor2 < testAuthor1);
}

- (void)testLessThanEquals {
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "1990-Dec-01");
    
    XCTAssert(testAuthor1 <= testAuthor2);
    
    testAuthor1.SetName("chris test");
    
    XCTAssert(testAuthor2 <= testAuthor1);
    
    testAuthor2.SetName("Laura Winner");
    
    XCTAssert(testAuthor1 <= testAuthor2);
    
    testAuthor1.SetName("a");
    testAuthor2.SetName("a");
    
    XCTAssert(testAuthor2 <= testAuthor1);
    
    testAuthor2.SetDateBorn("1990-Dec-02");
    
    XCTAssert(testAuthor1 <= testAuthor2);
}

- (void)testGreaterThan {
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "1990-Dec-01");
    
    XCTAssert(testAuthor2 > testAuthor1);
    
    testAuthor1.SetName("chris test");
    
    XCTAssert(testAuthor1 > testAuthor2);
    
    testAuthor2.SetName("Laura Winner");
    
    XCTAssert(testAuthor2 > testAuthor1);
    
    testAuthor1.SetName("a");
    testAuthor2.SetName("a");
    testAuthor1.SetDateBorn("1990-Dec-02");
    
    XCTAssert(testAuthor1 > testAuthor2);
}

- (void)testGreaterThanEquals {
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "1990-Dec-01");
    
    XCTAssert(testAuthor2 >= testAuthor1);
    
    testAuthor1.SetName("chris test");
    
    XCTAssert(testAuthor1 >= testAuthor2);
    
    testAuthor2.SetName("Laura Winner");
    
    XCTAssert(testAuthor2 >= testAuthor1);
    
    testAuthor1.SetName("a");
    testAuthor2.SetName("a");
    
    XCTAssert(testAuthor1 >= testAuthor2);
    
    testAuthor2.SetDateBorn("1990-Dec-02");
    
    XCTAssert(testAuthor2 >= testAuthor1);
}


- (void)testAuthorConstructors {
    //Author(std::string name, time_t dateBorn = std::time(&jan2038), std::vector<std::shared_ptr<Book>> booksWritten = {});
    //Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
    rtl::Author testAuthor("testName");
    XCTAssert(testAuthor.GetName() == "testName");
    XCTAssert(testAuthor.PrintDateBorn() == "2038-Jan-01");
    XCTAssert(testAuthor.GetBooksWritten().size() == 0);
    
    rtl::Author testAuthor2("testName2", "1990-Dec-01");
    XCTAssert(testAuthor2.GetName() == "testName2");
    XCTAssert(testAuthor2.PrintDateBorn() == "1990-Dec-01");
    XCTAssert(testAuthor2.GetBooksWritten().size() == 0);
    
    rtl::Author testAuthor3("testName3", "1975-Jun-02", bookCollection);
    XCTAssert(testAuthor3.GetName() == "testName3");
    XCTAssert(testAuthor3.PrintDateBorn() == "1975-Jun-02");
    XCTAssert(testAuthor3.GetBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor3.GetBooksWritten().size() == 2);
    XCTAssert(testAuthor3.GetBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor3.GetBooksWritten().at(1) == testBook1);
    
    rtl::Author testAuthor4("testName4", "1984-Aug-27");
    XCTAssert(testAuthor4.GetName() == "testName4");
    XCTAssert(testAuthor4.PrintDateBorn() == "1984-Aug-27");
    XCTAssert(testAuthor4.GetBooksWritten().size() == 0);
    
    rtl::Author testAuthor5("testName5", "2001-Feb-21", bookCollection);
    XCTAssert(testAuthor5.GetName() == "testName5");
    XCTAssert(testAuthor5.PrintDateBorn() == "2001-Feb-21");
    XCTAssert(testAuthor5.GetBooksWritten().size() == bookCollection.size());
    XCTAssert(testAuthor5.GetBooksWritten().size() == 2);
    XCTAssert(testAuthor5.GetBooksWritten().at(0) == testBook2);
    XCTAssert(testAuthor5.GetBooksWritten().at(1) == testBook1);
}

- (void)testPrintAuthorColumnHeaders {
    std::string testStr = "Author              Date Born   Books Written                            Year";
    rtl::Author testAuthor("testAuthor");
    XCTAssert(testAuthor.PrintHeader() == testStr);
}

- (void)testPrintCommandLineSimpleAuthor {
    std::string testMist = "Brandon Sanderson   1975-Dec-19 Mistborn: The Final Empire               2006\n                                Mistborn: The Well of Ascension          2007\n                                Mistborn: The Hero of Ages               2008";
    std::string testGirl = "Stieg Larsson       1964-Aug-15 The Girl with the Dragon Tattoo          2005";
    std::string testWidth = "Robert Jordan123456 1948-Oct-17 The Eye of the World12345678901234567890 1990";
    
    rtl::Book bookMist1("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17");
    rtl::Book bookMist2("Brandon Sanderson", "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 541, "fantasy", "2007-Jul-17");
    rtl::Book bookMist3("Brandon Sanderson", "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 541, "fantasy", "2008-Jul-17");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World1234567890123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15");
    
    std::vector<std::shared_ptr<rtl::Book>> mistbornVector;
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist1));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist2));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist3));
    
    rtl::Author authorMist("Brandon Sanderson", "1975-Dec-19", mistbornVector);
    rtl::Author authorGirl("Stieg Larsson", "1964-Aug-15");
    authorGirl.AddBookWritten(std::make_shared<rtl::Book>(bookGirl));
    rtl::Author authorWidth("Robert Jordan1234567");
    authorWidth.SetDateBorn("1948-Oct-17");
    authorWidth.AddBookWritten(std::make_shared<rtl::Book>(bookWidth));
    
    XCTAssert(authorMist.PrintSimple() == testMist);
    XCTAssert(authorGirl.PrintSimple() == testGirl);
    XCTAssert(authorWidth.PrintSimple() == testWidth);
}

- (void)testPrintCommandLineDetailedAuthor {
    std::string testMist = "Name:          Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nDate Born:     1975-Dec-19                                                      \nBooks Written:                                                                  \nTitle:         Mistborn: The Final Empire                                       \nBookId:        1c5fdaf7109aa47ef2                                               \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2006-Jul-17                                                      \nISBN:          9780765311788                                                    \nOCLC:          62342185                                                         \n\nTitle:         Mistborn: The Well of Ascension                                  \nBookId:        3ffc6bac06439747e1b0                                             \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2007-Jul-17                                                      \nISBN:                                                                           \nOCLC:                                                                           \n\nTitle:         Mistborn: The Hero of Ages                                       \nBookId:        ca903ec590e706e8318                                              \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2008-Jul-17                                                      \nISBN:                                                                           \nOCLC:                                                                           \n\n";
    std::string testGirl = "Name:          Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nDate Born:     1964-Aug-15                                                      \nBooks Written:                                                                  \nTitle:         The Girl with the Dragon Tattoo                                  \nBookId:        2c844f9a4aac31a8848f80                                           \nAuthor Name:   Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nSeries:        Millennium                                                       \nGenre:         thriller                                                         \nPage Count:    480                                                              \nPublisher:     Norstedts Förlag                                                \nPublish Date:  2005-Aug-01                                                      \nISBN:          9781847242532                                                    \nOCLC:          186764078                                                        \n\n";
    std::string testWidth = "Name:          Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nDate Born:     1948-Oct-17                                                      \nBooks Written:                                                                  \nTitle:         The Eye of the World123456789012345678901234567890123456789012345\nBookId:        cfcbb4cef513c9c904bf8                                            \nAuthor Name:   Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nSeries:        The Wheel of Time123456789012345678901234567890123456789012345678\nGenre:         fantasy                                                          \nPage Count:    70212                                                            \nPublisher:     Tor Books12345678901234567890123456789012345678901234567890123456\nPublish Date:  1990-Jan-15                                                      \nISBN:          19723327, 1234567890, 1234567890, 1234567890, 1234567890, 1234567\nOCLC:          0312850093, 1234567890, 1234567890, 1234567890, 1234567890, 12345\n\n";
    
    rtl::Book bookMist2("Brandon Sanderson", "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 541, "fantasy", "2007-Jul-17");
    rtl::Book bookMist3("Brandon Sanderson", "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 541, "fantasy", "2008-Jul-17");
    
    rtl::Book bookMist1("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", std::vector<std::string> {"9780765311788"}, std::vector<std::string> {"62342185"});
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", std::vector<std::string> {"9781847242532"}, std::vector<std::string> {"186764078"});
    rtl::Book bookWidth("Robert Jordan123456789012345678901234567890123456789012345678901234567890", "The Eye of the World12345678901234567890123456789012345678901234567890", "The Wheel of Time12345678901234567890123456789012345678901234567890", "Tor Books123456789012345678901234567890123456789012345678901234567890", 70212, "fantasy", "1990-Jan-15", std::vector<std::string> {"19723327", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"}, std::vector<std::string> {"0312850093", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"});
    
    std::vector<std::shared_ptr<rtl::Book>> mistbornVector;
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist1));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist2));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist3));
    
    rtl::Author authorMist("Brandon Sanderson", "1975-Dec-19", mistbornVector);
    rtl::Author authorGirl("Stieg Larsson", "1964-Aug-15");
    authorGirl.AddBookWritten(std::make_shared<rtl::Book>(bookGirl));
    rtl::Author authorWidth("Robert Jordan123456789012345678901234567890123456789012345678901234567890");
    authorWidth.SetDateBorn("1948-Oct-17");
    authorWidth.AddBookWritten(std::make_shared<rtl::Book>(bookWidth));
    
    XCTAssert(authorMist.PrintDetailed() == testMist);
    XCTAssert(authorGirl.PrintDetailed() == testGirl);
    XCTAssert(authorWidth.PrintDetailed() == testWidth);
}

- (void)testPrintJson {
    std::shared_ptr<rtl::Book> testBook1 = std::make_shared<rtl::Book>("3rd", "testTitle1", "testSeries1", "testPublisher1", 1, rtl::Genre::fantasy, "1992-Nov-11");
    std::shared_ptr<rtl::Book> testBook2 = std::make_shared<rtl::Book>("3rd", "testTitle2", "testSeries2", "testPublisher2", 22, rtl::Genre::western, "2020-Nov-11");
    rtl::Author testAuthor1("a", "1990-Dec-01");
    rtl::Author testAuthor2("b", "2001-Nov-12");
    rtl::Author testAuthor3("3rd", "2000-Apr-01");
    testAuthor3.AddBookWritten(testBook1);
    testAuthor3.AddBookWritten(testBook2);
    
    XCTAssert(testAuthor1.PrintJson() == R"({"authorId":"4e","name":"a","dateBorn":"1990-Dec-01","booksWritten":[]})");
    XCTAssert(testAuthor2.PrintJson() == R"({"authorId":"4f","name":"b","dateBorn":"2001-Nov-12","booksWritten":[]})");
    XCTAssert(testAuthor3.PrintJson() == R"({"authorId":"268","name":"3rd","dateBorn":"2000-Apr-01","booksWritten":[{"bookId":"4735c0","isbn":[],"oclc":[],"author":"3rd","authorId":"268","title":"testTitle1","series":"testSeries1","publisher":"testPublisher1","genre":"fantasy","pageCount":1,"publishDate":"1992-Nov-11"},{"bookId":"474dd0","isbn":[],"oclc":[],"author":"3rd","authorId":"268","title":"testTitle2","series":"testSeries2","publisher":"testPublisher2","genre":"western","pageCount":22,"publishDate":"2020-Nov-11"}]})");
}

@end
