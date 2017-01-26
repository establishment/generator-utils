install:
	sudo mkdir -p /usr/local/include/generator_utils_src/
	sudo cp src/*.hpp /usr/local/include/generator_utils_src/
	sudo cp src/generator_utils /usr/local/include/

clean:
	sudo rm -rf /usr/local/include/generator_utils_src
	sudo rm /usr/local/include/generator_utils
