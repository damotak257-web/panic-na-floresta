# Nome do executável
EE_BIN = panic_forest_ps2.elf

# Arquivos de objeto
EE_OBJS = src/main.o src/panic_forest.o 

# Incluir o Makefile do Tyra Engine
# (Assumindo que o projeto está dentro da pasta de exemplos do Tyra)
include $(TYRA)/scripts/Makefile.common
include $(TYRA)/scripts/Makefile.pref

# Regras de compilação
all: $(EE_BIN)

clean:
	rm -f $(EE_OBJS) $(EE_BIN)
