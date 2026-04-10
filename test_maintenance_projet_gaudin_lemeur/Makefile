#####################################################
CC=gcc # compilateur
CFLAGS=-W -Wall -g -Iincludes/ # warnings
EXTRA_CFLAGS=-fprofile-arcs -ftest-coverage # utile pour calculer la couverture de code
EXTRA_LDFLAGS= --coverage# edition de liens avec couverture de code

#### Variables liées à la compilation des sources
OBJ=build/struct.o 
EXEC=build/tri_comp
DIR=couverture

#### Variables liées à la compilation des tests unitaires
TEST_SRC=tests/unit_tests.c
TEST_OBJ=build/unit_tests.o
TEST_EXEC=build/tri_tests
TEST_LDFLAGS= -lcheck -lpthread -lm
TEST_OS_DEP_LFLAGS=

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	TEST_OS_DEP_LFLAGS=-lsubunit -lrt
endif
#####################################################

all: main tests

########### Compilation du code principal ###########
main: $(EXEC)

$(EXEC): build/main.o $(OBJ)
	$(CC) $^ $(EXTRA_LDFLAGS) -o $(EXEC)

build/main.o: src/main.c includes/struct.h
	$(CC) $(CFLAGS) -c $< -o $@

build/struct.o: src/struct.c includes/struct.h
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

#####################################################



########### Compilation du code de test ###########
tests: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ) $(OBJ)
	$(CC) $(OBJ) $(TEST_OBJ) $(TEST_LDFLAGS) $(EXTRA_LDFLAGS) $(TEST_OS_DEP_LFLAGS) -o $(TEST_EXEC)

$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)
#####################################################



#################### Nettoyage #####################
clean:
	@rm -rf build/*.o build/*.gc* *.gcov src/*.dump

mrproper: clean
	@rm -rf $(TEST_EXEC)

coverage:
	gcov -f -b $(OBJ)
	lcov --directory build --base-directory . -c -o $(DIR)/cov.info
	genhtml $(DIR)/cov.info -o $(DIR)/coverage_report
#####################################################
