CPPFLAGS=-Wall -Werror -DNDEBUG -O3 -std=c++2a

all: compil

clean:
	rm -rf build/*

compil:
	g++ ${CPPFLAGS} src/m_alignement.cpp -o build/m_alignement.exe

exec:
	./build/m_alignement.exe > build/m_alignement.txt ; cat build/m_alignement.txt

python:
	python3 --version	