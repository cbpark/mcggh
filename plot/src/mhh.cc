/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "TCanvas.h"
#include "TH1D.h"
#include "TStyle.h"
#include "common.h"

const char appname[] = "mhh";

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << appname << " <input> <output>\n";
        return 1;
    }

    std::ifstream fin(argv[1]);
    if (!fin.good()) { return failedToRead(appname, argv[1]); }

    // Create the canvas.
    auto canvas = std::make_unique<TCanvas>("c", "", 0, 0, 600, 600);
    canvas->SetTicks();
    gStyle->SetOptStat(0);  // no stat panel

    // Histogram.
    auto hist = std::make_shared<TH1D>("h", "", 75, 250, 1000);
    setHist(hist);
    hist->SetXTitle("m_{hh} (GeV)");
    hist->SetYTitle("1 / #sigma d#sigma / dm_{hh}");

    std::string line;
    while (std::getline(fin, line)) {
        if (line.front() == '#') { continue; }  // comment line

        std::istringstream iss(line);
        double mhh, pT;
        if (!(iss >> mhh >> pT)) { break; }

        if (pT > 0) { hist->Fill(mhh); }
    }
    fin.close();
    hist->DrawNormalized();

    auto cm_energy = mkText();
    cm_energy->DrawLatex(0.7, 0.92, "#sqrt{s} = 13 TeV");

    canvas->SaveAs(argv[2]);
}
