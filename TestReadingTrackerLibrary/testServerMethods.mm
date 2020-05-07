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

- (void)test_AddBookAndLoadBooks_PassBookToAws_RetrieveSameBookFromAws {
    /*
     Book(std::vector<std::string> authors, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::vector<std::string> isbn = {}, std::vector<std::string> oclc = {});
     */
    rtl::Book finalEmpire({"Brandon Sanderson"}, "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", {"9780765311788"}, {"62342185"});
    rtl::Book wellAscension({"Brandon Sanderson"}, "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 590, "fantasy", "2007-Aug-21", {"9780765316882"}, {"122715367"});
    rtl::Book heroAges({"Brandon Sanderson"}, "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 572, "fantasy", "2008-Oct-14", {"9780765356147"}, {"191245491"});
    
    XCTAssert(serverMethodsTest.AddBook(std::make_shared<rtl::Book>(finalEmpire)));
    XCTAssert(serverMethodsTest.AddBook(std::make_shared<rtl::Book>(wellAscension)));
    XCTAssert(serverMethodsTest.AddBook(std::make_shared<rtl::Book>(heroAges)));
    
    
    std::vector<rtl::Book> bookVector;
    
    bookVector = serverMethodsTest.LoadBooks();
    
    
    bool foundEmpire, foundWell, foundHero;
    XCTAssert(bookVector.size() == 3);
    
    for (auto x : bookVector) {
        if (x == finalEmpire) {
            foundEmpire = true;
        }
        else if (x == wellAscension) {
            foundWell = true;
        }
        else if (x == heroAges) {
            foundHero = true;
        }
    }
    
    XCTAssert(foundEmpire);
    XCTAssert(foundWell);
    XCTAssert(foundHero);
}



@end
