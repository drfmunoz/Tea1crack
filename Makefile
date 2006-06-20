CC        = gcc
CFLAGS    = -Wall
LDFLAGS   = 
EXE1      = ts
OBJS      = main.o tabu_search.o tea.o io.o
EXE2	  = test
TEST	  = test.o  tea.o io.o
EXE3	  = generate
GENERATE  = generate.o tea.o io.o
EXE4	  = component_test
COMPONENT = component_test.o tea.o io.o



all : main test gen comp
main : $(OBJS)
		$(CC) $(LDFLAGS) $(OBJS) -o $(EXE1)
test : $(TEST)
		$(CC) $(LDFLAGS) $(TEST) -o $(EXE2)
gen : $(GENERATE)
		$(CC) $(LDFLAGS) $(GENERATE) -o $(EXE3)
comp : $(COMPONENT)
		$(CC) $(LDFLAGS) $(COMPONENT) -o $(EXE4)
%.o : %.c
		$(CC) $(CFLAGS)  -c $<
clean:
		rm -rf *.o *~ $(EXE1) $(EXE2) $(EXE3) $(EXE4)