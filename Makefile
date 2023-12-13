CXXFLAGS=-Wall -O3 -g -Wno-narrowing
INCDIR=include
SRCDIR=src
MAINDIR=main
OBJDIR=obj
BINDIR=bin
OBJECTS=$(OBJDIR)/noise-field.o $(OBJDIR)/OpenSimplexNoise.o $(OBJDIR)/bit-field.o $(OBJDIR)/static-field.o $(OBJDIR)/RandomFunctions.o $(OBJDIR)/ArtFunctions.o $(OBJDIR)/print10.o
BINARIES=noise-field bit-field static-field print10

RGB_INCDIR=matrix/include
RGB_LIBDIR=matrix/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all : $(OBJDIR) $(BINDIR) $(addprefix $(BINDIR)/,$(BINARIES))

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/noise-field : $(OBJDIR)/noise-field.o $(OBJDIR)/OpenSimplexNoise.o $(OBJDIR)/ArtFunctions.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BINDIR)/bit-field : $(OBJDIR)/bit-field.o $(OBJDIR)/ArtFunctions.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BINDIR)/static-field : $(OBJDIR)/static-field.o $(OBJDIR)/RandomFunctions.o $(OBJDIR)/ArtFunctions.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BINDIR)/print10 : $(OBJDIR)/print10.o $(OBJDIR)/RandomFunctions.o $(OBJDIR)/ArtFunctions.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

$(OBJDIR)/%.o : $(MAINDIR)/%.cc
	$(CXX) -I$(INCDIR) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -I$(INCDIR) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)
	$(MAKE) -C $(RGB_LIBDIR) clean

FORCE:
.PHONY: FORCE
