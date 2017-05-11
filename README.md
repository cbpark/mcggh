# MCGGH

A parton-level Monte Carlo generator for Higgs production through gluon fusion process at hadron colliders.

## Requirements

* C++ compiler supporting C++14 features ([Clang](http://clang.llvm.org/cxx_status.html) > 3.4, [GCC](https://gcc.gnu.org/projects/cxx-status.html) > 4.9),

* [LHAPDF 6](http://lhapdf.hepforge.org/) and the `NNPDF23_lo_as_0130_qed` PDF data. The latter can be installed by

``` shell
lhapdf install NNPDF23_lo_as_0130_qed
```

* [LoopTools](http://www.feynarts.de/looptools/). Check that `f++` is in `$PATH` and edit the `LT` variable in [`Makefile`](Makefile). If you are in [ArchLinux](https://www.archlinux.org), you can install it via [AUR](https://aur.archlinux.org/packages/?O=0&K=looptools). For other Linux distribution, see the `build` function in [looptools](https://github.com/cbpark/archlinux-packages/blob/master/aur/looptools/PKGBUILD).

## Usage and example outputs

* `./bin/ggh1 13000 125`

```
* p p --> g g --> h (ECM = 13 TeV, MH = 125 GeV)
-- Integrating for cross section ...
-- Done integrating.
-- Total cross section = 13.9594 +- 0.852319 pb
```

* `./bin/ggh2`

```
Usage: ggh2 <ECM in GeV> <MH in GeV> [nevent] [output]
```

* `./bin/ggh2 13000 125 3`

```
* p p --> g g --> h h (ECM = 13 TeV, MH = 125 GeV)
-- Integrating for cross section ...
 ====================================================
   FF 2.0, a package to evaluate one-loop integrals
 written by G. J. van Oldenborgh, NIKHEF-H, Amsterdam
 ====================================================
 for the algorithms used see preprint NIKHEF-H 89/17,
 'New Algorithms for One-loop Integrals', by G.J. van
 Oldenborgh and J.A.M. Vermaseren, published in
 Zeitschrift fuer Physik C46(1990)425.
 ====================================================
-- Done integrating.
-- Total cross section = 12.8395 +- 0.0584059 fb
-- Generating events ...
   498.417      190.234
   540.578      238.768
   645.967      297.814
-- Done.
```

## References

* [arXiv:hep-ph/9504378](https://arxiv.org/abs/hep-ph/9504378) (pp --> h),
* [arXiv:hep-ph/0503172](https://arxiv.org/abs/hep-ph/0503172) (pp --> h),
* [arXiv:hep-ph/9603205](https://arxiv.org/abs/hep-ph/9603205) (pp --> hh),
* [arXiv:1405.7040](https://arxiv.org/abs/1405.7040) (pp --> hh).

## Plot

There are example codes for making some histograms using generated event data in the [`plot`](plot) directory. [ROOT](https://root.cern.ch/) is required to build them.
