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

    //TODO: add uniqueId for future DB storage
    class Author : public StandardOutput {
    public:
        void SetName(std::string name);
        void SetDateBorn(time_t dateBorn);
        bool SetDateBorn(std::string dateBorn);
        void AddBookWritten(std::shared_ptr<rtl::Book> book);
        void AddBookWritten(std::vector<std::shared_ptr<rtl::Book>> books);
        std::string GetAuthorId() const;
        std::vector<std::shared_ptr<rtl::Book>> GetBooksWritten() const;
        std::string GetName() const;
        tm GetDateBorn() const;
        time_t GetDateBornTimeT();
        std::string PrintDateBorn() const;
        
        std::string PrintJson() const override;
        std::string PrintCommandLineSimple() const override;
        std::string PrintCommandLineDetailed() const override;
        std::string PrintCommandLineHeader() const override;
        
        Author() = delete; //Author class HAS to be constructed with a name
        Author(std::string name, time_t dateBorn = jan2038, std::vector<std::shared_ptr<rtl::Book>> booksWritten = {});
        Author(std::string name, time_t dateBorn, std::shared_ptr<rtl::Book> bookWritten);
        Author(std::string name, std::string dateBorn, std::vector<std::shared_ptr<rtl::Book>> booksWritten = {});
    private:
        std::string authorId;
        std::string name;
        struct tm dateBorn;
        std::vector<std::shared_ptr<rtl::Book>> booksWritten;
        
        //used for printCommandLineSimple and printCommandLineHeader
        const int kWidthAuthor = 20;
        const int kWidthDateBorn = 12;
        const int kWidthTitle = 44;
        const int kWidthYear = 4;
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
