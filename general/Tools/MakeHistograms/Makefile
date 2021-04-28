#####################################################################
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
#-----------------------------------------
# LHCf Library
#
LIBDIR        = $(PWD)/../../
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
#-------------------------------------------------------------------
# 
# For this codes
#
INC_DIR       = ./include
SRC_DIR       = ./src
BIN_DIR       = ./bin
INCALL += -I$(INC_DIR) -I$(DICT_INC) -I$(FUNC_INC) -I$(SC_INC)
CXXFLAGS += $(INCALL)

ROOTLIBS  += -Wl,-rpath,$(ROOTSYS)/lib
ROOTGLIBS += -Wl,-rpath,$(ROOTSYS)/lib

# PROGRAMS = adchists adchists_Op2013  \
# 	   drawhists drawhists_Op2013 drawpede drawpede_Op2013 \
#            drawbeamconfig drawbeamconfig_Op2013 \
# 	   drawruninfo drawscl drawscl_Op2013

PROGRAMS = adchists_Op2015 \
	drawhists_Op2015 drawpede_Op2015 drawruninfo_Op2015 \
	filldaqinfo_Op2015 drawscl_Op2015 drawbeamconfig_Op2015 drawdschists_Op2015

all: $(PROGRAMS)

adchists : src/adchists.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

adchists_Op2013 : src/adchists_Op2013.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

adchists_Op2015 : src/adchists_Op2015.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

adchists_arm1 : src/adchists_arm1.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

adchists_arm2 : src/adchists_arm2.o 
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)	

comphists_arm1 : src/comphists_arm1.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

comphists_arm2 : src/comphists_arm2.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawhists : src/drawhists.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawhists_Op2013 : src/drawhists_Op2013.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawhists_Op2015 : src/drawhists_Op2015.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawpede : src/drawpede.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawpede_Op2013 : src/drawpede_Op2013.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawpede_Op2015 : src/drawpede_Op2015.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawbeamconfig : src/drawbeamconfig.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawbeamconfig_Op2013 : src/drawbeamconfig_Op2013.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawbeamconfig_Op2015 : src/drawbeamconfig_Op2015.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawruninfo : src/drawruninfo.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawruninfo_Op2015 : src/drawruninfo_Op2015.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawscl : src/drawscl.o src/RawL1TDraw.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawscl_Op2013 : src/drawscl_Op2013.o src/RawL1TDraw.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

drawscl_Op2015 : src/drawscl_Op2015.o 
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

filldaqinfo_Op2015 : src/filldaqinfo_Op2015.o 
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)

src/filldaqinfo_Op2015.o : $(INC_DIR)/ReadRunData_Op2015.h $(INC_DIR)/ReadDAQLog_Op2015.h

drawdschists_Op2015 : src/drawdschists_Op2015.o 
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS)



$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(INC_DIR)/%.h :

clean:
	rm -f *.o */*.o */*~ *~ \#*
	rm -f $(PROGRAMS)
