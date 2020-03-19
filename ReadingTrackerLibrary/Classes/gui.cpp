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
rtl::Author rtl::CommandLine::GetNewAuthor(std::istream& inputStream, std::ostream& outputStream) {
    std::string name;
    std::string dateBorn;
    
    OutputLine(outputStream, "Input author's name");
    name = GetInput(inputStream);
    OutputLine(outputStream, "Input author's date of birth (leave blank if unknown)");
    dateBorn = GetInput(inputStream);
    
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
//TODO: more descriptive input messages
rtl::Book rtl::CommandLine::GetNewBook(std::istream& inputStream, std::ostream& outputStream) {
    std::string author, isbn, oclc, title, publisher, series, genre, datePublished, pageCount;
    
    OutputLine(outputStream, "Input author");
    author = GetInput(inputStream);
    OutputLine(outputStream, "Input ISBN");
    isbn = GetInput(inputStream);
    OutputLine(outputStream, "Input OCLC");
    oclc = GetInput(inputStream);
    OutputLine(outputStream, "Input title");
    title = GetInput(inputStream);
    OutputLine(outputStream, "Input publisher");
    publisher = GetInput(inputStream);
    OutputLine(outputStream, "Input series");
    series = GetInput(inputStream);
    OutputLine(outputStream, "Input genre");
    genre = GetInput(inputStream);
    OutputLine(outputStream, "Input date published");
    datePublished = GetInput(inputStream);
    OutputLine(outputStream, "Input page count");
    pageCount = GetInput(inputStream);
    
    return rtl::Book(author, title, series, publisher, stoi(pageCount), genre, datePublished, isbn, oclc);
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
//TODO: validation on inputs, better input flow
rtl::ReadBook rtl::CommandLine::GetNewReadBook(std::istream& inputStream, std::ostream& outputStream, int readerId) {
    std::string author, title, publisher, series, genre, datePublished, pageCount, dateFinished, rating, isbn, oclc;
    
    OutputLine(outputStream, "Input author");
    author = GetInput(inputStream);
    OutputLine(outputStream, "Input title");
    title = GetInput(inputStream);
    OutputLine(outputStream, "Input isbn");
    isbn = GetInput(inputStream);
    OutputLine(outputStream, "Input oclc");
    oclc = GetInput(inputStream);
    OutputLine(outputStream, "Input publisher");
    publisher = GetInput(inputStream);
    OutputLine(outputStream, "Input series");
    series = GetInput(inputStream);
    OutputLine(outputStream, "Input genre");
    genre = GetInput(inputStream);
    OutputLine(outputStream, "Input date published");
    datePublished = GetInput(inputStream);
    OutputLine(outputStream, "Input page count");
    pageCount = GetInput(inputStream);
    OutputLine(outputStream, "Input date you finished reading");
    dateFinished = GetInput(inputStream);
    OutputLine(outputStream, "On a scale of 1 - 10 rate the book");
    rating = GetInput(inputStream);
    
    return rtl::ReadBook(readerId, rtl::Book(author, title, series, publisher, stoi(pageCount), genre, datePublished, isbn, oclc), stoi(rating), dateFinished);
}

void rtl::CommandLine::OutputLine(std::ostream& outputStream, std::string output) {
    outputStream << output << std::endl;
    return;
}

void rtl::CommandLine::OutputLine(std::ostream& outputStream, std::vector<std::string> output) {
    for (std::string x : output) {
        outputStream << x << std::endl;
    }
    return;
}

std::string rtl::CommandLine::GetInput(std::istream& inputStream) {
    std::string returnString;
    std::getline(inputStream, returnString);
    return returnString;
}

//helper function for user inputs
void userInputAgain(std::ostream& outputStream) {
    rtl::CommandLine::OutputLine(outputStream, "Invalid selection, please try again");
    outputStream << "\f";
    return;
}

//TODO: should only be called from mainMenu so not in header, do all the options need to share so much code not abstracted away (too much copy/paste)
void addMenu(std::istream& inputStream, std::ostream& outputStream, rtl::InMemoryContainers& masterList, int readerId) {
    
    while(true) {
        rtl::CommandLine::OutputLine(outputStream, std::vector<std::string>
        {   "Please select what you want to add",
            "1: Book",
            "2: Books that have been read",
            "3: Authors",
            "x: Return to main menu"
        });
        std::string input = rtl::CommandLine::GetInput(inputStream);
        
        if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
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
                rtl::Book newBook = rtl::CommandLine::GetNewBook(inputStream, outputStream);
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save:");
                rtl::CommandLine::OutputLine(outputStream, newBook.PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Y/N");
                input = rtl::CommandLine::GetInput(inputStream);
                if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
                    userInputAgain(outputStream);
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.AddMasterBooks(std::make_shared<rtl::Book>(newBook));
                        rtl::CommandLine::OutputLine(outputStream, "Book added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        rtl::CommandLine::OutputLine(outputStream, "Discarding new Book\n");
                    default:
                        break;
                }
                break;
            }
            //readbook
            case '2': {
                rtl::ReadBook newReadBook = rtl::CommandLine::GetNewReadBook(inputStream, outputStream, readerId);
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save:");
                rtl::CommandLine::OutputLine(outputStream, newReadBook.PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Y/N");
                input = rtl::CommandLine::GetInput(inputStream);
                if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
                    userInputAgain(outputStream);
                    continue;
                }
                
                char charSaveInput = input.at(0);

                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.AddMasterReadBooks(std::make_shared<rtl::ReadBook>(newReadBook));
                        rtl::CommandLine::OutputLine(outputStream, "Read book added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        rtl::CommandLine::OutputLine(outputStream, "Discarding new Read book\n");
                    default:
                        break;
                }
                break;
            }
            //author
            case '3': {
                rtl::Author newAuthor = rtl::CommandLine::GetNewAuthor(inputStream, outputStream);
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save:");
                rtl::CommandLine::OutputLine(outputStream, newAuthor.PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Y/N");
                input = rtl::CommandLine::GetInput(inputStream);
                if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
                    userInputAgain(outputStream);
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.AddMasterAuthors(std::make_shared<rtl::Author>(newAuthor));
                        rtl::CommandLine::OutputLine(outputStream, "Author added successfully\n");
                        break;
                    }
                    case 'n':
                    case 'N':
                        rtl::CommandLine::OutputLine(outputStream, "Discarding new Author\n");
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
        rtl::CommandLine::OutputLine(outputStream, std::vector<std::string>
        {   "Please select what you want to display",
            "1: Book",
            "2: Books that have been read",
            "3: Authors",
            "9: All",
            "s: Switch display mode. Currently: " + displayMode,
            "x: Return to main menu"
        });
        std::string input = rtl::CommandLine::GetInput(inputStream);
        
        if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
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
                    rtl::CommandLine::OutputLine(outputStream, rtl::Book::PrintCommandLineHeaders());
                    for (auto x : masterList.GetMasterBooks()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintCommandLine());
                    }
                    rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.GetMasterBooks()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintJson());
                        rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            //readbook
            case '2': {
                if (displayMode == "Simple") {
                    //column headers
                    rtl::CommandLine::OutputLine(outputStream, rtl::ReadBook::PrintCommandLineHeaders());
                    for (auto x : masterList.GetMasterReadBooks()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintCommandLine());
                    }
                    rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.GetMasterReadBooks()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintJson());
                        rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            //author
            case '3': {
                if (displayMode == "Simple") {
                    //column headers
                    rtl::CommandLine::OutputLine(outputStream, rtl::Author::PrintCommandLineHeaders());
                    for (auto x : masterList.GetMasterAuthors()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintCommandLine());
                    }
                    rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    for (auto x : masterList.GetMasterAuthors()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintJson());
                        rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                    }
                }
                break;
            }
            case '9': {
                if (displayMode == "Simple") {
                    //book
                    rtl::CommandLine::OutputLine(outputStream, "Books:\n");
                    //column headers
                    rtl::CommandLine::OutputLine(outputStream, rtl::Book::PrintCommandLineHeaders());
                    for (auto x : masterList.GetMasterBooks()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintCommandLine());
                    }
                    rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                    
                    //readbook
                    rtl::CommandLine::OutputLine(outputStream, "Read Books:\n");
                    //column headers
                    rtl::CommandLine::OutputLine(outputStream, rtl::ReadBook::PrintCommandLineHeaders());
                    for (auto x : masterList.GetMasterReadBooks()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintCommandLine());
                    }
                    rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation

                    //author
                    rtl::CommandLine::OutputLine(outputStream, "Authors:\n");
                    //column headers
                    rtl::CommandLine::OutputLine(outputStream, rtl::Author::PrintCommandLineHeaders());
                    for (auto x : masterList.GetMasterAuthors()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintCommandLine());
                    }
                    rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                }
                else {
                    //book
                    rtl::CommandLine::OutputLine(outputStream, "Books:\n");
                    for (auto x : masterList.GetMasterBooks()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintJson());
                        rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                    }
                    
                    //readbook
                    rtl::CommandLine::OutputLine(outputStream, "Read Books:\n");
                    for (auto x : masterList.GetMasterReadBooks()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintJson());
                        rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                    }

                    //author
                    rtl::CommandLine::OutputLine(outputStream, "Authors:\n");
                    for (auto x : masterList.GetMasterAuthors()) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintJson());
                        rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
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

