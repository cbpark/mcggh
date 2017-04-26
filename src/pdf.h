#ifndef SRC_PDF_H_
#define SRC_PDF_H_

#include <memory>
#include <string>
#include "LHAPDF/LHAPDF.h"

namespace mcggh {
std::shared_ptr<LHAPDF::PDF> mkPdf(const std::string &pdfname);
}  // namespace mcggh

#endif  // SRC_PDF_H_
