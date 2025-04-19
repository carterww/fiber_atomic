C_WARNING_FLAGS = -Werror -Wall -Wextra -Wno-unused -Wfloat-equal \
		  -Wdouble-promotion -Wformat-overflow -Wformat=2 \
		  -Wnull-dereference -Wmissing-include-dirs -Wswitch-default \
		  -Wswitch-enum
C_FLAGS = -I. -std=c89 $(C_OPT_FLAGS) $(C_WARNING_FLAGS)

all: test

test:
	@cc $(C_FLAGS) test.c
	@./a.out
