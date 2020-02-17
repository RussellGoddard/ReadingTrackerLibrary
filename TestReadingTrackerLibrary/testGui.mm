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

/*
 outputLine("Input author");
 input = getInput(inputStream);
 newReadBook.setAuthor(input);
 outputLine("Input title");
 input = getInput(inputStream);
 newReadBook.setTitle(input);
 outputLine("Input publisher");
 input = getInput(inputStream);
 newReadBook.setPublisher(input);
 outputLine("Input series");
 input = getInput(inputStream);
 newReadBook.setSeries(input);
 outputLine("Input genre");
 input = getInput(inputStream);
 newReadBook.setGenre(input);
 outputLine("Input date published");
 input = getInput(inputStream);
 newReadBook.setPublishDate(input);
 outputLine("Input page count");
 input = getInput(inputStream);
 newReadBook.setPageCount(stoi(input));
 outputLine("Input date you finished reading");
 input = getInput(inputStream);
 newReadBook.setDateRead(input);
 outputLine("On a scale of 1 - 10 rate the book");
 input = getInput(inputStream);
 newReadBook.setRating(stoi(input));
 */

- (void)testGetNewReadBook {
    std::stringstream inputSs, outputSs;
    
    inputSs.str("testAuthor\ntestTitle\ntestPublisher\ntestSeries\nfantasy\nOct 01 1999\n123\nOct 02 1999\n9\n");
    
    ReadBook testReadBook = getNewReadBook(inputSs, outputSs);
    
    XCTAssert(testReadBook.getAuthor() == "testAuthor");
    XCTAssert(testReadBook.getTitle() == "testTitle");
    XCTAssert(testReadBook.getPublisher() == "testPublisher");
    XCTAssert(testReadBook.getSeries() == "testSeries");
    XCTAssert(testReadBook.getGenre() == fantasy);
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
