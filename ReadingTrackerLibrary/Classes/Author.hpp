//
//  Author.hpp
//  Reading Tracker
//
//  Created by Frobu on 11/3/19.
//

#ifndef Author_hpp
#define Author_hpp

#include <string>
#include <vector>
#include <ctime>

class Book; //forward declaration of book
int convertAbbrMonthToInt(std::string month); //don't like this needing to be declared here, definition in book.cpp TODO

class Author {
public:
    void setName(std::string name);
    std::string getName();
    void setDateBorn(time_t dateBorn);
    void setDateBorn(std::string dateBorn);
    time_t getDateBorn();
    std::string printDateBorn();
    void addBookWritten(std::shared_ptr<Book> book);
    void addBooksWritten(std::vector<std::shared_ptr<Book>> books);
    std::vector<std::shared_ptr<Book>> getBooksWritten();
    Author() = delete; //Author class HAS to be constructed with a name
    Author(std::string name, time_t dateBorn = std::time(0), std::vector<std::shared_ptr<Book>> booksWritten = {});
    Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
private:
    std::string name;
    struct tm dateBorn;
    std::vector<std::shared_ptr<Book>> booksWritten;
};

#endif /* Author_hpp */
