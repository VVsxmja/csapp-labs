all: data-lab

mkdir: 
	mkdir -p results

data-lab: clean mkdir
	cd data-lab && make clean && make && ./btest > ../results/data-lab.txt

clean:
	rm -rf results
	cd data-lab && make clean