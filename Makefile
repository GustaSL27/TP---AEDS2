run:
	gcc main.c hash/hash.c PATRICIA/patricia.c -o tp_aeds2.exe
	./tp_aeds2.exe

clean:
	del /f /q tp_aeds2.exe
