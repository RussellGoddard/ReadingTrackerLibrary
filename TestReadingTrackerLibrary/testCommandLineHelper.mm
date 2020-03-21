//
//  CommandLineHelper.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 3/21/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "CommandLineHelper.hpp"

@interface CommandLineHelper : XCTestCase

@end

@implementation CommandLineHelper

- (void)setUp {
}

- (void)tearDown {
}

- (void)testPrintReadBookColumnHeaders {
    std::string testStr = "Author              Title                              Pages Date Read    Rating";
    
    XCTAssert(rtl::CommandLine::PrintReadBookCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLineReadBook {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         541   2019-Sep-13  9     ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    480   2019-Nov-19  9     ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 70212 2019-Oct-27  8     ";

    rtl::ReadBook bookMist(123, "Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", 9, "2019-Sep-13");
    rtl::ReadBook bookGirl(123, "Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", 9, "2019-Nov-19");
    rtl::ReadBook bookWidth(123, "Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15", 8, "2019-Oct-27");
    
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::ReadBook>(bookMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::ReadBook>(bookGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::ReadBook>(bookWidth)) == testWidth);
}

- (void)testPrintBookColumnHeaders {
    std::string testStr = "Author              Title                              Series              Pages";
    
    XCTAssert(rtl::CommandLine::PrintBookCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLineBook {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541  ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    Millennium          480  ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 The Wheel of Time12 70212";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15");
    
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::Book>(bookMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::Book>(bookGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::Book>(bookWidth)) == testWidth);
}

- (void)testPrintAuthorColumnHeaders {
    std::string testStr = "Author              Date Born   Books Written                               Year";
    
    XCTAssert(rtl::CommandLine::PrintAuthorCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLineAuthor {
    std::string testMist = "Brandon Sanderson   1975-Dec-19 Mistborn: The Final Empire                  2006\n                                Mistborn: The Well of Ascension             2007\n                                Mistborn: The Hero of Ages                  2008";
    std::string testGirl = "Stieg Larsson       1964-Aug-15 The Girl with the Dragon Tattoo             2005";
    std::string testWidth = "Robert Jordan123456 1948-Oct-17 The Eye of the World12345678901234567890123 1990";
    
    rtl::Book bookMist1("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17");
    rtl::Book bookMist2("Brandon Sanderson", "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 541, "fantasy", "2007-Jul-17");
    rtl::Book bookMist3("Brandon Sanderson", "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 541, "fantasy", "2008-Jul-17");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World1234567890123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15");
    
    std::vector<std::shared_ptr<rtl::Book>> mistbornVector;
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist1));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist2));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist3));
    
    rtl::Author authorMist("Brandon Sanderson", "1975-Dec-19", mistbornVector);
    rtl::Author authorGirl("Stieg Larsson", "1964-Aug-15");
    authorGirl.AddBookWritten(std::make_shared<rtl::Book>(bookGirl));
    rtl::Author authorWidth("Robert Jordan1234567");
    authorWidth.SetDateBorn("1948-Oct-17");
    authorWidth.AddBookWritten(std::make_shared<rtl::Book>(bookWidth));
    
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::Author>(authorMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::Author>(authorGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLine(std::make_shared<rtl::Author>(authorWidth)) == testWidth);
}

@end
