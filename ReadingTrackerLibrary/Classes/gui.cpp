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
rtl::Author rtl::CommandLine::GetNewAuthor(std::istream& inputStream, std::ostream& outputStream, int inputMode) {
    std::string name = "";
    std::string dateBorn = "";
    
    switch(inputMode) {
        //manual
        case 0: {
            OutputLine(outputStream, "Input author's name");
            name = GetInput(inputStream);
            OutputLine(outputStream, "Input author's date of birth (leave blank if unknown)");
            dateBorn = GetInput(inputStream);
            break;
        }
        //by identifier
        case 1: {
            //TODO: implement this
            std::cout << "not yet implemented, calling manual entry" << std::endl;
            return rtl::CommandLine::GetNewAuthor(inputStream, outputStream, 0);
        }
        //by title
        case 2: {
            //TODO: implement this
            std::cout << "not yet implemented, calling manual entry" << std::endl;
            return rtl::CommandLine::GetNewAuthor(inputStream, outputStream, 0);
        }
        default: {
            //TODO: log this, should never hit default
            break;
        }
    }
    
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

rtl::Book rtl::CommandLine::GetNewBook(std::istream& inputStream, std::ostream& outputStream, int inputMode) {
    std::string author = "";
    std::string isbn = "";
    std::string oclc = "";
    std::string title = "";
    std::string publisher = "";
    std::string series = "";
    std::string genre = "genre not set";
    std::string datePublished = "";
    std::string pageCount = "-1";
    
    switch(inputMode) {
        //manual
        case 0: {
            //TODO: more descriptive input messages
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
            break;
        }
        //by identifier (ISBN or OCLC)
        case 1: {
            //TODO: make better use of data in openlibrary
            
            OutputLine(outputStream, "Query openlibrary by? (input 'OCLC' or 'ISBN'");
            std::string identifier = GetInput(inputStream);
            OutputLine(outputStream, "Enter identifier number:");
            std::string identifierNum = GetInput(inputStream);
            OutputLine(outputStream, "Querying openlibrary for page titled: " + identifier + ":" + identifierNum);
            rtl::OpenLibraryValues openLibraryValues = rtl::QueryBookByIdentifier(identifier, identifierNum);
            if (!openLibraryValues.success) {
                OutputLine(outputStream, "Query failed, calling manual entry");
                return rtl::CommandLine::GetNewBook(inputStream, outputStream, 0);
            }
            
            rtl::WikiDataValues wikiDataValues = rtl::QueryBookByTitle(openLibraryValues.title);
            if (!wikiDataValues.success) {
                OutputLine(outputStream, "Query failed, calling manual entry");
                return rtl::CommandLine::GetNewBook(inputStream, outputStream, 0);
            }
            
            author = wikiDataValues.author;
            title = wikiDataValues.title;
            series = wikiDataValues.series;
            publisher = wikiDataValues.publisher;
            datePublished = boost::gregorian::to_simple_string(wikiDataValues.datePublished);
            isbn = wikiDataValues.isbn;
            oclc = wikiDataValues.oclc;
            break;
        }
        //by title
        case 2: {
            OutputLine(outputStream, "Input title, title should match the page title on wikidata.org, case sensitive");
            std::string query = GetInput(inputStream);
            OutputLine(outputStream, "Querying wikidata for page titled: " + query);
            
            rtl::WikiDataValues wikiDataValues = rtl::QueryBookByTitle(query);
            if (!wikiDataValues.success) {
                OutputLine(outputStream, "Query failed, calling manual entry");
                return rtl::CommandLine::GetNewBook(inputStream, outputStream, 0);
            }
            author = wikiDataValues.author;
            title = wikiDataValues.title;
            series = wikiDataValues.series;
            publisher = wikiDataValues.publisher;
            datePublished = boost::gregorian::to_simple_string(wikiDataValues.datePublished);
            isbn = wikiDataValues.isbn;
            oclc = wikiDataValues.oclc;
            
            OutputLine(outputStream, "Query success");
            break;
        }
        default:
            //TODO: log this, should never hit default
            break;
    }
    
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
//TODO: validation on inputs
rtl::ReadBook rtl::CommandLine::GetNewReadBook(std::istream& inputStream, std::ostream& outputStream, int readerId, int inputMode) {
    
    rtl::Book newBook = rtl::CommandLine::GetNewBook(inputStream, outputStream, inputMode);

    OutputLine(outputStream, "Input date you finished reading");
    std::string dateFinished = GetInput(inputStream);
    OutputLine(outputStream, "On a scale of 1 - 10 rate the book");
    std::string rating = GetInput(inputStream);
    
    return rtl::ReadBook(readerId, newBook, stoi(rating), dateFinished);
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

//resets istream, ostream, and input
void userInputAgain(std::istream& inputStream, std::ostream& outputStream, std::string& input) {
    rtl::CommandLine::OutputLine(outputStream, "Invalid selection, please try again");
    outputStream << "\f";
    input = "";
    inputStream.clear();
    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
}

//TODO: should only be called from mainMenu so not in header, do all the options need to share so much code not abstracted away (too much copy/paste)
void addMenu(std::istream& inputStream, std::ostream& outputStream, rtl::InMemoryContainers& masterList, int readerId) {
    
    std::vector<std::string> inputModes {"manual", "by identifier (isbn/oclc)", "by title" };
    int currentMode = 0;
    
    while(true) {
        rtl::CommandLine::OutputLine(outputStream, std::vector<std::string>
        {   "Please select what you want to add",
            "1: Book",
            "2: Books that you have read",
            "3: Authors",
            "c: Change input method. Currently: " + inputModes[currentMode],
            "x: Return to main menu"
        });
        std::string input = rtl::CommandLine::GetInput(inputStream);
        
        if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
            userInputAgain(inputStream, outputStream, input);
            continue;
        }
        
        char charInput = 'p';
        charInput = input.at(0);
        
        switch(charInput) {
            //book
            case '1': {
                auto newBook = std::make_shared<rtl::Book>(rtl::CommandLine::GetNewBook(inputStream, outputStream, currentMode));
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save:");
                rtl::CommandLine::OutputLine(outputStream, newBook->PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Y/N");
                input = rtl::CommandLine::GetInput(inputStream);
                if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
                    userInputAgain(inputStream, outputStream, input);
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.AddMasterBooks(newBook);
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
                auto newReadBook = std::make_shared<rtl::ReadBook>(rtl::CommandLine::GetNewReadBook(inputStream, outputStream, readerId, currentMode));
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save:");
                rtl::CommandLine::OutputLine(outputStream, newReadBook->PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Y/N");
                input = rtl::CommandLine::GetInput(inputStream);
                if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
                    userInputAgain(inputStream, outputStream, input);
                    continue;
                }
                
                char charSaveInput = input.at(0);

                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.AddMasterReadBooks(newReadBook);
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
                auto newAuthor = std::make_shared<rtl::Author>(rtl::CommandLine::GetNewAuthor(inputStream, outputStream, currentMode));
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save:");
                rtl::CommandLine::OutputLine(outputStream, newAuthor->PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Y/N");
                input = rtl::CommandLine::GetInput(inputStream);
                if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
                    userInputAgain(inputStream, outputStream, input);
                    continue;
                }
                
                char charSaveInput = input.at(0);
                
                switch(charSaveInput) {
                    case 'y':
                    case 'Y': {
                        masterList.AddMasterAuthors(newAuthor);
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
            case 'C':
            case 'c': {
                ++currentMode;
                if (currentMode >= inputModes.size()) {
                    currentMode = 0;
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
    std::vector<std::string> displayModes {"Json", "Simple", "Detailed"};
    int currentMode = 0;
    
    while(true) {
        rtl::CommandLine::OutputLine(outputStream, std::vector<std::string>
        {   "Please select what you want to display",
            "1: Book",
            "2: Books that have been read",
            "3: Authors",
            "9: All",
            "c: Change display mode. Currently: " + displayModes[currentMode],
            "x: Return to main menu"
        });
        std::string input = rtl::CommandLine::GetInput(inputStream);
        
        if (rtl::Trim(input).empty() || rtl::Trim(input).size() > 1) {
            userInputAgain(inputStream, outputStream, input);
            continue;
        }
        
        char charInput = 'p';
        charInput = input.at(0);
        std::vector<std::shared_ptr<rtl::StandardOutput>> outputVector;
        
        switch(charInput) {
            case '1': {
                //book
                for (auto x : masterList.GetMasterBooks()) {
                    outputVector.push_back(x);
                }
                break;
            }
            case '2': {
                //readbook
                for (auto x : masterList.GetMasterReadBooks()) {
                    outputVector.push_back(x);
                }
                break;
            }
            case '3': {
                //Author
                for (auto x : masterList.GetMasterAuthors()) {
                    outputVector.push_back(x);
                }
                break;
            }
            case '9': {
                //All
                for (auto x : masterList.GetMasterBooks()) {
                    outputVector.push_back(x);
                }
                outputVector.push_back(nullptr); //nullptr used as delim between types
                for (auto x : masterList.GetMasterReadBooks()) {
                    outputVector.push_back(x);
                }
                outputVector.push_back(nullptr);
                for (auto x : masterList.GetMasterAuthors()) {
                    outputVector.push_back(x);
                }
                break;
            }
            case 'C':
            case 'c': {
                //move to the next available mode
                ++currentMode;
                if (currentMode >= displayModes.size()) {
                    currentMode = 0;
                }
                continue;
            }
            case 'X':
            case 'x': {
                return;
            }
            default: {
                //TODO: log this
                userInputAgain(inputStream, outputStream, input);
                continue;
            }
        }

        switch(currentMode) {
            case 0: {
                //json
                for (auto x : outputVector) {
                    if (x == nullptr) {
                        //nothing needs to be done to seperate types when printing json
                        continue;
                    }
                    rtl::CommandLine::OutputLine(outputStream, x->PrintJson());
                    rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                }
                break;
            }
            case 1: {
                //simple
                bool printHeader = true;
                for (auto x : outputVector) {
                    if (x == nullptr) {
                        //nullptr is the delim between objects, print next objects commandlineheader
                        printHeader = true;
                        continue;
                    }
                    else if (printHeader) {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintHeader());
                        printHeader = false;
                    }
                    else {
                        rtl::CommandLine::OutputLine(outputStream, x->PrintSimple());
                    }
                }
                rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                break;
            }
            case 2: {
                //detailed
                for (auto x : outputVector) {
                    if (x == nullptr) {
                        //no headers for detailed
                        continue;
                    }
                    rtl::CommandLine::OutputLine(outputStream, x->PrintDetailed());
                }
                rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                break;
            }
            default: {
                //TODO: log this
                break;
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
            userInputAgain(inputStream, outputStream, input);
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
            default: {
                userInputAgain(inputStream, outputStream, input);
                continue;
            }
        }
    }
    
    return;
}
