/* See LICENSE file for copyright and license details. */

#ifndef _FIBER_ATOMIC_GCC_CLANG
#define _FIBER_ATOMIC_GCC_CLANG

#if !defined(__GNUC__) && !defined(__clang__)
#warning \
	"This file uses compiler extensions that may not be supported by your compiler."
#endif

enum fiber_atomic_memorder {
	FIBER_ATOMIC_RELAXED = __ATOMIC_RELAXED,
	FIBER_ATOMIC_ACQUIRE = __ATOMIC_ACQUIRE,
	FIBER_ATOMIC_RELEASE = __ATOMIC_RELEASE,
	FIBER_ATOMIC_ACQ_REL = __ATOMIC_ACQ_REL,
	FIBER_ATOMIC_SEQ_CST = __ATOMIC_SEQ_CST
};

#define fiber_atomic_memory_barrier(memorder) \
	((void)__atomic_thread_fence(memorder))

#define fiber_atomic_load(ptr, memorder) (__atomic_load_n(ptr, memorder))

#define fiber_atomic_load_into(ptr, dest_ptr, memorder) \
	((void)__atomic_load(ptr, dest_ptr, memorder))

#define fiber_atomic_store(ptr, val, memorder) \
	((void)__atomic_store_n(ptr, val, memorder))

#define fiber_atomic_store_from(ptr, src_ptr, memorder) \
	((void)__atomic_store(ptr, src_ptr, memorder))

#define fiber_atomic_exchange(ptr, val, memorder) \
	(__atomic_exchange_n(ptr, val, memorder))

#define fiber_atomic_exchange_into(ptr, src_ptr, res_ptr, memorder) \
	((void)__atomic_exchange(ptr, src_ptr, res_ptr, memorder))

#define fiber_atomic_cmp_xchng(ptr, expected_ptr, desired_val, is_weak,   \
			       success_memorder, failure_memorder)        \
	((int)__atomic_compare_exchange_n(ptr, expected_ptr, desired_val, \
					  is_weak, success_memorder,      \
					  failure_memorder))

#define fiber_atomic_cmp_xchng_from(ptr, expected_ptr, desired_ptr, is_weak, \
				    success_memorder, failure_memorder)      \
	((int)__atomic_compare_exchange(ptr, expected_ptr, desired_ptr,      \
					is_weak, success_memorder,           \
					failure_memorder))

#define fiber_atomic_add_fetch(ptr, val, memorder) \
	(__atomic_add_fetch(ptr, val, memorder))
#define fiber_atomic_sub_fetch(ptr, val, memorder) \
	(__atomic_sub_fetch(ptr, val, memorder))
#define fiber_atomic_and_fetch(ptr, val, memorder) \
	(__atomic_and_fetch(ptr, val, memorder))
#define fiber_atomic_xor_fetch(ptr, val, memorder) \
	(__atomic_xor_fetch(ptr, val, memorder))
#define fiber_atomic_or_fetch(ptr, val, memorder) \
	(__atomic_or_fetch(ptr, val, memorder))

#define fiber_atomic_fetch_add(ptr, val, memorder) \
	(__atomic_fetch_add(ptr, val, memorder))
#define fiber_atomic_fetch_sub(ptr, val, memorder) \
	(__atomic_fetch_sub(ptr, val, memorder))
#define fiber_atomic_fetch_and(ptr, val, memorder) \
	(__atomic_fetch_and(ptr, val, memorder))
#define fiber_atomic_fetch_xor(ptr, val, memorder) \
	(__atomic_fetch_xor(ptr, val, memorder))
#define fiber_atomic_fetch_or(ptr, val, memorder) \
	(__atomic_fetch_or(ptr, val, memorder))

#define fiber_atomic_fetch_inc(ptr, memorder) \
	fiber_atomic_fetch_add(ptr, 1, memorder)
#define fiber_atomic_fetch_dec(ptr, memorder) \
	fiber_atomic_fetch_sub(ptr, 1, memorder)

#define fiber_atomic_inc_fetch(ptr, memorder) \
	fiber_atomic_add_fetch(ptr, 1, memorder)
#define fiber_atomic_dec_fetch(ptr, memorder) \
	fiber_atomic_sub_fetch(ptr, 1, memorder)

#endif /* _FIBER_ATOMIC_GCC_CLANG */
