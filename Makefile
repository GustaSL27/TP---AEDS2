run:
	gcc main.c hash/hash.c PATRICIA/patricia.c -o tp_aeds2.exe
	./tp_aeds2.exe

clean:
	rm -f tp_aeds2.exe tp_aeds2 *.o
