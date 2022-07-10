BIN=./darr_test
CFLAGS+=-g -Wall -pedantic -std=c99
SRCS=test.c ../darr.c
HEADERS=../darr.h

all: ${SRCS} ${HEADERS}
	@gcc ${SRCS} -o ${BIN} ${CFLAGS}

test: all
	@echo ""
	@echo "Running tests normally..."
	${BIN} 1>/dev/null || (echo "Test failed: program crashed!"; exit 1)
	@echo "...normal tests successfull!"
	@echo ""
	@echo "Running tests in valgrind to check for memory leaks"
	valgrind --leak-check=full ${BIN} 1>/dev/null || (echo "Test failed: memory leaked!!"; exit 1)
	@echo "... no memory leaks found!"
	@echo ""
	@echo "All tests were succesfull!"
	@echo ""
	
	
