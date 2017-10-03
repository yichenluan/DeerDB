deerdb: bitcask.o deerdb.o interface.o tool.o
	g++ -o deerdb -std=c++11 bitcask.o deerdb.o interface.o tool.o

bitcask.o: db/bitcask.cpp db/bitcask.h conf/conf.h db/db_defines.h
	g++ -g -c -I. -std=c++11 db/bitcask.cpp

deerdb.o: db/deerdb.cpp db/deerdb.h db/bitcask.h
	g++ -g -c -I. -std=c++11 db/deerdb.cpp

interface.o: db/interface.cpp db/interface.h db/deerdb.h
	g++ -g -c -I. -std=c++11 db/interface.cpp

tool.o: db/tool.cpp db/interface.h db/deerdb.h
	g++ -g -c -I. -std=c++11 db/tool.cpp

clean:
	rm deerdb bitcask.o deerdb.o interface.o tool.o
