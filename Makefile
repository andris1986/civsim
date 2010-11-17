CC = g++
OBJDIR = .obj
SRCDIR = src
APPNAME = civsim
LIBS = -lglut

#Uncomment next line to enable debug
#CFLAGS = -DCIVSIM_DBG

SOURCES = $(shell mkdir -p $(OBJDIR); ls -t $(SRCDIR)/*.cpp) 
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(OBJECTS);
	$(CC) $(LIBS) $(OBJECTS) -o $(APPNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(APPNAME)

