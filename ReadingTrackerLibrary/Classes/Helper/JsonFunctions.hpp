//
//  JsonFunctions.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/21/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef JsonFunctions_hpp
#define JsonFunctions_hpp


#include <nlohmann/json.hpp>
#include "ReadBook.hpp"
#include "Author.hpp"

namespace rtl {
    template <typename T>
    std::string PrintJson(const std::shared_ptr<T> input);
    template<> std::string PrintJson(const std::shared_ptr<rtl::Author> input);
    template<> std::string PrintJson(const std::shared_ptr<rtl::Book> input);
    template<> std::string PrintJson(const std::shared_ptr<rtl::ReadBook> input);
    rtl::ReadBook ConvertJsonToReadBook(nlohmann::json json);
    std::shared_ptr<rtl::Book> ConvertJsonToBookPtr(nlohmann::json json);
    std::shared_ptr<rtl::ReadBook> ConvertJsonToReadBookPtr(nlohmann::json json);
    std::shared_ptr<rtl::Author> ConvertJsonToAuthorPtr(nlohmann::json json);
}

#endif /* JsonFunctions_hpp */
