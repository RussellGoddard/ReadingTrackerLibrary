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
#include "ReadBook.hpp" //TODO: this should only be Book.hpp but duplicate dependency due to FileMethod wanting to have both Author and ReadBook 

namespace rtl {
    //TODO: change default author dateBorn to something else
    const time_t jan2038 = 2145916800;
    template <typename T>
    void SortUnique(std::vector<T>& input);

    class Author {
    public:
        void SetName(std::string name);
        void SetDateBorn(time_t dateBorn);
        bool SetDateBorn(std::string dateBorn);
        void AddBookWritten(std::shared_ptr<rtl::Book> book);
        void AddBookWritten(std::vector<std::shared_ptr<rtl::Book>> books);
        std::vector<std::shared_ptr<rtl::Book>> GetBooksWritten() const;
        std::string GetName() const;
        tm GetDateBorn() const;
        time_t GetDateBornTimeT();
        std::string PrintDateBorn() const;
        std::string PrintJson() const;
        std::string PrintCommandLine() const;
        Author() = delete; //Author class HAS to be constructed with a name
        Author(std::string name, time_t dateBorn = jan2038, std::vector<std::shared_ptr<rtl::Book>> booksWritten = {});
        Author(std::string name, time_t dateBorn, std::shared_ptr<rtl::Book> bookWritten);
        Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten = {});
        
        static std::string PrintCommandLineHeaders();
    private:
        std::string name;
        struct tm dateBorn;
        std::vector<std::shared_ptr<rtl::Book>> booksWritten;
        
        //used for printCommandLine and printCommandLineHeaders
        static const int kWidthAuthor = 20;
        static const int kWidthDateBorn = 12;
        static const int kWidthTitle = 44;
        static const int kWidthYear = 4;
    };

    bool operator==(const Author& lhs, const Author& rhs);
    bool operator!=(const Author& lhs, const Author& rhs);
    bool operator<(const Author& lhs, const Author& rhs);
    bool operator>(const Author& lhs, const Author& rhs);
    bool operator>=(const Author& lhs, const Author& rhs);
    bool operator<=(const Author& lhs, const Author& rhs);

}

#endif /* Author_hpp */
