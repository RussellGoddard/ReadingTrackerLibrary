//
//  testFileMethods.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/24/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <vector>
#include "FileMethods.hpp"

@interface testFileMethods : XCTestCase

@end

@implementation testFileMethods

- (void)setUp {
}

- (void)tearDown {
}

- (void)testLoadReadingList {
    std::string testFile = "./testFileLoad.txt";
    
    std::vector<nlohmann::json> loadJson = loadReadingList(testFile);
    
    XCTAssert(4 == loadJson.size());
}


@end
