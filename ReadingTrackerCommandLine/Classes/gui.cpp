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
            BOOST_LOG_TRIVIAL(error) << "default hit in switch, input: " << inputMode;
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
    std::vector<std::string> author;
    std::vector<std::string> isbn;
    std::vector<std::string> oclc;
    std::string title = "";
    std::string publisher = "";
    std::string series = "";
    std::string genre = "genre not set";
    std::string datePublished = "";
    int pageCount = -1;
    std::string pageCountStr = "-1";
    
    switch(inputMode) {
        //manual
        case 0: {
            //TODO: more descriptive input messages
            OutputLine(outputStream, "Input author, seperate multiple authors by comma");
            author = rtl::splitString(GetInput(inputStream), ",");
            OutputLine(outputStream, "Input ISBN, seperate multiple ISBN by comma");
            isbn = rtl::splitString(GetInput(inputStream), ",");
            OutputLine(outputStream, "Input OCLC");
            oclc = rtl::splitString(GetInput(inputStream), ",");
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
            pageCountStr = GetInput(inputStream);
            pageCount = stoi(pageCountStr);
            break;
        }
        //by identifier (ISBN or OCLC)
        case 1: {
            //TODO: make better use of data in openlibrary, like openlibrary author vs wikidata author

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
            
            author.insert(std::end(author), std::begin(wikiDataValues.author), std::end(wikiDataValues.author));
            title = wikiDataValues.title;
            series = wikiDataValues.series;
            publisher = wikiDataValues.publisher;
            pageCount = openLibraryValues.pageCount;
            datePublished = boost::gregorian::to_simple_string(wikiDataValues.datePublished);
            isbn.insert(std::end(isbn), std::begin(openLibraryValues.isbn), std::end(openLibraryValues.isbn));
            isbn.insert(std::end(isbn), std::begin(wikiDataValues.isbn), std::end(wikiDataValues.isbn));
            std::sort(std::begin(isbn), std::end(isbn));
            std::unique(std::begin(isbn), std::end(isbn));
            oclc.insert(std::end(oclc), std::begin(openLibraryValues.oclc), std::end(openLibraryValues.oclc));
            oclc.insert(std::end(oclc), std::begin(wikiDataValues.oclc), std::end(wikiDataValues.oclc));
            std::sort(std::begin(oclc), std::end(oclc));
            std::unique(std::begin(oclc), std::end(oclc));
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
            
            author.insert(std::end(author), std::begin(wikiDataValues.author), std::end(wikiDataValues.author));
            title = wikiDataValues.title;
            series = wikiDataValues.series;
            publisher = wikiDataValues.publisher;
            datePublished = boost::gregorian::to_simple_string(wikiDataValues.datePublished);
            isbn.insert(std::end(isbn), std::begin(wikiDataValues.isbn), std::end(wikiDataValues.isbn));
            oclc.insert(std::end(oclc), std::begin(wikiDataValues.oclc), std::end(wikiDataValues.oclc));
            
            OutputLine(outputStream, "Query success");
            break;
        }
        default:
            BOOST_LOG_TRIVIAL(error) << "default hit in switch, input: " << inputMode;
            break;
    }
    
    return rtl::Book(author, title, series, publisher, pageCount, genre, datePublished, isbn, oclc);
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

