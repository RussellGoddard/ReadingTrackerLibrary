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

rtl::ServerMethods& serverMethodsTest = rtl::ServerMethods::GetInstance(true);
rtl::InMemoryContainers& testFileContainer = rtl::InMemoryContainers::GetInstance();

//TODO: need to clear tables after all tests

- (void)setUp {
}

- (void)tearDown {
    testFileContainer.ClearAll();
}

- (void)test_Dynamodb {
    std::vector<std::string> test = {"name"};
    //serverMethodsTest.testDyanamodb(2, test);
}

- (void)test_AddBook_LoadBooks_PassBookToAws_RetrieveSameBookFromAws {
    /*
     Book(std::vector<std::string> authors, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::vector<std::string> isbn = {}, std::vector<std::string> oclc = {});
     */
    rtl::Book finalEmpire({"Brandon Sanderson"}, "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", {"9780765311788"}, {"62342185"});
    rtl::Book wellAscension({"Brandon Sanderson"}, "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 590, "fantasy", "2007-Aug-21", {"9780765316882"}, {"122715367"});
    rtl::Book heroAges({"Brandon Sanderson"}, "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 572, "fantasy", "2008-Oct-14", {"9780765356147"}, {"191245491"});
    
    XCTAssert(serverMethodsTest.AddBook(std::make_shared<rtl::Book>(finalEmpire)));
    XCTAssert(serverMethodsTest.AddBook(std::make_shared<rtl::Book>(wellAscension)));
    XCTAssert(serverMethodsTest.AddBook(std::make_shared<rtl::Book>(heroAges)));
    
    std::vector<std::shared_ptr<rtl::Book>> bookVector;
    bookVector = serverMethodsTest.LoadBooks();
    
    bool foundEmpire, foundWell, foundHero;
    XCTAssert(bookVector.size() == 3);
    
    for (auto x : bookVector) {
        if (*x == finalEmpire) {
            foundEmpire = true;
        }
        else if (*x == wellAscension) {
            foundWell = true;
        }
        else if (*x == heroAges) {
            foundHero = true;
        }
    }
    
    XCTAssert(foundEmpire);
    XCTAssert(foundWell);
    XCTAssert(foundHero);
    XCTAssert(testFileContainer.GetMasterBooks().size() == 3);
    
    foundEmpire = false;
    foundWell = false;
    foundHero = false;
    
    for (auto x : testFileContainer.GetMasterBooks()) {
        if (*x == finalEmpire) {
            foundEmpire = true;
        }
        else if (*x == wellAscension) {
            foundWell = true;
        }
        else if (*x == heroAges) {
            foundHero = true;
        }
    }
    
    XCTAssert(foundEmpire);
    XCTAssert(foundWell);
    XCTAssert(foundHero);
}

- (void)test_AddReadBook_LoadReadBooks_PassReadBookToAws_RetrieveSameReadBookFromAws {
    /*
     ReadBook(std::string readerId, Book book, int rating, std::string dateRead);
     */
    rtl::Book finalEmpire({"Brandon Sanderson"}, "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", {"9780765311788"}, {"62342185"});
    rtl::Book wellAscension({"Brandon Sanderson"}, "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 590, "fantasy", "2007-Aug-21", {"9780765316882"}, {"122715367"});
    rtl::Book heroAges({"Brandon Sanderson"}, "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 572, "fantasy", "2008-Oct-14", {"9780765356147"}, {"191245491"});
    
    rtl::ReadBook readFinalEmpire("123", finalEmpire, 9, "2019-Sep-13");
    rtl::ReadBook readWellAscension("123", wellAscension, 8, "2019-Sep-30");
    rtl::ReadBook readHeroAges("123", heroAges, 7, "2019-Oct-15");
    
    XCTAssert(serverMethodsTest.AddReadBook(std::make_shared<rtl::ReadBook>(readFinalEmpire)));
    XCTAssert(serverMethodsTest.AddReadBook(std::make_shared<rtl::ReadBook>(readWellAscension)));
    XCTAssert(serverMethodsTest.AddReadBook(std::make_shared<rtl::ReadBook>(readHeroAges)));
    
    std::vector<std::shared_ptr<rtl::ReadBook>> readbookVector;
    readbookVector = serverMethodsTest.LoadReadBooks();
    
    bool foundEmpire, foundWell, foundHero;
    XCTAssert(readbookVector.size() == 3);
    
    for (auto x : readbookVector) {
        if (*x == finalEmpire) {
            foundEmpire = true;
        }
        else if (*x == wellAscension) {
            foundWell = true;
        }
        else if (*x == heroAges) {
            foundHero = true;
        }
    }
    
    XCTAssert(foundEmpire);
    XCTAssert(foundWell);
    XCTAssert(foundHero);
    XCTAssert(testFileContainer.GetMasterReadBooks().size() == 3);
    
    foundEmpire = false;
    foundWell = false;
    foundHero = false;
    
    for (auto x : testFileContainer.GetMasterReadBooks()) {
        if (*x == finalEmpire) {
            foundEmpire = true;
        }
        else if (*x == wellAscension) {
            foundWell = true;
        }
        else if (*x == heroAges) {
            foundHero = true;
        }
    }
    
    XCTAssert(foundEmpire);
    XCTAssert(foundWell);
    XCTAssert(foundHero);
}

- (void)test_AddAuthor_LoadAuthors_PassAuthorToAws_RetrieveSameAuthorFromAwsAndAuthorsInMemoryContainer {
    /*
     Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten = {});
     */
    rtl::Book finalEmpire({"Brandon Sanderson"}, "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", {"9780765311788"}, {"62342185"});
    rtl::Book wellAscension({"Brandon Sanderson"}, "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 590, "fantasy", "2007-Aug-21", {"9780765316882"}, {"122715367"});
    rtl::Book heroAges({"Brandon Sanderson"}, "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 572, "fantasy", "2008-Oct-14", {"9780765356147"}, {"191245491"});
    
    rtl::Author newAuthor("Brandon Sanderson", "1975-Dec-19", {std::make_shared<rtl::Book>(finalEmpire), std::make_shared<rtl::Book>(wellAscension), std::make_shared<rtl::Book>(heroAges)});
    
    XCTAssert(serverMethodsTest.AddAuthor(std::make_shared<rtl::Author>(newAuthor)));
    
    std::vector<std::shared_ptr<rtl::Author>> authorVector;
    authorVector = serverMethodsTest.LoadAuthors();

    XCTAssert(authorVector.size() == 1);
    XCTAssert(*authorVector.at(0) == newAuthor);
    
    bool foundEmpire, foundWell, foundHero;
    XCTAssert(authorVector.at(0)->GetBooksWritten().size() == 3);
    
    for (auto x : authorVector.at(0)->GetBooksWritten()) {
        if (*x == finalEmpire) {
            foundEmpire = true;
        }
        else if (*x == wellAscension) {
            foundWell = true;
        }
        else if (*x == heroAges) {
            foundHero = true;
        }
    }
    
    XCTAssert(foundEmpire);
    XCTAssert(foundWell);
    XCTAssert(foundHero);
    
    XCTAssert(testFileContainer.GetMasterAuthors().size() == 1);
    XCTAssert(*testFileContainer.GetMasterAuthors().at(0) == *authorVector.at(0));
}

@end
