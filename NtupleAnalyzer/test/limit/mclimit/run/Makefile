
MCLINC		= -I/home/kskovpen/work/testarea/Limit2012/mclimit
MCLLIB		= -L/home/kskovpen/work/testarea/Limit2012/mclimit \
		-lMCL

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)           

CXXFLAGS       = $(ROOTCFLAGS)
INCLUDE_FLAGS  = $(INCLUDES) $(MCLINC) 
LDLIBS         = $(ROOTLIBS) $(MCLLIB)
GLIBS          = $(ROOTGLIBS)

CXX           = gcc -Wno-write-strings
LD            = gcc
LDFLAGS       = -g -m64
SOFLAGS       = -shared

EXE	= toy
OBJS	= toy.o
SRC	= toy.cxx

$(EXE):       $(OBJS) $@

$(OBJS):      $(SRC) 
	      $(CXX) -c $(CXXFLAGS) $(INCLUDE_FLAGS) $(SRC)

clean:                                              
	@rm -f $(OBJS) $(EXE)
