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
#include <memory>
#include <string>
#include "TH1.h"
#include "TLatex.h"

const int FONT = 132;

int failedToRead(const std::string &appname, const std::string &fname) {
    std::cerr << appname << ": failed to read `" << fname << "'.\n";
    return 1;
}

void fillHist(std::unique_ptr<std::ifstream> fin, std::shared_ptr<TH1> hist);

void setHist(std::shared_ptr<TH1> hist) {
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->SetTitle("");
    hist->SetTitleOffset(0.9, "xy");
    hist->SetLineColor(kBlack);
    hist->SetLineWidth(2);
    hist->SetTitleSize(1.4 * hist->GetLabelSize(), "xy");
    hist->SetTitleFont(FONT, "xy");
    hist->SetLabelFont(FONT, "xy");
}

std::shared_ptr<TLatex> mkText() {
    auto text = std::make_shared<TLatex>();
    text->SetTextFont(FONT);
    text->SetTextSize(0.9 * text->GetTextSize());
    text->SetNDC();
    return text;
}

#endif  // PLOT_SRC_COMMON_H_
