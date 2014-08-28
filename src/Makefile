FUSEINC=-D_FILE_OFFSET_BITS=64 -I/home/roy/project/fuse/include/fuse
FUSELIB=-pthread -L/home/roy/project/fuse/lib -lfuse -lrt -ldl
GBUFLIB=-L/home/roy/project/gbuffer/lib

fusionfs : royfusion.o util.o roycache.o log.o
	gcc -g -Wall -o fusionfs royfusion.o util.o roycache.o log.o -Lzht/lib -lzht -lstdc++ $(GBUFLIB) -lprotobuf -lpthread -Lffsnet -lffsnet_bridger ${FUSELIB} 

royfusion.o : royfusion.c log.h royparams.h util.h
	gcc -g -Wall ${FUSEINC} -c royfusion.c -L./ffsnet -lffsnet_bridger 

roycache.o : roycache.c log.h royparams.h  util.h 
	gcc -g -Wall ${FUSEINC} -c roycache.c 

util.o : util.c log.h royparams.h util.h   
	gcc -g -Wall ${FUSEINC} -c util.c -L./zht/lib -lzht -lstdc++ -lprotobuf -lpthread 

log.o : log.c log.h royparams.h
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
