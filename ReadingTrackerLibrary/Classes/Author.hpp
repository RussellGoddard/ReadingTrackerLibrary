//
//  Author.hpp
//  Reading Tracker
//
//  Created by Frobu on 11/3/19.
//

#ifndef Author_hpp
#define Author_hpp

#include <algorithm>
#include <ctime>
#include <string>
#include <vector>


class Book; //forward declaration of book
template <typename T>
void sortUnique(std::vector<T>& input);
int convertAbbrMonthToInt(std::string month); //don't like this needing to be declared here, definition in book.cpp TODO


class Author {
public:
    void setName(std::string name);
    void setDateBorn(time_t dateBorn);
    void setDateBorn(std::string dateBorn);
    void addBookWritten(std::shared_ptr<Book> book);
    void addBookWritten(std::vector<std::shared_ptr<Book>> books);
    std::vector<std::shared_ptr<Book>> getBooksWritten() const;
    std::string getName() const;
    tm getDateBorn() const;
    time_t getDateBornTimeT();
    std::string printDateBorn() const;
    Author() = delete; //Author class HAS to be constructed with a name
    Author(std::string name, time_t dateBorn = std::time(0), std::vector<std::shared_ptr<Book>> booksWritten = {});
    Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<Book>> booksWritten = {});
private:
    std::string name;
    struct tm dateBorn;
    std::vector<std::shared_ptr<Book>> booksWritten;
};

bool operator==(const Author& lhs, const Author& rhs);
bool operator!=(const Author& lhs, const Author& rhs);
bool operator<(const Author& lhs, const Author& rhs);
bool operator>(const Author& lhs, const Author& rhs);
bool operator>=(const Author& lhs, const Author& rhs);
bool operator<=(const Author& lhs, const Author& rhs);


#endif /* Author_hpp */
