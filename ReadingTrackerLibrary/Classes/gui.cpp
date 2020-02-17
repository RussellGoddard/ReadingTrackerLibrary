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

void mainMenu(std::istream& inputStream, std::ostream& outputStream) {
    
    char charInput = 'p';
    InMemoryContainers& masterList = InMemoryContainers::getInstance();
    
    while(true) {
        outputLine(outputStream, "One step at a time");
        outputLine(outputStream, "Please select your option by typing the number displayed");
        outputLine(outputStream, "1: Add new ReadBook");
        outputLine(outputStream, "2: Display all ReadBooks");
        outputLine(outputStream, "3: nothing yet");
        outputLine(outputStream, "4: nothing yet");
        outputLine(outputStream, "5: nothing yet");
        outputLine(outputStream, "6: nothing yet");
        outputLine(outputStream, "7: Save to file");
        outputLine(outputStream, "8: Load file (adds to list, does not overwrite)");
        outputLine(outputStream, "9: Quit");
        outputLine(outputStream, "");
        
        std::string input = getInput(inputStream);
        
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
                ReadBook newReadBook = getNewReadBook(inputStream, outputStream); //TODO DO SOMETHING WITH THIS
                outputLine(outputStream, "Would you like to save:");
                outputLine(outputStream, newReadBook.printJson() + "?");
                outputLine(outputStream, "Y/N");
                input = getInput(inputStream);
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
                    outputLine(outputStream, x->printJson());
                }
                break;
            }
            case '7': {
                outputLine(outputStream, "Input file path for save file");
                input = getInput(inputStream);
                //shortcut for my desktop so I can test quicker TO DO change so it's generic desktop
                if(input == "desktop") {
                    input = "/Users/Frobu/Desktop/testFile.txt";
                }
                (masterList.saveInMemoryToFile(input) ? outputLine(outputStream, "save success") : outputLine(outputStream, "error saving"));
                break;
            }
            case '8': {
                outputLine(outputStream, "Input file path to load file");
                input = getInput(inputStream);
                //shortcut for my desktop so I can test quicker TO DO change so it's generic desktop
                if(input == "desktop") {
                    input = "/Users/Frobu/Desktop/testFile.txt";
                }
                (masterList.loadInMemoryFromFile(input) ? outputLine(outputStream, "load success") : outputLine(outputStream, "error loading"));
                break;
            }
            case '9': {
                outputLine(outputStream, "Are you sure you wish to quit? (Y/N)");
                input = getInput(inputStream);
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
