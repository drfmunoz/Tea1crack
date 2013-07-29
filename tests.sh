#/bin/sh!
# execute several test to asses te tabu search
# always test a max of 4000 iterations
./ts_full_test  -i data/prob1\ set1.txt -o results/prob1_set1.data -maxtstl 31 -maxtsiter 4000 -maxtsmdec 128 -itstl 10 -itsiter 1000 -itsmdec 64 -vartstl 5 -vartsiter 1000 -vartsmdec 64 -mintskep 10 -vartskep 20
./ts_full_test  -i data/prob1\ set2.txt -o results/prob1_set2.data -maxtstl 31 -maxtsiter 4000 -maxtsmdec 128 -itstl 10 -itsiter 1000 -itsmdec 64 -vartstl 5 -vartsiter 1000 -vartsmdec 64 -mintskep 10 -vartskep 20
./ts_full_test  -i data/prob1\ set3.txt -o results/prob1_set3.data -maxtstl 31 -maxtsiter 4000 -maxtsmdec 128 -itstl 10 -itsiter 1000 -itsmdec 64 -vartstl 5 -vartsiter 1000 -vartsmdec 64 -mintskep 10 -vartskep 20
./ts_full_test  -i data/1000generate.data -o results/1000gen.data -maxtstl 31 -maxtsiter 4000 -maxtsmdec 128 -itstl 10 -itsiter 1000 -itsmdec 64 -vartstl 5 -vartsiter 1000 -vartsmdec 64 -mintskep 10 -vartskep 20
./ts_full_test  -i data/2000generate.data -o results/2000gen.data -maxtstl 31 -maxtsiter 4000 -maxtsmdec 128 -itstl 10 -itsiter 1000 -itsmdec 64 -vartstl 5 -vartsiter 1000 -vartsmdec 64 -mintskep 10 -vartskep 20
./ts_full_test  -i data/3000generate.data -o results/3000gen.data -maxtstl 31 -maxtsiter 4000 -maxtsmdec 128 -itstl 10 -itsiter 1000 -itsmdec 64 -vartstl 5 -vartsiter 1000 -vartsmdec 64 -mintskep 10 -vartskep 20
./ts_full_test  -i data/4000generate.data -o results/4000gen.data -maxtstl 31 -maxtsiter 4000 -maxtsmdec 128 -itstl 10 -itsiter 1000 -itsmdec 64 -vartstl 5 -vartsiter 1000 -vartsmdec 64 -mintskep 10 -vartskep 20
./ts_full_test  -i data/5000generate.data -o results/5000gen.data -maxtstl 31 -maxtsiter 4000 -maxtsmdec 128 -itstl 10 -itsiter 1000 -itsmdec 64 -vartstl 5 -vartsiter 1000 -vartsmdec 64 -mintskep 10 -vartskep 20
