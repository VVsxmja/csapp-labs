all: data-lab

mkdir: 
	mkdir -p results

data-lab: data-lab-check data-lab-test

data-lab-check: clean mkdir
	cd data-lab && chmod +x ./dlc && ./dlc bits.c > ../results/data-lab-check.txt && cat ../results/data-lab-check.txt

data-lab-test: clean mkdir
	cd data-lab && make clean && make && ./btest > ../results/data-lab-test.txt && cat ../results/data-lab-test.txt

clean:
	rm -rf results
	cd data-lab && make clean