SRCS := $(shell find . -name "*.c")
OBJS := $(SRCS:%.c=%.o)

CFLAGS := -std=c99 -O2 -Wall
LDFLAGS := -lm -ledit

APP := lispy

$(APP): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Alternative command
mylisp:
	$(CC) -std=c99 -O2 -Wall lispy.c mpc.c lenv.c lval.c builtin.c -ledit -lm -o mylisp

.PHONY: clean
clean:
	rm -f $(APP) $(OBJS) mylisp
