//
//  testServerMethods.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 4/20/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "ServerMethods.hpp"

@interface testServerMethods : XCTestCase

@end

@implementation testServerMethods

rtl::ServerMethods& serverMethodsTest = rtl::ServerMethods::GetInstance();

- (void)setUp {
}

- (void)tearDown {
}

- (void)test_Dynamodb {
    std::vector<std::string> test = {"name"};
    serverMethodsTest.testDyanamodb(2, test);
}

@end
