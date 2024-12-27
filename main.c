#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#include "debug.h"
#include "trace.h"
#include "vector.h"

void list_test();
void vector_test();

int main(int argc, char *argv[]) {

  debug_printf("Debug print enabled!\n");

  vector_test();
  list_test();

  return 0;
}

void vector_test() {

  struct vec_test_struct {
    int val;
  };

  VECTOR_INIT(test_vec, 1, struct vec_test_struct);

  const size_t test_struct_size = sizeof(struct vec_test_struct);
  struct vec_test_struct *tmp;

  for (int i = 0; i < 9; i++) {
    tmp = malloc(test_struct_size);
    tmp->val = 2 * (i + 1);
    vector_push_back(test_vec, *tmp);
  }

  VECTOR_INIT(second_test_vec, 1, struct vec_test_struct);

  printf("Normal vector\n");
  vector_for_each(tmp, test_vec) {
    trace_ascend();
    printf("Vec val: %i \n", tmp->val);

    // Create reversed vector
    vector_push_front(second_test_vec, *tmp);
    trace_descend();
  }

  printf("Reversed vector (3rd and 6th element is removed\n");
  // 3rd element is 12
  vector_erase(&second_test_vec, 3);
  // 6ht now 5th element is 6
  vector_erase(&second_test_vec, 5);

  vector_for_each(tmp, second_test_vec) { printf("Vec val: %i \n", tmp->val); }
}

void list_test() {

  struct list_test_struct {
    struct list_head head;
    int val;
  };

  LIST_HEAD_INIT(test_head);

  const size_t test_struct_size = sizeof(struct list_test_struct);

  struct list_test_struct *tmp;

  for (int i = 0; i < 9; i++) {
    tmp = malloc(test_struct_size);
    list_add(&test_head, &tmp->head);
    tmp->val = 2 * (i + 1);
  }

  LIST_HEAD_INIT(second_test_head);

  struct list_test_struct *tmp2;
  printf("Normal list\n");
  list_for_each_entry(tmp, &test_head, head) {
    trace_ascend();
    printf("Element: %i\n", tmp->val);
    // Create reversed list
    tmp2 = malloc(test_struct_size);
    memcpy(tmp2, tmp, test_struct_size);
    list_prepend(&second_test_head, &tmp2->head);
    trace_descend();
  }

  printf("Prepended list\n");
  list_for_each_entry(tmp, &second_test_head, head) {
    printf("Element: %i\n", tmp->val);
  }

  printf("List1 count: %zu List2 count: %zu \n", list_len(&test_head),
         list_len(&second_test_head));
}
