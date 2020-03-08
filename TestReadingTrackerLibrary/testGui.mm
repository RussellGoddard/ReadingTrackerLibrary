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
    
    rtl::Author testAuthor = rtlCommandLine::getNewAuthor(inputSs, outputSs);
    
    XCTAssert(testAuthor.getName() == "testAuthor");
    XCTAssert(testAuthor.printDateBorn() == "1998-Nov-25");
}

- (void)testGetNewBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n");
    
    rtl::Book testBook = rtlCommandLine::getNewBook(inputSs, outputSs);
    
    XCTAssert(testBook.getAuthor() == "testAuthor");
    XCTAssert(testBook.getTitle() == "testTitle");
    XCTAssert(testBook.getPublisher() == "testPublisher");
    XCTAssert(testBook.getSeries() == "testSeries");
    XCTAssert(testBook.getGenre() == rtl::fantasy);
    XCTAssert(testBook.printPublishDate() == "1999-Oct-01");
    XCTAssert(testBook.getPageCount() == 123);
}

- (void)testGetNewReadBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\ntestTitle\ntestPublisher\ntestSeries\nfantasy\n1999-Oct-01\n123\n1999-Oct-02\n9\n");
    
    rtl::ReadBook testReadBook = rtlCommandLine::getNewReadBook(inputSs, outputSs, 123);
    
    XCTAssert(testReadBook.getReaderId() == 123);
    XCTAssert(testReadBook.getAuthor() == "testAuthor");
    XCTAssert(testReadBook.getTitle() == "testTitle");
    XCTAssert(testReadBook.getPublisher() == "testPublisher");
    XCTAssert(testReadBook.getSeries() == "testSeries");
    XCTAssert(testReadBook.getGenre() == rtl::fantasy);
    XCTAssert(testReadBook.printPublishDate() == "1999-Oct-01");
    XCTAssert(testReadBook.getPageCount() == 123);
    XCTAssert(testReadBook.printDateRead() == "1999-Oct-02");
    XCTAssert(testReadBook.getRating() == 9);
}

- (void)testOutputLine {
    std::stringstream outputSs;
    
    rtlCommandLine::outputLine(outputSs, "test Input 23");
    
    std::string word1, word2, word3;
    
    outputSs >> word1 >> word2 >> word3;
    
    XCTAssert(word1 == "test");
    XCTAssert(word2 == "Input");
    XCTAssert(word3 == "23");
}

@end
