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

- (void)test_GenerateId {
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

- (void)test_RemoveNonPrintChar_PassInvalidCharacters_ReturnOnlyValidString {
    std::string test1 = "\nhi\n";
    std::string test2 = "\a\b\t\n\v\f\r\e";
    std::string test3 = "The Quick Brown Fox Jumped Over The Lazy Moon";
    std::string test4 = "1 2 3 456 7 8 90";
    
    XCTAssert(rtl::StandardOutput::RemoveNonPrint(test1) == "hi");
    XCTAssert(rtl::StandardOutput::RemoveNonPrint(test2) == "");
    XCTAssert(rtl::StandardOutput::RemoveNonPrint(test3) == "The Quick Brown Fox Jumped Over The Lazy Moon");
    XCTAssert(rtl::StandardOutput::RemoveNonPrint(test4) == "1 2 3 456 7 8 90");
}

- (void)test_Trim {
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

- (void)test_ConvertGenreToString_PassDetective_ReturnDetective {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::detective) == "detective");
}

- (void)test_ConvertGenreToString_PassDystopia_ReturnDystopia {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::dystopia) == "dystopia");
}

- (void)test_ConvertGenreToString_PassFantasy_ReturnFantasy {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::fantasy) == "fantasy");
}

- (void)test_ConvertGenreToString_PassMystery_ReturnMystery {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::mystery) == "mystery");
}

- (void)test_ConvertGenreToString_PassNonFiction_ReturnNonFiction {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::nonFiction) == "non-fiction");
}

- (void)test_ConvertGenreToString_PassRomance_ReturnRomance {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::romance) == "romance");
}

- (void)test_ConvertGenreToString_PassScienceFiction_ReturnScienceFiction {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::scienceFiction) == "science fiction");
}

- (void)test_ConvertGenreToString_PassTechnical_ReturnTechnical {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::technical) == "technical");
}

- (void)test_ConvertGenreToString_PassThriller_ReturnThriller {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::thriller) == "thriller");
}

- (void)test_ConvertGenreToString_PassWestern_ReturnWestern {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::western) == "western");
}

- (void)test_ConvertGenreToString_PassGenreNotSet_ReturnGenreNotSet {
    XCTAssert(rtl::ConvertGenreToString(rtl::Genre::genreNotSet) == "genre not set");
}

- (void)test_ConvertStringToGenre_PassDetective_ReturnDetective {
    XCTAssert(rtl::ConvertStringToGenre("detective") == rtl::Genre::detective);
}

- (void)test_ConvertStringToGenre_PassDystopia_ReturnDystopia {
    XCTAssert(rtl::ConvertStringToGenre("dystopia") == rtl::Genre::dystopia);
}

- (void)test_ConvertStringToGenre_PassFantasy_ReturnFantasy {
    XCTAssert(rtl::ConvertStringToGenre("fantasy") == rtl::Genre::fantasy);
}

- (void)test_ConvertStringToGenre_PassMystery_ReturnMystery {
    XCTAssert(rtl::ConvertStringToGenre("mystery") == rtl::Genre::mystery);
}

- (void)test_ConvertStringToGenre_PassNonHyphenFiction_ReturnNonFiction {
    XCTAssert(rtl::ConvertStringToGenre("non-fiction") == rtl::Genre::nonFiction);
}

- (void)test_ConvertStringToGenre_PassNonFiction_ReturnNonFiction {
    XCTAssert(rtl::ConvertStringToGenre("nonfiction") == rtl::Genre::nonFiction);
}

- (void)test_ConvertStringToGenre_PassRomance_ReturnRomance {
    XCTAssert(rtl::ConvertStringToGenre("romance") == rtl::Genre::romance);
}

- (void)test_ConvertStringToGenre_PassScienceFiction_ReturnScienceFiction {
    XCTAssert(rtl::ConvertStringToGenre("science fiction") == rtl::Genre::scienceFiction);
}

- (void)test_ConvertStringToGenre_PassSciFi_ReturnScienceFiction {
    XCTAssert(rtl::ConvertStringToGenre("sci fi") == rtl::Genre::scienceFiction);
}

- (void)test_ConvertStringToGenre_PassTechnical_ReturnTechnical {
    XCTAssert(rtl::ConvertStringToGenre("technical") == rtl::Genre::technical);
}

- (void)test_ConvertStringToGenre_PassThriller_ReturnThriller {
    XCTAssert(rtl::ConvertStringToGenre("thriller") == rtl::Genre::thriller);
}

- (void)test_ConvertStringToGenre_PassWestern_ReturnWestern {
    XCTAssert(rtl::ConvertStringToGenre("western") == rtl::Genre::western);
}

- (void)test_ConvertStringToGenre_PassInvalidGenre_ReturnGenreNotSet {
    XCTAssert(rtl::ConvertStringToGenre("asdf") == rtl::Genre::genreNotSet);
}

@end
