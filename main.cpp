/*
MIT License

Copyright (c) 2013-2019 Niels Lohmann

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//
//  main.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/17/19.
//

/*
 {"author":"Brandon Sanderson","dateRead":"Fri Sep 13 00:00:00 2019","genre":"fantasy","pageCount":541,"publisher":"Tor Books","rating":9,"series":"Mistborn","title":"Mistborn: The Final Empire"}
 {"author":"Brandon Sanderson","dateRead":"Mon Sep 30 00:00:00 2019","genre":"fantasy","pageCount":590,"publisher":"Tor Books","rating":8,"series":"Mistborn", "title":"Mistborn: The Well of Ascension"}
 {"author":"Brandon Sanderson","dateRead":"Tue Oct 15 00:00:00 2019","genre":"fantasy","pageCount":572,"publisher":"Tor Books","rating":7,"series":"Mistborn","title":"Mistborn: The Hero of Ages"}
 {"author":"Robert Jordan","dateRead":"Sun Oct 27 00:00:00 2019","genre":"fantasy","pageCount":782,"publisher":"Tor Books","rating":8,"series":"The Wheel of Time","title":"The Eye of the World"}
 */

//#include <iostream>
//#include <vector>
//#include <fstream>
//#include "Author.hpp"
//#include "Book.hpp"
//#include "ReadBook.hpp"
//#include "FileMethods.hpp"
//#include "gui.hpp"

int main() {
    /*
    std::cout << "One step at a time" << std::endl << std::endl;
    std::string desktopPathLoad = "/Users/Frobu/Desktop/testFile.txt";
    std::string desktopPathSave = "/Users/Frobu/Desktop/testFileSave.txt";
    
    std::vector<nlohmann::json> test;
    std::vector<std::shared_ptr<ReadBook>> readBookVector;
    test = loadReadingList(desktopPathLoad);
    
    for (auto x : test) {
        readBookVector.push_back(convertJsonToReadBookPtr(x));
    }
    
    readBookVector.push_back(std::make_shared<ReadBook>(getNewReadBook()));
    
    test.clear();
    
    for (auto x : readBookVector) {
        test.push_back(nlohmann::json::parse(x->printJson()));
    }
    
    saveReadingList(test, desktopPathSave);
    
    //part 2
    Author sanderson("Brandon Sanderson", "Dec 19 1975");
    
    for (auto x : readBookVector) {
        if (x->getAuthor() == sanderson.getName()) {
            sanderson.addBookWritten(x);
        }
    }
    
    for (auto x : sanderson.getBooksWritten()) {
        std::cout << x->printJson() << std::endl;
    }
    */
    return 0;
}
