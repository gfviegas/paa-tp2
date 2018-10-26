all:
	gcc -c util/fileReader.h util/fileReader.c util/logger.c util/logger.h main.c wordHunt/wordHunt.c wordHunt/wordHunt.h wordHunt/interfaceWH.c wordHunt/interfaceWH.h sudoku/sudoku.c sudoku/sudoku.h sudoku/interfaceS.h sudoku/interfaceS.c util/interface.c util/interface.h
	gcc  -o exec fileReader.o logger.o main.o wordHunt.o interfaceWH.o sudoku.o interfaceS.o interface.o
clean:
	rm *.o *.gch exec
run:
	./exec
analysis:
	./exec -a
