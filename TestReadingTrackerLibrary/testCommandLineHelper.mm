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

- (void)testPrintCommandLineSimpleReadBook {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         541   2019-Sep-13  9     ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    480   2019-Nov-19  9     ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 70212 2019-Oct-27  8     ";

    rtl::ReadBook bookMist(123, "Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", 9, "2019-Sep-13");
    rtl::ReadBook bookGirl(123, "Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", 9, "2019-Nov-19");
    rtl::ReadBook bookWidth(123, "Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15", 8, "2019-Oct-27");
    
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::ReadBook>(bookMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::ReadBook>(bookGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::ReadBook>(bookWidth)) == testWidth);
}

- (void)testPrintCommandLineDetailedReadBook {
    std::string testMist = "Title:         Mistborn: The Final Empire                                       \nBookId:        1c5fdaf7109aa47ef2                                               \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2006-Jul-17                                                      \nISBN:          9780765311788                                                    \nOCLC:          62342185                                                         \nReaderId:      123                                                              \nRating:        9                                                                \nDate Read:     2019-Sep-13                                                      \n";
    std::string testGirl = "Title:         The Girl with the Dragon Tattoo                                  \nBookId:        2c844f9a4aac31a8848f80                                           \nAuthor Name:   Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nSeries:        Millennium                                                       \nGenre:         thriller                                                         \nPage Count:    480                                                              \nPublisher:     Norstedts Förlag                                                \nPublish Date:  2005-Aug-01                                                      \nISBN:          9781847242532                                                    \nOCLC:          186764078                                                        \nReaderId:      123                                                              \nRating:        9                                                                \nDate Read:     2019-Nov-19                                                      \n";
    std::string testWidth = "Title:         The Eye of the World123456789012345678901234567890123456789012345\nBookId:        cfcbb4cef513c9c904bf8                                            \nAuthor Name:   Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nSeries:        The Wheel of Time123456789012345678901234567890123456789012345678\nGenre:         fantasy                                                          \nPage Count:    70212                                                            \nPublisher:     Tor Books12345678901234567890123456789012345678901234567890123456\nPublish Date:  1990-Jan-15                                                      \nISBN:          19723327, 1234567890, 1234567890, 1234567890, 1234567890, 1234567\nOCLC:          0312850093, 1234567890, 1234567890, 1234567890, 1234567890, 12345\nReaderId:      123                                                              \nRating:        8                                                                \nDate Read:     2019-Oct-27                                                      \n";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", std::vector<std::string> {"9780765311788"}, std::vector<std::string> {"62342185"});
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", std::vector<std::string> {"9781847242532"}, std::vector<std::string> {"186764078"});
    rtl::Book bookWidth("Robert Jordan123456789012345678901234567890123456789012345678901234567890", "The Eye of the World12345678901234567890123456789012345678901234567890", "The Wheel of Time12345678901234567890123456789012345678901234567890", "Tor Books123456789012345678901234567890123456789012345678901234567890", 70212, "fantasy", "1990-Jan-15", std::vector<std::string> {"19723327", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"}, std::vector<std::string> {"0312850093", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"});
    
    rtl::ReadBook readBookMist(123, bookMist, 9, "2019-Sep-13");
    rtl::ReadBook readBookGirl(123, bookGirl, 9, "2019-Nov-19");
    rtl::ReadBook readBookWidth(123, bookWidth, 8, "2019-Oct-27");
    
    std::cout << rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::ReadBook>(readBookGirl)) << std::endl;
    std::cout << testGirl << std::endl;
    
    std::cout << rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::ReadBook>(readBookGirl)).compare(testGirl) << std::endl;
    
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::ReadBook>(readBookMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::ReadBook>(readBookGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::ReadBook>(readBookWidth)) == testWidth);
}

