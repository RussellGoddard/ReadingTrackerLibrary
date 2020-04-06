//
//  Book.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#ifndef Book_hpp
#define Book_hpp

#include <ios>
#include <ctime>
#include <exception>
#include <sstream>
#include <string>
#include "HelperFunctions.hpp"
#include "Logger.hpp"
#include "StandardOutput.hpp"

//below pragma's are taken from https://stackoverflow.com/a/13492589 to suppress warnings from boost
// save diagnostic state
#pragma GCC diagnostic push

// turn off the specific warning
#pragma GCC diagnostic ignored "-Wcomma"
#pragma GCC diagnostic ignored "-Wdocumentation"

#include <boost/date_time/gregorian/gregorian.hpp>

// turn the warnings back on
#pragma GCC diagnostic pop

namespace rtl {

    
    class Book : public StandardOutput {
    public:
        std::string GetAuthor() const;
        std::string GetTitle() const;
        std::string GetSeries() const;
        std::string GetPublisher() const;
        int GetPageCount() const;
        Genre GetGenre() const;
        std::string PrintGenre() const;
        tm GetPublishDate() const;
        time_t GetPublishDateAsTimeT();
        std::vector<std::string> GetOclc() const;
        std::vector<std::string> GetIsbn() const;
        std::string GetAuthorId() const;
        std::string GetBookId() const;
        std::string PrintPublishDate() const;
        
        bool SetSeries(std::string series);
        bool SetPublisher(std::string publisher);
        bool SetPageCount(int pageCount);
        bool SetPageCount(char pageCount);
        bool SetPageCount(std::string pageCount);
        bool SetGenre(Genre genre);
        bool SetGenre(std::string genre);
        bool SetPublishDate(time_t publishDate);
        bool SetPublishDate(std::string publishDate);
        bool AddOclc(std::string oclc);
        bool AddIsbn(std::string isbn);
        
        SetsPtr GetUpdateFunction(std::string input) override;
        std::string PrintJson() const override;
        std::string PrintSimple() const override;
        std::string PrintDetailed() const override;
        std::string PrintHeader() const override;
        
        Book() = delete; //Book class HAS to be constructed with a title and author
        Book(std::string author, std::string title, std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = rtl::Genre::genreNotSet, time_t publishDate = std::time(0));
        Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate);
        Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::string isbn = "", std::string oclc = "");
        Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, std::vector<std::string> isbn, std::vector<std::string> oclc);
        
    private:
        std::string authorId = "";
        std::string bookId = "";
        std::vector<std::string> isbnVector;
        std::vector<std::string> oclcVector;
        std::string author = "";
        std::string title = "";
        std::string publisher = "";
        std::string series = "";
        Genre genre = rtl::Genre::genreNotSet;
        int pageCount = -1; //default value is -1
        tm publishDate;
        
        //used for printCommandLineSimple and printCommandLineHeaders, 77 characters total
        const int kWidthAuthor = 20;
        const int kWidthTitle = 33;
        const int kWidthSeries = 19;
        const int kWidthPage = 5;
        
        const std::string kAuthor = "Author Name";
        const std::string kAuthorId = "AuthorId";
        const std::string kTitle = "Title";
        const std::string kBookId = "BookId";
        const std::string kSeries = "Series";
        const std::string kGenre = "Genre";
        const std::string kPageCount = "Page Count";
        const std::string kPublisher = "Publisher";
        const std::string kPublishDate = "Publish Date";
        const std::string kIsbn = "ISBN";
        const std::string kOclc = "OCLC";
    };

    bool operator==(const Book& lhs, const Book& rhs);
    bool operator!=(const Book& lhs, const Book& rhs);
    bool operator<(const Book& lhs, const Book& rhs);
    bool operator>(const Book& lhs, const Book& rhs);
    bool operator>=(const Book& lhs, const Book& rhs);
    bool operator<=(const Book& lhs, const Book& rhs);
}

#endif /* Book_hpp */
