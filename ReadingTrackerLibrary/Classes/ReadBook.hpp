//
//  ReadBook.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#ifndef ReadBook_hpp
#define ReadBook_hpp

#include "Book.hpp"

class ReadBook : public Book {
public:
    void setDateRead(time_t time);
    void setDateRead(std::string time);
    time_t getDateRead();
    std::string printDateRead();
    void setRating(int rating);
    void setRating(char pageCount); //will result in rating being set to 0
    void setRating(std::string pageCount); //will attempt a stoi if it fails set rating to 0
    int getRating();
    std::string printJson();
    ReadBook(Book book, int rating, time_t dateRead);
    ReadBook(Book book, int rating, std::string dateRead);
    ReadBook(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, time_t publishDate = std::time(0), int rating = 0, time_t dateRead = std::time(0));
    ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, std::string publishDate, int rating, std::string dateRead);
private:
    struct tm dateRead;
    int rating;
};

#endif /* ReadBook_hpp */
