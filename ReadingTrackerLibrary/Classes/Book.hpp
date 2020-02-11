//
//  Book.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/19/19.
//

#ifndef Book_hpp
#define Book_hpp

#include <string>
#include <ctime>
#include <sstream>

enum Genre { genreNotSet, detective, dystopia, fantasy, mystery, romance, scienceFiction, thriller, western };

int convertAbbrMonthToInt(std::string month);
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
    std::string printPublishDate() const;
    std::string printJson() const;
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
    void setPublishDate(std::string publishDate);
    Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, time_t publishDate = std::time(0));
    Book(std::string author, std::string title, std::string series, std::string publisher, int pageCount, Genre genre, std::string publishDate);
private:
    std::string author;
    std::string title;
    std::string publisher;
    std::string series;
    Genre genre;
    int pageCount;
    tm publishDate;
};

bool operator==(const Book& lhs, const Book& rhs);
bool operator!=(const Book& lhs, const Book& rhs);
bool operator<(const Book& lhs, const Book& rhs);
bool operator>(const Book& lhs, const Book& rhs);
bool operator>=(const Book& lhs, const Book& rhs);
bool operator<=(const Book& lhs, const Book& rhs);

#endif /* Book_hpp */
