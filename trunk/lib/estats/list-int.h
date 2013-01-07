#ifndef ESTATS_LIST_INT_H
#define ESTATS_LIST_INT_H

/*
 *  Intrusive list structure, similar to <linux/list.h>
 *  from the Linux kernel, or Boost.Instrusive from the
 *  Boost libraries.
 *
 *  The below code is modified from that of the GNU C Library,
 *  (glibc-2.13/nptl/sysdeps/pthread/list.h), in accordance with
 *  the LGPL 2.1.
 */

#ifdef __cplusplus
extern "C" {
#endif

static inline void _estats_list_init(struct estats_list* ptr)
{
    ptr->next = ptr;
    ptr->prev = ptr;
}

static inline void _estats_list_add2(struct estats_list* item,
                                     struct estats_list* prev,
                                     struct estats_list* next)
{
    next->prev = item;
    item->next = next;
    item->prev = prev;
    prev->next = item;
}

static inline void _estats_list_add(struct estats_list* item,
                                    struct estats_list* head)
{
    _estats_list_add2(item, head, head->next);
}

static inline void _estats_list_add_tail(struct estats_list* item,
                                         struct estats_list* head)
{
    _estats_list_add2(item, head->prev, head);
}

static inline void _estats_list_del2(struct estats_list* prev,
                                     struct estats_list* next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void _estats_list_del(struct estats_list* entry)
{
    _estats_list_del2(entry->prev, entry->next);
    entry->prev = entry->next = 0;
}

static inline int _estats_list_empty(struct estats_list* head)
{
    return head->next == head;
}

#define ESTATS_LIST_ENTRY(ptr, type, member) \
    ((type*)((char*)(ptr) - (unsigned long)(&((type*)0)->member)))
#define ESTATS_LIST_FOREACH(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)
#define ESTATS_LIST_FOREACH_PREV(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)
#define ESTATS_LIST_FOREACH_SAFE(pos, tmp, head) \
    for (pos = (head)->next, tmp = pos->next; pos != (head); pos = tmp, tmp = pos->next)

#ifdef __cplusplus
}
#endif

#endif /* ESTATS_LIST_INT_H */
