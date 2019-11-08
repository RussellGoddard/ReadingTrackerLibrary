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

int convertAbbrMonthToInt(std::string month);

enum Genre { genreNotSet, detective, dystopia, fantasy, mystery, romance, scienceFiction, thriller, western };

class Book {
public:
    std::string getAuthor() const;
    std::string getTitle() const;
    std::string getSeries() const;
    std::string getPublisher() const;
    int getPageCount() const;
    Genre getGenre() const;
    std::string printGenre() const;
    time_t getPublishDate();
    std::string printPublishDate() const;
    std::string printJson() const;
    void setAuthor(std::string author);
    void setTitle(std::string title);
    void setSeries(std::string series);
    void setPublisher(std::string publisher);
    void setPageCount(int wordCount);
    void setGenre(Genre genre);
    void setGenre(std::string genre);
    void setPublishDate(time_t publishDate);
    void setPublishDate(std::string publishDate);
    Book(std::string author = "", std::string title = "", std::string series = "", std::string publisher = "", int pageCount = -1, Genre genre = genreNotSet, time_t publishDate = std::time(0));
    static Genre convertStringToGenre(std::string genre);
    static std::string convertGenreToString(Genre genre);
private:
    std::string author;
    std::string title;
    std::string publisher;
    std::string series;
    Genre genre;
    int pageCount;
    struct tm publishDate;
};

bool operator==(const Book& lhs, const Book& rhs);
bool operator!=(const Book& lhs, const Book& rhs);
bool operator<(const Book& lhs, const Book& rhs);
bool operator>(const Book& lhs, const Book& rhs);
bool operator>=(const Book& lhs, const Book& rhs);
bool operator<=(const Book& lhs, const Book& rhs);

#endif /* Book_hpp */
