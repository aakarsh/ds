FLAGS:=-pipe -O2 -std=c++0x -g
#-DDEBUG
all: tree-orders tree-orders_d

tree-orders: tree-orders.cc
	g++  $(FLAGS) tree-orders.cc   -lm -o ./bin/tree-orders
tree-orders_d: tree-orders.cc
	g++  $(FLAGS) tree-orders.cc -DDEBUG   -lm -o ./bin/tree-orders_d
