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
        
        SetsPtr GetUpdateFunction(std::string input) override;
        std::string PrintJson() const override;
        std::string PrintSimple() const override;
        std::string PrintDetailed() const override;
        std::string PrintHeader() const override;
        
        ReadBook() = delete; //ReadBook class HAS to be constructed with a readerId, book author and book title
        ReadBook(int readerId, Book book, int rating, time_t dateRead);
        ReadBook(int readerId, Book book, int rating, std::string dateRead);
        ReadBook(int readerId, std::string author, std::string title, std::string series = "", std::string publisher = "", int pageCount = -1, rtl::Genre genre = rtl::Genre::genreNotSet, time_t publishDate = std::time(0), int rating = 0, time_t dateRead = std::time(0));
        ReadBook(int readerId, std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead);
    private:
        int readerId;
        tm dateRead;
        int rating;
        
        //used for printCommandLineSimple and printCommandLineHeaders, 77 characters total
        const int kWidthAuthor = 20;
        const int kWidthTitle = 34;
        const int kWidthPage = 6;
        const int kWidthDateRead = 13;
        const int kWidthRating = 4;
    };

    bool operator==(const ReadBook& lhs, const ReadBook& rhs);
    bool operator!=(const ReadBook& lhs, const ReadBook& rhs);
    bool operator<(const ReadBook& lhs, const ReadBook& rhs);
    bool operator>(const ReadBook& lhs, const ReadBook& rhs);
    bool operator>=(const ReadBook& lhs, const ReadBook& rhs);
    bool operator<=(const ReadBook& lhs, const ReadBook& rhs);

}
#endif /* ReadBook_hpp */
