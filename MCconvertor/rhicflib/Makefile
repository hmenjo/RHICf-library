#####################################################################

#-------------------------------------------------------------------

INC_DIR       = ./include
SRC_DIR       = ./src
LIB_DIR       = $(PWD)/lib
#-------------------------------------------------------------------

LIBNAME          = libRHICfEvent

LIBEVENT_HLIST  +=  RHICfBBC.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfBBC.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfBBC.o 

LIBEVENT_HLIST  +=  RHICfZDC.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfZDC.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfZDC.o 

LIBEVENT_HLIST  +=  RHICfFC.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfFC.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfFC.o 

LIBEVENT_HLIST  +=  RHICfRoman.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfRoman.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfRoman.o 

LIBEVENT_HLIST  +=  RHICfSimP.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfSimP.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfSimP.o 

LIBEVENT_HLIST  +=  RHICfSimIncidents.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfSimIncidents.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfSimIncidents.o 

LIBEVENT_HLIST  +=  ParticlesInfo.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/ParticlesInfo.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/ParticlesInfo.o 

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

$(SRC_DIR)/A2Cal2M.o : $(INC_DIR)/A2Cal2.h $(INC_DIR)/Rec0.h

$(SRC_DIR)/A2Rec1.o : $(INC_DIR)/Rec0.h

$(SRC_DIR)/A2Rec2.o : $(INC_DIR)/Rec0.h $(INC_DIR)/A2Rec1.h

$(SRC_DIR)/SimIncidents.o :  $(INC_DIR)/SimP.h

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


