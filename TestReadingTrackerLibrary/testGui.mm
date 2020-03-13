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
    
    rtl::Author testAuthor = rtlCommandLine::GetNewAuthor(inputSs, outputSs);
    
    XCTAssert(testAuthor.GetName() == "testAuthor");
    XCTAssert(testAuthor.PrintDateBorn() == "1998-Nov-25");
}

- (void)testGetNewBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n");
    
    rtl::Book testBook = rtlCommandLine::GetNewBook(inputSs, outputSs);
    
    XCTAssert(testBook.GetAuthor() == "testAuthor");
    XCTAssert(testBook.GetTitle() == "testTitle");
    XCTAssert(testBook.GetPublisher() == "testPublisher");
    XCTAssert(testBook.GetSeries() == "testSeries");
    XCTAssert(testBook.GetGenre() == rtl::fantasy);
    XCTAssert(testBook.PrintPublishDate() == "1999-Oct-01");
    XCTAssert(testBook.GetPageCount() == 123);
}

- (void)testGetNewReadBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n1999-Oct-02\n9\n");
    
    rtl::ReadBook testReadBook = rtlCommandLine::GetNewReadBook(inputSs, outputSs, 123);
    
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
}

- (void)testOutputLine {
    std::stringstream outputSs;
    
    rtlCommandLine::OutputLine(outputSs, "test Input 23");
    
    std::string word1, word2, word3;
    outputSs >> word1 >> word2 >> word3;
    
    XCTAssert(word1 == "test");
    XCTAssert(word2 == "Input");
    XCTAssert(word3 == "23");
}

@end
