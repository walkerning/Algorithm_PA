QMAKEFILE=qmakefile

all: $(QMAKEFILE)
	make -f $(QMAKEFILE)

$(QMAKEFILE):
	qmake main_gui.pro -o $(QMAKEFILE)

clean: $(QMAKEFILE)
	@make -f $(QMAKEFILE) clean
	rm $(QMAKEFILE)
	rm -rf build/
