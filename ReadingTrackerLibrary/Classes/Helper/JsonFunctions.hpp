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
    std::shared_ptr<rtl::Book> ConvertJsonToBookPtr(nlohmann::json json);
    std::shared_ptr<rtl::ReadBook> ConvertJsonToReadBookPtr(nlohmann::json json);
    std::shared_ptr<rtl::Author> ConvertJsonToAuthorPtr(nlohmann::json json);
}

#endif /* JsonFunctions_hpp */
