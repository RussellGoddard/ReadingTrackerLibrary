//
//  test.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/7/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "Book.hpp"

@interface test : XCTestCase

@end

@implementation test

Book testBook;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    testBook.setAuthor("testAuthor");
    testBook.setTitle("testTitle");
    testBook.setSeries("testSeries");
    testBook.setPublisher("testPublisher");
    testBook.setGenre("fantasy");
    testBook.setPageCount(10);
    testBook.setPublishDate("Dec 01 1990");
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    
    XCTAssert("testAuthor" == testBook.getAuthor());
    XCTAssert("testTitle" == testBook.getTitle());
    XCTAssert("testSeries" == testBook.getSeries());
    XCTAssert("testPublisher" == testBook.getPublisher());
    XCTAssert("fantasy" == testBook.printGenre());
    XCTAssert(10 == testBook.getPageCount());
    XCTAssert("Dec 01 1990" == testBook.printPublishDate());
}

@end
