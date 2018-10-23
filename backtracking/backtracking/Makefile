all:
	gcc -c util/fileReader.h util/fileReader.c util/logger.c util/logger.h main.c wordHunt/wordHunt.c wordHunt/wordHunt.h sudoku/sudoku.c sudoku/sudoku.h util/interface.c util/interface.h
	gcc  -o exec fileReader.o logger.o main.o wordHunt.o sudoku.o interface.o
production:
	gcc -Wall util/fileheader.h util/fileHeader.c util/logger.h util/logger.h util/interface.h util/interface.c main.c -o tp
clean:
	rm fileReader.o logger.o wordHunt.o main.o sudoku.o exec
run:
	./exec
