CC = gcc
LEX = flex
YACC = bison
MOVE = mv

PARSER_FILE = parser.y
FLEX_FILE = flex.l
RESULT_FILES = ./build/lex.yy.c ./build/parser.tab.h ./build/parser.tab.c ./build/logs.txt ./build/calc

log:
	$(YACC) -d $(PARSER_FILE) -Wcounterexamples 2> logs.txt
	$(MOVE) parser.tab.h ./build
	$(MOVE) parser.tab.c ./build
	$(MOVE) logs.txt ./build

clean:
	rm -f $(RESULT_FILES)

run:
	$(YACC) -d $(PARSER_FILE)
	$(LEX) $(FLEX_FILE)
	$(MOVE) lex.yy.c ./build
	$(MOVE) parser.tab.h ./build
	$(MOVE) parser.tab.c ./build
	$(CC) main.c poly.c ./build/lex.yy.c ./build/parser.tab.c -I . -I ./build/ -lm -o ./build/calc

all: clean run
