CC=gcc
FLAGS=-g -Wall -Wextra -Werror -std=c11 -pedantic
CFLAGS=-c $(FLAGS)
TEST_FLAGS=-lcheck -lgcov -lm -lrt -lpthread -lsubunit

#SRCS
SRC_CFILES=CalculationController.cc CalculateModel.cc EquationMember.cc StringTransformer.cc Validator.cc
SRC_TEST=s21_test.c

SOURCES=./SmartCalc/Qcustomplot/qcustomplot.cpp \
        ./view/main.cc \
        ./view/MainWindow.cc \
        ./controller/calculation_controller.cc \
        ./model/CalculateModel.cc \
        ./model/EquationMember.cc \
        ./model/StringTransformer.cc \
        ./model/Validator.cc \

HEADERS=./SmartCalc/Qcustomplot/qcustomplot.h \
        ./view/MainWindow.h \
        ./controller/calculation_controller.h \
        ./model/CalculateModel.h \
        ./model/EquationMember.h \
        ./model/StringTransformer.h \
        ./model/Utility.h \
        ./model/Validator.h \


#OBJECTS
OBJ=$(notdir $(SRC_CFILES:.c=.o))
OBJ_TEST=$(notdir $(SRC_TEST:.c=.o))

#DIRECTORY
OBJ_DIR=objects
SRC_DIR=./SmartCalc ./model ./view ./controller
TEST_DIR=s21_test
BD=../build/

#INCLUDES
INCLUDE=Validator.h \
        Utility.h \
        StringTransformer.h \
        CalculateModel.h \
        CalculationController.h \
        

vpath %.cc $(SRC_DIR) $(TEST_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(SRC_DIR)

.PHONY: all clean test gcov_report build install uninstall div

all: build

build: $(BD)SmartCalc.pro
	cd $(BD); qmake SmartCalc.pro
	make -C $(BD)

./$(BD)SmartCalc.pro:
	@mkdir -p ../build/  2>/dev/null
	cp SmartCalc.pro $(BD)

./$(BD)%.o: */*/%.cpp
	g++ -C $< -o $@

install: build
	@mkdir -p ../Applications/  2>/dev/null
	cp -rf $(BD)SmartCalc ../Applications/
	make clean

uninstall:
	rm -rf ../Applications

dvi:
	latex ./Documentation/SmartCalc.tex
	mv ./SmartCalc.dvi ./Documentation
	rm -rf ./SmartCalc.aux ./SmartCalc.log

dist: install dvi
	tar -cvf SmartCalc.tar Documentation/SmartCalc.dvi ../Applications/SmartCalc
	gzip SmartCalc.tar

%.o: %.cc $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) -c $<

tests: $(OBJ_TEST) $(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ) $(OBJ_TEST)) $(TEST_FLAGS) -o test
	./test

gcov_report:CFLAGS += -coverage
gcov_report: clean tests
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;

valgrind: tests
	valgrind --leak-check=full ./test

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ./SmartCalc/*.c ./$(TEST_DIR)/*.c ./SmartCalc/s21_collection/*.c \
	./SmartCalc/s21_polish_notation/*.c ./SmartCalc/s21_calculations/*.c

clean:
	rm -rf $(OBJ_DIR) report test gcov_report.info ./$(BD)* ./$(BD).qmake.stash ./$(BD).qm

fclean: clean uninstall
	rm ./Documentation/SmartCalc.dvi SmartCalc.tar.gz
