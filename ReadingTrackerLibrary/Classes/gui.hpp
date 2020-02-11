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
#include "FileMethods.hpp"

std::string& rightTrim(std::string& input);
std::string& leftTrim(std::string& input);
std::string& trim(std::string& input);
ReadBook getNewReadBook();
void outputLine(std::string output);
void mainMenu();
std::string getInput();


#endif /* gui_hpp */
