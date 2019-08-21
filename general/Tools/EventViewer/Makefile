######################################################################
#------------------------------------------------
#
# Configuration for each architecture
# (Updated for  ROOT version > 5.32)

MAKEARCH        :=      $(shell find $(ROOTSYS)/test -name Makefile.arch)
ifeq ($(MAKEARCH), )
# 41594 or later
MAKEARCH        :=      $(shell find $(ROOTSYS)/etc -name Makefile.arch)
endif

include $(MAKEARCH)

# For MAC OS X users
ifneq (,$(filter $(ARCH),macosx macosx64))
SOFLAGS  += -install_name $(LIB_DIR)/$(LIBNAME).so
endif
#
#-------------------------------------------------
# LHCf Library
#
LIBDIR = $(PWD)/../../

DICTNAME      = libLHCfEvent.so
DICT_DIR      = $(LIBDIR)/dict
DICT_INC      = $(DICT_DIR)/include
DICT_SRC      = $(DICT_DIR)/src
DICT_LIB      = $(DICT_DIR)/lib
FUNCNAME      = libLHCfFunction.so
FUNC_DIR      = $(LIBDIR)/func
FUNC_INC      = $(FUNC_DIR)/include
FUNC_SRC      = $(FUNC_DIR)/src
FUNC_LIB      = $(FUNC_DIR)/lib
SCNAME        = libLHCfSC.so
SC_DIR        = $(LIBDIR)/sc
SC_INC        = $(SC_DIR)/include
SC_SRC        = $(SC_DIR)/src
SC_LIB        = $(SC_DIR)/lib
LHCFLIBS      = $(DICT_LIB)/$(DICTNAME) $(FUNC_LIB)/$(FUNCNAME) \
                $(SC_LIB)/$(SCNAME)
LHCFLIBS      += -Wl,-rpath,$(DICT_LIB) -Wl,-rpath,$(FUNC_LIB) -Wl,-rpath,$(SC_LIB)
#
#--------------------------------------------------
# For this codes
#
BIN_DIR       = ./
INCALL += -I$(DICT_INC) -I$(FUNC_INC) -I$(SC_INC) -I./include 
CDIR    = \"$(shell pwd)\"
COPTION = -DEVENTVIEWDIR=$(CDIR)

FORMAT = 2015
CXXFLAGS += $(INCALL) -DFORMAT=$(FORMAT)

ROOTLIBS  += -Wl,-rpath,$(ROOTSYS)/lib
ROOTGLIBS += -Wl,-rpath,$(ROOTSYS)/lib

all: message

message:
	@echo
	@echo "!! select the version !!"
	@echo "make pp2010/pPb2013/pp2015/pPb2016/rhicf"
	@echo

pp2010:
	make clean 
	make eventview 'FORMAT=2010'
	make slink

pPb2013:
	make clean 
	make eventview 'FORMAT=2013'
	make slink

pp2015:
	make clean 
	make eventview 'FORMAT=2015'
	make slink

pPb2016:
	make clean 
	make eventview 'FORMAT=2016'
	make slink

rhicf:
	make clean 
	make eventview 'FORMAT=2017'
	make slink

eventview : src/eventview.o \
	    src/TGTextButtonMod.o src/EventMarker.o src/EventTagFrame.o \
	    src/FrameEventView.o src/MkPedestalFrame.o src/LHCfParamFiles.o \
	    src/GainConfigWindow.o src/AdamoFrame.o src/MkAdamoPedestalFrame.o \
	    src/libEventView.o \
	    src/RawL1TDraw.o
	mkdir -p .eventview
	$(CXX) $(CXXFLAGS) -o $@ $^ \
	$(LIBS) $(ROOTLIBS) $(ROOTGLIBS) $(LHCFLIBS)

src/eventview.o : src/eventview.cpp $(EVB_INC) 
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) $(COPTION) -c $< -o $@	

src/LHCfParamFiles.o : src/LHCfParamFiles.cpp include/LHCfParamFiles.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) $(COPTION)  -c $< -o $@

src/%.o  :  src/%.cpp  src/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

src/%.o  :  src/%.cpp
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

test 	:
	echo $(CDIR)

src/libEventView.o : include/FrameEventView.h include/TGTextButtonMod.h \
		     include/EventMarker.h include/EventTagFrame.h \
                     include/MkPedestalFrame.h include/GainConfigWindow.h \
                     include/AdamoFrame.h include/MkAdamoPedestalFrame.h \
	             include/LinkDef_eventview.h
	rootcint -f libEventView.cpp -c  -I./include -I./src \
	-I$(DICT_INC) -I$(FUNC_INC) -I$(DICT_SRC) -I$(FUNC_SRC) \
	FrameEventView.h TGTextButtonMod.h EventMarker.h EventTagFrame.h \
	MkPedestalFrame.h GainConfigWindow.h  AdamoFrame.h MkAdamoPedestalFrame.h \
        LinkDef_eventview.h;
	mv libEventView.h    ./include
	mv libEventView.cpp  ./src
	$(CXX)  $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c src/libEventView.cpp -o $@

$(INC_DIR)/%.h :

.PHONY: clean slink

slink : eventview
	cd ../../bin/ ; \
	rm -f  ./LHCfeventview ; \
	ln -s  ../Tools/EventViewer/eventview ./LHCfeventview

clean:
	rm -f *.o */*.o */*~ *~ \#*
	rm -f include/libEventView.h src/libEventView.cpp 
	rm -f eventview
