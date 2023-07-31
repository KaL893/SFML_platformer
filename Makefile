# Makefile
CXX = g++
CXXFLAGS = -g
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
SRC = main.cpp Game.cpp player.cpp gameBlock.cpp stoneBlock.cpp bullet.cpp Projectile.cpp Tile.cpp Parralax.cpp floatingTile.cpp Enemy.cpp Grenade.cpp healthBar.cpp Spikes.cpp healthPickup.cpp Menu.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
