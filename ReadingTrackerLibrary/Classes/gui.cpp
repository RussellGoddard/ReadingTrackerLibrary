//
//  gui.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/28/19.
//

#include "gui.hpp"

using namespace rtlCommandLine;

/*
    "name":"Robert Jordan",
    "dateBorn":"Oct 17 1948",
    "booksWritten":[]

*/

rtl::Author rtlCommandLine::getNewAuthor(std::istream& inputStream, std::ostream& outputStream) {
    std::string name, dateBorn;
    
    outputLine(outputStream, "Input author's name");
    name = getInput(inputStream);
    outputLine(outputStream, "Input author's date of birth (leave blank if unknown)");
    dateBorn = getInput(inputStream);
    rtl::Author newAuthor(name, dateBorn);
    
    return newAuthor;
}
 
/*
{
    "author" : "Robert Jordan",
    "title" : "Eye of the World",
    "publisher" : "Tor Books",
    "series" : "The Wheel of Time",
    "genre" : "fantasy",
    "publishDate" : "Oct 14 2008",
    "pageCount" : 782
}
*/

rtl::Book rtlCommandLine::getNewBook(std::istream& inputStream, std::ostream& outputStream) {
    std::string input;
    rtl::Book newBook;
    
    outputLine(outputStream, "Input author");
    input = getInput(inputStream);
    newBook.setAuthor(input);
    outputLine(outputStream, "Input title");
    input = getInput(inputStream);
    newBook.setTitle(input);
    outputLine(outputStream, "Input publisher");
    input = getInput(inputStream);
    newBook.setPublisher(input);
    outputLine(outputStream, "Input series");
    input = getInput(inputStream);
    newBook.setSeries(input);
    outputLine(outputStream, "Input genre");
    input = getInput(inputStream);
    newBook.setGenre(input);
    outputLine(outputStream, "Input date published");
    input = getInput(inputStream);
    newBook.setPublishDate(input);
    outputLine(outputStream, "Input page count");
    input = getInput(inputStream);
    newBook.setPageCount(stoi(input));
    
    return newBook;
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
rtl::ReadBook rtlCommandLine::getNewReadBook(std::istream& inputStream, std::ostream& outputStream, int readerId) {
    std::string input;
    rtl::ReadBook newReadBook(readerId);
    
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

void rtlCommandLine::outputLine(std::ostream& outputStream, std::string output) {
    outputStream << output << std::endl;
}

std::string rtlCommandLine::getInput(std::istream& inputStream) {
    std::string returnString;
    std::getline(inputStream, returnString);
    return returnString;
}

void userInputAgain() {
    outputLine(std::cout, "Invalid selection, please try again");
    
    std::cout << "\f";
    
    return;
}

//should only be called from mainMenu so not in header, TODO do all the options need to share so much code not abstracted away (too much copy/paste)
void addMenu(std::istream& inputStream, std::ostream& outputStream, rtl::InMemoryContainers& masterList, int readerId) {
    
    while(true) {
        char charInput = 'p';
        outputLine(outputStream, "Please select what you want to add");
        outputLine(outputStream, "1: Book");
        outputLine(outputStream, "2: Books that have been read");
        outputLine(outputStream, "3: Authors");
        outputLine(outputStream, "x: Return to main menu");
        
        std::string input = getInput(inputStream);
        
        if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
            userInputAgain();
            input = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        charInput = input.at(0);
        
        switch(charInput) {
            //book
            case '1': {
                rtl::Book newBook = getNewBook(inputStream, outputStream);
                outputLine(outputStream, "Would you like to save:");
                outputLine(outputStream, newBook.printJson() + "?");
                outputLine(outputStream, "Y/N");
                input = getInput(inputStream);
                if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
                    userInputAgain();
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.addMasterBooks(std::make_shared<rtl::Book>(newBook));
                        outputLine(outputStream, "Book added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        outputLine(outputStream, "Discarding new Book\n");
                    default:
                        break;
                }
                break;
            }
            //readbook
            case '2': {
                rtl::ReadBook newReadBook = getNewReadBook(inputStream, outputStream, readerId);
                outputLine(outputStream, "Would you like to save:");
                outputLine(outputStream, newReadBook.printJson() + "?");
                outputLine(outputStream, "Y/N");
                input = getInput(inputStream);
                if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
                    userInputAgain();
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.addMasterReadBooks(std::make_shared<rtl::ReadBook>(newReadBook));
                        outputLine(outputStream, "Read book added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        outputLine(outputStream, "Discarding new Read book\n");
                    default:
                        break;
                }
                break;
            }
            //author
            case '3': {
                rtl::Author newAuthor = getNewAuthor(inputStream, outputStream);
                outputLine(outputStream, "Would you like to save:");
                outputLine(outputStream, newAuthor.printJson() + "?");
                outputLine(outputStream, "Y/N");
                input = getInput(inputStream);
                if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
                    userInputAgain();
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.addMasterAuthors(std::make_shared<rtl::Author>(newAuthor));
                        outputLine(outputStream, "Author added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        outputLine(outputStream, "Discarding new Author\n");
                    default:
                        break;
                }
                break;
            }
            case 'X':
            case 'x': {
                return;
            }
        }
    }
    
    return;
}

//should only be called from mainMenu so not in header
void displayMenu(std::istream& inputStream, std::ostream& outputStream, rtl::InMemoryContainers& masterList) {
    
    std::string displayMode = "Json";
    
    while(true) {
        char charInput = 'p';
        outputLine(outputStream, "Please select what you want to display");
        outputLine(outputStream, "1: Book");
        outputLine(outputStream, "2: Books that have been read");
        outputLine(outputStream, "3: Authors");
        outputLine(outputStream, "9: All");
        outputLine(outputStream, "s: Switch display mode. Currently: " + displayMode);
        outputLine(outputStream, "x: Return to main menu");
        
        std::string input = getInput(inputStream);
        
        if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
            userInputAgain();
            input = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        charInput = input.at(0);
        
        switch(charInput) {
            //book
            case '1': {
                if (displayMode == "Simple") {
                    //column headers
                    outputLine(outputStream, rtl::Book::printCommandLineHeaders());
                    for (auto x : masterList.getMasterBooks()) {
                        outputLine(outputStream, x->printCommandLine());
                    }
                    outputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.getMasterBooks()) {
                        outputLine(outputStream, x->printJson());
                        outputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            //readbook
            case '2': {
                if (displayMode == "Simple") {
                    //column headers
                    outputLine(outputStream, rtl::ReadBook::printCommandLineHeaders());
                    for (auto x : masterList.getMasterReadBooks()) {
                        outputLine(outputStream, x->printCommandLine());
                    }
                    outputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.getMasterReadBooks()) {
                        outputLine(outputStream, x->printJson());
                        outputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            //author
            case '3': {
                if (displayMode == "Simple") {
                    //column headers
                    outputLine(outputStream, rtl::Author::printCommandLineHeaders());
                    for (auto x : masterList.getMasterAuthors()) {
                        outputLine(outputStream, x->printCommandLine());
                    }
                    outputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.getMasterAuthors()) {
                        outputLine(outputStream, x->printJson());
                        outputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            case '9': {
                if (displayMode == "Simple") {
                    //book
                    outputLine(outputStream, "Books:\n");
                    //column headers
                    outputLine(outputStream, rtl::Book::printCommandLineHeaders());
                    for (auto x : masterList.getMasterBooks()) {
                        outputLine(outputStream, x->printCommandLine());
                    }
                    outputLine(outputStream, ""); //blank line for seperation
                    
                    //readbook
                    outputLine(outputStream, "Read Books:\n");
                    //column headers
                    outputLine(outputStream, rtl::ReadBook::printCommandLineHeaders());
                    for (auto x : masterList.getMasterReadBooks()) {
                        outputLine(outputStream, x->printCommandLine());
                    }
                    outputLine(outputStream, ""); //blank line for seperation

                    //author
                    outputLine(outputStream, "Authors:\n");
                    //column headers
                    outputLine(outputStream, rtl::Author::printCommandLineHeaders());
                    for (auto x : masterList.getMasterAuthors()) {
                        outputLine(outputStream, x->printCommandLine());
                    }
                    outputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    //book
                    outputLine(outputStream, "Books:\n");
                    for (auto x : masterList.getMasterBooks()) {
                        outputLine(outputStream, x->printJson());
                        outputLine(outputStream, ""); //blank line for seperation
                    }
                    
                    //readbook
                    outputLine(outputStream, "Read Books:\n");
                    for (auto x : masterList.getMasterReadBooks()) {
                        outputLine(outputStream, x->printJson());
                        outputLine(outputStream, ""); //blank line for seperation
                    }

                    //author
                    outputLine(outputStream, "Authors:\n");
                    for (auto x : masterList.getMasterAuthors()) {
                        outputLine(outputStream, x->printJson());
                        outputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            case 'S':
            case 's': {
                if (displayMode == "Json") {
                    displayMode = "Simple";
                }
                else if (displayMode == "Simple") {
                    displayMode = "Json";
                }
                break;
            }
            case 'X':
            case 'x': {
                return;
            }
        }
    }
    
    return;
}

void rtlCommandLine::mainMenu(std::istream& inputStream, std::ostream& outputStream, int readerId) {
    
    rtl::InMemoryContainers& masterList = rtl::InMemoryContainers::getInstance();
    
    while(true) {
        char charInput = 'p';
        outputLine(outputStream, "Please select your option by typing the number displayed");
        outputLine(outputStream, "1: Add new object");
        outputLine(outputStream, "2: Display object");
        outputLine(outputStream, "3: nothing yet");
        outputLine(outputStream, "4: nothing yet");
        outputLine(outputStream, "5: nothing yet");
        outputLine(outputStream, "6: nothing yet");
        outputLine(outputStream, "7: Save to file");
        outputLine(outputStream, "8: Load file (adds to list, does not overwrite)");
        outputLine(outputStream, "x: Quit");
        
        std::string input = getInput(inputStream);
        
        if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
            userInputAgain();
            input = "";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        charInput = input.at(0);
        
        switch(charInput) {
            case '1': {
                addMenu(inputStream, outputStream, masterList, readerId);
                break;
            }
            case '2': {
                displayMenu(inputStream, outputStream, masterList);
                break;
            }
            case '7': {
                outputLine(outputStream, "Input file path for save file");
                input = getInput(inputStream);
                //shortcut to macOS desktop TODO dedicated save space than desktop
                if(input == "desktop") {
                    input = std::getenv("HOME");
                    input += "/Desktop/testFile.txt";
                }
                (masterList.saveInMemoryToFile(input) ? outputLine(outputStream, "save success\n") : outputLine(outputStream, "error saving"));
                break;
            }
            case '8': {
                outputLine(outputStream, "Input file path to load file");
                input = getInput(inputStream);
                //shortcut to macOS desktop TODO dedicated save space than desktop
                if(input == "desktop") {
                    input = std::getenv("HOME");
                    input += "/Desktop/testFile.txt";
                }
                (masterList.loadInMemoryFromFile(input) ? outputLine(outputStream, "load success\n") : outputLine(outputStream, "error loading"));
                break;
            }
            case 'X':
            case 'x': {
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
