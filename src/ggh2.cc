/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include <iostream>

int main(int argc, char *argv[]) {
    const char appname[] = "ggh2";
    if (argc != 4) {
        std::cerr << "Usage: " << appname
                  << " <ECM in GeV> <MH in GeV> <nevent>\n";
        return 1;
    }

    const double eCM = std::atof(argv[1]);
    const double mH = std::atof(argv[2]);
    std::cout << "* p p --> g g --> H H (ECM = " << eCM << " GeV, MH = " << mH
              << " GeV)\n";
}
