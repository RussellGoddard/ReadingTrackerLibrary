//
//  testGui.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 2/12/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "gui.hpp"


@interface testGui : XCTestCase

@end

@implementation testGui

- (void)setUp {
}

- (void)tearDown {
}

- (void)test_GetNewAuthor_Manual_ReturnNewAuthor {
    std::stringstream inputSs, outputSs;
    inputSs.str("testAuthor\n1998-Nov-25\n");
    rtl::Author testAuthor = rtl::CommandLine::GetNewAuthor(inputSs, outputSs, 0);
    
    XCTAssert(testAuthor.GetName() == "testAuthor");
    XCTAssert(testAuthor.PrintDateBorn() == "1998-Nov-25");
}

- (void)test_GetNewAuthor_ByIdentifier_ReturnNewAuthor {
    std::stringstream inputSs, outputSs;
    inputSs.str("testAuthor\n1998-Nov-25\n");
    rtl::Author testAuthor = rtl::CommandLine::GetNewAuthor(inputSs, outputSs, 1);
    
    XCTAssert(testAuthor.GetName() == "testAuthor");
    XCTAssert(testAuthor.PrintDateBorn() == "1998-Nov-25");
}

- (void)test_GetNewAuthor_ByTitle_ReturnNewAuthor {
    std::stringstream inputSs, outputSs;
    inputSs.str("testAuthor\n1998-Nov-25\n");
    rtl::Author testAuthor = rtl::CommandLine::GetNewAuthor(inputSs, outputSs, 2);
    
    XCTAssert(testAuthor.GetName() == "testAuthor");
    XCTAssert(testAuthor.PrintDateBorn() == "1998-Nov-25");
}

- (void)test_GetNewAuthor_InvalidInputMode_ReturnEmptyAuthor {
    //TODO: verify logging when this happens
    std::stringstream inputSs, outputSs;
    inputSs.str("testAuthor\n1998-Nov-25\n");
    rtl::Author testAuthor = rtl::CommandLine::GetNewAuthor(inputSs, outputSs, 10000);
    
    XCTAssert(testAuthor.GetName() == "");}

- (void)test_GetNewBook_Manual_ReturnNewBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n");
    
    rtl::Book testBook = rtl::CommandLine::GetNewBook(inputSs, outputSs, 0);
    
    XCTAssert(testBook.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testBook.GetTitle() == "testTitle");
    XCTAssert(testBook.GetPublisher() == "testPublisher");
    XCTAssert(testBook.GetSeries() == "testSeries");
    XCTAssert(testBook.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testBook.GetPageCount() == 123);
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == "123456");
}

- (void)test_GetNewBook_ByIdentifier_PassInvalidIdentifierThenGoManualMode_ReturnNewBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("OCLC\n21341234123412341234\ntestAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n");
    rtl::Book testBook = rtl::CommandLine::GetNewBook(inputSs, outputSs, 1);
    
    XCTAssert(testBook.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testBook.GetTitle() == "testTitle");
    XCTAssert(testBook.GetPublisher() == "testPublisher");
    XCTAssert(testBook.GetSeries() == "testSeries");
    XCTAssert(testBook.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testBook.GetPageCount() == 123);
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == "123456");
}

- (void)test_GetNewBook_ByIdentifier_ReturnNewBook {
    std::stringstream inputSs, outputSs;
    std::vector<std::string> isbnAnswer {"0312850093", "9780765324887"};
    std::vector<std::string> oclcAnswer {"19723327"};
    
    inputSs.str("ISBN\n0312850093\n");
    rtl::Book testBook = rtl::CommandLine::GetNewBook(inputSs, outputSs, 1);
    
    XCTAssert(testBook.GetAuthors().at(0) == "Robert Jordan");
    XCTAssert(testBook.GetTitle() == "The Eye of the World");
    XCTAssert(testBook.GetPublisher() == "Tor Publishing");
    XCTAssert(testBook.GetSeries() == "The Wheel of Time");
    XCTAssert(testBook.GetGenre() == rtl::Genre::genreNotSet);
    XCTAssert(testBook.PrintPublishDate() == "1990-Jan-15");
    XCTAssert(testBook.GetPageCount() == -1);
    XCTAssert(testBook.GetIsbn()  == isbnAnswer);
    XCTAssert(testBook.GetOclc() == oclcAnswer);
}

