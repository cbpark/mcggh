SRCDIR   := src
BINDIR   := bin
CXXFLAGS := -g -O2 -Wall -Wextra -std=c++14 -pedantic -I$(SRCDIR)
LDFLAGS  := -O2 -m64
MKDIR    := mkdir -p
RM       := rm -f

# ROOT (https://root.cern.ch)
CXXFLAGS += $(shell root-config --cflags)
LDFLAGS  += $(shell root-config --ldflags)
LIBS     += $(shell root-config --libs)

# Targets
EXE    := $(BINDIR)/mhh $(BINDIR)/mhh2 $(BINDIR)/pt $(BINDIR)/pt2
EXESRC := $(patsubst $(BINDIR)/%,$(SRCDIR)/%.cc,$(EXE))
EXEOBJ := $(EXESRC:.cc=.o)

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
