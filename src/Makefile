FUSEINC=-D_FILE_OFFSET_BITS=64 -I/home/roy/project/fuse/include/fuse
FUSELIB=-pthread -L/home/roy/project/fuse/lib -lfuse -lrt -ldl
GBUFLIB=-L/home/roy/project/gbuffer/lib

fusionfs : fusion.o util.o clock.o log.o
	gcc -g -Wall -o fusionfs fusion.o util.o clock.o log.o -Lzht/lib -lzht -lstdc++ $(GBUFLIB) -lprotobuf -lpthread -Lffsnet -lffsnet_bridger ${FUSELIB} 

fusion.o : fusion.c log.h params.h util.h
	gcc -g -Wall ${FUSEINC} -c fusion.c -L./ffsnet -lffsnet_bridger 

clock.o : clock.c log.h params.h  util.h 
	gcc -g -Wall ${FUSEINC} -c clock.c 

util.o : util.c log.h params.h util.h   
	gcc -g -Wall ${FUSEINC} -c util.c -L./zht/lib -lzht -lstdc++ -lprotobuf -lpthread 

log.o : log.c log.h params.h
	gcc -g -Wall ${FUSEINC} -c log.c 

clean:
	rm -f fusionfs *.o

dist:
	rm -rf fuse-tutorial/
	mkdir fuse-tutorial/
	cp ../*.html fuse-tutorial/
	mkdir fuse-tutorial/example/
	mkdir fuse-tutorial/example/mountdir/
	mkdir fuse-tutorial/example/rootdir/
	echo "a bogus file" > fuse-tutorial/example/rootdir/bogus.txt
	mkdir fuse-tutorial/src
	cp Makefile *.c *.h fuse-tutorial/src/
	tar cvzf ../../fuse-tutorial.tgz fuse-tutorial/
	rm -rf fuse-tutorial/
