OBJ = obj
BIN = bin
INC = include
LIB = lib
SRC = src
CPPFLAGS = g++ -std=c++11 -g -Wall

all : $(BIN)/testimagen $(BIN)/arteASCII2 $(BIN)/suma

$(BIN)/testimagen : $(LIB)/libimagen.a $(OBJ)/testimagen.o
	$(CPPFLAGS) -o $(BIN)/testimagen $(OBJ)/testimagen.o  -Llib/ -limagen

$(BIN)/arteASCII2: $(LIB)/libimagen.a $(OBJ)/arteASCII2.o
	$(CPPFLAGS) -o $(BIN)/arteASCII2 $(OBJ)/arteASCII2.o -Llib/ -limagen

$(BIN)/suma: $(LIB)/libimagen.a $(OBJ)/suma.o
	$(CPPFLAGS) -o $(BIN)/suma $(OBJ)/suma.o -Llib/ -limagen

$(OBJ)/suma.o: $(SRC)/suma.cpp $(INC)/imagen.h $(INC)/pgm.h
	$(CPPFLAGS) -c $(SRC)/suma.cpp -o $(OBJ)/suma.o -Iinclude/

$(OBJ)/arteASCII2.o: $(SRC)/arteASCII2.cpp $(INC)/imagen.h $(INC)/lista.h
	$(CPPFLAGS) -c $(SRC)/arteASCII2.cpp -o $(OBJ)/arteASCII2.o -Iinclude/

$(OBJ)/testimagen.o: $(SRC)/testimagen.cpp $(INC)/imagen.h
	$(CPPFLAGS) -c $(SRC)/testimagen.cpp -o $(OBJ)/testimagen.o -Iinclude/

$(OBJ)/pgm.o: $(SRC)/pgm.cpp $(INC)/pgm.h
	$(CPPFLAGS) -c $(SRC)/pgm.cpp -o $(OBJ)/pgm.o -Iinclude/

$(OBJ)/byte.o: $(SRC)/byte.cpp $(INC)/byte.h
	$(CPPFLAGS) -c $(SRC)/byte.cpp -o $(OBJ)/byte.o -Iinclude/

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/pgm.h $(INC)/imagen.h $(INC)/byte.h $(INC)/lista.h
	$(CPPFLAGS) -c $(SRC)/imagen.cpp -o $(OBJ)/imagen.o -Iinclude/

$(OBJ)/lista.o: $(SRC)/lista.cpp $(INC)/lista.h
	$(CPPFLAGS) -c $(SRC)/lista.cpp -o $(OBJ)/lista.o -Iinclude/

$(LIB)/libimagen.a: $(OBJ)/pgm.o $(OBJ)/imagen.o $(OBJ)/byte.o  $(OBJ)/lista.o
	ar rsv $(LIB)/libimagen.a $(OBJ)/pgm.o $(OBJ)/imagen.o $(OBJ)/byte.o $(OBJ)/lista.o

clean:
	echo "Limpiando..."
	rm $(OBJ)/*.o

mrproper: clean
	rm $(BIN)/*
	rm $(LIB)/*
