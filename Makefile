CPPFLAGS=-Wall -Werror -O3 -std=c++2a
CPPFLAGS=-Wall -Werror -DNDEBUG -O3 -std=c++2a
PYTHONPATH=/home/godefroy/miniconda3/envs/CacheEffect/bin/python

# Compile executable and generate assembly code
define compile_exe_file 
	g++ 	  ${CPPFLAGS} 	$(2) src/$(1).cpp 	-o build/$(1).exe
	g++ -S 	  ${CPPFLAGS}  	$(2) src/$(1).cpp 	-o build/$(1).s
endef

# Compile object file and generate assembly code
define compile_obj_file 
	g++ -c	  ${CPPFLAGS} 	$(2) src/$(1).cpp 	-o build/$(1).o
	g++ -c -S ${CPPFLAGS}  	$(2) src/$(1).cpp 	-o build/$(1).s
endef

# Run an executable and redirect the ouput
define exec_file 
	./build/$(1).exe > build/$(1).txt ;
endef

# Typically used to convert results into an image
define run_python 
	${PYTHONPATH} python/$(1).py	
endef


all: compil exec python webpage

.PHONY: clean
clean:
	rm -rf build/*

build/m_alignement.txt: build/m_alignement.exe
	$(call exec_file,m_alignement)
build/m_alignement.exe: src/m_alignement.cpp 
	$(call compile_exe_file,m_alignement)
m_alignement: build/m_alignement.txt build/m_alignement.exe

build/m_l1_l2.txt: build/m_l1_l2.exe
	$(call exec_file,m_l1_l2)
build/m_l1_l2.exe: src/m_l1_l2.cpp 
	$(call compile_exe_file,m_l1_l2)
m_l1_l2: build/m_l1_l2.txt build/m_l1_l2.exe
	
build/m_cache_lines.txt: build/m_cache_lines.exe
	$(call exec_file,m_cache_lines)
build/m_cache_lines.exe: src/m_cache_lines.cpp 
	$(call compile_exe_file,m_cache_lines)
m_cache_lines: build/m_cache_lines.txt build/m_cache_lines.exe
		
build/m_cache_associativity.txt: build/m_cache_associativity.exe
	$(call exec_file,m_cache_associativity)
build/m_cache_associativity.exe: src/m_cache_associativity.cpp 
	$(call compile_exe_file,m_cache_associativity)
m_cache_associativity: build/m_cache_associativity.txt build/m_cache_associativity.exe
		


py:
	$(call run_python,m_cache_lines)

webpage:
	$(call run_python,replace)
	pandoc -c style.css -s doc/index.md -o doc/index.html

    
        
# TODO
.PHONY: build
build: src/m_alignement.exe
