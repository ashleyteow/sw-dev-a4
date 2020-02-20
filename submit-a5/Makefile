build:
	g++ -std=c++11 -pthread Bench.cpp -o main


run:
	docker build . -t a5-test
	wget https://raw.githubusercontent.com/ashleyteow/sw-dev-a4/a5/part1/datafile.txt.zip
	unzip datafile.txt.zip
	python3 simple_test.py

clean:
	- rm main
	- rm -rf __pycache__
	- rm datafile.txt*
