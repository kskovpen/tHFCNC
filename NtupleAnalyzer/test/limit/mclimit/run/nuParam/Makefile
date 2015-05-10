ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)           
ADDLIBS = -Latlasstyle-00-03-04 -lAtlasStyle -lAtlasUtils

CXXFLAGS       = $(ROOTCFLAGS)
INCLUDE_FLAGS  = $(INCLUDES)
LDLIBS         = $(ROOTLIBS) $(ADDLIBS)
GLIBS          = $(ROOTGLIBS)

CXX           = gcc -Wno-write-strings
LD            = gcc
LDFLAGS       = -g -m64
SOFLAGS       = -shared

EXE	= nup
OBJS	= nup.o
SRC	= nup.cxx

$(EXE):       $(OBJS) $@

$(OBJS):      $(SRC) 
	      $(CXX) -c $(CXXFLAGS) $(INCLUDE_FLAGS) $(SRC)

clean:                                              
	@rm -f $(OBJS) $(EXE)
