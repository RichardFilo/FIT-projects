CPPFLAGS = -g -Wall
TESTS = examples/test_block examples/test_block_schema

all: 
	make -C src

run: src/proj
	./src/proj

doxygen: Doxyfile
	$@ $^ 

tests: $(TESTS)

examples/test_block: examples/test_block.cpp src/block.o
	$(CXX) $(CPPFLAGS) -o $@ $^

src/block.o: src/block.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $^

examples/test_block_schema: examples/test_block_schema.cpp src/block_schema.o src/block.o
	$(CXX) $(CPPFLAGS) -o $@ $^

src/block_schema.o: src/block_schema.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $^

clean:
	$(RM) -r $(TESTS) doc/* src/proj
	make -C src clean

pack:
	zip -r 2-xfilor00-xlisic01.zip *
