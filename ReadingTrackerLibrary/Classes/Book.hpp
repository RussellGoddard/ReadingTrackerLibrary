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

    enum Genre { genreNotSet, detective, dystopia, fantasy, mystery, romance, scienceFiction, thriller, western };

    Genre ConvertStringToGenre(std::string genre);
    std::string ConvertGenreToString(Genre genre);
    
    //TODO: expand OCLC and ISBN support
    //TODO: add uniqueId for future DB storage
    class Book {
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
        std::string PrintPublishDate() const;
        std::string PrintJson() const;
        std::string PrintCommandLine() const;
        void SetAuthor(std::string author);
        void SetTitle(std::string title);
        void SetSeries(std::string series);
        void SetPublisher(std::string publisher);
        void SetPageCount(int pageCount);
        void SetPageCount(char pageCount); //will result in pageCount being set to -1
        void SetPageCount(std::string pageCount); //will attempt a stoi if it fails set pageCount to -1
        void SetGenre(Genre genre);
        void SetGenre(std::string genre);
        void SetPublishDate(time_t publishDate);
        bool SetPublishDate(std::string publishDate);
        void AddOclc(std::string oclc);
        void AddIsbn(std::string isbn);
        Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, time_t publishDate = std::time(0));
        Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate);
        Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate);
        
        static std::string PrintCommandLineHeaders();
    private:
        std::vector<std::string> isbnVector;
        std::vector<std::string> oclcVector;
        std::string author;
        std::string title;
        std::string publisher;
        std::string series;
        Genre genre;
        int pageCount;
        tm publishDate;
        
        //used for printCommandLine and printCommandLineHeaders
        static const int kWidthAuthor = 20;
        static const int kWidthTitle = 35;
        static const int kWidthSeries = 20;
        static const int kWidthPage = 5;
    };

    bool operator==(const Book& lhs, const Book& rhs);
    bool operator!=(const Book& lhs, const Book& rhs);
    bool operator<(const Book& lhs, const Book& rhs);
    bool operator>(const Book& lhs, const Book& rhs);
    bool operator>=(const Book& lhs, const Book& rhs);
    bool operator<=(const Book& lhs, const Book& rhs);
}

#endif /* Book_hpp */
