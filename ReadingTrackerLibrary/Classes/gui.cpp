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
ReadBook getNewReadBook(std::istream &inputStream, std::ostream &outputStream) {
    std::string input;
    ReadBook newReadBook;
    
    outputLine(outputStream, "Input author");
    input = getInput(inputStream);
    newReadBook.setAuthor(input);
    outputLine(outputStream, "Input title");
    input = getInput(inputStream);
    newReadBook.setTitle(input);
    outputLine(outputStream, "Input publisher");
    input = getInput(inputStream);
    newReadBook.setPublisher(input);
    outputLine(outputStream, "Input series");
    input = getInput(inputStream);
    newReadBook.setSeries(input);
    outputLine(outputStream, "Input genre");
    input = getInput(inputStream);
    newReadBook.setGenre(input);
    outputLine(outputStream, "Input date published");
    input = getInput(inputStream);
    newReadBook.setPublishDate(input);
    outputLine(outputStream, "Input page count");
    input = getInput(inputStream);
    newReadBook.setPageCount(stoi(input));
    outputLine(outputStream, "Input date you finished reading");
    input = getInput(inputStream);
    newReadBook.setDateRead(input);
    outputLine(outputStream, "On a scale of 1 - 10 rate the book");
    input = getInput(inputStream);
    newReadBook.setRating(stoi(input));
    
    return newReadBook;
}

void outputLine(std::ostream &outputStream, std::string output) {
    outputStream << output << std::endl;
}

std::string getInput(std::istream &inputStream) {
    std::string returnString;
    std::getline(inputStream, returnString);
    return returnString;
}

void userInputAgain() {
    outputLine(std::cout, "Invalid selection, please try again");
    
    std::cout << "\f";
    
    return;
}

void mainMenu() {
    
    char charInput = 'p';
    InMemoryContainers& masterList = InMemoryContainers::getInstance();
    
    while(true) {
        outputLine(std::cout, "One step at a time");
        outputLine(std::cout, "Please select your option by typing the number displayed");
        outputLine(std::cout, "1: Add new Book");
        outputLine(std::cout, "2: Display all ReadBooks");
        outputLine(std::cout, "3:");
        outputLine(std::cout, "4:");
        outputLine(std::cout, "5:");
        outputLine(std::cout, "6:");
        outputLine(std::cout, "7: Save to file");
        outputLine(std::cout, "8: Load file (adds to list, does not overwrite)");
        outputLine(std::cout, "9: Quit");
        outputLine(std::cout, "");
        
        std::string input = getInput(std::cin);
        
        if (trim(input).empty() || trim(input).size() > 1) {
            userInputAgain();
            input = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        charInput = input.at(0);
        
        switch(charInput) {
            case '1': {
                ReadBook newReadBook = getNewReadBook(std::cin, std::cout); //TODO DO SOMETHING WITH THIS
                outputLine(std::cout, "Would you like to save:");
                outputLine(std::cout, newReadBook.printJson() + "?");
                outputLine(std::cout, "Y/N");
                input = getInput(std::cin);
                if (trim(input).empty() || trim(input).size() > 1) {
                    userInputAgain();
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'Y': {
                        masterList.addMasterReadBooks(std::make_shared<ReadBook>(newReadBook));
                        break;
                    }
                    case 'N':
                    default:
                        break;
                }
                
                break;
            }
            case '2': {
                for (auto x : masterList.getMasterReadBooks()) {
                    outputLine(std::cout, x->printJson());
                }
                break;
            }
            case '7': {
                
            }
            case '8': {
                
            }
            case '9': {
                outputLine(std::cout, "Are you sure you wish to quit? (Y/N)");
                input = getInput(std::cin);
                if (!input.empty() && (input.at(0) == 'Y' || input.at(0) == 'y')) {
                    return;
                }
                else {
                    break;
                }
            }
            default:
                userInputAgain();
                input = "";
                charInput = 'p';
                //std::cin.clear();
                //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
        }
    }
        
    
    return;
}