- (void)test_GetNewBook_ByTitle_ReturnNewBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("The Eye of the World");
    rtl::Book testBook = rtl::CommandLine::GetNewBook(inputSs, outputSs, 2);
    
    XCTAssert(testBook.GetAuthors().at(0) == "Robert Jordan");
    XCTAssert(testBook.GetTitle() == "The Eye of the World");
    XCTAssert(testBook.GetPublisher() == "Tor Publishing");
    XCTAssert(testBook.GetSeries() == "The Wheel of Time");
    XCTAssert(testBook.GetGenre() == rtl::Genre::genreNotSet);
    XCTAssert(testBook.PrintPublishDate() == "1990-Jan-15");
    XCTAssert(testBook.GetPageCount() == -1);
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == "9780765324887");
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == "19723327");
}

- (void)test_GetNewBook_ByTitle_PassInvalidTitleRevertToManualMode_ReturnNewBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("gibberishtitle\ntestAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n");
    rtl::Book testBook = rtl::CommandLine::GetNewBook(inputSs, outputSs, 2);
    
    XCTAssert(testBook.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testBook.GetTitle() == "testTitle");
    XCTAssert(testBook.GetPublisher() == "testPublisher");
    XCTAssert(testBook.GetSeries() == "testSeries");
    XCTAssert(testBook.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testBook.GetPageCount() == 123);
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == "123456");
}

//TODO: get logging on invalid input mode
/*
- (void)testGetNewBookInvalidInputMode {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n");
    rtl::Book testBook = rtl::CommandLine::GetNewBook(inputSs, outputSs, 1234213);
    
    XCTAssert(testBook.GetAuthor() == "testAuthor");
    XCTAssert(testBook.GetTitle() == "testTitle");
    XCTAssert(testBook.GetPublisher() == "testPublisher");
    XCTAssert(testBook.GetSeries() == "testSeries");
    XCTAssert(testBook.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testBook.GetPageCount() == 123);
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == "123456");
}
*/
 
- (void)test_GetNewReadBook_Manual_ReturnNewReadBook {
    std::stringstream inputSs, outputSs;
    inputSs.str("testAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n1999-Oct-02\n9\n");
    
    rtl::ReadBook testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123, 0);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    XCTAssert(testReadBook.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testReadBook.GetTitle() == "testTitle");
    XCTAssert(testReadBook.GetPublisher() == "testPublisher");
    XCTAssert(testReadBook.GetSeries() == "testSeries");
    XCTAssert(testReadBook.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testReadBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testReadBook.GetPageCount() == 123);
    XCTAssert(testReadBook.PrintDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.GetRating() == 9);
    XCTAssert(testReadBook.GetIsbn().size() == 1);
    XCTAssert(testReadBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testReadBook.GetOclc().size() == 1);
    XCTAssert(testReadBook.GetOclc().at(0) == "123456");
}

- (void)test_GetNewReadBook_ByIdentifier_PassInvalidIdentifierThenRevertToManualMode_ReturnNewReadBook {
    std::stringstream inputSs, outputSs;
    inputSs.str("ISBN\n12341234213412341234\ntestAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n1999-Oct-02\n9\n");
    
    rtl::ReadBook testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123, 1);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    XCTAssert(testReadBook.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testReadBook.GetTitle() == "testTitle");
    XCTAssert(testReadBook.GetPublisher() == "testPublisher");
    XCTAssert(testReadBook.GetSeries() == "testSeries");
    XCTAssert(testReadBook.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testReadBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testReadBook.GetPageCount() == 123);
    XCTAssert(testReadBook.PrintDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.GetRating() == 9);
    XCTAssert(testReadBook.GetIsbn().size() == 1);
    XCTAssert(testReadBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testReadBook.GetOclc().size() == 1);
    XCTAssert(testReadBook.GetOclc().at(0) == "123456");
}

