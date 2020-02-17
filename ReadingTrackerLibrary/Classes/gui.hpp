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


ReadBook getNewReadBook(std::istream &inputStream, std::ostream &outputStream);
void outputLine(std::ostream &outputStream, std::string output);
void mainMenu(std::istream& inputStream, std::ostream& outputStream);
std::string getInput(std::istream &inputStream);


#endif /* gui_hpp */
