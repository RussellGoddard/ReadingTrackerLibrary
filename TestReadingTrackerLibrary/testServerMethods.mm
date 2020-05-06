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
    //serverMethodsTest.testDyanamodb(2, test);
}

- (void)test_LoadBooks_ReturnAllBooksInAWS {
    std::vector<rtl::Book> bookVector;
    
    bookVector = serverMethodsTest.LoadBooks();
    
    XCTAssert(bookVector.size() == 2);
    XCTAssert(bookVector.at(0).GetBookId() == "1c5fdaf7109aa47ef2");
    XCTAssert(bookVector.at(0).GetAuthors().at(0) == "Brandon Sanderson");
    XCTAssert(bookVector.at(0).GetAuthorId().at(0) == "1567187");
    XCTAssert(bookVector.at(0).PrintGenre() == "fantasy");
    XCTAssert(bookVector.at(0).GetIsbn().at(0) == "9780765311788");
    XCTAssert(bookVector.at(0).GetOclc().at(0) == "62342185");
    XCTAssert(bookVector.at(0).GetPageCount() == 541);
    XCTAssert(bookVector.at(0).PrintPublishDate() == "2006-Jul-17");
    XCTAssert(bookVector.at(0).GetPublisher() == "Tor Books");
    XCTAssert(bookVector.at(0).GetSeries() == "Mistborn");
    XCTAssert(bookVector.at(0).GetTitle() == "Mistborn: The Final Empire");
    
    XCTAssert(bookVector.at(1).GetBookId() == "3ffc6bac06439747e1b0");
    XCTAssert(bookVector.at(1).GetAuthors().at(0) == "Brandon Sanderson");
    XCTAssert(bookVector.at(1).GetAuthorId().at(0) == "1567187");
    XCTAssert(bookVector.at(1).PrintGenre() == "fantasy");
    XCTAssert(bookVector.at(1).GetIsbn().at(0) == "9780765316882");
    XCTAssert(bookVector.at(1).GetOclc().at(0) == "122715367");
    XCTAssert(bookVector.at(1).GetPageCount() == 590);
    XCTAssert(bookVector.at(1).PrintPublishDate() == "2007-Aug-21");
    XCTAssert(bookVector.at(1).GetPublisher() == "Tor Books");
    XCTAssert(bookVector.at(1).GetSeries() == "Mistborn");
    XCTAssert(bookVector.at(1).GetTitle() == "Mistborn: The Well of Ascension");
}

@end
