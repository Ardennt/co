#compiler flags:
# -Wall turns on most compiler warnings
# -g adds debugging information to the executable files
CFLAGS = -g -Wall -fno-inline -fno-omit-frame-pointer

#the build target executable
PROGRAM = main.c
OBJFILES = read.o print.o alloc.o mult.o main.o
INCLUDES:= -Iinclude

all: $(PROGRAM)
$(PROGRAM): $(OBJFILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(PROGRAMS) $(OBJFILES) -lm

%.o: %.c
	$CC -C $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	$(RM) $(OBJFILES) $(PROGRAM)