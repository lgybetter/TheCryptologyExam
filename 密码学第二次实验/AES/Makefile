example.so:rijndael-test-fst.o wrap.o rijndael-alg-fst.o rijndael-api-fst.o
	gcc -shared -o example.so rijndael-test-fst.o wrap.o rijndael-alg-fst.o rijndael-api-fst.o
rijndael-test-fst.o:rijndael-test-fst.c wrap.c
	gcc -fpic -c -I/usr/include/python2.7 -I/usr/lib/python2.7/config rijndael-test-fst.c wrap.c
wrap.o:rijndael-test-fst.c wrap.c
	gcc -fpic -c -I/usr/include/python2.7 -I/usr/lib/python2.7/config rijndael-test-fst.c wrap.c
CFLAGS=-Wall -O2 -DTRACE_KAT_MCT -DINTERMEDIATE_VALUE_KAT
rijndael-test-fst:	rijndael-test-fst.o rijndael-api-fst.o rijndael-alg-fst.o

clean:
	-rm -f *.o
	-rm -f *.so


