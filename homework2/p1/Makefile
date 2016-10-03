all: build_gui build_cmd

build_gui:
	make -C gui
	ln -s gui/build ./build_gui

build_cmd:
	make -C cmd
	ln -s cmd/build ./build_cmd

clean:
	@rm -rf build_gui
	@rm -rf build_cmd
	make -C gui clean
	make -C cmd clean
