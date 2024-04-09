CC = gcc
LEX = flex
YACC = bison

PARSER_FILE = parser.y
FLEX_FILE = flex.l
RESULT_FILES = lex.yy.c parser.tab.h parser.tab.c ./build/calc

clean:
	rm -f $(RESULT_FILES)

run:
	$(YACC) -d $(PARSER_FILE)
	$(LEX) $(FLEX_FILE)
	$(CC) main.c poly.c lex.yy.c parser.tab.c -lm -o ./build/calc

all: clean run
