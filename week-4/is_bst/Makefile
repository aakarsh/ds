FLAGS:=-pipe -O2 -std=c++0x -g
#-DDEBUG
all: is_bst is_bst_d

is_bst: is_bst.cc
	g++  $(FLAGS) is_bst.cc   -lm -o ./bin/is_bst
is_bst_d: is_bst.cc
	g++  $(FLAGS) is_bst.cc -DDEBUG   -lm -o ./bin/is_bst_d
