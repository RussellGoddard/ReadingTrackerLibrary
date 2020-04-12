//
//  testFileMethods.m
//  TestReadingTrackerLibrary
//
//  Created by Frobu on 11/24/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <filesystem>
#include <vector>
#include "FileMethods.hpp"

@interface testFileMethods : XCTestCase

@end

@implementation testFileMethods

rtl::InMemoryContainers& testContainer = rtl::InMemoryContainers::GetInstance();

- (void)setUp {
}

- (void)tearDown {
    testContainer.ClearAll();
}

- (void)test_AddMasterReadBooks_PassSharedPtrReadBook_ThenReadBookAndBookVectorHaveNewBook {
    rtl::ReadBook testReadBook1(1, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    std::shared_ptr<rtl::ReadBook> testPtrReadBook1 = std::make_shared<rtl::ReadBook>(testReadBook1);

    testContainer.AddMasterReadBooks(testPtrReadBook1);
    
    XCTAssert(testContainer.GetMasterReadBooks().size() == 1);
    XCTAssert(testContainer.GetMasterReadBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainer.GetMasterBooks().size() == 1);
    XCTAssert(testContainer.GetMasterBooks().at(0) == testPtrReadBook1);
}

- (void)test_AddMasterReadBooks_PassSharedPtrReadBookVector_ThenReadBookAndBookVectorHaveNewBooksAndDuplicatesRemoved {
    rtl::ReadBook testReadBook1(1, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook2(1, "b", "b");
    testReadBook2.SetSeries("b");
    testReadBook2.SetPublisher("b");
    testReadBook2.SetGenre("fantasy");
    testReadBook2.SetPageCount(100);
    testReadBook2.SetPublishDate("1990-Dec-01");
    testReadBook2.SetRating(4);
    testReadBook2.SetDateRead("1993-Mar-25");
    
    rtl::ReadBook testReadBook3(1, "a", "a");
    testReadBook3.SetSeries("a");
    testReadBook3.SetPublisher("a");
    testReadBook3.SetGenre("fantasy");
    testReadBook3.SetPageCount(100);
    testReadBook3.SetPublishDate("1990-Dec-01");
    testReadBook3.SetRating(4);
    testReadBook3.SetDateRead("1993-Mar-25");
    
    std::shared_ptr<rtl::ReadBook> testPtrReadBook1 = std::make_shared<rtl::ReadBook>(testReadBook1);
    std::shared_ptr<rtl::ReadBook> testPtrReadBook2 = std::make_shared<rtl::ReadBook>(testReadBook2);
    std::shared_ptr<rtl::ReadBook> testPtrReadBook3 = std::make_shared<rtl::ReadBook>(testReadBook3);
    std::vector<std::shared_ptr<rtl::ReadBook>> testReadBooks;
    testReadBooks.push_back(testPtrReadBook1);
    testReadBooks.push_back(testPtrReadBook2);
    testReadBooks.push_back(testPtrReadBook3);
    
    testContainer.AddMasterReadBooks(testReadBooks);
    
    XCTAssert(testContainer.GetMasterReadBooks().size() == 2);
    XCTAssert(testContainer.GetMasterReadBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainer.GetMasterReadBooks().at(1) == testPtrReadBook2);
    XCTAssert(testContainer.GetMasterBooks().size() == 2);
    XCTAssert(testContainer.GetMasterBooks().at(0) == testPtrReadBook1);
    XCTAssert(testContainer.GetMasterBooks().at(1) == testPtrReadBook2);
}

- (void)test_AddMasterBooks_PassSharedPtrBook_ThenBookVectorHasNewBook {
    rtl::Book testBook1("testAuthor", "testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    std::shared_ptr<rtl::Book> testPtrBook1 = std::make_shared<rtl::Book>(testBook1);
    
    testContainer.AddMasterBooks(testPtrBook1);
    
    XCTAssert(testContainer.GetMasterBooks().size() == 1);
    XCTAssert(testContainer.GetMasterBooks().at(0) == testPtrBook1);
}

- (void)test_AddMasterBooks_PassSharedPtrBookVector_ThenBookVectorHasNewBooksAndDuplicateRemoved {
    rtl::Book testBook1("testAuthor", "testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("testAuthor2", "testTitle2");
    testBook2.SetSeries("testSeries2");
    testBook2.SetPublisher("testPublisher2");
    testBook2.SetGenre("western");
    testBook2.SetPageCount(100);
    testBook2.SetPublishDate("1991-Dec-01");
    
    rtl::Book testBook3("testAuthor", "testTitle");
    testBook3.SetSeries("testSeries");
    testBook3.SetPublisher("testPublisher");
    testBook3.SetGenre("fantasy");
    testBook3.SetPageCount(10);
    testBook3.SetPublishDate("1990-Dec-01");
    
    std::shared_ptr<rtl::Book> testPtrBook1 = std::make_shared<rtl::Book>(testBook1);
    std::shared_ptr<rtl::Book> testPtrBook2 = std::make_shared<rtl::Book>(testBook2);
    std::shared_ptr<rtl::Book> testPtrBook3 = std::make_shared<rtl::Book>(testBook3);
    std::vector<std::shared_ptr<rtl::Book>> testBooks;
    testBooks.push_back(testPtrBook1);
    testBooks.push_back(testPtrBook2);
    testBooks.push_back(testPtrBook3);
    
    testContainer.AddMasterBooks(testBooks);
    
    XCTAssert(testContainer.GetMasterBooks().size() == 2);
    XCTAssert(testContainer.GetMasterBooks().at(0) == testPtrBook1);
    XCTAssert(testContainer.GetMasterBooks().at(1) == testPtrBook2);
}

- (void)test_AddMasterAuthors_PassSharedPtrAuthor_ThenAuthorVectorHasNewAuthor {
    rtl::Author testAuthor1("test author", "1990-Dec-01");
    std::shared_ptr<rtl::Author> testPtrAuthor1 = std::make_shared<rtl::Author>(testAuthor1);

    testContainer.AddMasterAuthors(testPtrAuthor1);
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 1);
    XCTAssert(testContainer.GetMasterAuthors().at(0) == testPtrAuthor1);
}

- (void)test_AddMasterAuthors_PassSharedPtrAuthorVector_ThenAuthorVectorHasNewAuthorAndDuplicateRemoved {
    rtl::Author testAuthor1("test author", "1990-Dec-01");
    rtl::Author testAuthor2("test buthor", "1990-Dec-03");
    rtl::Author testAuthor3("test author", "1990-Dec-01");
    
    std::shared_ptr<rtl::Author> testPtrAuthor1 = std::make_shared<rtl::Author>(testAuthor1);
    std::shared_ptr<rtl::Author> testPtrAuthor2 = std::make_shared<rtl::Author>(testAuthor2);
    std::shared_ptr<rtl::Author> testPtrAuthor3 = std::make_shared<rtl::Author>(testAuthor3);
    std::vector<std::shared_ptr<rtl::Author>> testAuthors;
    testAuthors.push_back(testPtrAuthor1);
    testAuthors.push_back(testPtrAuthor2);
    testAuthors.push_back(testPtrAuthor3);
    
    testContainer.AddMasterAuthors(testAuthors);
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 2);
    XCTAssert(testContainer.GetMasterAuthors().at(0) == testPtrAuthor1);
    XCTAssert(testContainer.GetMasterAuthors().at(1) == testPtrAuthor2);
}

- (void)test_AddMasterAuthors_PassSharedPtrBook_ThenAuthorVectorHasBookAuthor {
    rtl::Book testBook1("testAuthor1", "testTitle1");
    testBook1.SetSeries("testSeries1");
    testBook1.SetPublisher("testPublisher1");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(1);
    testBook1.SetPublishDate("1990-Dec-01");
    
    std::shared_ptr<rtl::Book> testPtrBook1 = std::make_shared<rtl::Book>(testBook1);
    
    testContainer.AddMasterAuthors(testPtrBook1);
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 1);
    XCTAssert(testContainer.GetMasterAuthors().at(0)->GetName() == "testAuthor1");
}

- (void)test_AddMasterAuthors_PassSharedPtrBookVector_ThenAuthorVectorHasNewAuthorsDuplicateRemoved {
    rtl::Book testBook1("testAuthor1", "testTitle1");
    testBook1.SetSeries("testSeries1");
    testBook1.SetPublisher("testPublisher1");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(1);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::Book testBook2("testAuthor2", "testTitle2");
    testBook2.SetSeries("testSeries2");
    testBook2.SetPublisher("testPublisher2");
    testBook2.SetGenre("western");
    testBook2.SetPageCount(20);
    testBook2.SetPublishDate("1991-Dec-01");
    
    rtl::Book testBook3("testAuthor1", "testTitle1");
    testBook3.SetSeries("testSeries1");
    testBook3.SetPublisher("testPublisher1");
    testBook3.SetGenre("fantasy");
    testBook3.SetPageCount(1);
    testBook3.SetPublishDate("1990-Dec-01");
    
    std::shared_ptr<rtl::Book> testPtrBook1 = std::make_shared<rtl::Book>(testBook1);
    std::shared_ptr<rtl::Book> testPtrBook2 = std::make_shared<rtl::Book>(testBook2);
    std::shared_ptr<rtl::Book> testPtrBook3 = std::make_shared<rtl::Book>(testBook3);
    std::vector<std::shared_ptr<rtl::Book>> testBooks;
    testBooks.push_back(testPtrBook1);
    testBooks.push_back(testPtrBook2);
    testBooks.push_back(testPtrBook3);
    
    testContainer.AddMasterAuthors(testBooks);
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 2);
    XCTAssert(testContainer.GetMasterAuthors().at(0)->GetName() == "testAuthor1");
    XCTAssert(testContainer.GetMasterAuthors().at(1)->GetName() == "testAuthor2");
}

