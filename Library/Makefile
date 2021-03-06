#####################################################################

#-------------------------------------------------------------------

INC_DIR       = ./include
SRC_DIR       = ./src
LIB_DIR       = $(PWD)/lib
#-------------------------------------------------------------------

LIBNAME          = libRHICf

LIBEVENT_HLIST  =  RHICfPhys.h 
LIBEVENT_HLISTS =  $(INC_DIR)/RHICfPhys.h
LIBEVENT_LIBS   =  $(SRC_DIR)/RHICfPhys.o

LIBEVENT_HLIST  +=  RHICfRec0.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfRec0.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfRec0.o

LIBEVENT_HLIST  +=  RHICfRec1.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfRec1.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfRec1.o

LIBEVENT_HLIST  +=  RHICfBBC.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfBBC.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfBBC.o 

LIBEVENT_HLIST  +=  RHICfZDC.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfZDC.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfZDC.o 

LIBEVENT_HLIST  +=  RHICfRoman.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfRoman.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfRoman.o 

LIBEVENT_HLIST  +=  RHICfSimP.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfSimP.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfSimP.o 

LIBEVENT_HLIST  +=  RHICfSimIncidents.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfSimIncidents.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfSimIncidents.o 

#
LIBEVENT_LIBS   +=  $(SRC_DIR)/$(LIBNAME).o 

INCALL += -I$(INC_DIR) 

#------------------------------------------------
#
# Configuration for each architecture
# (Updated for  ROOT version > 5.32)

MAKEARCH        :=      $(shell find $(ROOTSYS)/test -name Makefile.arch)
ifeq ($(MAKEARCH), )
# 41594 or later
MAKEARCH        :=      $(shell find $(ROOTSYS)/etc -name Makefile.arch)
endif

#include $(ROOTSYS)/test/Makefile.arch
include $(MAKEARCH)

#EXPLLINKLIBS += -lEG 
# For MAC OS X users 
ifneq (,$(filter $(ARCH),macosx macosx64))
SOFLAGS  += -install_name $(LIB_DIR)/$(LIBNAME).so
endif

#-------------------------------------------------

CXXFLAGS  += $(INCALL)

all: dict

$(SRC_DIR)/%.o	:  $(SRC_DIR)/%.cpp  
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(SRC_DIR)/%.o	:  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(SRC_DIR)/RHICfSimIncidents.o :  $(INC_DIR)/RHICfSimP.h

$(INC_DIR)/$(LIBNAME).h : $(LIBEVENT_HLISTS) $(INC_DIR)/LinkDef.h
	rootcint -f $(LIBNAME).cpp -c -I$(INC_DIR) -I$(SRC_DIR) \
	$(LIBEVENT_HLIST) $(INC_DIR)/LinkDef.h
	mv $(LIBNAME).h $(INC_DIR)/
	mv $(LIBNAME).cpp $(SRC_DIR)/

$(SRC_DIR)/$(LIBNAME).o :  $(INC_DIR)/$(LIBNAME).h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/$(LIBNAME).cpp -o $@

$(LIB_DIR)/$(LIBNAME).so : $(LIBEVENT_LIBS)
	$(LD) $(LDFLAGS) $(SOFLAGS) $^ -o $@ $(EXPLLINKLIBS) 

dict: 	$(LIB_DIR)/$(LIBNAME).so

$(INC_DIR)/%.h :

clean:
	rm -f $(INC_DIR)/$(LIBNAME).h
	rm -f $(SRC_DIR)/$(LIBNAME).cpp
	rm -f $(LIBEVENT_LIBS)
	rm -f $(LIB_DIR)/$(LIBNAME).so

print:
	echo $(CFLAGS)
	echo $LIBS

