PKGNAME  := MCGGH
SRCDIR   := src
BINDIR   := bin
LIBDIR   := lib
CXXFLAGS := -g -O2 -m64 -march=native -Wall -Wextra -std=c++14 -pedantic -I$(SRCDIR)
LDFLAGS  := -O2 -m64
LIBS     :=
AR       := ar crs
MKDIR    := mkdir -p
RM       := rm -f
UNAME    := $(shell uname -s)

ifeq ($(UNAME), Darwin)
	CXXFLAGS += -stdlib=libc++
endif

EXE    := $(BINDIR)/ggh1 $(BINDIR)/ggh2
EXESRC := $(patsubst $(BINDIR)/%,$(SRCDIR)/%.cc,$(EXE))
EXEOBJ := $(EXESRC:.cc=.o)
LIB    := $(LIBDIR)/lib$(PKGNAME).a
LIBSRC := $(filter-out $(EXESRC),$(wildcard $(SRCDIR)/*.cc))
LIBOBJ := $(LIBSRC:.cc=.o)

# LHAPDF (http://lhapdf.hepforge.org/)
CXXFLAGS += $(shell lhapdf-config --cflags)
LIBS     += $(shell lhapdf-config --libs)

# LoopTools (http://www.feynarts.de/looptools/)
LT       := /usr
CXXFLAGS += -I$(LT)/include
LIBS     += -L$(LT)/lib -looptools

.PHONY: all build clean

all: $(EXE)

$(BINDIR)/%: $(SRCDIR)/%.o build $(LIB)
	$(LT)/bin/f++ $(LDFLAGS) -o $@ $< -L$(LIBDIR) -l$(PKGNAME) $(LIBS)

$(LIB): CXXFLAGS += -fPIC
$(LIB): $(LIBOBJ)
	$(AR) $@ $^
	ranlib $@

build:
	$(MKDIR) $(LIBDIR)
	$(MKDIR) $(BINDIR)

clean::
	$(RM) $(EXEOBJ) $(LIBOBJ)
	$(RM) $(EXE) $(LIB)
	$(RM) -r $(BINDIR) $(LIBDIR)
