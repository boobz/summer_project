# --------
# Makefile
# --------

# Executable name
EXE = prog.exe

# Directories
SRC_DIR = src
OBJ_DIR = obj
CONF_DIR = configs
PPM_DIR = tests/ppm

# Compiler
CC = g++
# Compiler options
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -W -Wall -Wextra -g # -Werror
# Linker options
LDFLAGS = 

# ----

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


all : tests $(EXE)

.PHONY: tests
tests :
	cd tests ; make

$(EXE) : $(OBJS) obj/graphic.o 
	$(CC) $(LDFLAGS) -o $@ $^

# Create obj directory if needed
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/graphic.o : src/graphic.cpp obj
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean :
	@rm $(OBJS)

.PHONY: cleaner
cleaner : clean
	# The || avoid errors if OBJ_DIR does not exist
	@rmdir "$(OBJ_DIR)" || echo ; \
	rm "$(EXE)"
	
$(PPM_DIR)/tests/%.ppm : $(CONF_DIR)/%.txt
	./$(EXE) $< $@
