
MCLINC		= -I.
MCLLIB		= -L. \
		-lMCL

ROOTCFLAGS    = $(shell root-config --cflags | sed -e "s%-std=c++0x%%g")
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)           

CXXFLAGS       = $(ROOTCFLAGS)
INCLUDE_FLAGS  = $(INCLUDES) $(MCLINC) 
LDLIBS         = $(ROOTLIBS) $(MCLLIB) -L/usr/lib64 -lstdc++ 
GLIBS          = $(ROOTGLIBS)

CXX           = gcc -fPIC -Wno-write-strings
LD            = gcc
LDFLAGS       = -g
SOFLAGS       = -shared

EXE	= toy
OBJS	= toy.o
INC     = mclimit_csm.h
SRC	= toy.cxx

$(EXE):       $(OBJS) $@

$(OBJS):      $(SRC) $(INC)
	      $(CXX) -c $(CXXFLAGS) $(INCLUDE_FLAGS) $(SRC)

clean:                                              
	@rm -f $(OBJS) $(EXE)
