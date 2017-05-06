SRCDIR   := src
BINDIR   := bin
CXXFLAGS := -g -O2 -Wall -Wextra -std=c++14 -pedantic -I$(SRCDIR)
LDFLAGS  :=
MKDIR    := mkdir -p
RM       := rm -f
UNAME    := $(shell uname -s)

ifeq ($(UNAME), Darwin)
	CXXFLAGS += -stdlib=libc++
endif

EXE    := $(BINDIR)/mhh
EXESRC := $(patsubst $(BINDIR)/%,$(SRCDIR)/%.cc,$(EXE))
EXEOBJ := $(EXESRC:.cc=.o)

# ROOT (https://root.cern.ch)
CXXFLAGS += $(shell root-config --cflags)
LDFLAGS  += $(shell root-config --ldflags)
LIBS     += $(shell root-config --libs)

.PHONY: all build clean

all: $(EXE)

$(BINDIR)/%: $(SRCDIR)/%.o build
	$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

build:
	$(MKDIR) $(BINDIR)

clean::
	$(RM) $(EXEOBJ)
	$(RM) $(EXE)
	$(RM) -r $(BINDIR)
