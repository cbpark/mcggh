# MCGGH

A parton-level Monte Carlo generator for Higgs production through gluon fusion process at hadron collider.

## Requirements

* C++ compiler supporting C++14 features ([Clang](http://clang.llvm.org/cxx_status.html) > 3.4, [GCC](https://gcc.gnu.org/projects/cxx-status.html) > 4.9).

* [LHAPDF 6](http://lhapdf.hepforge.org/) and the `NNPDF23_lo_as_0130_qed` PDF data. The version of LHAPDF can be checked by `lhapdf-config --version`. The `NNPDF23_lo_as_0130_qed` data can be installed by

``` shell
lhapdf-config install NNPDF23_lo_as_0130_qed
```

* [LoopTools](http://www.feynarts.de/looptools/).
