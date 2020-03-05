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

    class ReadBook : public rtl::Book {
    public:
        void setDateRead(time_t time);
        void setDateRead(std::string time);
        void setRating(int rating);
        void setRating(char pageCount); //will result in rating being set to 0
        void setRating(std::string pageCount); //will attempt a stoi if it fails set rating to 0
        tm getDateRead() const;
        time_t getDateReadAsTimeT();
        std::string printDateRead() const;
        int getRating() const;
        int getReaderId() const;
        std::string printJson() const;
        std::string printCommandLine() const;
        ReadBook(int readerId, Book book, int rating, time_t dateRead);
        ReadBook(int readerId, Book book, int rating, std::string dateRead);
        ReadBook(int readerId, std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, rtl::Genre genre = rtl::genreNotSet, time_t publishDate = std::time(0), int rating = 0, time_t dateRead = std::time(0));
        ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead);
        
        static std::string printCommandLineHeaders();
    private:
        int readerId;
        tm dateRead;
        int rating;
    };

    bool operator==(const ReadBook& lhs, const ReadBook& rhs);
    bool operator!=(const ReadBook& lhs, const ReadBook& rhs);
    bool operator<(const ReadBook& lhs, const ReadBook& rhs);
    bool operator>(const ReadBook& lhs, const ReadBook& rhs);
    bool operator>=(const ReadBook& lhs, const ReadBook& rhs);
    bool operator<=(const ReadBook& lhs, const ReadBook& rhs);

}
#endif /* ReadBook_hpp */
