all:
	gcc -c util/fileReader.h util/fileReader.c util/logger.c util/logger.h main.c wordHunt/wordHunt.c wordHunt/wordHunt.h wordHunt/interfaceWH.c wordHunt/interfaceWH.h sudoku/sudoku.c sudoku/sudoku.h sudoku/interfaceS.h sudoku/interfaceS.c util/interface.c util/interface.h
	gcc  -o exec fileReader.o logger.o main.o wordHunt.o interfaceWH.o sudoku.o interfaceS.o interface.o
production:
	gcc -Wall util/fileheader.h util/fileHeader.c util/logger.h util/logger.h util/interface.h util/interface.c main.c -o tp
clean:
	rm fileReader.o logger.o main.o wordHunt.o interfaceWH.o sudoku.o interfaceS.o interface.o exec
run:
	./exec
