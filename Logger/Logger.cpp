//
//  Logger.cpp
//  Logger
//
//  Created by Frobu on 4/4/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#include "Logger.hpp"
#include "LoggerPriv.hpp"

void logging::InitLogging() {
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

    boost::log::add_file_log
    (
        boost::log::keywords::file_name = "sample.log",
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
    );

    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

    boost::log::add_common_attributes();
    /*
    boost::log::add_file_log("sample.log");
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
     */
}

