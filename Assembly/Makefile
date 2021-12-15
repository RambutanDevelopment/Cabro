TARGET_EXEC = Assembly
CC = gcc
LD = ld

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ = $(SRC:.c=.o) 
ASM = $(SRC:.c=.S)
BIN = bin

INC_DIR_SRC = -Isrc
INC_DIR_LIB =

DEBUGFLAGS = $(INC_DIR_SRC) $(INC_DIR_LIB)
RELEASEFLAGS = $(INC_DIR_SRC) $(INC_DIR_LIB) -O3
ASMFLAGS = $(INC_DIR_SRC) $(INC_DIR_LIBS) -Wall
LDFLAGS = -e main -ffreestanding -shared -nostdlib 

.PHONY: all libs clean

all: clean cleanassembly dirs libs link

dirs:
	mkdir -p ./$(BIN)

link: $(OBJ)
	@echo 'Building target executable:' $(TARGET_EXEC)
	@echo 'Invoking: GCC C++ Linker'
	$(LD) -o $(BIN)/$(TARGET_EXEC) $^ $(LDFLAGS)
	@echo 'Finished building target executable:' $(TARGET_EXEC)
	@echo ' '

asm: cleanassembly $(ASM)

%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) -o $@ -c $< $(DEBUGFLAGS)
	@echo 'Finished building: $<'
	@echo ' '

%.o: %.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) -o $@ -c $< $(ASMFLAGS)
	@echo 'Finished building: $<'
	@echo ' '

%.S: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@echo 'Building ASM'
	$(CC) -S -O0 -o $@ -c $< $(DEBUGFLAGS)
	@echo 'Finished building: $<'
	@echo ' '

build: dirs cleanassembly link

run:
	@echo 'Running executable: '$(TARGET_EXEC)
	./$(BIN)/$(TARGET_EXEC);
	@echo 'Finished running executable: '$(TARGET_EXEC)
	@echo ' '

clean:
	clear
	rm -rf $(BIN) $(OBJ)

cleanassembly:
	rm -rf $(ASM)

