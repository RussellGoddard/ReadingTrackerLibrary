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
    int getRating();
    std::string printJson();
    ReadBook(Book book, int rating, time_t time);
    ReadBook(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, int rating = 0, time_t time = std::time(0));
    ReadBook(std::string author, std::string title, std::string series, std::string publisher, int pageCount, std::string genre, int rating, std::string time);
private:
    struct tm dateRead;
    int rating;
};

#endif /* ReadBook_hpp */
