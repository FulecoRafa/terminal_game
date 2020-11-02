build: io src semaphore
	echo $^
	make -C io
	make -C src
	make -C semaphore
