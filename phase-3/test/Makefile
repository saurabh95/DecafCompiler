build:
	bison -d parser.yy; \
	flex scanner.l; \
	g++ -lfl -o compiler lex.yy.c parser.tab.cc `llvm-config --libs core jit native --cxxflags` `llvm-config --ldflags`;
