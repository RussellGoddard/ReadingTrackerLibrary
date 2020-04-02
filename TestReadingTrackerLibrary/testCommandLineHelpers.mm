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

- (void)test_PrintHeaderNumber {
    XCTAssert(rtl::CommandLine::PrintHeaderNumber() == "#: ");
}

- (void)test_PrintNumberSelector_PassInt_ReturnIntPlusString {
    XCTAssert(rtl::CommandLine::PrintNumberSelector(3) == "3: ");
}

@end
