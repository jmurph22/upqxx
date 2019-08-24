release:
	g++ upqxx.cpp -std=c++14 -O2 -Wall -c -fpic -lpq -lpqxx
	g++ -shared -o libupqxx.so upqxx.o

debug:
	g++ upqxx.cpp -std=c++14 -O0 -Wall -c -fpic -lpq -lpqxx
	g++ -shared -o libupqxx.so upqxx.o

test:
	g++ test.cpp -o test -std=c++14 -Os -Wall -lpq -lpqxx -lupqxx

clean:
	rm *.o *.so test
