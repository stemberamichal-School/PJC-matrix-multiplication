//
//  OptionControl.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 20/10/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef OptionControl_hpp
#define OptionControl_hpp

#include <stdio.h>
#include <iostream>
#include <getopt.h>
#include <vector>
#include <string>

class OptionControl {
protected:
    const char * short_opts = "t:m:h";
    const struct option long_opts[4] = {
        { "threads", required_argument, nullptr, 't' },
        { "matrixes", required_argument, nullptr, 'm' },
        { "help", no_argument, nullptr, 'h' },
        { 0, 0, 0, 0} // Terminate with structure containing all zeros according to docs
    };

    int m_threads_count;
    std::vector<const std::string> m_matrixes_files;
    bool m_show_help;

public:
    OptionControl();

    /// Number of threads that should be used for calculation
    int getThreadsCount() const;

    /// Number of matrixes that should be generated for running
    const std::vector<const std::string>& getMatrixesFiles() const;

    /// Flag whether the user requested showing help
    bool getShowHelp() const;


    /// Parses options and uses them to  set parameters
    /// Returns true if the program should quit
    bool parseOptions(int argc, char ** argv, std::ostream & error_out);

    /// Prints out help to given stream
    void printHelp(std::ostream & out);

    /// Prints selected options to stream
    friend std::ostream & operator<<(std::ostream & os, OptionControl const & option_control);
};
#endif /* OptionControl_hpp */
