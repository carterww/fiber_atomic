/* See LICENSE file for copyright and license details. */

#ifndef FIBER_ATOMIC_H
#define FIBER_ATOMIC_H

/* The implementation should define an enum with the possible values of the "memorder"
 * parameter.
 * - FIBER_ATOMIC_RELAXED: No inter-thread constraints. Only guarantees the
 *   operation is atomic, no guarantees about ordering.
 * - FIBER_ATOMIC_ACQUIRE: Ensures all memory operations declared after actually
 *   occur after the load. It should prevent hoisting code before the
 *   load. It should create an inter-thread happens-before constraint from a RELEASE
 *   (or stronger) store.
 * - FIBER_ATOMIC_RELEASE: Ensures all memory operations declared before actually
 *   occur before the store. It should prevent sinking code after the store. It should
 *   create an inter-thread happens-before constraint from an ACQUIRE (or stronger)
 *   load.
 * - FIBER_ATOMIC_ACQ_REL: Combined ACQUIRE and RELEASE memory ordering. Useful for
 *   RMW operations like atomic_fetch_add.
 * - FIBER_ATOMIC_SEQ_CST: Enforces total ordering with other SEQ_CST atomic operations.
 *   This is useful, for example, when you must store some variable before loading a
 *   another variable.
 * If you are implementing this interface and need more details on the expected
 * behavior of each value, please see how GCC describes them:
 * https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
 */

/* The implementation must also define a set of operations. These operations should
 * be implemented as macros to support generic atomic operations. Please note that
 * any parameter with "ptr" in its name is a nonnull pointer.
 * - fiber_atomic_memory_barrier(memorder): Memory barrier.
 * - fiber_atomic_load(ptr, memorder): Loads the value from ptr and returns it. 
 * - fiber_atomic_load_into(ptr, dest_ptr, memorder): Loads the value from ptr into
 *   dest_ptr.
 * - fiber_atomic_store(ptr, val, memorder): Stores the value val in ptr.
 * - fiber_atomic_store_from(ptr, src_ptr, memorder): Stores the value from src_ptr
 *   in ptr.
 * - fiber_atomic_exchange(ptr, val, memorder): Stores the value val in ptr and returns
 *   ptr's previous value.
 * - fiber_atomic_exchange_into(ptr, src_ptr, res_ptr, memorder): Stores src_ptr's value
 *   in ptr and places ptr's previous value in res_ptr.
 * - fiber_atomic_cmp_xchng(ptr, expected_ptr, desired_val, is_weak, success_memorder,
 *   failure_memorder): Checks if ptr's value equals expected_ptr's value. If so,
 *   desired_val is placed in ptr and a nonzero value is returned. If not, ptr's value
 *   is written to expected_ptr and 0 is returned. is_weak should be 0 to perform a
 *   strong cmp_xchng (doesn't fail spuriously).
 * - fiber_atomic_cmp_xchng_from(ptr, expected_ptr, desired_ptr, is_weak, success_memorder,
 *   failure_memorder): Same behavior as fiber_atomic_cmp_xchng except disired_ptr holds
 *   the desired value.
 * - fiber_atomic_[OP]_fetch(ptr, val, memorder): Performs OP on ptr's value with val and
 *   returns the result. OP can be add, sub, and, xor, or.
 * - fiber_atomic_fetch_OP(ptr, val, memorder): Performs OP on ptr's value with val and
 *   returns ptr's previous value. OP can be add, sub, and, xor, or.
 * - fiber_atomic_inc_fetch(ptr, memorder): Increments ptr's value and returns the result.
 * - fiber_atomic_dec_fetch(ptr, memorder): Decrements ptr's value and returns the result.
 * - fiber_atomic_fetch_inc(ptr, memorder): Increments ptr's value and returns ptr's previous
 *   value.
 * - fiber_atomic_fetch_dec(ptr, memorder): Decrements ptr's value and returns ptr's previous
 *   value.
 */

#if defined(__GNUC__) || defined(FIBER_ATOMIC_OPERATIONS_IMPL_GCC)
#define FIBER_ATOMIC_OPERATIONS_IMPL_GCC
#include "atomic_gcc_clang.h"
#elif defined(__clang__) || defined(FIBER_ATOMIC_OPERATIONS_IMPL_CLANG)
#define FIBER_ATOMIC_OPERATIONS_IMPL_CLANG
#include "atomic_gcc_clang.h"
#else
#error "Unsupported platform. fiber_atomic only supports atomic ops using GCC and Clang extensions."
#endif

#endif /* FIBER_ATOMIC_H */
