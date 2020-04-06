//
//  Logger.hpp
//  Logger
//
//  Created by Frobu on 4/4/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef Logger_
#define Logger_

/* The classes below are exported */
#pragma GCC visibility push(default)


// save diagnostic state
#pragma GCC diagnostic push

// turn off the specific warning
#pragma GCC diagnostic ignored "-Wcomma"
#pragma GCC diagnostic ignored "-Wdocumentation"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

// turn the warnings back on
#pragma GCC diagnostic pop

namespace logging {
    void InitLogging();
}

#pragma GCC visibility pop
#endif
