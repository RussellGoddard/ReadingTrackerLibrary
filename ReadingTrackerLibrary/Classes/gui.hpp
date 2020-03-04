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

Author getNewAuthor(std::istream& inputStream, std::ostream& outputStream);
rtlBook::Book getNewBook(std::istream& inputStream, std::ostream& outputStream);
rtlBook::ReadBook getNewReadBook(std::istream& inputStream, std::ostream& outputStream, int readerId);
void outputLine(std::ostream& outputStream, std::string output);
void mainMenu(std::istream& inputStream, std::ostream& outputStream, int readerId);
std::string getInput(std::istream& inputStream);


#endif /* gui_hpp */
