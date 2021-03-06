.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
PDFLATEX = pdflatex
BIBTEX = bibtex
######################################
# Project Name (generate executable with this name)
TARGET = cs251_base
PDF = report
BEAMER = Presentation
# Project Paths
PROJECT_ROOT=./
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall -fno-strict-aliasing -pg
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib -pg

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


.PHONY: all setup doc clean distclean

all: setup $(BINDIR)/$(TARGET)

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin
	@cd external && cd src && if ! [ -d Box2D ]; then tar zxfv Box2D.tar.gz ; cd ..; cd ..; pushd ./external/src && cd Box2D && mkdir build251 && cd build251 && cmake ../ &&  make && make install ; popd ;fi;
	


$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include -include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

codeDoc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 >/dev/null
	@$(ECHO) "Done"

report: 
	@cd ./doc && $(PDFLATEX) $(PDF).tex 2 > /dev/null && $(BIBTEX) -terse $(PDF)  && $(PDFLATEX) $(PDF).tex 2 > /dev/null && $(PDFLATEX) $(PDF).tex 2 > /dev/null && $(PDFLATEX) $(BEAMER).tex 2 > /dev/null;

release: setup $(BINDIR)/$(TARGET)
	@./bin/cs251_base	
profile:
	@make all
	@$(PRINTF) "$(MESG_COLOR)Please close the simulation when it has run upto desired length of time \n $(NO_COLOR)"
	@./bin/cs251_base
	@gprof ./bin/cs251_base gmon.out > flatprofile.txt
	@gprof ./bin/cs251_base gmon.out -P -b > callgraph.txt
	@python gprof2dot.py callgraph.txt> callgraph.dot
	@dot callgraph.dot -Tpng > callgraph.png

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(DOCDIR)/*.aux $(DOCDIR)/*.bbl $(DOCDIR)/*.blg $(DOCDIR)/*.log $(DOCDIR)/*.out $(DOCDIR)/*.nav $(DOCDIR)/*.toc $(DOCDIR)/*.snm callgraph.txt flatprofile.txt gmon.out callgraph.dot
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html $(DOCDIR)/*.aux $(DOCDIR)/*.bbl $(DOCDIR)/*.blg $(DOCDIR)/*.log $(DOCDIR)/*.out $(DOCDIR)/*.pdf $(DOCDIR)/*.nav $(DOCDIR)/*.toc $(DOCDIR)/*.snm flatprofile.txt gmon.out callgraph.*

