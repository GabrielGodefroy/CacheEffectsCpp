CPPFLAGS=-Wall -Werror -DNDEBUG -O3 -std=c++2a
CPPFLAGS=-Wall -Werror -O3 -std=c++2a

all: compil exec python webpage

clean:
	rm -rf build/*

compil:
	g++ ${CPPFLAGS} src/m_alignement.cpp -o build/m_alignement.exe
	g++ ${CPPFLAGS} src/m_cache_lines.cpp -o build/m_cache_lines.exe

exec:
	./build/m_alignement.exe > build/m_alignement.txt ; cat build/m_alignement.txt
	./build/m_cache_lines.exe > build/m_cache_lines.txt ; cat build/m_cache_lines.txt

py:
	/home/godefroy/miniconda3/envs/CacheEffect/bin/python python/m_cache_lines.py	

webpage:
	#cp build/*.txt build/*.png doc/ 
	python3 python/replace.py 
	pandoc -c style.css -s doc/index.md -o doc/index.html

    
        
