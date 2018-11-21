compile: bell.c parser.c builtins.c bell.h
	gcc bell.c parser.c builtins.c bell.h -o bell

debug: bell.c parser.c builtins.c bell.h
	gcc bell.c parser.c builtins.c bell.h -o bell -g

