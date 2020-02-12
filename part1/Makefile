all:
	make docker-build
	docker run -it -v "`pwd`":/a4 a4-image bash -c "cd /a4 && make run-test"


run-test:
	make build-local
	- cd build && ./submitted_test_1
	- cd build && ./submitted_test_2 
	- cd build && ./submitted_test_3 
	- cd build && ./submitted_test_4 
	- cd build && ./submitted_test_5 
	- cd build && ./submitted_test_6 
	- cd build && ./submitted_test_7 
	- cd build && ./personal_test_suite



build-local: 
	# - rm -rf build
	- mkdir build
	cd build && cmake .. && make


docker-build:
	docker build . -t a4-image
	