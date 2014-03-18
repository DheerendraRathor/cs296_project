.SUFFIX: .cpp .hpp

# Group Number 12

# Project name
TARGET = cs296_12_exe

# Commands
TAR = tar 
UNTAR = -xzf
CD = cd
MK = mkdir
ECHO = echo
CAT = cat
PRINTF = printf
CC = g++
DOXYGEN = doxygen


# Variables
SHARED_LIB = TRUE
PROJECT_ROOT := $(CURDIR)
EXTERNAL = $(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/myobjs
BINDIR = $(PROJECT_ROOT)/mybins
LIBDIR = $(PROJECT_ROOT)/mylibs
EXTSRC = $(EXTERNAL)/src
EXTLIB = $(EXTERNAL)/lib
INCLUDE = $(EXTERNAL)/include
BOX2D_FOLDER = $(INCLUDE)/Box2D
DOCDIR = $(PROJECT_ROOT)/doc

# Run time varibles
SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
ALL_MAIN:= $(wildcard $(OBJDIR)/*[!main].o)


# Library Paths
BOX2D_ROOT=$(EXTERNAL)
GLUI_ROOT=/usr
GL_ROOT=/usr/include

# Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall -fno-strict-aliasing
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

.PHONY: setup clean doc report distclean

# Default target
helloworld: setup 


setup:
	@$(ECHO) "setting up compilation now....please wait.."
	@$(MK) -p $(PROJECT_ROOT)/myobjs
	@$(MK) -p $(PROJECT_ROOT)/mylibs
	@$(MK) -p $(PROJECT_ROOT)/mybins
	@if test -d $(BOX2D_FOLDER) -a -d $(EXTLIB)/Box2D -a -e $(EXTLIB)/libBox2D.a;\
	then $(ECHO) "Box 2D found installed";\
	else $(ECHO) "You haven't installed Box2D...Let me do it for you."\
	&& $(CD) $(EXTSRC) \
	&& $(TAR) $(UNTAR) Box2D.tgz \
	&& $(CD) Box2D \
	&& $(MK) -p build296 \
	&& $(CD) build296 \
	&& cmake ../ \
	&& make \
	&& make install \
	&& $(CD) ../../../../;	\
	fi;
	@$(ECHO) "Done"

-include $(OBJS:.o=.d)

#target for compiling .cpp into .o
$(OBJS):$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "Compiling: %25s" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) "%30s\n" "[Fix This Error]" && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) "%30s\n" "[Just a Warning, You can ignore it]" && $(CAT) temp.log; \
	else $(PRINTF) "%30s\n" "[Complied Without Error]"; \
	fi;
	@$(RM) -f temp.log temp.err

exe:	setup $(OBJS)
	@$(PRINTF) "Building executable:%16s" "$(notdir $(BINDIR)/$(TARGET))"
	@$(CC) -o $(BINDIR)/$(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) "%30s\n" "[Fix this Error]" && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) "%30s\n" "[Just a Warning, You can ignore it]" && $(CAT) temp.log; \
	else $(PRINTF) "%30s\n" "[Executable file made!]"; \
	fi;
	@$(RM) -f temp.log temp.err

#target for building library according to SHARED_LIB
libs: 
	@if test $(SHARED_LIB) = FALSE;\
	then make -s static;\
	else make -s dynamic;\
	fi;

#target for building static library
static:	$(OBJS)
	@ar -cq $(LIBDIR)/libCS296test.a $(ALL_MAIN)

#target for building dynamic library
dynamic:$(OBJS)
	@gcc -shared -Wall $(CPPFLAGS) -o $(LIBDIR)/libCS296test.so -fPIC $(SRCDIR)/*[!main].cpp

exelib: setup $(OBJS) libs
	@$(PRINTF) "Building executable:%25s" "$(notdir $(BINDER)/cs296_12_exelib)"
	@if test $(SHARED_LIB) = TRUE;\
	then $(CC) -o $(BINDIR)/cs296_12_exelib $(LDFLAGS) $(OBJDIR)/main.o $(LIBDIR)/libCS296test.so $(LIBS) 2> temp.log || touch temp.err;\
	else $(CC) -o $(BINDIR)/cs296_12_exelib $(LDFLAGS) $(OBJDIR)/main.o $(LIBDIR)/libCS296test.a $(LIBS) 2> temp.log || touch temp.err;\
	fi;
	@if test -e temp.err; \
	then $(PRINTF) "%30s\n" "[Fix this Error]" && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) "%30s\n" "[Just a Warning, You can ignore it]" && $(CAT) temp.log; \
	else $(PRINTF) "%30s\n" "[Executable file made!]"; \
	fi;
	@$(RM) -f temp.log temp.err

clean: 
	@$(ECHO) "Cleaning up mylibs, mybins, myobjs..."
	@rm -rf $(PROJECT_ROOT)/my* *~ $(DOCDIR)/cs296_report_12.aux $(DOCDIR)/cs296_report_12.pdf $(DOCDIR)/cs296_report_12.dvi $(DOCDIR)/cs296_report_12.bbl $(DOCDIR)/cs296_report_12.blg $(DOCDIR)/cs296_report_12.log
	@rm -rf $(PROJECT_ROOT)/data $(PROJECT_ROOT)/plots $(DOCDIR)/*.html
	@$(ECHO) "Done"

distclean:clean
	@$(ECHO) "Now Uninstalling Box2D"
	@rm -rf $(INCLUDE)/* $(EXTLIB)/* $(EXTSRC)/Box2D
	@$(ECHO) "Done"

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"
	

