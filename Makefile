CC = g++
CCFLAGS = -g -W -Wall
CCLIBS = -lstdc++fs

FLEX = flex
FLEX_OPTS = -PInstant

BISON = bison
BISON_OPTS = -t -pInstant

OBJS = Absyn.o Lexer.o Parser.o
JVM_OBJS = JVMInstructionsVisitor.o JVMPreprocessingVisitor.o

.PHONY: clean distclean

all: insc_llvm insc_jvm

clean:
	rm -f *.o insc_llvm insc_jvm
	cd src/
	rm -f Instant.aux Instant.log Instant.pdf Instant.dvi Instant.ps Instant

distclean: clean
	rm -f Makefile
	cd src/
	rm -f Instant.l Instant.y Instant.tex insc_llvm.cpp insc_jvm.cpp
	rm -f Absyn.cpp Parser.cpp Lexer.cpp JVMInstructionsVisitor.cpp JVMPreprocessingVisitor.cpp Printer.cpp
	rm -f Absyn.h Parser.h JVMInstructionsVisitor.h JVMPreprocessingVisitor.h CompilerOutput.h JVMVariables.h Printer.h Utils.h

insc_llvm: ${OBJS} insc_llvm.o
	@echo "Linking insc_llvm..."
	${CC} ${CCFLAGS} ${OBJS} insc_llvm.o -o insc_llvm ${CCLIBS}

insc_jvm: ${OBJS} ${JVM_OBJS} insc_jvm.o
	@echo "Linking insc_jvm..."
	${CC} ${CCFLAGS} ${OBJS} ${JVM_OBJS} insc_jvm.o -o insc_jvm ${CCLIBS}

Absyn.o: src/Absyn.cpp src/Absyn.h
	${CC} ${CCFLAGS} -c src/Absyn.cpp

src/Lexer.cpp: src/Instant.l
	${FLEX} -o src/Lexer.cpp src/Instant.l

src/Parser.cpp: src/Instant.y
	${BISON} src/Instant.y -o src/Parser.cpp

Lexer.o: src/Lexer.cpp src/Parser.h
	${CC} ${CCFLAGS} -c src/Lexer.cpp

Parser.o: src/Parser.cpp src/Absyn.h
	${CC} ${CCFLAGS} -c src/Parser.cpp

JVMInstructionsVisitor.o: src/JVMInstructionsVisitor.cpp src/JVMInstructionsVisitor.h src/Absyn.h
	${CC} ${CCFLAGS} -c src/JVMInstructionsVisitor.cpp

JVMPreprocessingVisitor.o: src/JVMPreprocessingVisitor.cpp src/JVMPreprocessingVisitor.h src/Absyn.h
	${CC} ${CCFLAGS} -c src/JVMPreprocessingVisitor.cpp

insc_llvm.o: src/insc_llvm.cpp src/Parser.h src/Absyn.h
	${CC} ${CCFLAGS} -c src/insc_llvm.cpp

insc_jvm.o: src/insc_jvm.cpp src/Parser.h src/Absyn.h
	${CC} ${CCFLAGS} -c src/insc_jvm.cpp

