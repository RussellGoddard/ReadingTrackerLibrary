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
    
    inputSs.str("testAuthor\nNov 25 1998\n");
    
    rtl::Author testAuthor = getNewAuthor(inputSs, outputSs);
    
    XCTAssert(testAuthor.getName() == "testAuthor");
    XCTAssert(testAuthor.printDateBorn() == "Nov 25 1998");
}

- (void)testGetNewBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\ntestTitle\ntestPublisher\ntestSeries\nfantasy\nOct 01 1999\n123\n");
    
    rtl::Book testBook = getNewBook(inputSs, outputSs);
    
    XCTAssert(testBook.getAuthor() == "testAuthor");
    XCTAssert(testBook.getTitle() == "testTitle");
    XCTAssert(testBook.getPublisher() == "testPublisher");
    XCTAssert(testBook.getSeries() == "testSeries");
    XCTAssert(testBook.getGenre() == rtl::fantasy);
    XCTAssert(testBook.printPublishDate() == "Oct 01 1999");
    XCTAssert(testBook.getPageCount() == 123);
}

- (void)testGetNewReadBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\ntestTitle\ntestPublisher\ntestSeries\nfantasy\nOct 01 1999\n123\nOct 02 1999\n9\n");
    
    rtl::ReadBook testReadBook = getNewReadBook(inputSs, outputSs, 123);
    
    XCTAssert(testReadBook.getReaderId() == 123);
    XCTAssert(testReadBook.getAuthor() == "testAuthor");
    XCTAssert(testReadBook.getTitle() == "testTitle");
    XCTAssert(testReadBook.getPublisher() == "testPublisher");
    XCTAssert(testReadBook.getSeries() == "testSeries");
    XCTAssert(testReadBook.getGenre() == rtl::fantasy);
    XCTAssert(testReadBook.printPublishDate() == "Oct 01 1999");
    XCTAssert(testReadBook.getPageCount() == 123);
    XCTAssert(testReadBook.printDateRead() == "Oct 02 1999");
    XCTAssert(testReadBook.getRating() == 9);
}

- (void)testOutputLine {
    std::stringstream outputSs;
    
    outputLine(outputSs, "test Input 23");
    
    std::string word1, word2, word3;
    
    outputSs >> word1 >> word2 >> word3;
    
    XCTAssert(word1 == "test");
    XCTAssert(word2 == "Input");
    XCTAssert(word3 == "23");
}

@end