void rtl::CommandLine::MainMenu(std::istream& inputStream, std::ostream& outputStream, int readerId) {
    rtl::InMemoryContainers& masterList = rtl::InMemoryContainers::GetInstance();
    
    while(true) {
        rtl::CommandLine::OutputLine(outputStream, std::vector<std::string>
        {   "Please select your option by typing the number displayed",
            "1: Add new object",
            "2: Display object",
            "3: nothing yet",
            "4: nothing yet",
            "5: nothing yet",
            "6: nothing yet",
            "7: Save to file",
            "8: Load file (adds to list, does not overwrite)",
            "x: Quit"
        });
        std::string input = rtl::CommandLine::GetInput(inputStream);
        
        if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
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
                rtl::CommandLine::OutputLine(outputStream, "Input file path for save file");
                input = rtl::CommandLine::GetInput(inputStream);
                //shortcut to macOS desktop TODO: dedicated save space than desktop
                if(input == "desktop") {
                    input = std::getenv("HOME");
                    input += "/Desktop/testFile.txt";
                }
                //TODO: log on error
                (masterList.SaveInMemoryToFile(input) ? rtl::CommandLine::OutputLine(outputStream, "save success\n") : rtl::CommandLine::OutputLine(outputStream, "error saving"));
                break;
            }
            case '8': {
                rtl::CommandLine::OutputLine(outputStream, "Input file path to load file");
                input = rtl::CommandLine::GetInput(inputStream);
                //shortcut to macOS desktop TODO: dedicated save space than desktop
                if(input == "desktop") {
                    input = std::getenv("HOME");
                    input += "/Desktop/testFile.txt";
                }
                //TODO: log on error
                (masterList.LoadInMemoryFromFile(input) ? rtl::CommandLine::OutputLine(outputStream, "load success\n") : rtl::CommandLine::OutputLine(outputStream, "error loading"));
                break;
            }
            case 'X':
            case 'x': {
                rtl::CommandLine::OutputLine(outputStream, "Are you sure you wish to quit? (Y/N)");
                input = rtl::CommandLine::GetInput(inputStream);
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
