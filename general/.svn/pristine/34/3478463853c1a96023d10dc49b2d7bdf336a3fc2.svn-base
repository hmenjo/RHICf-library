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

CXXFLAGS += $(INCALL)

ROOTLIBS  += -Wl,-rpath,$(ROOTSYS)/lib
ROOTGLIBS += -Wl,-rpath,$(ROOTSYS)/lib

all: printeventview slink

printeventview : src/printeventview.o 
	mkdir -p .eventview
	$(CXX) $(CXXFLAGS) -o $@ $^ \
	$(LIBS) $(ROOTLIBS) $(ROOTGLIBS) $(LHCFLIBS)

src/%.o  :  src/%.cpp  src/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

src/%.o  :  src/%.cpp
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(INC_DIR)/%.h :

slink : printeventview
	cd ../../bin/ ; \
	rm -f  ./LHCfprinteventview; \
	ln -s  ../Tools/PrintEventView/printeventview ./LHCfprinteventview


clean:
	rm -f *.o */*.o */*~ *~ \#* 
	rm -f printeventview
