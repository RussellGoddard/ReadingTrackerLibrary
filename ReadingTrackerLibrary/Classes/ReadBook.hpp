//
//  ReadBook.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#ifndef ReadBook_hpp
#define ReadBook_hpp

#include <sstream>
#include <string>
#include "Book.hpp"
#include "Logger.hpp"

//below pragma's are taken from https://stackoverflow.com/a/13492589 to suppress warnings from boost
// save diagnostic state
#pragma GCC diagnostic push

// turn off the specific warning
#pragma GCC diagnostic ignored "-Wcomma"
#pragma GCC diagnostic ignored "-Wdocumentation"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// turn the warnings back on
#pragma GCC diagnostic pop

namespace rtl {

    class ReadBook : public rtl::Book {
    public:
        bool SetDateRead(boost::posix_time::ptime time);
        bool SetDateRead(std::string time);
        bool SetRating(int rating);
        bool SetRating(char pageCount); //will result in rating being set to 0
        bool SetRating(std::string pageCount); //will attempt a stoi if it fails set rating to 0
        tm GetDateRead() const;
        boost::posix_time::ptime GetDateReadAsPosixTime();
        std::string PrintDateRead() const;
        int GetRating() const;
        std::string GetReaderId() const;
        
        SetsPtr GetUpdateFunction(std::string input) override;
        std::string PrintJson() const override;
        std::string PrintSimple() const override;
        std::string PrintDetailed() const override;
        std::string PrintHeader() const override;
        
        ReadBook() = delete; //ReadBook class HAS to be constructed with a readerId, book author and book title
        ReadBook(std::string readerId, Book book, int rating, boost::posix_time::ptime dateRead);
        ReadBook(std::string readerId, Book book, int rating, std::string dateRead);
        ReadBook(std::string readerId, std::string author, std::string title, std::string series = "", std::string publisher = "", int pageCount = -1, rtl::Genre genre = rtl::Genre::genreNotSet, boost::posix_time::ptime publishDate = boost::posix_time::second_clock::universal_time(), int rating = 0, boost::posix_time::ptime dateRead = boost::posix_time::second_clock::universal_time());
        ReadBook(std::string readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead);
    private:
        std::string readerId;
        tm dateRead;
        int rating = -1;
        
        //used for printCommandLineSimple and printCommandLineHeaders, 77 characters total
        const int kWidthAuthor = 20;
        const int kWidthTitle = 34;
        const int kWidthPage = 6;
        const int kWidthDateRead = 13;
        const int kWidthRating = 4;
        
        const std::string kReaderId = "Reader ID";
        const std::string kDateRead = "Date Read";
        const std::string kRating = "Rating";
    };

    bool operator==(const ReadBook& lhs, const ReadBook& rhs);
    bool operator!=(const ReadBook& lhs, const ReadBook& rhs);
    bool operator<(const ReadBook& lhs, const ReadBook& rhs);
    bool operator>(const ReadBook& lhs, const ReadBook& rhs);
    bool operator>=(const ReadBook& lhs, const ReadBook& rhs);
    bool operator<=(const ReadBook& lhs, const ReadBook& rhs);

}
#endif /* ReadBook_hpp */
