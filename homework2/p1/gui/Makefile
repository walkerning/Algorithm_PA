QMAKEFILE=qmakefile
EXE_DIR=build/debug/main_gui.app/Contents/MacOS
EXE_FILE=$(EXE_DIR)/main_gui

all: $(QMAKEFILE)
	make -f $(QMAKEFILE)
	@# for mac OS X only
	@for lib in `otool -L $(EXE_FILE) | tail -n +2 | awk '{print $$1}'`; do	\
		echo "copy dylib:" $${lib}; \
		cp $${lib} $(EXE_DIR)/				;\
		install_name_tool -change $${lib} @loader_path/`basename $${lib}` $(EXE_FILE) ;\
	done;	\

$(QMAKEFILE):
	qmake main_gui.pro -o $(QMAKEFILE)

clean: $(QMAKEFILE)
	@make -f $(QMAKEFILE) clean
	rm $(QMAKEFILE)
	rm -rf build/
