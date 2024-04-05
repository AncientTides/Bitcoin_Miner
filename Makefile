__: t_incrementus.o 
	g++ -o offline __.o

__.o: t_incrementus.cpp __.h json.hpp infint.h
	g++ -c __.cpp

#headers.h InfInt.h reverse_convert.h Grada_Merkle_Hash.h Grada_sha256.h coinbase_creation_2.h json.hpp