- (void)test_AddMasterAuthors_PassEqualAuthorsWithDifferentBooks_ThenAuthorVectorIsOneAuthorWithBothBooks {
    std::vector<std::shared_ptr<rtl::Book>> books1;
    std::vector<std::shared_ptr<rtl::Book>> books2;
    
    books1.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::Genre::romance, boost::posix_time::ptime((boost::date_time::min_date_time))));
    books1.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle3", "testSeries3", "testPublisher3", 3333, rtl::Genre::romance, boost::posix_time::ptime((boost::date_time::min_date_time))));
    books2.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle", "testSeries", "testPublisher", 1111, rtl::Genre::romance, boost::posix_time::ptime((boost::date_time::min_date_time))));
    books2.push_back(std::make_shared<rtl::Book>("testAuthor", "testTitle2", "testSeries2", "testPublisher2", 2222, rtl::Genre::romance, boost::posix_time::ptime((boost::date_time::min_date_time))));
    
    std::shared_ptr<rtl::Author> testPtrAuthor1 = std::make_shared<rtl::Author>("testAuthor", "1990-Dec-01", books1);
    std::shared_ptr<rtl::Author> testPtrAuthor2 = std::make_shared<rtl::Author>("testAuthor", "1990-Dec-01", books2);
    
    testContainer.AddMasterAuthors(testPtrAuthor1);
    testContainer.AddMasterAuthors(testPtrAuthor2);
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 1);
    XCTAssert(testContainer.GetMasterAuthors().at(0)->GetBooksWritten().size() == 3);
    XCTAssert(testContainer.GetMasterAuthors().at(0)->GetBooksWritten().at(0) == books1.at(0));
    XCTAssert(testContainer.GetMasterAuthors().at(0)->GetBooksWritten().at(1) == books2.at(1));
    XCTAssert(testContainer.GetMasterAuthors().at(0)->GetBooksWritten().at(2) == books1.at(1));

}

