CC = gcc
CFLAGS = -Wall -g -fopenmp
LDFLAGS = -lm -fopenmp
SRC = main.c scene.c ppm.c
OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)
EXEC = myprogram

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

-include $(DEPS)

clean:
	rm -f $(OBJ) $(EXEC) $(DEPS)
