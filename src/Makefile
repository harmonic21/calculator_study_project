CC=g++
FLAGS=-Wall -Wextra -Werror -g --std=c++17 -pedantic
GCOV=-coverage
UNAME := $(shell uname)
TEST_FLAGS=-lgtest -lpthread

#SRCS
SRC_CFILES=calculation_controller.cc calculate_model.cc equation_member.cc string_transformer.cc validator.cc
SRC_TEST=s21_test.cc

SOURCES=./SmartCalc/Qcustomplot/qcustomplot.cpp \
        ./view/main.cc \
        ./view/main_window.cc \
        ./view/graph.cc \
        ./controller/calculation_controller.cc \
        ./model/calculate_model.cc \
        ./model/equation_member.cc \
        ./model/string_transformer.cc \
        ./model/validator.cc \

HEADERS=./SmartCalc/Qcustomplot/qcustomplot.h \
        ./view/main_window.h \
        ./view/graph.h \
        ./controller/calculation_controller.h \
        ./model/calculate_model.h \
        ./model/equation_member.h \
        ./model/string_transformer.h \
        ./model/utility.h \
        ./model/validator.h \


#OBJECTS
OBJ=$(notdir $(SRC_CFILES:.cc=.o))
OBJ_TEST=$(notdir $(SRC_TEST:.cc=.o))

#DIRECTORY
OBJ_DIR=objects
SRC_DIR=./SmartCalc ./model ./view ./controller
TEST_DIR=s21_test
BD=./build/

#INCLUDES
INCLUDE=validator.h \
        utility.h \
        string_transformer.h \
        equation_member.h \
        calculate_model.h \
        calculation_controller.h \
        graph.h \
        main_window.h \

vpath %.cc $(SRC_DIR) $(TEST_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(SRC_DIR)

.PHONY: all clean test gcov_report build install uninstall div

all: build

build: $(BD)SmartCalc.pro
	cd $(BD); qmake SmartCalc.pro
	make -C $(BD)

./$(BD)SmartCalc.pro:
	@mkdir -p ./build/  2>/dev/null
	cp SmartCalc.pro $(BD)

install: build
	@mkdir -p ./Applications/  2>/dev/null
	cp -rf $(BD)SmartCalc ./Applications/
	make clean

uninstall:
	rm -rf ./Applications

dvi:
	latex ./Documentation/SmartCalc.tex
	mv ./SmartCalc.dvi ./Documentation
	rm -rf ./SmartCalc.aux ./SmartCalc.log
	open ./Documentation/SmartCalc.dvi

dist: install dvi
	tar -cvf SmartCalc.tar Documentation/SmartCalc.dvi ./Applications/SmartCalc
	gzip SmartCalc.tar

%.o: %.cc $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) -c $<

tests: $(OBJ_TEST) $(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ) $(OBJ_TEST)) $(TEST_FLAGS) -o test
	./test

valgrind: tests
	valgrind --leak-check=full ./test

clean:
	rm -rf $(OBJ_DIR) report test gcov_report.info ./$(BD)* ./$(BD).qmake.stash ./$(BD).qm

fclean: clean uninstall
	rm ./Documentation/SmartCalc.dvi SmartCalc.tar.gz
