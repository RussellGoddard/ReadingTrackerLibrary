//
//  gui.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/28/19.
//

#include "gui.hpp"
/*
{
    "author" : "Robert Jordan",
    "title" : "Eye of the World",
    "publisher" : "Tor Books",
    "series" : "The Wheel of Time",
    "genre" : "fantasy",
    "publishDate" : "Oct 14 2008",
    "pageCount" : 782,
    "rating" : 9,
    "dateRead" : "Oct 26 2019"
}
*/
ReadBook getNewReadBook() {
    std::string input = "";
    ReadBook newReadBook;
    
    outputString("Input author");
    std::getline(std::cin, input);
    newReadBook.setAuthor(input);
    outputString("Input title");
    std::getline(std::cin, input);
    newReadBook.setTitle(input);
    outputString("Input publisher");
    std::getline(std::cin, input);
    newReadBook.setPublisher(input);
    outputString("Input series");
    std::getline(std::cin, input);
    newReadBook.setSeries(input);
    outputString("Input genre");
    std::getline(std::cin, input);
    newReadBook.setGenre(input);
    outputString("Input date published");
    std::getline(std::cin, input);
    newReadBook.setPublishDate(input);
    outputString("Input page count");
    std::getline(std::cin, input);
    newReadBook.setPageCount(stoi(input));
    outputString("Input date you finished reading");
    std::getline(std::cin, input);
    newReadBook.setDateRead(input);
    outputString("On a scale of 1 - 10 rate the book");
    std::getline(std::cin, input);
    newReadBook.setRating(stoi(input));
    
    return newReadBook;
}

void outputString(std::string output) {
    std::cout << output << std::endl;
}
