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

    Genre convertStringToGenre(std::string genre);
    std::string convertGenreToString(Genre genre);

    class Book {
    public:
        std::string getAuthor() const;
        std::string getTitle() const;
        std::string getSeries() const;
        std::string getPublisher() const;
        int getPageCount() const;
        Genre getGenre() const;
        std::string printGenre() const;
        tm getPublishDate() const;
        time_t getPublishDateAsTimeT();
        std::string getOclc() const;
        std::string printPublishDate() const;
        std::string printJson() const;
        std::string printCommandLine() const;
        void setAuthor(std::string author);
        void setTitle(std::string title);
        void setSeries(std::string series);
        void setPublisher(std::string publisher);
        void setPageCount(int pageCount);
        void setPageCount(char pageCount); //will result in pageCount being set to -1
        void setPageCount(std::string pageCount); //will attempt a stoi if it fails set pageCount to -1
        void setGenre(Genre genre);
        void setGenre(std::string genre);
        void setPublishDate(time_t publishDate);
        bool setPublishDate(std::string publishDate);
        void setOclc(std::string oclc);
        Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, time_t publishDate = std::time(0));
        Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate);
        Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate);
        
        static std::string printCommandLineHeaders();
    private:
        std::string oclc;
        std::string author;
        std::string title;
        std::string publisher;
        std::string series;
        Genre genre;
        int pageCount;
        tm publishDate;
        
        //used for printCommandLine and printCommandLineHeaders
        static const int cWidthAuthor = 20;
        static const int cWidthTitle = 35;
        static const int cWidthSeries = 20;
        static const int cWidthPage = 5;
    };

    bool operator==(const Book& lhs, const Book& rhs);
    bool operator!=(const Book& lhs, const Book& rhs);
    bool operator<(const Book& lhs, const Book& rhs);
    bool operator>(const Book& lhs, const Book& rhs);
    bool operator>=(const Book& lhs, const Book& rhs);
    bool operator<=(const Book& lhs, const Book& rhs);
}

#endif /* Book_hpp */
