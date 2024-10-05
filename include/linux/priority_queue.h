// File: priority_queue.h

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <linux/slab.h>   // For kmalloc and kfree
#include <linux/sched.h>  // For task_struct
#include <linux/list.h>
struct prio_node {
    struct task_struct *task; // Pointer to the task_struct of the thread
    int priority;             // Thread priority
    struct list_head list;    // List head for linking in the priority queue
};

struct priority_queue {
    struct list_head head;    // Head of the linked list representing the queue
};

struct priority_queue *create_priority_queue(void);
void add_to_priority_queue(struct priority_queue *queue, struct task_struct *task, int priority);
struct task_struct *get_highest_priority_task(struct priority_queue *queue);
void remove_from_priority_queue(struct priority_queue *queue, struct task_struct *task);
void free_priority_queue(struct priority_queue *queue);

#endif // PRIORITY_QUEUE_H


