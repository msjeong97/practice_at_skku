all:
	flex minicp.l
	bison -d minicp.y
	gcc lex.yy.c minicp.tab.c cfg.c -o cfg -lfl -g

clean:
	rm -rf lex.yy.c minicp.tab.c minicp.tab.h cfg
