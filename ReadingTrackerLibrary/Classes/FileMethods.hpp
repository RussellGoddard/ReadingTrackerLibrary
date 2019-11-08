//
//  FileMethods.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/27/19.
//

#ifndef FileMethods_hpp
#define FileMethods_hpp

#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include "ReadBook.hpp"

bool saveReadingList(std::vector<nlohmann::json> input, std::string filePath);
std::vector<nlohmann::json> loadReadingList(std::string filePath);
ReadBook convertJsonToReadBook(nlohmann::json json);
std::shared_ptr<ReadBook> convertJsonToReadBookPtr(nlohmann::json json);

#endif /* FileMethods_hpp */
