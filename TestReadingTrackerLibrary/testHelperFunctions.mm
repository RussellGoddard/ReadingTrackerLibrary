//
//  testHelper.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 3/20/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "HelperFunctions.hpp"
#include "StandardOutput.hpp"

@interface testHelper : XCTestCase

@end

@implementation testHelper

- (void)setUp {
}

- (void)tearDown {
}

- (void)testGenerateId {
    std::string test1 = "test input";
    std::string test2 = "input test";
    std::string test3 = "Robert Jordan";
    std::string test4 = "robert jordan";
    std::string test5 = "robertjordan";
    std::string test6 = "Robert Jordan The Eye of the World";
    std::string test7 = "Robert Jordan The Path of Daggers";
    
    XCTAssert(rtl::StandardOutput::GenerateId(test1) == "27f8e2");
    XCTAssert(rtl::StandardOutput::GenerateId(test2) == "281d72");
    XCTAssert(rtl::StandardOutput::GenerateId(test3) == "72d2ce");
    XCTAssert(rtl::StandardOutput::GenerateId(test4) == "72d2ce");
    XCTAssert(rtl::StandardOutput::GenerateId(test5) == "2a9d");
    XCTAssert(rtl::StandardOutput::GenerateId(test6) == "77b0cf3cbc95a4b81c");
    XCTAssert(rtl::StandardOutput::GenerateId(test7) == "7bc75959ace9d2a0");
}

- (void)testTrim {
    
    std::string test1 = "test1";
    std::string test2 = "   test2";
    std::string test3 = "test3   ";
    std::string test4 = "   test4   ";
    std::string test5 = " a  test5  b";
    std::string test6 = "\ttest6";
    std::string test7 = "test7 \n";
    std::string test8 = "  \v  test8    ";
    std::string test9 = "\ftest9\f";
    std::string test10 = "\rtest10           a   ";
    
    XCTAssert(rtl::Trim(test1) == "test1");
    XCTAssert(rtl::Trim(test2) == "test2");
    XCTAssert(rtl::Trim(test3) == "test3");
    XCTAssert(rtl::Trim(test4) == "test4");
    XCTAssert(rtl::Trim(test5) == "a  test5  b");
    XCTAssert(rtl::Trim(test6) == "test6");
    XCTAssert(rtl::Trim(test7) == "test7");
    XCTAssert(rtl::Trim(test8) == "test8");
    XCTAssert(rtl::Trim(test9) == "test9");
    XCTAssert(rtl::Trim(test10) == "test10           a");
}

@end
