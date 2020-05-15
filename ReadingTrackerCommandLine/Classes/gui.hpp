//
//  gui.hpp
//  Reading Tracker
//
//  Created by Frobu on 10/28/19.
//

#ifndef gui_hpp
#define gui_hpp

#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include "CommandLineHelpers.hpp"
#include "FileMethods.hpp"
#include "Logger.hpp"
#include "ServerMethods.hpp"

namespace rtl::CommandLine {
   
    rtl::Author GetNewAuthor(std::istream& inputStream, std::ostream& outputStream, int inputMode);
    rtl::Book GetNewBook(std::istream& inputStream, std::ostream& outputStream, int inputMode);
    rtl::ReadBook GetNewReadBook(std::istream& inputStream, std::ostream& outputStream, std::string readerId, int inputMode);
    void UpdateRecord(std::istream& inputStream, std::ostream& outputStream, int maxRange, std::vector<std::shared_ptr<rtl::StandardOutput>>::iterator it);
    void MainMenu(std::istream& inputStream, std::ostream& outputStream, std::string readerId);
    
}

#endif /* gui_hpp */
