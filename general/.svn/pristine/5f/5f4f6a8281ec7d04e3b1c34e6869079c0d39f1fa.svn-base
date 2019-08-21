#####################################################################

#-------------------------------------------------------------------
INC_DIR       = ./include
SRC_DIR       = ./src
LIB_DIR       = ./lib
#-------------------------------------------------------------------

LIBNAME          = libLHCfSC
# SlowControl
LIBSC_HLIST  +=  TLHCFSDATA.h
LIBSC_HLIST  +=  TLHCFDIPDATAH.h TLHCFDIPDATAL.h
LIBSC_HLIST  +=  TLHCFDIPDATAVH.h
LIBSC_HLISTS +=  $(INC_DIR)/TLHCFSDATA.h
LIBSC_HLISTS +=  $(INC_DIR)/TLHCFDIPDATAH.h $(INC_DIR)/TLHCFDIPDATAL.h
LIBSC_HLISTS +=  $(INC_DIR)/TLHCFDIPDATAVH.h
LIBSC_LIBS   +=  $(SRC_DIR)/TLHCFSDATA.o
LIBSC_LIBS   +=  $(SRC_DIR)/TLHCFDIPDATAH.o $(SRC_DIR)/TLHCFDIPDATAL.o
LIBSC_LIBS   +=  $(SRC_DIR)/TLHCFDIPDATAVH.o
LIBSC_HLIST  +=  SocketControl.h
LIBSC_HLISTS +=  $(INC_DIR)/SocketControl.h
LIBSC_LIBS   +=  $(SRC_DIR)/SocketControl.o
#
LIBSC_LIBS   +=  $(SRC_DIR)/$(LIBNAME).o 

INCALL += -I$(INC_DIR) 

include ../Makefile.arch

CXXFLAGS  +=  $(INCALL)

all: dict

$(SRC_DIR)/TLHCFDIPDATAL.o :  $(INC_DIR)/lhcfdipdata.h

$(SRC_DIR)/TLHCFDIPDATAH.o :  $(INC_DIR)/lhcfdipdata.h

$(SRC_DIR)/TLHCFDIPDATAVH.o : $(INC_DIR)/lhcfdipdata.h

$(SRC_DIR)/%.o	:  $(SRC_DIR)/%.cpp  
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o	:  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(INC_DIR)/$(LIBNAME).h : $(LIBSC_HLISTS) $(INC_DIR)/LinkDef.h
#	cd $(INC_DIR); \
#	rootcint -f $(LIBNAME).cpp -c $(LIBSC_HLIST) LinkDef.h ; \
#	cd -;
#	mv $(INC_DIR)/$(LIBNAME).cpp $(SRC_DIR)
	rootcint -f $(LIBNAME).cpp -c -I$(INC_DIR) -I$(SRC_DIR) \
	$(LIBSC_HLIST) $(INC_DIR)/LinkDef.h
	mv $(LIBNAME).h $(INC_DIR)/
	mv $(LIBNAME).cpp $(SRC_DIR)/

$(SRC_DIR)/$(LIBNAME).o :  $(INC_DIR)/$(LIBNAME).h
	$(CXX) $(ROOTCFLAGS) $(OSFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/$(LIBNAME).cpp -o $@

$(LIB_DIR)/$(LIBNAME).so : $(LIBSC_LIBS)
	$(LD) $(ROOTCFLAGS) $(LDFLAGS) $(SOFLAGS) $^ -o $@

dict: 	$(LIB_DIR)/$(LIBNAME).so

$(INC_DIR)/%.h :

clean:
	rm -f $(INC_DIR)/$(LIBNAME).h
	rm -f $(SRC_DIR)/$(LIBNAME).cpp
	rm -f $(LIBSC_LIBS)
	rm -f $(LIB_DIR)/$(LIBNAME).so


# for synchronization 
GENERALDIR=/home/menjo/LHCf/LHC/general/sc_old/sc_op2010_04
cp:	cp2general
cp2general:
	rsync -av Makefile  README $(GENERALDIR)

	cd $(INC_DIR);\
	rsync -av \
	lhcfsdata.h lhcfdipdata.h TLHCFSDATA.h \
	TLHCFDIPDATAH.h TLHCFDIPDATAL.h TLHCFDIPDATAVH.h \
	feparam_fe3.h SocketControl.h \
	LinkDef.h \
	$(GENERALDIR)/include/

	cd $(SRC_DIR);\
	rsync -av \
	TLHCFDIPDATAH.cpp TLHCFDIPDATAL.cpp TLHCFDIPDATAVH.cpp \
	TLHCFSDATA.cpp SocketControl.cpp \
	$(GENERALDIR)/src/

#end file
