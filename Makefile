CC          = gcc
CFLAGS      = -std=c11 -Wall -Wextra -O2 -D_POSIX_C_SOURCE=200809L
BISON       = bison
BISONFLAGS  = -Wcounterexamples -d
FLEX        = flex

TARGET = prog
SRCS   = main.c ast.c parser.tab.c lex.yy.c code.c typeChecker.c hashTable.c genMIPS.c
OBJS   = $(SRCS:.c=.o)

.PHONY: clean

all: $(TARGET)

parser.tab.c parser.tab.h: parser.y
	$(BISON) $(BISONFLAGS) -o parser.tab.c $<

lex.yy.c: lexer.l parser.tab.h
	$(FLEX) -o $@ $<

main.o: main.c parser.tab.h ast.h code.h hashTable.h typeChecker.h genMIPS.h
ast.o: ast.c ast.h
code.o: code.c code.h ast.h hashTable.h
typeChecker.o: typeChecker.c typeChecker.h ast.h hashTable.h
hashTable.o: hashTable.c hashTable.h
genMIPS.o: genMIPS.c genMIPS.h code.h
parser.tab.o: parser.tab.c ast.h
lex.yy.o: lex.yy.c parser.tab.h

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	rm -f $(OBJS)

clean:
	rm -f $(TARGET) parser.tab.c parser.tab.h lex.yy.c *.o