- (void)test_GetNewReadBook_ByIdentifier_ReturnNewReadBook {
    std::stringstream inputSs, outputSs;
    inputSs.str("ISBN\n0312850093\n1999-Oct-02\n9\n");
    std::vector<std::string> isbnAnswer {"0312850093", "9780765324887"};
    std::vector<std::string> oclcAnswer {"19723327"};
    
    rtl::ReadBook testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123, 1);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    XCTAssert(testReadBook.PrintDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.GetRating() == 9);
    XCTAssert(testReadBook.GetAuthors().at(0) == "Robert Jordan");
    XCTAssert(testReadBook.GetTitle() == "The Eye of the World");
    XCTAssert(testReadBook.GetPublisher() == "Tor Publishing");
    XCTAssert(testReadBook.GetSeries() == "The Wheel of Time");
    XCTAssert(testReadBook.GetGenre() == rtl::Genre::genreNotSet);
    XCTAssert(testReadBook.PrintPublishDate() == "1990-Jan-15");
    XCTAssert(testReadBook.GetPageCount() == -1);
    XCTAssert(testReadBook.GetIsbn() == isbnAnswer);
    XCTAssert(testReadBook.GetOclc() == oclcAnswer);
}

- (void)test_GetNewReadBook_ByTitle_PassInvalidTitleThenRevertToManual_ReturnNewReadBook {
    std::stringstream inputSs, outputSs;
    inputSs.str("gibberishtitle\ntestAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n1999-Oct-02\n9\n");
    
    rtl::ReadBook testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123, 2);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    XCTAssert(testReadBook.GetAuthors().at(0) == "testAuthor");
    XCTAssert(testReadBook.GetTitle() == "testTitle");
    XCTAssert(testReadBook.GetPublisher() == "testPublisher");
    XCTAssert(testReadBook.GetSeries() == "testSeries");
    XCTAssert(testReadBook.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testReadBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testReadBook.GetPageCount() == 123);
    XCTAssert(testReadBook.PrintDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.GetRating() == 9);
    XCTAssert(testReadBook.GetIsbn().size() == 1);
    XCTAssert(testReadBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testReadBook.GetOclc().size() == 1);
    XCTAssert(testReadBook.GetOclc().at(0) == "123456");
}

- (void)test_GetNewReadBook_ByTitle_ReturnNewReadBook {
    std::stringstream inputSs, outputSs;
    inputSs.str("The Eye of the World\n1999-Oct-02\n9\n");
    
    rtl::ReadBook testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123, 2);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    XCTAssert(testReadBook.PrintDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.GetRating() == 9);
    XCTAssert(testReadBook.GetAuthors().at(0) == "Robert Jordan");
    XCTAssert(testReadBook.GetTitle() == "The Eye of the World");
    XCTAssert(testReadBook.GetPublisher() == "Tor Publishing");
    XCTAssert(testReadBook.GetSeries() == "The Wheel of Time");
    XCTAssert(testReadBook.GetGenre() == rtl::Genre::genreNotSet);
    XCTAssert(testReadBook.PrintPublishDate() == "1990-Jan-15");
    XCTAssert(testReadBook.GetPageCount() == -1);
    XCTAssert(testReadBook.GetIsbn().size() == 1);
    XCTAssert(testReadBook.GetIsbn().at(0) == "9780765324887");
    XCTAssert(testReadBook.GetOclc().size() == 1);
    XCTAssert(testReadBook.GetOclc().at(0) == "19723327");
}

- (void)test_GetNewBook_ByTitle_PassInvalidDate_OutputErrorMessageAndReadBookReadDateIsEmpty {
    std::stringstream inputSs, outputSs;
    inputSs.str("The Eye of the World\n199-123-ab\n9\n");
    
    rtl::ReadBook testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123, 2);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    std::string testStr = testReadBook.PrintDateRead();
    XCTAssert(testReadBook.PrintDateRead() == "");
    XCTAssert(testReadBook.GetRating() == 9);
    XCTAssert(testReadBook.GetAuthors().at(0) == "Robert Jordan");
    XCTAssert(testReadBook.GetTitle() == "The Eye of the World");
    XCTAssert(testReadBook.GetPublisher() == "Tor Publishing");
    XCTAssert(testReadBook.GetSeries() == "The Wheel of Time");
    XCTAssert(testReadBook.GetGenre() == rtl::Genre::genreNotSet);
    XCTAssert(testReadBook.PrintPublishDate() == "1990-Jan-15");
    XCTAssert(testReadBook.GetPageCount() == -1);
    XCTAssert(testReadBook.GetIsbn().size() == 1);
    XCTAssert(testReadBook.GetIsbn().at(0) == "9780765324887");
    XCTAssert(testReadBook.GetOclc().size() == 1);
    XCTAssert(testReadBook.GetOclc().at(0) == "19723327");
}

