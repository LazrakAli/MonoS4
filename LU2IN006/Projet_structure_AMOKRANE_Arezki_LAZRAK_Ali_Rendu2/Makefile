all: main_exo1 main_exo3 main_exo5 main_exo7_8 main_exo9

main_exo1:main_exo1.c exo1.c exo2.c
	gcc -Wall -o main_exo1 main_exo1.c exo1.c exo2.c -lm -g

main_exo3: main_exo3.c exo1.c exo2.c exo3.c
	gcc -Wall -o main_exo3 main_exo3.c exo1.c exo2.c exo3.c -lm -g

main_exo5: main_exo5.c exo1.c exo2.c exo3.c exo5.c exo6.c
	gcc -Wall -o main_exo5 main_exo5.c exo1.c exo2.c exo3.c exo5.c exo6.c -lm -g

main_exo7_8: main_exo7_8.c  exo1.c exo2.c exo3.c exo5.c exo6.c exo7.c exo8.c
	gcc -Wall -o main_exo7_8 main_exo7_8.c  exo1.c exo2.c exo3.c exo5.c exo6.c exo7.c exo8.c -lm -lssl -lcrypto -g


main_exo9: main_exo9.c exo1.c exo2.c exo3.c exo5.c exo6.c exo7.c exo8.c exo9.c
			gcc -Wall -o main_exo9 main_exo9.c  exo1.c exo2.c exo3.c exo5.c exo6.c exo7.c exo8.c exo9.c -lm -lssl -lcrypto -g

clean:
	rm -rf main_exo1
	rm -rf main_exo3
	rm -rf main_exo5
	rm -rf candidate.txt
	rm -rf declaration.txt
	rm -rf sortir_modpow.txt
	rm -rf keys.txt
	rm -rf main_exo7_8
	rm -rf main_exo9



