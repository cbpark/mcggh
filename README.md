# MCGGH

A parton-level Monte Carlo generator for Higgs production through gluon fusion process at hadron collider.

## Requirements

* C++ compiler supporting C++14 features ([Clang](http://clang.llvm.org/cxx_status.html) > 3.4, [GCC](https://gcc.gnu.org/projects/cxx-status.html) > 4.9).

* [LHAPDF 6](http://lhapdf.hepforge.org/) and the `NNPDF23_lo_as_0130_qed` PDF data. The version of LHAPDF can be checked by `lhapdf-config --version`. The `NNPDF23_lo_as_0130_qed` data can be installed by

``` shell
lhapdf install NNPDF23_lo_as_0130_qed
```

* [LoopTools](http://www.feynarts.de/looptools/).

## References

* [arXiv:hep-ph/9504378](https://arxiv.org/abs/hep-ph/9504378) (pp --> H),
* [arXiv:hep-ph/9603205](https://arxiv.org/abs/hep-ph/9603205) (pp --> H H),
* [arXiv:1405.7040](https://arxiv.org/abs/1405.7040) (pp --> H H).
