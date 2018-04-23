#Jiwon Topper
#jxt171830@utdallas.edu
#CS3377.002

# Set up info for C++ implicit rule
CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -I/scratch/perkins/include

# Set up any Linker Flags
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

# We choose the project name.  This is used in building the file name for the backup target
PROJECTNAME = program6 

# We choose the source files to include and name the output
SRCS = cdkexample.cc 
# We choose the name of the executable to be created
EXEC = program6

OBJS = $(SRCS:cc=o)

# man pages for cdk
MANPATH = $MANPATH:/scratch/perkins/man; export MANPATH

all: $(EXEC)

clean:
	rm -f $(OBJS) *.d *~ \#* $(EXEC)

Makefile: $(SRCS:.cc=.d)

# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(LDFLAGS) $(OBJS) $(LDLIBS)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


# Include the dependency files
-include $(SRCS:.cc=.d)

