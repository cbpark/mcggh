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
#include <utility>
#include "TCanvas.h"
#include "TH1D.h"
#include "TStyle.h"
#include "common.h"

using namespace std;

const char appname[] = "mhh2";

int main(int argc, char *argv[]) {
    if (argc != 4) { return howToUse(appname, "<input1> <input2> <output>"); }

    auto fin1 = make_unique<ifstream>(argv[1]);
    if (!fin1->good()) { return failedToRead(appname, argv[1]); }
    auto fin2 = make_unique<ifstream>(argv[2]);
    if (!fin2->good()) { return failedToRead(appname, argv[2]); }

    // Create the canvas.
    auto canvas = make_unique<TCanvas>("c", "", 0, 0, 600, 600);
    canvas->SetTicks();
    gStyle->SetOptStat(0);  // no stat panel

    const auto bin = make_pair(250.0, 1050.0);
    const double nbin = 80;

    // Histograms.
    auto hist1 = make_shared<TH1D>("h1", "", nbin, bin.first, bin.second);
    setHist(hist1);
    hist1->SetLineColor(kBlue);
    hist1->SetXTitle("m_{hh} (GeV)");
    hist1->SetYTitle("1 / #sigma d#sigma / dm_{hh}");

    auto hist2 = make_shared<TH1D>("h2", "", nbin, bin.first, bin.second);
    setHist(hist2);
    hist2->SetLineColor(kRed);
    hist2->SetLineStyle(2);

    // Fill and draw histogram
    fillHist(move(fin1), hist1);
    hist1->DrawNormalized();
    fillHist(move(fin2), hist2);
    hist2->DrawNormalized("SAME");

    auto legend = mkLegend(0.6, 0.7, 0.9, 0.85);
    legend->AddEntry("h1", "#sqrt{s} = 13 TeV");
    legend->AddEntry("h2", "#sqrt{s} = 100 TeV");
    legend->Draw();

    canvas->SaveAs(argv[3]);
}

void fillHist(unique_ptr<ifstream> fin, shared_ptr<TH1> hist) {
    string line;
    while (getline(*fin, line)) {
        if (line.front() == '#') { continue; }  // comment line

        istringstream iss(line);
        double mhh, pT;
        if (!(iss >> mhh >> pT)) { break; }

        if (pT > 0) { hist->Fill(mhh); }
    }
    fin->close();
}
