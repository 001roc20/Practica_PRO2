 
OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Especie.o Cjt_especies.o
	g++ -o program.exe Especie.o Cjt_especies.o program.o $(OPCIONS)
	rm *.o

Especie.o: Especie.cc 
	g++ -c Especie.cc $(OPCIONS)

Cjt_especies.o: Cjt_especies.cc 
	g++ -c Cjt_especies.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe