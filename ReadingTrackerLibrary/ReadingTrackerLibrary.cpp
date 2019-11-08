//
//  ReadingTrackerLibrary.cpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 11/7/19.
//  Copyright © 2019 Russell Goddard. All rights reserved.
//

#include <iostream>
#include "ReadingTrackerLibrary.hpp"
#include "ReadingTrackerLibraryPriv.hpp"

void ReadingTrackerLibrary::HelloWorld(const char * s)
{
    ReadingTrackerLibraryPriv *theObj = new ReadingTrackerLibraryPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void ReadingTrackerLibraryPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

