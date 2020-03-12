//
//  gui.cpp
//  Reading Tracker
//
//  Created by Frobu on 10/28/19.
//

#include "gui.hpp"

/*
    "name":"Robert Jordan",
    "dateBorn":"Oct 17 1948",
    "booksWritten":[]

*/
rtl::Author rtlCommandLine::getNewAuthor(std::istream& inputStream, std::ostream& outputStream) {
    std::string name;
    std::string dateBorn;
    
    outputLine(outputStream, "Input author's name");
    name = getInput(inputStream);
    outputLine(outputStream, "Input author's date of birth (leave blank if unknown)");
    dateBorn = getInput(inputStream);
    
    return rtl::Author(name, dateBorn);
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

void userInputAgain(std::ostream& outputStream) {
    rtlCommandLine::outputLine(outputStream, "Invalid selection, please try again");
    outputStream << "\f";
    return;
}

//TODO: should only be called from mainMenu so not in header, do all the options need to share so much code not abstracted away (too much copy/paste)
void addMenu(std::istream& inputStream, std::ostream& outputStream, rtl::InMemoryContainers& masterList, int readerId) {
    
    while(true) {
        rtlCommandLine::outputLine(outputStream, "Please select what you want to add");
        rtlCommandLine::outputLine(outputStream, "1: Book");
        rtlCommandLine::outputLine(outputStream, "2: Books that have been read");
        rtlCommandLine::outputLine(outputStream, "3: Authors");
        rtlCommandLine::outputLine(outputStream, "x: Return to main menu");
        
        std::string input = rtlCommandLine::getInput(inputStream);
        
        if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
            userInputAgain(outputStream);
            input = "";
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        char charInput = 'p';
        charInput = input.at(0);
        
        switch(charInput) {
            //book
            case '1': {
                rtl::Book newBook = rtlCommandLine::getNewBook(inputStream, outputStream);
                rtlCommandLine::outputLine(outputStream, "Would you like to save:");
                rtlCommandLine::outputLine(outputStream, newBook.printJson() + "?");
                rtlCommandLine::outputLine(outputStream, "Y/N");
                input = rtlCommandLine::getInput(inputStream);
                if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
                    userInputAgain(outputStream);
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.addMasterBooks(std::make_shared<rtl::Book>(newBook));
                        rtlCommandLine::outputLine(outputStream, "Book added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        rtlCommandLine::outputLine(outputStream, "Discarding new Book\n");
                    default:
                        break;
                }
                break;
            }
            //readbook
            case '2': {
                rtl::ReadBook newReadBook = rtlCommandLine::getNewReadBook(inputStream, outputStream, readerId);
                rtlCommandLine::outputLine(outputStream, "Would you like to save:");
                rtlCommandLine::outputLine(outputStream, newReadBook.printJson() + "?");
                rtlCommandLine::outputLine(outputStream, "Y/N");
                input = rtlCommandLine::getInput(inputStream);
                if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
                    userInputAgain(outputStream);
                    continue;
                }
                
                char charSaveInput = input.at(0);

                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.addMasterReadBooks(std::make_shared<rtl::ReadBook>(newReadBook));
                        rtlCommandLine::outputLine(outputStream, "Read book added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        rtlCommandLine::outputLine(outputStream, "Discarding new Read book\n");
                    default:
                        break;
                }
                break;
            }
            //author
            case '3': {
                rtl::Author newAuthor = rtlCommandLine::getNewAuthor(inputStream, outputStream);
                rtlCommandLine::outputLine(outputStream, "Would you like to save:");
                rtlCommandLine::outputLine(outputStream, newAuthor.printJson() + "?");
                rtlCommandLine::outputLine(outputStream, "Y/N");
                input = rtlCommandLine::getInput(inputStream);
                if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
                    userInputAgain(outputStream);
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.addMasterAuthors(std::make_shared<rtl::Author>(newAuthor));
                        rtlCommandLine::outputLine(outputStream, "Author added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        rtlCommandLine::outputLine(outputStream, "Discarding new Author\n");
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
        rtlCommandLine::outputLine(outputStream, "Please select what you want to display");
        rtlCommandLine::outputLine(outputStream, "1: Book");
        rtlCommandLine::outputLine(outputStream, "2: Books that have been read");
        rtlCommandLine::outputLine(outputStream, "3: Authors");
        rtlCommandLine::outputLine(outputStream, "9: All");
        rtlCommandLine::outputLine(outputStream, "s: Switch display mode. Currently: " + displayMode);
        rtlCommandLine::outputLine(outputStream, "x: Return to main menu");
        
        std::string input = rtlCommandLine::getInput(inputStream);
        
        if (rtl::trim(input).empty() || rtl::trim(input).size() > 1) {
            userInputAgain(outputStream);
            input = "";
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        char charInput = 'p';
        charInput = input.at(0);
        
        switch(charInput) {
            //book
            case '1': {
                if (displayMode == "Simple") {
                    //column headers
                    rtlCommandLine::outputLine(outputStream, rtl::Book::printCommandLineHeaders());
                    for (auto x : masterList.getMasterBooks()) {
                        rtlCommandLine::outputLine(outputStream, x->printCommandLine());
                    }
                    rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.getMasterBooks()) {
                        rtlCommandLine::outputLine(outputStream, x->printJson());
                        rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            //readbook
            case '2': {
                if (displayMode == "Simple") {
                    //column headers
                    rtlCommandLine::outputLine(outputStream, rtl::ReadBook::printCommandLineHeaders());
                    for (auto x : masterList.getMasterReadBooks()) {
                        rtlCommandLine::outputLine(outputStream, x->printCommandLine());
                    }
                    rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.getMasterReadBooks()) {
                        rtlCommandLine::outputLine(outputStream, x->printJson());
                        rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            //author
            case '3': {
                if (displayMode == "Simple") {
                    //column headers
                    rtlCommandLine::outputLine(outputStream, rtl::Author::printCommandLineHeaders());
                    for (auto x : masterList.getMasterAuthors()) {
                        rtlCommandLine::outputLine(outputStream, x->printCommandLine());
                    }
                    rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.getMasterAuthors()) {
                        rtlCommandLine::outputLine(outputStream, x->printJson());
                        rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            case '9': {
                if (displayMode == "Simple") {
                    //book
                    rtlCommandLine::outputLine(outputStream, "Books:\n");
                    //column headers
                    rtlCommandLine::outputLine(outputStream, rtl::Book::printCommandLineHeaders());
                    for (auto x : masterList.getMasterBooks()) {
                        rtlCommandLine::outputLine(outputStream, x->printCommandLine());
                    }
                    rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                    
                    //readbook
                    rtlCommandLine::outputLine(outputStream, "Read Books:\n");
                    //column headers
                    rtlCommandLine::outputLine(outputStream, rtl::ReadBook::printCommandLineHeaders());
                    for (auto x : masterList.getMasterReadBooks()) {
                        rtlCommandLine::outputLine(outputStream, x->printCommandLine());
                    }
                    rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation

                    //author
                    rtlCommandLine::outputLine(outputStream, "Authors:\n");
                    //column headers
                    rtlCommandLine::outputLine(outputStream, rtl::Author::printCommandLineHeaders());
                    for (auto x : masterList.getMasterAuthors()) {
                        rtlCommandLine::outputLine(outputStream, x->printCommandLine());
                    }
                    rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    //book
                    rtlCommandLine::outputLine(outputStream, "Books:\n");
                    for (auto x : masterList.getMasterBooks()) {
                        rtlCommandLine::outputLine(outputStream, x->printJson());
                        rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                    }
                    
                    //readbook
                    rtlCommandLine::outputLine(outputStream, "Read Books:\n");
                    for (auto x : masterList.getMasterReadBooks()) {
                        rtlCommandLine::outputLine(outputStream, x->printJson());
                        rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
                    }

                    //author
                    rtlCommandLine::outputLine(outputStream, "Authors:\n");
                    for (auto x : masterList.getMasterAuthors()) {
                        rtlCommandLine::outputLine(outputStream, x->printJson());
                        rtlCommandLine::outputLine(outputStream, ""); //blank line for seperation
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
            userInputAgain(outputStream);
            input = "";
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        char charInput = 'p';
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
                //shortcut to macOS desktop TODO: dedicated save space than desktop
                if(input == "desktop") {
                    input = std::getenv("HOME");
                    input += "/Desktop/testFile.txt";
                }
                //TODO: log on error
                (masterList.saveInMemoryToFile(input) ? outputLine(outputStream, "save success\n") : outputLine(outputStream, "error saving"));
                break;
            }
            case '8': {
                outputLine(outputStream, "Input file path to load file");
                input = getInput(inputStream);
                //shortcut to macOS desktop TODO: dedicated save space than desktop
                if(input == "desktop") {
                    input = std::getenv("HOME");
                    input += "/Desktop/testFile.txt";
                }
                //TODO: log on error
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
                userInputAgain(outputStream);
                input = "";
                charInput = 'p';
                inputStream.clear();
                inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
        }
    }
        
    
    return;
}
