run:
	gcc main.c hash/hash.c PATRICIA/patricia.c stopwords/stopword.c PATRICIA/lista/lista.c leitura/leitura.c relevancia/relevancia.c -o tp_aeds2.exe
	./tp_aeds2.exe

clean:
	rm -f tp_aeds2.exe tp_aeds2 *.o
