//
//  Logger.cpp
//  Logger
//
//  Created by Frobu on 4/4/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "Logger.hpp"

using namespace boost;

/*
 BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
 BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
 BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
 BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
 BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
 BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";
 */

void logging::InitLogging() {
    log::register_simple_formatter_factory<log::trivial::severity_level, char>("Severity");

    std::string utcDate = posix_time::to_simple_string(posix_time::second_clock::universal_time());
    log::add_file_log (
        log::keywords::file_name = "./Logs/testLog" + utcDate + ".log",
        log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%",
        log::keywords::auto_flush = true,
        log::keywords::open_mode = (std::ios::out | std::ios::app)
    );

    log::core::get()->set_filter(log::trivial::severity >= log::trivial::info);

    log::add_common_attributes();
}

