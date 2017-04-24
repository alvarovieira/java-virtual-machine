PROG_NAME = jvm
PROG_OBJ = $(OBJ_DIR)/$(PROG_NAME).o
PROG_BIN = $(BIN_DIR)/$(PROG_NAME)
PROG_SRC = $(SRC_DIR)/$(PROG_NAME).c

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BIN_DIR = bin
OBJ_DIR = $(SRC_DIR)/obj

GCC = @gcc -g -Wall -I include
RM = @rm -rf
MKDIR = @mkdir -p

LIBS_OBJS = $(patsubst $(INCLUDE_DIR)/%.h, $(OBJ_DIR)/%.o, $(wildcard $(INCLUDE_DIR)/*.h))

all : clean $(PROG_BIN)

run : clean all
	@echo -n Running the program.....
	@echo OK
	@echo
	@./$(PROG_BIN)

test:
	@echo Em desenvolvimento

clean :
	@echo -n Cleaning older objects and binaries.....
	$(RM) $(OBJ_DIR)
	$(RM) $(BIN_DIR)
	@echo OK

$(OBJ_DIR)/%.o :
	$(eval LIB_NAME := $(patsubst $(OBJ_DIR)/%.o, %, $@))
	@echo -n Compiling library: $(LIB_NAME).h.....
	$(MKDIR) $(OBJ_DIR)
	$(GCC) -o $(OBJ_DIR)/$(LIB_NAME).o -c $(LIB_DIR)/$(LIB_NAME).c
	@echo OK

$(PROG_OBJ) :
	@echo -n Compiling program source.....
	$(MKDIR) $(OBJ_DIR)
	$(GCC) -o $(PROG_OBJ) -c $(PROG_SRC)
	@echo OK

$(PROG_BIN) : $(PROG_OBJ) $(LIBS_OBJS)
	@echo -n Generating program executable.....
	$(MKDIR) $(BIN_DIR)
	$(GCC) -o $(PROG_BIN) $(PROG_OBJ) $(LIBS_OBJS)
	@echo OK