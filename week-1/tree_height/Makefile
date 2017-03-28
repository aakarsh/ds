FLAGS:=-pipe -O2 -std=c++0x -g
all: tree-height_d tree-height
#-DDEBUG
tree-height_d: tree-height.cc
	g++  $(FLAGS) tree-height.cc -DDEBUG   -lm -o ./bin/tree-height_d

tree-height: tree-height.cc
	g++  $(FLAGS) tree-height.cc   -lm -o ./bin/tree-height
