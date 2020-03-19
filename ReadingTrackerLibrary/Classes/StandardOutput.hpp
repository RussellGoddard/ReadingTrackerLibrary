//
//  StandardOutput.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/19/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef StandardOutput_hpp
#define StandardOutput_hpp

#include <string>

namespace rtl {

    class StandardOutput {
    public:
        virtual std::string PrintJson() = 0;
        virtual std::string PrintCommandLine() = 0;
    protected:
        //virtual std::string PrintCommandLineHeaders() = 0;
    };
}

#endif /* StandardOutput_hpp */
