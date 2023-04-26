// SPDX-License-Identifier: GPL-2.0

#include <linux/ipc_namespace.h>

void __binder_wake_up_pollfree(struct wait_queue_head *wq_head);

static inline void binder_wake_up_pollfree(struct wait_queue_head *wq_head)
{
	/*
	 * For performance reasons, we don't always take the queue lock here.
	 * Therefore, we might race with someone removing the last entry from
	 * the queue, and proceed while they still hold the queue lock.
	 * However, rcu_read_lock() is required to be held in such cases, so we
	 * can safely proceed with an RCU-delayed free.
	 */
	if (waitqueue_active(wq_head))
		__binder_wake_up_pollfree(wq_head);
}

struct ipc_namespace* get_init_ipc_ns_ptr(void);
