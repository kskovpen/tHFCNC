
include Makefile.arch

%.o : %.C
	$(CXX) $(CXXFLAGS) -c $<

mclimit_csm.o : mclimit_csm.C mclimit_csm.h

tchanlc.o : tchanlc.C preparetchan.h

tchanlc : tchanlc.o mclimit_csm.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(OutPutOpt)$@
	@echo "$@ done"

tchan_cls.o : tchan_cls.C preparetchan.h

tchan_cls : tchan_cls.o mclimit_csm_printpx.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(OutPutOpt)$@
	@echo "$@ done"
