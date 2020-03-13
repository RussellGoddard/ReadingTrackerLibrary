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
#include "FileMethods.hpp"

namespace rtlCommandLine {

    rtl::Author GetNewAuthor(std::istream& inputStream, std::ostream& outputStream);
    rtl::Book GetNewBook(std::istream& inputStream, std::ostream& outputStream);
    rtl::ReadBook GetNewReadBook(std::istream& inputStream, std::ostream& outputStream, int readerId);
    void OutputLine(std::ostream& outputStream, std::string output);
    void MainMenu(std::istream& inputStream, std::ostream& outputStream, int readerId);
    std::string GetInput(std::istream& inputStream);

}

#endif /* gui_hpp */
