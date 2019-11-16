//
//  testClassAuthor.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/15/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "Author.hpp"

@interface testClassAuthor : XCTestCase

@end

@implementation testClassAuthor

- (void)setUp {
}

- (void)tearDown {
}

- (void)testSetName {
    Author testAuthor("testAuthor");
    XCTAssert("testAuthor" == testAuthor.getName());
    testAuthor.setName("pickle");
    XCTAssert("pickle" == testAuthor.getName());
}

- (void)testSetDateBorn {
    Author testAuthor("testAuthor");
    time_t testValue = 1573862400;
    testAuthor.setDateBorn(testValue);
    tm initialTm = *std::gmtime(&testValue);
    tm testTm = testAuthor.getDateBorn();
    
    XCTAssert(std::mktime(&initialTm) == std::mktime(&testTm));
    XCTAssert(1573880400 == testAuthor.getDateBornTimeT());
    XCTAssert("Nov 16 2019" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("Dec ab 2000");
    XCTAssert("Nov 16 2019" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("Dec -8 1990");
    XCTAssert("Nov 16 2019" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("Dec 01 1890");
    XCTAssert("Nov 16 2019" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("Dec 01 1990");
    XCTAssert(660045600 == testAuthor.getDateBornTimeT());
    XCTAssert("Dec 01 1990" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("invalid string");
    XCTAssert("Dec 01 1990" == testAuthor.printDateBorn());
    
    testAuthor.setDateBorn("AAA 01 3453");
    XCTAssert("Dec 01 1990" == testAuthor.printDateBorn());
    
    
}

@end
