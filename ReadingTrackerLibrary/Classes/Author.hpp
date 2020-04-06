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
#include "HelperFunctions.hpp"
#include "Logger.hpp"
#include "Book.hpp"

//below pragma's are taken from https://stackoverflow.com/a/13492589 to suppress warnings from boost
// save diagnostic state
#pragma GCC diagnostic push

// turn off the specific warning
#pragma GCC diagnostic ignored "-Wcomma"
#pragma GCC diagnostic ignored "-Wdocumentation"

#include <boost/date_time/gregorian/gregorian.hpp>

// turn the warnings back on
#pragma GCC diagnostic pop

namespace rtl {

    
    //TODO: change default author dateBorn to something else
    const time_t jan2038 = 2145916800;

    class Author : public StandardOutput {
    public:
        bool SetName(std::string name);
        bool SetDateBorn(time_t dateBorn);
        bool SetDateBorn(std::string dateBorn);
        bool AddBookWritten(std::shared_ptr<rtl::Book> book);
        bool AddBookWritten(std::vector<std::shared_ptr<rtl::Book>> books);
        std::string GetAuthorId() const;
        std::vector<std::shared_ptr<rtl::Book>> GetBooksWritten() const;
        std::string GetName() const;
        tm GetDateBorn() const;
        time_t GetDateBornTimeT();
        std::string PrintDateBorn() const;
        
        rtl::SetsPtr GetUpdateFunction(std::string input) override;
        std::string PrintJson() const override;
        std::string PrintSimple() const override;
        std::string PrintDetailed() const override;
        std::string PrintHeader() const override;
        
        Author() = delete; //Author class HAS to be constructed with a name
        Author(std::string name, time_t dateBorn = jan2038, std::vector<std::shared_ptr<rtl::Book>> booksWritten = {});
        Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten = {});
    private:
        std::string authorId;
        std::string name;
        struct tm dateBorn;
        std::vector<std::shared_ptr<rtl::Book>> booksWritten;
        
        //used for printCommandLineSimple and printCommandLineHeader, 77 characters total
        const int kWidthAuthor = 20;
        const int kWidthDateBorn = 12;
        const int kWidthTitle = 41;
        const int kWidthYear = 4;
        const std::string kAuthor = "Author";
        const std::string kDateBorn = "Date Born";
        const std::string kAuthorId = "AuthorId";
        const std::string kBooksWritten = "Books Written";
    };

    bool operator==(const Author& lhs, const Author& rhs);
    bool operator!=(const Author& lhs, const Author& rhs);
    bool operator<(const Author& lhs, const Author& rhs);
    bool operator>(const Author& lhs, const Author& rhs);
    bool operator>=(const Author& lhs, const Author& rhs);
    bool operator<=(const Author& lhs, const Author& rhs);

    //template specialization so that when authors are the same the booksWritten vector is combined before duplicate author removed
    template <>
    inline void uniqueVector(std::vector<std::shared_ptr<rtl::Author>>& input) {
        int index = 1;
        
        while (index < input.size()) {
            if (*input.at(index - 1) == *input.at(index)) {
                //if authors are the same combine unique books
                input.at(index - 1)->AddBookWritten(input.at(index)->GetBooksWritten());
                
                input.erase(std::begin(input) + index);
            }
            else {
                ++index;
            }
        }
        
        return;
    }

}

#endif /* Author_hpp */