rtl::ReadBook rtl::CommandLine::GetNewReadBook(std::istream& inputStream, std::ostream& outputStream, std::string readerId, int inputMode) {
    
    rtl::Book newBook = rtl::CommandLine::GetNewBook(inputStream, outputStream, inputMode);

    OutputLine(outputStream, "Input date you finished reading");
    std::string dateFinished = GetInput(inputStream);
    OutputLine(outputStream, "On a scale of 1 - 10 rate the book");
    std::string rating = GetInput(inputStream);
    int intRating = -1;
    try {
        intRating = stoi(rating);
    }
    catch(std::invalid_argument& ex) {
        BOOST_LOG_TRIVIAL(warning) << ex.what();
        rating = "-1";
    }
    
    return rtl::ReadBook(readerId, newBook, intRating, dateFinished);
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

void rtl::CommandLine::UpdateRecord(std::istream& inputStream, std::ostream& outputStream, int maxRange, std::vector<std::shared_ptr<rtl::StandardOutput>>::iterator it) {
    rtl::CommandLine::OutputLine(outputStream, "To select an item input the number in front, else press enter to continue");
    std::string itemSelection = rtl::CommandLine::GetInput(inputStream);
    rtl::Trim(itemSelection);
    int selectionInput;
    
    try {
        if (itemSelection == "") {
            return;
        }
        selectionInput = stoi(itemSelection);
        if (selectionInput < 0 || selectionInput > maxRange) {
            selectionInput = -1;
        }
        else {
            std::advance(it, -(maxRange - selectionInput));
            rtl::CommandLine::OutputLine(outputStream, (*it)->PrintDetailed());
            rtl::CommandLine::OutputLine(outputStream, "Enter the name of the record you would like to update, else press enter");
            std::string updateRecord = rtl::CommandLine::GetInput(inputStream);
            rtl::SetsPtr updatePtr = (*it)->GetUpdateFunction(updateRecord);
            if (updatePtr == nullptr) {
                rtl::CommandLine::OutputLine(outputStream, "Field not entered correctly or field not allowed to be changed");
            }
            else {
                rtl::CommandLine::OutputLine(outputStream, "Enter the updated field:");
                std::string newRecord = rtl::CommandLine::GetInput(inputStream);
                if (std::invoke(updatePtr, *it, newRecord)) {
                    rtl::CommandLine::OutputLine(outputStream, "Update Success");
                }
                else {
                    rtl::CommandLine::OutputLine(outputStream, "Update Failed");
                }
            }
        }
    }
    catch (std::exception& ex) {
        BOOST_LOG_TRIVIAL(error) << ex.what();
        selectionInput = -1;
    }
    
    return;
}

//TODO: do all the options need to share so much code not abstracted away (too much copy/paste)
//should only be called from mainMenu so not in header
void addMenu(std::istream& inputStream, std::ostream& outputStream, rtl::InMemoryContainers& masterList, std::string readerId) {
    
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
                rtl::CommandLine::OutputLine(outputStream, newBook->PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save (Y/N): ");
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
                rtl::CommandLine::OutputLine(outputStream, newReadBook->PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save (Y/N): ");
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
                rtl::CommandLine::OutputLine(outputStream, newAuthor->PrintJson() + "?");
                rtl::CommandLine::OutputLine(outputStream, "Would you like to save (Y/N): ");
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
    int currentDisplay = 0;
    
    while(true) {
        //TODO: implement sort and search
        rtl::CommandLine::OutputLine(outputStream, std::vector<std::string>
        {   "Please select what you want to display",
            "1: Book",
            "2: Books that have been read",
            "3: Authors",
            "9: All",
            "c: Change display mode. Currently: " + displayModes[currentDisplay],
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
                //move to the next available display mode
                ++currentDisplay;
                if (currentDisplay >= displayModes.size()) {
                    currentDisplay = 0;
                }
                continue;
            }
            case 'X':
            case 'x': {
                return;
            }
            default: {
                BOOST_LOG_TRIVIAL(info) << "invalid selection: " << charInput;
                userInputAgain(inputStream, outputStream, input);
                continue;
            }
        }
        
        switch(currentDisplay) {
            case 0: {
                //json
                int count = 0;
                auto it = std::begin(outputVector);
                while (it != std::end(outputVector)) {
                    if (*it == nullptr) {
                        //nothing needs to be done to seperate types when printing json
                        ++it;
                        continue;
                    }
                    rtl::CommandLine::OutputLine(outputStream, rtl::CommandLine::PrintNumberSelector(count % 10) + (*it)->PrintJson());
                    
                    //display 10 items at a timee
                    if (count % 10 == 9) {
                        rtl::CommandLine::UpdateRecord(inputStream, outputStream, count, it);
                    }
                    ++it;
                    count = (count + 1) % 10;
                }
                int maxRange = count % 10;
                rtl::CommandLine::UpdateRecord(inputStream, outputStream, maxRange, it);
                rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                break;
            }
            case 1: {
                //simple
                bool printHeader = true;
                int count = 0;
                auto it = std::begin(outputVector);
                while (it != std::end(outputVector)) {
                    if (*it == nullptr) {
                        //nullptr is the delim between objects, print next objects commandlineheader
                        printHeader = true;
                        rtl::CommandLine::OutputLine(outputStream, "");
                        ++it;
                        continue;
                    }
                    if (printHeader) {
                        rtl::CommandLine::OutputLine(outputStream, rtl::CommandLine::PrintHeaderNumber() + (*it)->PrintHeader());
                        printHeader = false;
                    }
                    rtl::CommandLine::OutputLine(outputStream, rtl::CommandLine::PrintNumberSelector(count % 10) + (*it)->PrintSimple());
                    
                    //display 10 items at a timee
                    if (count % 10 == 9) {
                        rtl::CommandLine::UpdateRecord(inputStream, outputStream, count, it);
                    }
                    ++it;
                    count = (count + 1) % 10;
                }
                int maxRange = count % 10;
                rtl::CommandLine::UpdateRecord(inputStream, outputStream, maxRange, it);
                rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                break;
            }
            case 2: {
                //detailed
                int count = 0;
                auto it = std::begin(outputVector);
                while (it != std::end(outputVector)) {
                    if (*it == nullptr) {
                        //nothing needs to be done to seperate types when printing json
                        ++it;
                        continue;
                    }
                    rtl::CommandLine::OutputLine(outputStream, rtl::CommandLine::PrintNumberSelector(count % 10) + (*it)->PrintDetailed());
                    
                    //display 10 items at a timee
                    if (count % 10 == 9) {
                        rtl::CommandLine::UpdateRecord(inputStream, outputStream, count, it);
                    }
                    ++it;
                    count = (count + 1) % 10;
                }
                int maxRange = count % 10;
                rtl::CommandLine::UpdateRecord(inputStream, outputStream, maxRange, it);
                rtl::CommandLine::OutputLine(outputStream, ""); //blank line for seperation
                break;
            }
            default: {
                BOOST_LOG_TRIVIAL(error) << "invalid selection: " << currentDisplay;
                break;
            }
        }
    }
    return;
}

void rtl::CommandLine::MainMenu(std::istream& inputStream, std::ostream& outputStream, std::string readerId) {
    rtl::InMemoryContainers& masterList = rtl::InMemoryContainers::GetInstance();
    rtl::ServerMethods& awsConnection = rtl::ServerMethods::GetInstance(false);
    
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
                rtl::CommandLine::OutputLine(outputStream, std::vector<std::string> {
                    "Input file path for save file or enter shortcut below:",
                    "default: same as blank, saves in ./Files/",
                    "desktop: (shortcut to macOS user desktop)",
                    "aws: saves to AWS"
                });
                input = rtl::CommandLine::GetInput(inputStream);
                bool saveSuccess = false;
                if (input == "aws") {
                    //saveSuccess = awsConnection.AddAuthor(<#std::shared_ptr<rtl::Author> input#>);
                    //awsConnection.AddReadBook(<#std::shared_ptr<rtl::ReadBook> input#>);
                    //awsConnection.AddBook(<#std::shared_ptr<rtl::Book> input#>);
                }
                else if (input == "" || input == "default") {
                    input = "./Files/rtlDataFile.txt";
                    saveSuccess = masterList.SaveInMemoryToFile(input);
                }
                //shortcut to macOS desktop
                else if (input == "desktop") {
                    input = std::getenv("HOME");
                    input += "/Desktop/rtlDataFile.txt";
                    saveSuccess = masterList.SaveInMemoryToFile(input);
                }
                if (saveSuccess) {
                    rtl::CommandLine::OutputLine(outputStream, "save success\n");
                }
                else {
                    BOOST_LOG_TRIVIAL(error) << "error saving to path: " << input;
                    rtl::CommandLine::OutputLine(outputStream, "error saving\n");
                }
                break;
            }
            case '8': {
                rtl::CommandLine::OutputLine(outputStream, std::vector<std::string> {
                    "Input file path to load file or enter shortcut below:",
                    "desktop: (shortcut to macOS user desktop)"
                });
                input = rtl::CommandLine::GetInput(inputStream);
                if (input == "" || input == "default") {
                    input = "./Files/rtlDataFile.txt";
                }
                //shortcut to macOS desktop
                else if (input == "desktop") {
                    input = std::getenv("HOME");
                    input += "/Desktop/rtlDataFile.txt";
                }
                if (masterList.LoadInMemoryFromFile(input)) {
                    rtl::CommandLine::OutputLine(outputStream, "load success\n");
                }
                else {
                    BOOST_LOG_TRIVIAL(error) << "error loading path: " << input;
                    rtl::CommandLine::OutputLine(outputStream, "error loading\n");
                }
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
                BOOST_LOG_TRIVIAL(info) << "invalid selection: " << charInput;
                userInputAgain(inputStream, outputStream, input);
                continue;
            }
        }
    }
    
    return;
}
