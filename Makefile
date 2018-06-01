notebook:
	make program -C 'src'
	cp src/program notebook

clean:
	make clean -C 'src'
	rm notebook
