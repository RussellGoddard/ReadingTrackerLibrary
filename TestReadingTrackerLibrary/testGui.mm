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
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testGetNewAuthor {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\n1998-Nov-25\n");
    
    rtl::Author testAuthor = rtl::CommandLine::GetNewAuthor(inputSs, outputSs);
    
    XCTAssert(testAuthor.GetName() == "testAuthor");
    XCTAssert(testAuthor.PrintDateBorn() == "1998-Nov-25");
}

- (void)testGetNewBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\n1234567890\n123456\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n");
    
    rtl::Book testBook = rtl::CommandLine::GetNewBook(inputSs, outputSs);
    
    XCTAssert(testBook.GetAuthor() == "testAuthor");
    XCTAssert(testBook.GetTitle() == "testTitle");
    XCTAssert(testBook.GetPublisher() == "testPublisher");
    XCTAssert(testBook.GetSeries() == "testSeries");
    XCTAssert(testBook.GetGenre() == rtl::fantasy);
    XCTAssert(testBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testBook.GetPageCount() == 123);
    XCTAssert(testBook.GetIsbn().size() == 1);
    XCTAssert(testBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testBook.GetOclc().size() == 1);
    XCTAssert(testBook.GetOclc().at(0) == "123456");
}

- (void)testGetNewReadBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\ntestTitle\n1234567890\n123456\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n1999-Oct-02\n9\n");
    
    rtl::ReadBook testReadBook = rtl::CommandLine::GetNewReadBook(inputSs, outputSs, 123);
    
    XCTAssert(testReadBook.GetReaderId() == 123);
    XCTAssert(testReadBook.GetAuthor() == "testAuthor");
    XCTAssert(testReadBook.GetTitle() == "testTitle");
    XCTAssert(testReadBook.GetPublisher() == "testPublisher");
    XCTAssert(testReadBook.GetSeries() == "testSeries");
    XCTAssert(testReadBook.GetGenre() == rtl::fantasy);
    XCTAssert(testReadBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testReadBook.GetPageCount() == 123);
    XCTAssert(testReadBook.PrintDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.GetRating() == 9);
    XCTAssert(testReadBook.GetIsbn().size() == 1);
    XCTAssert(testReadBook.GetIsbn().at(0) == "1234567890");
    XCTAssert(testReadBook.GetOclc().size() == 1);
    XCTAssert(testReadBook.GetOclc().at(0) == "123456");
}

- (void)testOutputLine {
    std::stringstream outputSs;
    
    rtl::CommandLine::OutputLine(outputSs, "test Input 23");
    
    char word[256];
    outputSs.getline(word, 256);
    XCTAssert(std::string(word) == "test Input 23");
    outputSs.getline(word, 256);
    XCTAssert(outputSs.eof());
}

- (void)testOutputLineVector {
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
