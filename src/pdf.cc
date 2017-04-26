#include "pdf.h"
#include <memory>
#include <string>
#include "LHAPDF/AlphaS.h"
#include "LHAPDF/Info.h"  // for LHAPDF::getConfig
#include "LHAPDF/LHAPDF.h"
#include "constants.h"

namespace mcggh {
std::shared_ptr<LHAPDF::PDF> mkPdf(const std::string &pdfname) {
    LHAPDF::Info &cfg = LHAPDF::getConfig();
    cfg.set_entry("Verbosity", 0);  // make lhapdf quiet

    LHAPDF::AlphaS *alphas = new LHAPDF::AlphaS_ODE();
    alphas->setQuarkMass(5, MB);
    alphas->setQuarkMass(6, MT);
    alphas->setMZ(MZ);
    alphas->setAlphaSMZ(ALPHAS);
    std::shared_ptr<LHAPDF::PDF> pdf(LHAPDF::mkPDF(pdfname));
    pdf->setAlphaS(alphas);
    return pdf;
}
}  // namespace mcggh