- (void)test_SaveInMemoryToFileAndLoadInMemoryFromFile_SaveAndLoadInMemoryToFile {
    std::string testFilePath = "./testSaveFile.txt";
    
    rtl::Book testBook1("testAuthor", "testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::ReadBook testReadBook1(1, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    std::vector<std::shared_ptr<rtl::Book>> testBookVector1;
    testBookVector1.push_back(std::make_shared<rtl::Book>(testBook1));
    testBookVector1.push_back(std::make_shared<rtl::Book>(testReadBook1));
    
    rtl::Author testAuthor1("testAuthor", "1990-Dec-01", testBookVector1);
    
    testContainer.AddMasterAuthors(std::make_shared<rtl::Author>(testAuthor1));
    testContainer.AddMasterBooks(std::make_shared<rtl::Book>(testBook1));
    testContainer.AddMasterReadBooks(std::make_shared<rtl::ReadBook>(testReadBook1));
    
    testContainer.SaveInMemoryToFile(testFilePath);
    testContainer.ClearAll();
    testContainer.LoadInMemoryFromFile(testFilePath);
    
    XCTAssert(testContainer.GetMasterBooks().size() == 2);
    XCTAssert(testContainer.GetMasterReadBooks().size() == 1);
    XCTAssert(testContainer.GetMasterAuthors().size() == 2);
    XCTAssert(testContainer.GetMasterAuthors().at(0)->GetBooksWritten().size() == 1);
    XCTAssert(testContainer.GetMasterAuthors().at(1)->GetBooksWritten().size() == 2);
    XCTAssert(*testContainer.GetMasterBooks().at(0) == testReadBook1);
    XCTAssert(*testContainer.GetMasterBooks().at(1) == testBook1);
    XCTAssert(*testContainer.GetMasterReadBooks().at(0) == testReadBook1);
    XCTAssert(testContainer.GetMasterAuthors().at(0)->GetName() == "a");
    XCTAssert(*testContainer.GetMasterAuthors().at(1) == testAuthor1);
    
    std::remove(testFilePath.c_str());
}

- (void)test_ClearAll {
    rtl::Book testBook1("testAuthor", "testTitle");
    testBook1.SetSeries("testSeries");
    testBook1.SetPublisher("testPublisher");
    testBook1.SetGenre("fantasy");
    testBook1.SetPageCount(10);
    testBook1.SetPublishDate("1990-Dec-01");
    
    rtl::ReadBook testReadBook1(1, "a", "a");
    testReadBook1.SetSeries("a");
    testReadBook1.SetPublisher("a");
    testReadBook1.SetGenre("fantasy");
    testReadBook1.SetPageCount(100);
    testReadBook1.SetPublishDate("1990-Dec-01");
    testReadBook1.SetRating(4);
    testReadBook1.SetDateRead("1993-Mar-25");
    
    rtl::Author testAuthor1("test author", "1990-Dec-01");
    
    testContainer.AddMasterAuthors(std::make_shared<rtl::Author>(testAuthor1));
    testContainer.AddMasterReadBooks(std::make_shared<rtl::ReadBook>(testReadBook1));
    testContainer.AddMasterBooks(std::make_shared<rtl::Book>(testBook1));
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 3);
    XCTAssert(testContainer.GetMasterBooks().size() == 2);
    XCTAssert(testContainer.GetMasterReadBooks().size() == 1);
    
    testContainer.ClearAll();
    
    XCTAssert(testContainer.GetMasterAuthors().size() == 0);
    XCTAssert(testContainer.GetMasterBooks().size() == 0);
    XCTAssert(testContainer.GetMasterReadBooks().size() == 0);
}

