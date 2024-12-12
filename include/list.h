#ifndef _LIST_H_
#define _LIST_H_
#include "config.h"
#include "container_of.h"
#include "private/linkage_pre.h"
#include <stdatomic.h>

struct list_head {
  struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) struct list_head name = {&(name), &(name)}

static inline int list_empty(const struct list_head *head) {
  return head->next == head;
}

static inline int list_is_head(const struct list_head *list,
                               const struct list_head *head) {
  return list == head;
}

static inline void list_del(struct list_head *entry) {

  entry->prev->next = entry->next;
  entry->next->prev = entry->prev;

  entry->next = entry;
  entry->prev = entry;
}

static inline void list_add(struct list_head *head, struct list_head *entry) {
  entry->next = head;
  entry->prev = head->prev;
  head->prev->next = entry;
  head->prev = entry;
}

static inline void list_prepend(struct list_head *head,
                                struct list_head *entry) {

  entry->next = head->next;
  entry->prev = head;
  head->next->prev = entry;
  head->next = entry;
}

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define list_entry_is_head(pos, head, member) list_is_head(&pos->member, (head))

#define list_first_entry(head_ptr, type, member)                               \
  list_entry((head_ptr)->next, type, member)

#define list_last_entry(head_ptr, type, member)                                \
  list_entry((head_ptr)->prev, type, member)

#define list_next_entry(pos, member)                                           \
  list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_prev_entry(pos, member)                                           \
  list_entry((pos)->member.prev, typeof(*(pos)), member)

#define list_for_each(pos, head)                                               \
  for (pos = (head)->next; !list_is_head(pos, (head)); pos = pos->next)

#define list_for_each_entry(pos, head, member)                                 \
  for (pos = list_first_entry(head, typeof(*pos), member);                     \
       !list_entry_is_head(pos, head, member);                                 \
       pos = list_next_entry(pos, member))

// Head is not counted
static inline size_t list_len(struct list_head *head) {
  struct list_head *pos;
  size_t count = 0;
  list_for_each(pos, head) count++;
  return count;
}

static inline void list_swap(struct list_head *entry1,
                             struct list_head *entry2) {}

#include "private/linkage_post.h"
#endif //_LIST_H_
