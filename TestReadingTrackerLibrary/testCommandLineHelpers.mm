//
//  testCommandLineHelpers.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 3/26/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "CommandLineHelpers.hpp"

@interface testCommandLineHelpers : XCTestCase

@end

@implementation testCommandLineHelpers

- (void)setUp {
}

- (void)tearDown {
}

- (void)testPrintHeaderNumber {
    XCTAssert(rtl::CommandLine::PrintHeaderNumber() == "#: ");
}

- (void)testPrintNumberSelector {
    XCTAssert(rtl::CommandLine::PrintNumberSelector(3) == "3: ");
}

@end
