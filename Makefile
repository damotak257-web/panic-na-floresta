# Nome do arquivo final
TARGET = panic_forest.elf

# Arquivos de código
OBJS = main.o panic_forest.o

# Caminhos e ferramentas
EE_CC = ee-gcc
EE_CXX = ee-g++
EE_LD = ee-g++

# Flags de compilação
CFLAGS = -O2 -Wall -I$(PS2SDK)/ee/include -I.
CXXFLAGS = $(CFLAGS)
LDFLAGS = -L$(PS2SDK)/ee/lib -lpatches -lkernel -lc -lm

# Regras
all: $(TARGET)

$(TARGET): $(OBJS)
	$(EE_LD) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(EE_CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(EE_CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