- (void)test_QueryBookByIdentifier_PassISBNAndISBNNumber_ReturnOpenLibraryValues {
    std::vector<std::string> isbnAnswer {"0812511816", "081257995X", "0613176340", "0812500482", "9780812511819", "9780812579956", "9780613176347", "9780812500486"};
    std::vector<std::string> oclcAnswer {"22671036"};
    
    rtl::OpenLibraryValues testQuery = rtl::QueryBookByIdentifier("ISBN", "08-1251181-6");
    
    XCTAssert(testQuery.success);
    XCTAssert(testQuery.isbn == isbnAnswer);
    XCTAssert(testQuery.oclc == oclcAnswer);
    XCTAssert(testQuery.title == "The eye of the world");
    XCTAssert(testQuery.authors.size() == 1);
    XCTAssert(testQuery.authors.at(0) == "Robert Jordan");
}

- (void)test_QueryBookByIdentifier_PassOCLCAndOCLCNumber_ReturnOpenLibraryValues {
    std::vector<std::string> isbnAnswer {"0739384155", "9780739384152"};
    std::vector<std::string> oclcAnswer{"861961500"};
    
    rtl::OpenLibraryValues testQuery = rtl::QueryBookByIdentifier("oclc", "861961500");
    
    XCTAssert(testQuery.success);
    XCTAssert(testQuery.isbn == isbnAnswer);
    XCTAssert(testQuery.oclc == oclcAnswer);
    XCTAssert(testQuery.title == "The Girl with the Dragon Tattoo");
    XCTAssert(testQuery.authors.size() == 1);
    XCTAssert(testQuery.authors.at(0) == "Stieg Larsson");
}