- (void)testPrintBookColumnHeaders {
    std::string testStr = "Author              Title                              Series              Pages";
    
    XCTAssert(rtl::CommandLine::PrintBookCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLineSimpleBook {
    std::string testMist = "Brandon Sanderson   Mistborn: The Final Empire         Mistborn            541  ";
    std::string testGirl = "Stieg Larsson       The Girl with the Dragon Tattoo    Millennium          480  ";
    std::string testWidth = "Robert Jordan123456 The Eye of the World12345678901234 The Wheel of Time12 70212";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17");
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01");
    rtl::Book bookWidth("Robert Jordan1234567", "The Eye of the World123456789012345", "The Wheel of Time123", "Tor Books", 70212, "fantasy", "1990-Jan-15");
    
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::Book>(bookMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::Book>(bookGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::Book>(bookWidth)) == testWidth);
}

- (void)testPrintCommandLineDetailedBook {
    std::string testMist = "Title:         Mistborn: The Final Empire                                       \nBookId:        1c5fdaf7109aa47ef2                                               \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2006-Jul-17                                                      \nISBN:          9780765311788                                                    \nOCLC:          62342185                                                         \n";
    std::string testGirl = "Title:         The Girl with the Dragon Tattoo                                  \nBookId:        2c844f9a4aac31a8848f80                                           \nAuthor Name:   Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nSeries:        Millennium                                                       \nGenre:         thriller                                                         \nPage Count:    480                                                              \nPublisher:     Norstedts Förlag                                                \nPublish Date:  2005-Aug-01                                                      \nISBN:          9781847242532                                                    \nOCLC:          186764078                                                        \n";
    std::string testWidth = "Title:         The Eye of the World123456789012345678901234567890123456789012345\nBookId:        cfcbb4cef513c9c904bf8                                            \nAuthor Name:   Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nSeries:        The Wheel of Time123456789012345678901234567890123456789012345678\nGenre:         fantasy                                                          \nPage Count:    70212                                                            \nPublisher:     Tor Books12345678901234567890123456789012345678901234567890123456\nPublish Date:  1990-Jan-15                                                      \nISBN:          19723327, 1234567890, 1234567890, 1234567890, 1234567890, 1234567\nOCLC:          0312850093, 1234567890, 1234567890, 1234567890, 1234567890, 12345\n";
    
    rtl::Book bookMist("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", std::vector<std::string> {"9780765311788"}, std::vector<std::string> {"62342185"});
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", std::vector<std::string> {"9781847242532"}, std::vector<std::string> {"186764078"});
    rtl::Book bookWidth("Robert Jordan123456789012345678901234567890123456789012345678901234567890", "The Eye of the World12345678901234567890123456789012345678901234567890", "The Wheel of Time12345678901234567890123456789012345678901234567890", "Tor Books123456789012345678901234567890123456789012345678901234567890", 70212, "fantasy", "1990-Jan-15", std::vector<std::string> {"19723327", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"}, std::vector<std::string> {"0312850093", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"});
    
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::Book>(bookMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::Book>(bookGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::Book>(bookWidth)) == testWidth);
}

- (void)testPrintAuthorColumnHeaders {
    std::string testStr = "Author              Date Born   Books Written                               Year";
    
    XCTAssert(rtl::CommandLine::PrintAuthorCommandLineHeaders() == testStr);
}

- (void)testPrintCommandLineSimpleAuthor {
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
    
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::Author>(authorMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::Author>(authorGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLineSimple(std::make_shared<rtl::Author>(authorWidth)) == testWidth);
}

- (void)testPrintCommandLineDetailedAuthor {
    std::string testMist = "Name:          Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nDate Born:     1975-Dec-19                                                      \nBooks Written:                                                                  \nTitle:         Mistborn: The Final Empire                                       \nBookId:        1c5fdaf7109aa47ef2                                               \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2006-Jul-17                                                      \nISBN:          9780765311788                                                    \nOCLC:          62342185                                                         \nTitle:         Mistborn: The Well of Ascension                                  \nBookId:        3ffc6bac06439747e1b0                                             \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2007-Jul-17                                                      \nISBN:                                                                           \nOCLC:                                                                           \nTitle:         Mistborn: The Hero of Ages                                       \nBookId:        ca903ec590e706e8318                                              \nAuthor Name:   Brandon Sanderson                                                \nAuthorId:      1567187                                                          \nSeries:        Mistborn                                                         \nGenre:         fantasy                                                          \nPage Count:    541                                                              \nPublisher:     Tor Books                                                        \nPublish Date:  2008-Jul-17                                                      \nISBN:                                                                           \nOCLC:                                                                           \n";
    std::string testGirl = "Name:          Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nDate Born:     1964-Aug-15                                                      \nBooks Written:                                                                  \nTitle:         The Girl with the Dragon Tattoo                                  \nBookId:        2c844f9a4aac31a8848f80                                           \nAuthor Name:   Stieg Larsson                                                    \nAuthorId:      7052c8                                                           \nSeries:        Millennium                                                       \nGenre:         thriller                                                         \nPage Count:    480                                                              \nPublisher:     Norstedts Förlag                                                \nPublish Date:  2005-Aug-01                                                      \nISBN:          9781847242532                                                    \nOCLC:          186764078                                                        \n";
    std::string testWidth = "Name:          Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nDate Born:     1948-Oct-17                                                      \nBooks Written:                                                                  \nTitle:         The Eye of the World123456789012345678901234567890123456789012345\nBookId:        cfcbb4cef513c9c904bf8                                            \nAuthor Name:   Robert Jordan1234567890123456789012345678901234567890123456789012\nAuthorId:      2766def2                                                         \nSeries:        The Wheel of Time123456789012345678901234567890123456789012345678\nGenre:         fantasy                                                          \nPage Count:    70212                                                            \nPublisher:     Tor Books12345678901234567890123456789012345678901234567890123456\nPublish Date:  1990-Jan-15                                                      \nISBN:          19723327, 1234567890, 1234567890, 1234567890, 1234567890, 1234567\nOCLC:          0312850093, 1234567890, 1234567890, 1234567890, 1234567890, 12345\n";
    
    rtl::Book bookMist2("Brandon Sanderson", "Mistborn: The Well of Ascension", "Mistborn", "Tor Books", 541, "fantasy", "2007-Jul-17");
    rtl::Book bookMist3("Brandon Sanderson", "Mistborn: The Hero of Ages", "Mistborn", "Tor Books", 541, "fantasy", "2008-Jul-17");
    
    rtl::Book bookMist1("Brandon Sanderson", "Mistborn: The Final Empire", "Mistborn", "Tor Books", 541, "fantasy", "2006-Jul-17", std::vector<std::string> {"9780765311788"}, std::vector<std::string> {"62342185"});
    rtl::Book bookGirl("Stieg Larsson", "The Girl with the Dragon Tattoo", "Millennium", "Norstedts Förlag", 480, "thriller", "2005-Aug-01", std::vector<std::string> {"9781847242532"}, std::vector<std::string> {"186764078"});
    rtl::Book bookWidth("Robert Jordan123456789012345678901234567890123456789012345678901234567890", "The Eye of the World12345678901234567890123456789012345678901234567890", "The Wheel of Time12345678901234567890123456789012345678901234567890", "Tor Books123456789012345678901234567890123456789012345678901234567890", 70212, "fantasy", "1990-Jan-15", std::vector<std::string> {"19723327", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"}, std::vector<std::string> {"0312850093", "1234567890", "1234567890", "1234567890", "1234567890", "1234567890"});
    
    std::vector<std::shared_ptr<rtl::Book>> mistbornVector;
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist1));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist2));
    mistbornVector.push_back(std::make_shared<rtl::Book>(bookMist3));
    
    rtl::Author authorMist("Brandon Sanderson", "1975-Dec-19", mistbornVector);
    rtl::Author authorGirl("Stieg Larsson", "1964-Aug-15");
    authorGirl.AddBookWritten(std::make_shared<rtl::Book>(bookGirl));
    rtl::Author authorWidth("Robert Jordan123456789012345678901234567890123456789012345678901234567890");
    authorWidth.SetDateBorn("1948-Oct-17");
    authorWidth.AddBookWritten(std::make_shared<rtl::Book>(bookWidth));
    
    std::cout << rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::Author>(authorWidth)) << std::endl;
    
    std::cout << testWidth << std::endl;
    
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::Author>(authorMist)) == testMist);
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::Author>(authorGirl)) == testGirl);
    XCTAssert(rtl::CommandLine::PrintCommandLineDetailed(std::make_shared<rtl::Author>(authorWidth)) == testWidth);
}

@end
