/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of mcggh, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_PDF_H_
#define SRC_PDF_H_

#include <memory>
#include <string>
#include "LHAPDF/LHAPDF.h"

namespace mcggh {
std::shared_ptr<LHAPDF::PDF> mkPdf(const std::string &pdfname);
}  // namespace mcggh

#endif  // SRC_PDF_H_
