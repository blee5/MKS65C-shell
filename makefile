compile: bell.c parser.c parser.h
	gcc bell.c parser.c parser.h -o bell -g

test: unittest.c parser.c parser.h
	gcc unittest.c parser.c parser.h -o test -g
