install:
	mkdir -p /usr/local/include/generator_utils_src/
	cp src/*.hpp /usr/local/include/generator_utils_src/
	cp src/generator_utils /usr/local/include/

clean:
	rm -rf /usr/local/include/generator_utils_src
	rm /usr/local/include/generator_utils
