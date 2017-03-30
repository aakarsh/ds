FLAGS:=-pipe -O2 -std=c++0x -g
#-DDEBUG
all: hash_chains hash_chains_d

hash_chains: hash_chains.cc
	g++  $(FLAGS) hash_chains.cc   -lm -o ./bin/hash_chain
hash_chains_d: hash_chains.cc
	g++  $(FLAGS) hash_chains.cc -DDEBUG   -lm -o ./bin/hash_chain_d
