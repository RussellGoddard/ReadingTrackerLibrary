//
//  Logger.cpp
//  Logger
//
//  Created by Frobu on 4/4/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "Logger.hpp"
#include "LoggerPriv.hpp"

/*
 BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
 BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
 BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
 BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
 BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
 BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";
 */

void logging::InitLogging() {
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

    boost::log::add_file_log (
        boost::log::keywords::file_name = "sample.log",
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%"
    );

    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

    boost::log::add_common_attributes();
}

