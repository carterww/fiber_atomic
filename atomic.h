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
#if defined(__GNUC__) || defined(__clang__)
#include "atomic_gcc_clang.h"
#else
#error "Unsupported platform. fiber_atomic only supports atomic ops using GCC and Clang extensions."
#endif

#endif /* FIBER_ATOMIC_H */
