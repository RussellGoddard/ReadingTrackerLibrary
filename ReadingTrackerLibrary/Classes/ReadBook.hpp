//
//  ReadBook.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#ifndef ReadBook_hpp
#define ReadBook_hpp

#include "Book.hpp"
#include <sstream>

namespace rtl {

    //TODO: add uniqueId for future DB storage
    class ReadBook : public rtl::Book {
    public:
        void SetDateRead(time_t time);
        bool SetDateRead(std::string time);
        void SetRating(int rating);
        void SetRating(char pageCount); //will result in rating being set to 0
        void SetRating(std::string pageCount); //will attempt a stoi if it fails set rating to 0
        tm GetDateRead() const;
        time_t GetDateReadAsTimeT();
        std::string PrintDateRead() const;
        int GetRating() const;
        int GetReaderId() const;
        std::string PrintJson() const;
        std::string PrintCommandLine() const;
        ReadBook(int readerId, Book book, int rating, time_t dateRead);
        ReadBook(int readerId, Book book, int rating, std::string dateRead);
        ReadBook(int readerId, std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, rtl::Genre genre = rtl::genreNotSet, time_t publishDate = std::time(0), int rating = 0, time_t dateRead = std::time(0));
        ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead);
        
        static std::string PrintCommandLineHeaders();
    private:
        int readerId;
        tm dateRead;
        int rating;
        
        //used for printCommandLine and printCommandLineHeaders
        static const int kWidthAuthor = 20;
        static const int kWidthTitle = 35;
        static const int kWidthPage = 6;
        static const int kWidthDateRead = 13;
        static const int kWidthRating = 6;
    };

    bool operator==(const ReadBook& lhs, const ReadBook& rhs);
    bool operator!=(const ReadBook& lhs, const ReadBook& rhs);
    bool operator<(const ReadBook& lhs, const ReadBook& rhs);
    bool operator>(const ReadBook& lhs, const ReadBook& rhs);
    bool operator>=(const ReadBook& lhs, const ReadBook& rhs);
    bool operator<=(const ReadBook& lhs, const ReadBook& rhs);

}
#endif /* ReadBook_hpp */
