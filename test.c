#include <stdio.h>
#include <stdlib.h>

#include "atomic.h"

#define ASSERT(expr)                                                      \
	do {                                                              \
		if (!(expr)) {                                            \
			fprintf(stderr, "[%s:%d]: Assertion failed %s\n", \
				__FILE__, __LINE__, #expr);               \
			exit(1);                                          \
		}                                                         \
	} while (0)

void test_memory_barrier()
{
	/* Ensure that is is defined */
	fiber_atomic_memory_barrier(FIBER_ATOMIC_RELAXED);
}

void test_load()
{
	int x;
	int x_dest;

	x = 10;

	ASSERT(10 == fiber_atomic_load(&x, FIBER_ATOMIC_RELAXED));

	fiber_atomic_load_into(&x, &x_dest, FIBER_ATOMIC_RELAXED);

	ASSERT(x == x_dest);
}

void test_store()
{
	int x;
	int y;

	y = 20;

	fiber_atomic_store(&x, 10, FIBER_ATOMIC_RELAXED);
	ASSERT(x == 10);

	fiber_atomic_store_from(&x, &y, FIBER_ATOMIC_RELAXED);
	ASSERT(x == y);
}

void test_exchange()
{
	int x;
	int y;
	int dest;

	x = 5;
	y = 20;

	ASSERT(5 == fiber_atomic_exchange(&x, 10, FIBER_ATOMIC_RELAXED));

	x = 5;
	fiber_atomic_exchange_into(&x, &y, &dest, FIBER_ATOMIC_RELAXED);
	ASSERT(dest == 5);
	ASSERT(x == y);
}

void test_cmp_xchng_success()
{
	int x;
	int x_expected;
	int x_desired;
	int success;

	x = x_expected = 10;
	success = fiber_atomic_cmp_xchng(&x, &x_expected, 20, 0,
					 FIBER_ATOMIC_RELAXED,
					 FIBER_ATOMIC_RELAXED);
	ASSERT(success);
	ASSERT(x == 20);

	x = x_expected = 10;
	x_desired = x + 1;
	success = fiber_atomic_cmp_xchng_from(&x, &x_expected, &x_desired, 0,
					      FIBER_ATOMIC_RELAXED,
					      FIBER_ATOMIC_RELAXED);
	ASSERT(success);
	ASSERT(x == x_desired);
}

void test_cmp_xchng_failure()
{
	int x;
	int x_expected;
	int x_desired;
	int success;

	x = 10;
	x_expected = 50;

	success = fiber_atomic_cmp_xchng(&x, &x_expected, 20, 0,
					 FIBER_ATOMIC_RELAXED,
					 FIBER_ATOMIC_RELAXED);
	ASSERT(!success);
	ASSERT(x == 10);
	ASSERT(x_expected == x);

	x_expected = 50;
	x_desired = 100;

	success = fiber_atomic_cmp_xchng_from(&x, &x_expected, &x_desired, 0,
					      FIBER_ATOMIC_RELAXED,
					      FIBER_ATOMIC_RELAXED);
	ASSERT(!success);
	ASSERT(x == 10);
	ASSERT(x_expected == x);
	ASSERT(x_desired == 100);
}

#define test_atomic_fetch(start_val, op_val, expected_val, macro_op_fetch, \
			  macro_fetch_op)                                  \
	do {                                                               \
		int x;                                                     \
		int new_x;                                                 \
		int old_x;                                                 \
                                                                           \
		x = start_val;                                             \
		new_x = macro_op_fetch(&x, op_val, FIBER_ATOMIC_RELAXED);  \
		ASSERT(new_x == x);                                        \
		ASSERT(x == expected_val);                                 \
                                                                           \
		x = start_val;                                             \
		old_x = macro_fetch_op(&x, op_val, FIBER_ATOMIC_RELAXED);  \
		ASSERT(old_x == start_val);                                \
		ASSERT(x == expected_val);                                 \
	} while (0)

void test_add()
{
	int x;
	int new_x;
	int old_x;

	test_atomic_fetch(0, 10, 10, fiber_atomic_add_fetch,
			  fiber_atomic_fetch_add);

	x = 0;
	new_x = fiber_atomic_inc_fetch(&x, FIBER_ATOMIC_RELAXED);
	ASSERT(new_x == x);
	ASSERT(x == 1);

	x = 0;
	old_x = fiber_atomic_fetch_inc(&x, FIBER_ATOMIC_RELAXED);
	ASSERT(old_x == 0);
	ASSERT(x == 1);
}

void test_sub()
{
	int x;
	int new_x;
	int old_x;

	test_atomic_fetch(0, 10, -10, fiber_atomic_sub_fetch,
			  fiber_atomic_fetch_sub);

	x = 0;
	new_x = fiber_atomic_dec_fetch(&x, FIBER_ATOMIC_RELAXED);
	ASSERT(new_x == x);
	ASSERT(x == -1);

	x = 0;
	old_x = fiber_atomic_fetch_dec(&x, FIBER_ATOMIC_RELAXED);
	ASSERT(old_x == 0);
	ASSERT(x == -1);
}

void test_and()
{
	test_atomic_fetch(0b1111, 0b0001, 0b0001, fiber_atomic_and_fetch,
			  fiber_atomic_fetch_and);
	test_atomic_fetch(0, 0b1111, 0, fiber_atomic_and_fetch,
			  fiber_atomic_fetch_and);
	test_atomic_fetch(0b1111, 0b1111, 0b1111, fiber_atomic_and_fetch,
			  fiber_atomic_fetch_and);
}

void test_xor()
{
	test_atomic_fetch(0b1, 0b1, 0b0, fiber_atomic_xor_fetch,
			  fiber_atomic_fetch_xor);
	test_atomic_fetch(0b0, 0b1, 0b1, fiber_atomic_xor_fetch,
			  fiber_atomic_fetch_xor);
}

void test_or()
{
	test_atomic_fetch(0b10, 0b01, 0b11, fiber_atomic_or_fetch,
			  fiber_atomic_fetch_or);
	test_atomic_fetch(0, 0, 0, fiber_atomic_or_fetch,
			  fiber_atomic_fetch_or);
}

int main(void)
{
	test_memory_barrier();
	test_load();
	test_store();
	test_exchange();
	test_cmp_xchng_success();
	test_cmp_xchng_failure();
	test_add();
	test_sub();
	test_and();
	test_xor();
        test_or();
	return 0;
}
