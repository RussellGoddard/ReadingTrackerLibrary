//
//  gui.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/28/19.
//

#include "gui.hpp"


std::string& leftTrim(std::string& input) {
  auto it2 =  std::find_if(input.begin(), input.end(), [](char ch){ return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(input.begin(), it2);
  return input;
}

std::string& rightTrim(std::string& input)
{
  auto it1 = std::find_if(input.rbegin(), input.rend(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); } );
  input.erase(it1.base(), input.end());
  return input;
}

std::string& trim(std::string& str)
{
   return leftTrim(rightTrim(str));
}


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
    std::string input;
    ReadBook newReadBook;
    
    outputLine("Input author");
    input = getInput();
    newReadBook.setAuthor(input);
    outputLine("Input title");
    input = getInput();
    newReadBook.setTitle(input);
    outputLine("Input publisher");
    input = getInput();
    newReadBook.setPublisher(input);
    outputLine("Input series");
    input = getInput();
    newReadBook.setSeries(input);
    outputLine("Input genre");
    input = getInput();
    newReadBook.setGenre(input);
    outputLine("Input date published");
    input = getInput();
    newReadBook.setPublishDate(input);
    outputLine("Input page count");
    input = getInput();
    newReadBook.setPageCount(stoi(input));
    outputLine("Input date you finished reading");
    input = getInput();
    newReadBook.setDateRead(input);
    outputLine("On a scale of 1 - 10 rate the book");
    input = getInput();
    newReadBook.setRating(stoi(input));
    
    return newReadBook;
}

void outputLine(std::string output) {
    std::cout << output << std::endl;
}

std::string getInput() {
    std::string returnString;
    std::getline(std::cin, returnString);
    return returnString;
}

void userInputAgain() {
    outputLine("Invalid selection, please try again");
    
    std::cout << "\f";
    
    return;
}

void mainMenu() {
    
    char charInput = 'p';
    InMemoryContainers& masterList = InMemoryContainers::getInstance();
    
    while(true) {
        outputLine("One step at a time");
        outputLine("Please select your option by typing the number displayed");
        outputLine("1: Add new Book");
        outputLine("2: Display all ReadBooks");
        outputLine("9: Quit");
        outputLine("");
        
        std::string input = getInput();
        
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
                ReadBook newReadBook = getNewReadBook(); //TODO DO SOMETHING WITH THIS
                outputLine("Would you like to save:");
                outputLine(newReadBook.printJson() + "?");
                outputLine("Y/N");
                input = getInput();
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
            case '2':
                for (auto x : masterList.getMasterReadBooks()) {
                    outputLine(x->printJson());
                }
                break;
            case '9':
                outputLine("Are you sure you wish to quit? (Y/N)");
                input = getInput();
                if (!input.empty() && (input.at(0) == 'Y' || input.at(0) == 'y')) {
                    return;
                }
                else {
                    break;
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
