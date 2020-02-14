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
ReadBook getNewReadBook(std::istream &inputStream) {
    std::string input;
    ReadBook newReadBook;
    
    outputLine("Input author");
    input = getInput(inputStream);
    newReadBook.setAuthor(input);
    outputLine("Input title");
    input = getInput(inputStream);
    newReadBook.setTitle(input);
    outputLine("Input publisher");
    input = getInput(inputStream);
    newReadBook.setPublisher(input);
    outputLine("Input series");
    input = getInput(inputStream);
    newReadBook.setSeries(input);
    outputLine("Input genre");
    input = getInput(inputStream);
    newReadBook.setGenre(input);
    outputLine("Input date published");
    input = getInput(inputStream);
    newReadBook.setPublishDate(input);
    outputLine("Input page count");
    input = getInput(inputStream);
    newReadBook.setPageCount(stoi(input));
    outputLine("Input date you finished reading");
    input = getInput(inputStream);
    newReadBook.setDateRead(input);
    outputLine("On a scale of 1 - 10 rate the book");
    input = getInput(inputStream);
    newReadBook.setRating(stoi(input));
    
    return newReadBook;
}

void outputLine(std::string output) {
    std::cout << output << std::endl;
}

std::string getInput(std::istream &inputStream) {
    std::string returnString;
    std::getline(inputStream, returnString);
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
                ReadBook newReadBook = getNewReadBook(std::cin); //TODO DO SOMETHING WITH THIS
                outputLine("Would you like to save:");
                outputLine(newReadBook.printJson() + "?");
                outputLine("Y/N");
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
            case '2':
                for (auto x : masterList.getMasterReadBooks()) {
                    outputLine(x->printJson());
                }
                break;
            case '9':
                outputLine("Are you sure you wish to quit? (Y/N)");
                input = getInput(std::cin);
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
