CXX = gcc
CXXFLAGS = -Iinclude/
CXXFLAGS_END = -lm
# DEBUGFLAGS = -g

# Adding SDL compilation flags
SDL_FLAGS = $(shell pkg-config --cflags sdl2)
SDL_LIBS = $(shell pkg-config --libs sdl2)
CXXFLAGS_END += $(SDL_FLAGS)
CXXFLAGS_END += $(SDL_LIBS)
CXXFLAGS_END += -lX11

BIN = SpaceWarrior
SOURCE = $(wildcard src/*.c)
OBJSDIR = objs
OBJS = $(patsubst src/%,$(OBJSDIR)/%,$(patsubst %.c,%.o,$(SOURCE)))
INCLUDES = $(wildcard include/*.h)


all: $(BIN)

$(BIN): $(OBJSDIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS)  -o $@ $(OBJS) $(CXXFLAGS_END)

$(OBJSDIR):
	mkdir -p $@

$(OBJSDIR)/%.o: src/%.c $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $< -o $@ $(CXXFLAGS_END)


clean:
	rm -rf $(OBJSDIR) ; rm $(BIN)