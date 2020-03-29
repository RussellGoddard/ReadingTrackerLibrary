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
#include "FileMethods.hpp"
#include "CommandLineHelpers.hpp"

namespace rtl::CommandLine {
   
    rtl::Author GetNewAuthor(std::istream& inputStream, std::ostream& outputStream, int inputMode);
    rtl::Book GetNewBook(std::istream& inputStream, std::ostream& outputStream, int inputMode);
    rtl::ReadBook GetNewReadBook(std::istream& inputStream, std::ostream& outputStream, int readerId, int inputMode);
    void UpdateRecord(std::istream& inputStream, std::ostream& outputStream, int maxRange, std::vector<std::shared_ptr<rtl::StandardOutput>>::iterator it);
    void MainMenu(std::istream& inputStream, std::ostream& outputStream, int readerId);
    
}

#endif /* gui_hpp */
