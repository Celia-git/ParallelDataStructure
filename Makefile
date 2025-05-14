MPICC = mpicc
CFLAGS = -Wall
LIBS = -lstdc++ -lmpi

TESTER_SRC = tester.cpp
TESTER_OBJ = tester.o
TESTER_TARGET = tester

all: $(TESTER_TARGET) 

$(TESTER_TARGET): $(TESTER_OBJ)
	$(MPICC) $(TESTER_OBJ) $(LIBS) -o $(TESTER_TARGET)

$(TESTER_OBJ): $(TESTER_SRC)
	$(MPICC) $(CFLAGS) -c $(TESTER_SRC) -o $(TESTER_OBJ)

clean:
	rm -f $(TESTER_TARGET) $(TESTER_OBJ) 

run: all
	mpirun -np 4 ./$(TESTER_TARGET)

.PHONY: all clean run
