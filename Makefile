CC = g++
OBJDIR = .obj
SRCDIR = src
APPNAME = civsim
LIBS =  -lglut -lGLU -lGL
DOC_APP = doxygen
DOC_CONFIG = Doxyfile
DOC_FOLDER = html

TESTDIR = test
TESTAPP = civsim_ut
TESTLIBS = -lgtest

#Uncomment next line to enable debug
CFLAGS = -DCIVSIM_DBG

SOURCES = $(shell mkdir -p $(OBJDIR); ls -t $(SRCDIR)/*.cpp) 
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TESTS   = $(TESTDIR)/utest.cpp \
		  $(TESTDIR)/CPointTest.cpp \
		  $(SRCDIR)/CPoint.cpp 

all: $(OBJECTS);
	$(CC) $(OBJECTS) $(LIBS) -o $(APPNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

docs:
	$(DOC_APP) $(DOC_CONFIG)

clean:
	rm -rf $(OBJDIR) $(APPNAME) $(DOC_FOLDER) $(TESTAPP)

tests: all	
	$(CC) $(LIBS) $(CFLAGS) $(TESTLIBS) $(TESTS) -o $(TESTAPP)