- (void)test_QueryBookByIdentifier_PassEmptyIdentifier_ReturnOpenLibraryValuesSuccessIsFalse {
    XCTAssert(rtl::QueryBookByIdentifier(" ", "1234").success == false); //identifier can't be empty
}

- (void)test_QueryBookByIdentifier_PassEmptyIdentifierNumber_ReturnOpenLibraryValuesSuccessIsFalse {
    XCTAssert(rtl::QueryBookByIdentifier("OCLC", "  ").success == false); //identifierNum can't be empty
}

- (void)test_QueryBookByIdentifier_PassInvalidIdentifier_ReturnOpenLibraryValuesSuccessIsFalse {
    XCTAssert(rtl::QueryBookByIdentifier("Babble", "1234").success == false); //identifier must be OCLC or ISBN
}

- (void)test_QueryBookByIdentifier_PassInvalidIdentifierNumber_ReturnOpenLibraryValuesSuccessIsFalse {
    XCTAssert(rtl::QueryBookByIdentifier("ISBN", "asdf").success == false); //identifierNum must not be empty after removing all non digits
}

- (void)test_QueryBookByIdentifier_PassInvalidISBN_ReturnOpenLibraryValuesSuccessIsFalse {
    XCTAssert(rtl::QueryBookByIdentifier("ISBN", "123412351231234").success == false); //gibberish isbn
}

- (void)test_QueryBookByTitle_PassBookTitle_ReturnWikiDataValues {
    rtl::WikiDataValues newQuery = rtl::QueryBookByTitle("The Eye of the World");
    
    XCTAssert(newQuery.success == true);
    XCTAssert(newQuery.author.at(0) == "Robert Jordan");
    XCTAssert(newQuery.oclc.at(0) == "19723327");
    XCTAssert(newQuery.isbn.at(0) == "978-0-7653-2488-7");
    XCTAssert(newQuery.series == "The Wheel of Time");
    XCTAssert(newQuery.title == "The Eye of the World");
    XCTAssert(newQuery.publisher == "Tor Publishing");
}

- (void)test_QueryBookByTitle_PassEmptyTitle_ReturnWikiDataValuesSuccessIsFalse {
    XCTAssert(rtl::QueryBookByTitle("  ").success == false);
}

- (void)test_QueryBooksByTitle_PassInvalidTitle_ReturnWikiDataValuesSuccessIsFalse {
    XCTAssert(rtl::QueryBookByTitle("gibberishthatwonthaveapage").success == false);
}

- (void)test_QueryBooksByIdentifier_PassIdentifier_ReturnWithAllIsbn {
    rtl::OpenLibraryValues newQuery = rtl::QueryBookByIdentifier("ISBN", "0261102354");
    std::vector<std::string> answerVector {"0261102354", "9780261102354"};
    
    XCTAssert(newQuery.success == true);
    XCTAssert(newQuery.isbn == answerVector);
    
}

- (void)test_QueryBooksByIdentifier_PassIdentifier_ReturnWithAllOclc {
    rtl::OpenLibraryValues newQuery = rtl::QueryBookByIdentifier("ISBN", "0261102354");
    std::vector<std::string> answerVector {"869828061", "644361719", "49652808", "847522557", "892147306", "918598176", "473798507"};
    
    
    XCTAssert(newQuery.success == true);
    XCTAssert(newQuery.oclc == answerVector);
}

- (void)test_QueryBooksByTitle_PassIdentifier_ReturnAllAuthors {
    std::vector<std::string> authorVector {"Terry Pratchett", "Neil Gaiman"};
    std::vector<std::string> oclcVector {"21299949"};
    std::vector<std::string> isbnVector {"978-2-84626-021-3", "2-84626-021-4"};
    
    rtl::WikiDataValues newQuery = rtl::QueryBookByTitle("Good Omens");
    
    XCTAssert(newQuery.success == true);
    XCTAssert(newQuery.author == authorVector);
    XCTAssert(newQuery.oclc == oclcVector);
    XCTAssert(newQuery.isbn == isbnVector);
    XCTAssert(newQuery.series == "");
    XCTAssert(newQuery.title == "Good Omens");
    XCTAssert(newQuery.publisher == "Victor Gollancz");
    XCTAssert(newQuery.datePublishedString() == "1990-May-01");
}

@end
