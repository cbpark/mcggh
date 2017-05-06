/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef PLOT_SRC_COMMON_H_
#define PLOT_SRC_COMMON_H_

#include <iostream>
#include <string>

int failedToRead(const std::string &appname, const std::string &fname) {
    std::cerr << appname << ": failed to read `" << fname << "'.\n";
    return 1;
}

#endif  // PLOT_SRC_COMMON_H_