- (void)test_GetNewBook_ByTitle_PassInvalidRating_ReadBookRatingIsNeg1 {
    std::stringstream inputSs, outputSs;
    inputSs.str("The Eye of the World\n1999-Oct-02\nab\n");
    
    rtl::ReadBook testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123, 2);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    XCTAssert(testReadBook.PrintDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.GetRating() == -1);
    XCTAssert(testReadBook.GetAuthors().at(0) == "Robert Jordan");
    XCTAssert(testReadBook.GetTitle() == "The Eye of the World");
    XCTAssert(testReadBook.GetPublisher() == "Tor Publishing");
    XCTAssert(testReadBook.GetSeries() == "The Wheel of Time");
    XCTAssert(testReadBook.GetGenre() == rtl::Genre::genreNotSet);
    XCTAssert(testReadBook.PrintPublishDate() == "1990-Jan-15");
    XCTAssert(testReadBook.GetPageCount() == -1);
    XCTAssert(testReadBook.GetIsbn().size() == 1);
    XCTAssert(testReadBook.GetIsbn().at(0) == "9780765324887");
    XCTAssert(testReadBook.GetOclc().size() == 1);
    XCTAssert(testReadBook.GetOclc().at(0) == "19723327");
}

//TODO: logging when this happens
/*
- (void)testGetNewReadBookInvalidInputMode {
     std::stringstream inputSs, outputSs;
     inputSs.str("testAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n1999-Oct-02\n9\n");
     
    testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123, 12341234);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    XCTAssert(testReadBook.GetAuthor() == "testAuthor");
    XCTAssert(testReadBook.GetTitle() == "testTitle");
    XCTAssert(testReadBook.GetPublisher() == "testPublisher");
    XCTAssert(testReadBook.GetSeries() == "testSeries");
    XCTAssert(testReadBook.GetGenre() == rtl::Genre::fantasy);
    XCTAssert(testReadBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testReadBook.GetPageCount() == 123);
    XCTAssert(testReadBook.PrintDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.GetRating() == 9);
    XCTAssert(testReadBook.GetIsbn().size() == 1);
    XCTAssert(testReadBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testReadBook.GetOclc().size() == 1);
    XCTAssert(testReadBook.GetOclc().at(0) == "123456");
}
*/

- (void)test_OutputLine_PassOutputStreamAndString_ReturnOutputStreamContainingPassedStringAndNewLine {
    std::stringstream outputSs;
    
    rtl::CommandLine::OutputLine(outputSs, "test Input 23");
    
    char word[256];
    outputSs.getline(word, 256);
    XCTAssert(std::string(word) == "test Input 23");
    outputSs.getline(word, 256);
    XCTAssert(outputSs.eof());
}

- (void)test_OutputLineVector_PassOutputStreamAndVectorOfStrings_ReturnOutputStreamContainingPassedVector {
    std::stringstream outputSs;
    std::vector<std::string> input {"the", "Rain", "in", "Sp Ain", "t h     e", "p   "};
    
    rtl::CommandLine::OutputLine(outputSs, input);
    
    char word[64];
    outputSs.getline(word, 64);
    XCTAssert(std::string(word) == "the");
    outputSs.getline(word, 64);
    XCTAssert(std::string(word) == "Rain");
    outputSs.getline(word, 64);
    XCTAssert(std::string(word) == "in");
    outputSs.getline(word, 64);
    XCTAssert(std::string(word) == "Sp Ain");
    outputSs.getline(word, 64);
    XCTAssert(std::string(word) == "t h     e");
    outputSs.getline(word, 64);
    XCTAssert(std::string(word) == "p   ");
    outputSs.getline(word, 64);
    XCTAssert(outputSs.eof());
}

@end
