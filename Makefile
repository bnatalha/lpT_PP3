##by @bnatalha.

# - - - - - - - - - - - - - - - - - - - -
# - - ---------- VARIABLES ---------- - -
# - - - - - - - - - - - - - - - - - - - -

# Directories
INC_DIR =include
SRC_DIR =src
OBJ_DIR =build
LIB_DIR =lib

# Compilation flags
#CPPFLAGS += -Wall -ansi -std=c++11 -pedantic -O0
# For debugging
CPPFLAGS += -Wall -ansi -std=c++11 -pedantic -O0 -g -I $(INC_DIR) -I.


# Compilators
CC =g++
AR =ar

# - - - - - - - - - - - - - - - - - - - -
# - - ----------- TARGETS ----------- - -
# - - - - - - - - - - - - - - - - - - - -

# =============== PHONY =================
.PHONY: windows linux init val clean docs
#.PHONY: linux init val clean docs

# Generates the necessary files for this library to run on a (Debian based) linux system
linux: init qlevetudo.so QLT exportar

# Generates the necessary files for this library to run on a windows system with MinGW
windows: init qlevetudo.dll QLT.exe exportar.exe

# Creates the 'build' folder at the current directory if there's no other folder with this name on it.
init:
	mkdir -p lib ;\
	mkdir -p build

# ============ DOCUMENTATION ==============
# Creates the 'docs' folder at the current directory if there's no other folder with this name on it.
# Generates .html documentation via doxygen at the folder 'docs'
docs: Doxyfile
	mkdir -p docs ;\
	doxygen	

# ============== VALGRIND =================
# Runs valgrind with 'build/QLT'
valq:
	valgrind --leak-check=yes build/QLT

# Runs valgrind with 'build/exportar'
vale:
	valgrind --leak-check=yes build/exportar


# LINUX

qlevetudo.so: $(SRC_DIR)/Menu.cpp $(INC_DIR)/CD.h $(INC_DIR)/Salgado.h $(INC_DIR)/Produto.h $(INC_DIR)/header.h
	$(CC) $(CPPFLAGS) -fPIC -c $(SRC_DIR)/Menu.cpp -o $(OBJ_DIR)/Menu.o
	$(CC) -shared -fPIC -o $(LIB_DIR)/$@ $(OBJ_DIR)/Menu.o
	@echo "++++++ [Biblioteca dinâmica para linux criada em $(LIB_DIR)/$@] ++++++"

QLT:
	$(CC) $(CPPFLAGS) $(SRC_DIR)/main.cpp $(LIB_DIR)/qlevetudo.so -o $(OBJ_DIR)/$@

exportar:
	$(CC) $(CPPFLAGS) $(SRC_DIR)/exportar.cpp $(LIB_DIR)/qlevetudo.so -o $(OBJ_DIR)/$@ 	



# WINDOWS

qlevetudo.dll: $(SRC_DIR)/Menu.cpp $(INC_DIR)/CD.h $(INC_DIR)/Salgado.h $(INC_DIR)/Produto.h $(INC_DIR)/header.h
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/Menu.cpp -o $(OBJ_DIR)/Menu.o
	$(CC) -shared -o $(LIB_DIR)/$@ $(OBJ_DIR)/Menu.o
	@echo "+++ [Biblioteca dinamica para windows criada em $(LIB_DIR)/$@] +++"

QLT.exe:
	$(CC) $(CPPFLAGS) $(SRC_DIR)/main.cpp $(LIB_DIR)/qlevetudo.dll -o $(OBJ_DIR)/$@ 	

exportar.exe:
	$(CC) $(CPPFLAGS) $(SRC_DIR)/exportar.cpp $(LIB_DIR)/qlevetudo.dll -o $(OBJ_DIR)/$@ 	


# ================ CLEANER ================
# Removes objects
clean:
	@echo "Removendo arquivos objeto e executaveis/binarios..."
	@rm -rf $(OBJ_DIR)/*