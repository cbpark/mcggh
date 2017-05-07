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
#include <utility>
#include "TCanvas.h"
#include "TH1D.h"
#include "TStyle.h"
#include "common.h"

const char appname[] = "pt";

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << appname << " <input> <output>\n";
        return 1;
    }

    auto fin = std::make_unique<std::ifstream>(argv[1]);
    if (!fin->good()) { return failedToRead(appname, argv[1]); }

    // Create the canvas.
    auto canvas = std::make_unique<TCanvas>("c", "", 0, 0, 600, 600);
    canvas->SetTicks();
    gStyle->SetOptStat(0);  // no stat panel

    // Histogram.
    auto hist = std::make_shared<TH1D>("h", "", 70, 0, 700);
    setHist(hist);
    hist->SetXTitle("p_{T} (GeV)");
    hist->SetYTitle("1 / #sigma d#sigma / dp_{T}");

    // Fill and draw histogram
    fillHist(std::move(fin), hist);
    hist->DrawNormalized();

    auto cm_energy = mkText();
    cm_energy->DrawLatex(0.7, 0.92, "#sqrt{s} = 13 TeV");

    canvas->SaveAs(argv[2]);
}

void fillHist(std::unique_ptr<std::ifstream> fin, std::shared_ptr<TH1> hist) {
    std::string line;
    while (std::getline(*fin, line)) {
        if (line.front() == '#') { continue; }  // comment line

        std::istringstream iss(line);
        double mhh, pT;
        if (!(iss >> mhh >> pT)) { break; }

        if (pT > 0) { hist->Fill(pT); }
    }
    fin->close();
}
