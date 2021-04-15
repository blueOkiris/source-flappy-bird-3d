# Build properties
OBJNAME :=	flappy-bird-3d
SRC :=		$(wildcard src/*.cpp)
HFILES :=	$(wildcard include/*.hpp)
INC :=		-Iinclude
CPPC :=		g++
CPPFLAGS :=	-O2 -Wall -std=c++17
LD :=		g++
LDFLAGS :=	-L/usr/lib/x86_64-linux-gnu -lglut -lGL -lGLU

# Autogen properties
OBJS :=		$(subst .cpp,.o,$(subst src/,obj/,$(SRC)))

# Helper targets
.PHONY : all
all : $(OBJNAME)

.PHONY : clean
clean :
	rm -rf obj/
	rm -rf $(OBJNAME)

obj/%.o : src/%.cpp $(HFILES)
	mkdir -p obj/
	$(CC) $(CPPFLAGS) $(INC) -o $@ -c $<

# Main targets
$(OBJNAME) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)