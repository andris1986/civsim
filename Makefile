CC = g++
OBJDIR = .obj
SRCDIR = src
APPNAME = civsim
LIBS = -lglut
DOC_APP = doxygen
DOC_CONFIG = Doxyfile
DOC_FOLDER = html

#Uncomment next line to enable debug
#CFLAGS = -DCIVSIM_DBG

#Unconnect next line to compile without GL
#CFLAGS = -DC_NO_GL

SOURCES = $(shell mkdir -p $(OBJDIR); ls -t $(SRCDIR)/*.cpp) 
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(OBJECTS);
	$(CC) $(LIBS) $(OBJECTS) -o $(APPNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

docs:
	$(DOC_APP) $(DOC_CONFIG)

clean:
	rm -rf $(OBJDIR) $(APPNAME) $(DOC_FOLDER)

