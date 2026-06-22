EE_BIN = panic_forest_ps2.elf

EE_OBJS = main.o panic_forest.o

EE_LIBS = -ltyra



all: $(EE_BIN)



clean:

	rm -f $(EE_BIN) $(EE_OBJS)



include $(TYRA)/scripts/Makefile.pref

include $(TYRA)/scripts/Makefile.eeglobal



