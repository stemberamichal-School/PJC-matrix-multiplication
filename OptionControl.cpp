//
//  OptionControl.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 20/10/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include "OptionControl.hpp"

#define DEFAULT_THREADS_COUNT 1

OptionControl::OptionControl()
:m_threads_count(DEFAULT_THREADS_COUNT), m_matrixes_files(std::vector<const std::string>()), m_show_help(false) { }

bool OptionControl::parseOptions(int argc, char ** argv, std::ostream & error_out) {
    int long_opt_idx = 0; // Will be ignored as return value will be used instead
    int arg = 0;
    bool is_error = false;

    do {
        arg = getopt_long(argc, argv, short_opts, long_opts, &long_opt_idx);
        try {
            switch (arg) {
                case 't': // Threads
                    m_threads_count = std::max(1, std::stoi(optarg, nullptr));
                    break;
                case 'm': // Matrixes
                    m_matrixes_files.push_back(std::string(optarg));
                    break;
                case 'h': // Help
                    m_show_help = true;
                    break;
                case -1: // Done with supplying parameters
                    break;
                case '?': // Something else -> error
                default:
                    is_error = true;
                    break;
            }
        } catch (const std::invalid_argument & exc) {
            is_error = true;
            error_out << "Invalid argument for option: -" << (char)arg << std::endl;
        } catch (const std::out_of_range & exc) {
            is_error = true;
            error_out << "Out of range argument for option: -" << (char)arg << std::endl;
        } catch (const std::exception & exc) {
            is_error = true;
            error_out << "Invalid input for option: -" << (char)arg << std::endl;
        }
    } while(arg != -1);

    return is_error;
}

int OptionControl::getThreadsCount() const {
    return m_threads_count;
}

const std::vector<const std::string>& OptionControl::getMatrixesFiles() const {
    return m_matrixes_files;
}

bool OptionControl::getShowHelp() const {
    return m_show_help;
}

void OptionControl::printHelp(std::ostream & out) {
    // Heading
    out << "Multithread Matrix multiplier by Michal Stembera" << std::endl;
    out << std::endl;
    // Usage
    out << "Usage:" << std::endl;
    out << "matrix-mult [options]" << std::endl;
    // Options
    out << "Options:" << std::endl;
    out << "    -t --threads <count> Number of threads used [default: " << DEFAULT_THREADS_COUNT << "]." << std::endl;
    out << "    -m --matrixes <filename> File containing two square matrices separated by empty line, can be used multiple times." << std::endl;
    out << "    -h --help Show help." << std::endl;
}

std::ostream & operator<<(std::ostream & os, OptionControl const & option_control) {
    os << "Selected options:" << std::endl;
    os << "Number of threads (-t --threads): " << option_control.getThreadsCount() << std::endl;
    os << "Matrixes files (-m --matrixes): ";
    for (auto it = option_control.getMatrixesFiles().begin(); it != option_control.getMatrixesFiles().end(); ++it) {
        os << *it << " ";
    }
    os << std::endl;
    os << "Show help: (-h --help): " << std::boolalpha << option_control.getShowHelp() << std::endl;
     return os;
}
