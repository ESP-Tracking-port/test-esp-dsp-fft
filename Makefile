PYINTERP=python3

.PHONY: clean build pygen

main: build

signal.h:
	$(PYINTERP) generate.py

build: signal.h
	mkdir -p build && cd build && cmake .. && make -j$(shell nproc)

clean:
	rm -rf build
	rm -f signal.h

