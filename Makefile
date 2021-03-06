#CPPFLAGS=-Wall -Werror -O3 -std=c++2a
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
	${PYTHONPATH} python/$(1).py $(2)	
endef

# Replace what needed to be in input.md file, and call pandoc
define replace_and_pandoc 
	$(call run_python,replace,  docs/$(1).input.md docs/$(1).md)
	pandoc -c style.css -s docs/$(1).md -o docs/$(1).html
endef


all: build_and_run_all webpage

build_and_run_all: m_loop_vect m_false_sharing m_cache_associativity m_cache_lines m_cache_list_vs_vec m_cache_oop_spatial m_cache_oop_temporal m_l1_l2 m_l1_l2_detail m_alignement m_padding 


.PHONY: clean
clean:
	rm -rf build/*

build/m_memory_vs_compute.txt: build/m_memory_vs_compute.exe
	$(call exec_file,m_memory_vs_compute)
build/m_memory_vs_compute.exe: src/m_memory_vs_compute.cpp 
	$(call compile_exe_file,m_memory_vs_compute)
m_memory_vs_compute: build/m_memory_vs_compute.txt build/m_memory_vs_compute.exe

build/m_alignement.txt: build/m_alignement.exe
	$(call exec_file,m_alignement)
build/m_alignement.exe: src/m_alignement.cpp src/f_show_size_alignment.hpp
	$(call compile_exe_file,m_alignement)
m_alignement: build/m_alignement.txt build/m_alignement.exe

build/m_padding.txt: build/m_padding.exe
	$(call exec_file,m_padding)
build/m_padding.exe: src/m_padding.cpp src/f_show_size_alignment.hpp
	$(call compile_exe_file,m_padding)
m_padding: build/m_padding.txt build/m_padding.exe


build/m_l1_l2.txt: build/m_l1_l2.exe
	$(call exec_file,m_l1_l2)
build/f_l1_l2.o: src/f_l1_l2.cpp src/f_l1_l2.h
	$(call compile_obj_file,f_l1_l2)
build/m_l1_l2.exe: build/f_l1_l2.o src/m_l1_l2.cpp src/DoNotOptimize.hpp
	$(call compile_exe_file,m_l1_l2, -I/src build/f_l1_l2.o)
docs/m_l1_l2.png: python/m_l1_l2.py build/m_l1_l2.txt
	$(call run_python,m_l1_l2)
m_l1_l2: build/m_l1_l2.txt build/m_l1_l2.exe docs/m_l1_l2.png

build/m_l1_l2_detail.txt: build/m_l1_l2_detail.exe
	$(call exec_file,m_l1_l2_detail)
build/m_l1_l2_detail.exe: build/f_l1_l2.o src/m_l1_l2_detail.cpp src/DoNotOptimize.hpp
	$(call compile_exe_file,m_l1_l2_detail, -I/src build/f_l1_l2.o)
docs/m_l1_l2_detail.png: python/m_l1_l2_detail.py build/m_l1_l2_detail.txt
	$(call run_python,m_l1_l2_detail)
m_l1_l2_detail: build/m_l1_l2_detail.txt build/m_l1_l2_detail.exe docs/m_l1_l2_detail.png
	
	
build/m_cache_lines.txt: build/m_cache_lines.exe
	$(call exec_file,m_cache_lines)
build/m_cache_lines.exe: src/m_cache_lines.cpp src/f_cache_lines.hpp 
	$(call compile_exe_file,m_cache_lines)
docs/m_cache_lines.png: python/m_cache_lines.py build/m_cache_lines.txt
	$(call run_python,m_cache_lines)
m_cache_lines: build/m_cache_lines.txt build/m_cache_lines.exe docs/m_cache_lines.png

build/m_cache_list_vs_vec.txt: build/m_cache_list_vs_vec.exe
	$(call exec_file,m_cache_list_vs_vec)
build/m_cache_list_vs_vec.exe: src/m_cache_list_vs_vec.cpp  src/DoNotOptimize.hpp
	$(call compile_exe_file,m_cache_list_vs_vec)
m_cache_list_vs_vec: build/m_cache_list_vs_vec.txt build/m_cache_list_vs_vec.exe 

build/m_cache_oop_spatial.txt: build/m_cache_oop_spatial.exe
	$(call exec_file,m_cache_oop_spatial)
build/m_cache_oop_spatial.exe: src/m_cache_oop_spatial.cpp  
	$(call compile_exe_file,m_cache_oop_spatial)
docs/m_cache_oop_spatial.png: python/m_cache_oop_spatial.py build/m_cache_oop_spatial.txt
	$(call run_python,m_cache_oop_spatial)
m_cache_oop_spatial: build/m_cache_oop_spatial.txt build/m_cache_oop_spatial.exe docs/m_cache_oop_spatial.png

build/m_cache_oop_temporal.txt: build/m_cache_oop_temporal.exe
	$(call exec_file,m_cache_oop_temporal)
build/m_cache_oop_temporal.exe: src/m_cache_oop_temporal.cpp  
	$(call compile_exe_file,m_cache_oop_temporal)
docs/m_cache_oop_temporal.png: python/m_cache_oop_temporal.py build/m_cache_oop_temporal.txt
	$(call run_python,m_cache_oop_temporal)
m_cache_oop_temporal: build/m_cache_oop_temporal.txt build/m_cache_oop_temporal.exe docs/m_cache_oop_temporal.png


build/m_cache_associativity.txt: build/m_cache_associativity.exe
	$(call exec_file,m_cache_associativity)
docs/m_cache_associativity.png: python/m_cache_associativity.py build/m_cache_associativity.txt
	$(call run_python,m_cache_associativity)
build/m_cache_associativity.exe: build/f_l1_l2.o src/m_cache_associativity.cpp src/DoNotOptimize.hpp
	$(call compile_exe_file,m_cache_associativity, -I/src build/f_l1_l2.o)
m_cache_associativity: build/m_cache_associativity.txt build/m_cache_associativity.exe docs/m_cache_associativity.png


build/m_false_sharing.txt: build/m_false_sharing.exe
	$(call exec_file,m_false_sharing)
build/m_false_sharing.exe: src/m_false_sharing.cpp 
	$(call compile_exe_file,m_false_sharing, -pthread)
m_false_sharing: build/m_false_sharing.txt build/m_false_sharing.exe
		
		
build/m_loop_vect.txt: build/m_loop_vect.exe
	$(call exec_file,m_loop_vect)
build/m_loop_vect.exe: build/f_loop_vect.o src/m_loop_vect.cpp 
	$(call compile_exe_file,m_loop_vect, -I/src build/f_loop_vect.o)
build/f_loop_vect.o: src/f_loop_vect.cpp src/f_loop_vect.h
	$(call compile_obj_file,f_loop_vect)
m_loop_vect: build/m_loop_vect.txt build/m_loop_vect.exe
		


py: docs/m_cache_lines.png
 
webpage:
	$(call replace_and_pandoc,index)
	$(call replace_and_pandoc,alignement)
	$(call replace_and_pandoc,cache_lines)
	$(call replace_and_pandoc,l1_l2)
	$(call replace_and_pandoc,cache_associativity)

    
        
# TODO
.PHONY: build
build: src/m_alignement.exe
