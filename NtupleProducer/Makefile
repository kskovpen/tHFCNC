CMSINC      = -I$(CMSSW_BASE)/src

CMSSWINC      = -I/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_12/src
JECLIB      = -L/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_12/lib/slc6_amd64_gcc530/ -lCondFormatsJetMETObjects -lJetMETCorrectionsModules -lRecoEgammaEgammaTools

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

CXX           = g++ -g -Wno-write-strings -Wno-attributes -fPIC
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared

CXXFLAGS       = $(ROOTCFLAGS)
INCLUDE_FLAGS  = $(CMSSWINC)
LDLIBS         = $(ROOTLIBS) $(JECLIB)
GLIBS          = $(ROOTGLIBS)

EXE           = test/NtupleProducer

INC 	      = include/NtupleProducer.h include/Tree.h include/Base.h \
                include/Electron.h include/Muon.h include/Ntuple.h \
		include/Event.h include/Jet.h include/Truth.h \
		include/BTagCalibrationStandalone.h include/Common.h

SRC	      = src/NtupleProducer.cxx src/Tree.cxx src/Base.cxx \
                src/Electron.cxx src/Muon.cxx src/Ntuple.cxx \
		src/Event.cxx src/Jet.cxx src/Truth.cxx \
		src/BTagCalibrationStandalone.cxx

OBJS          = obj/NtupleProducer.o obj/Tree.o obj/Base.o \
                obj/Electron.o obj/Muon.o obj/Ntuple.o \
		obj/Event.o obj/Jet.o obj/Truth.o \
		obj/BTagCalibrationStandalone.o

LIB           = libNtuple.so

all: 	      $(LIB) $(EXE)

$(LIB):	      $(INC) $(SRC)
	      @echo "####### Generating dictionary"
	      @rootcint -f obj/NtupleProducerDict.cxx -c -p $(CXXFLAGS) \
	      $(INCLUDE_FLAGS) -I. $(INC) include/LinkDef.h

	      @echo "####### Building library $(LIB)"
	      @$(CXX) $(SOFLAGS) $(CXXFLAGS) $(ROOTLIBS) $(INCLUDE_FLAGS) -I. $(SRC) \
	      obj/NtupleProducerDict.cxx -o $(LIB) $(ROOTLIBS)
	      
	      @echo  "####### Removing generated dictionary"
	      @rm -f obj/NtupleProducerDict.cxx obj/NtupleProducerDict.h
	      @rm -f *.o

$(EXE):	      $(LIB) src/NtupleProducer.cxx
	      @echo "####### Building object file for executable"
	      @$(CXX) -c $(CXXFLAGS) $(INCLUDE_FLAGS) src/NtupleProducer.cxx -o obj/NtupleProducer.o
	      @echo "####### Building executable"
	      @$(CXX) $(CXXFLAGS) obj/NtupleProducer.o $(LDLIBS) $(LIB) -o $(EXE)

clean:
	      @rm -f $(OBJS) $(EXE) obj/NtupleProducerDict.cxx obj/NtupleProducerDict.h obj/NtupleProducerDict_rdict.pcm $(LIB)
