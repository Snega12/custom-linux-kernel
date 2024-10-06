// File: priority_test.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/random.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/delay.h> // Include for prandom_u32
#include <linux/sched.h>
#include <linux/priority_queue.h>

// Define a priority-based semaphore structure
struct semaphore sem;
struct priority_queue *prio_queue;

static int thread_fn(void *data) {
    int thread_priority = *(int *)data;
    printk(KERN_INFO "Thread with priority %d: Trying to acquire semaphore\n", thread_priority);
    add_to_priority_queue(prio_queue, current, thread_priority);
    down(&sem);
    printk(KERN_INFO "Thread with priority %d: Acquired semaphore!\n", thread_priority);
    ssleep(2);
    up(&sem);
    remove_from_priority_queue(prio_queue, current);
    printk(KERN_INFO "Thread with priority %d: Released semaphore\n", thread_priority);
    return 0;
}

static int __init priority_test_init(void) {
    int i;
    struct task_struct *task;
    int priorities[3];

    sema_init(&sem, 1);
    prio_queue = create_priority_queue();

    // Generate random priorities for the threads
    for (i = 0; i < 3; i++) {
        priorities[i] = get_random_u32() % 100; // Random priority between 0 and 99
    }

    printk(KERN_INFO "Priority Test: Module loaded\n");

    for (i = 0; i < 3; i++) {
        task = kthread_run(thread_fn, &priorities[i], "test_thread_%d", i);
        if (IS_ERR(task)) {
            printk(KERN_ERR "Failed to create thread %d\n", i);
        }
    }

    return 0;
}

static void __exit priority_test_exit(void) {
    free_priority_queue(prio_queue);
    printk(KERN_INFO "Priority Test: Module unloaded\n");
}

module_init(priority_test_init);
module_exit(priority_test_exit);

MODULE_LICENSE("GPL");  // Add this line
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Test Module for Priority Queue and Semaphore");


