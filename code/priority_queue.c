#include "priority_queue.h"

PQNode *pq_enqueue(PQNode **a_head, void *a_value, int (*cmp_fn)(const void *, const void *))
{
  PQNode *new_PQNode = malloc(sizeof(*new_PQNode));
  *new_PQNode = (PQNode){.a_value = a_value, .next = NULL};

  if (*a_head == NULL || cmp_fn == NULL || cmp_fn(a_value, (*a_head)->a_value) < 0)
  {
    new_PQNode->next = *a_head;
    *a_head = new_PQNode;
  }
  else
  {
    PQNode *curr = *a_head;
    while (curr->next != NULL && cmp_fn(a_value, curr->next->a_value) >= 0)
    {
      curr = curr->next;
    }
    new_PQNode->next = curr->next;
    curr->next = new_PQNode;
  }

  return new_PQNode;
}

PQNode *pq_dequeue(PQNode **a_head)
{
  PQNode *removed_PQNode = *a_head;
  if (removed_PQNode != NULL)
  {
    *a_head = removed_PQNode->next;
    removed_PQNode->next = NULL;
  }
  return removed_PQNode;
}

PQNode *stack_push(PQNode **stack, void *a_value)
{
  return pq_enqueue(stack, a_value, NULL);
}

PQNode *stack_pop(PQNode **stack)
{
  return pq_dequeue(stack);
}

void destroy_list(PQNode **a_head, void (*destroy_fn)(void *))
{
  while (*a_head != NULL)
  {
    PQNode *removed_PQNode = pq_dequeue(a_head);
    if (destroy_fn != NULL)
    {
      destroy_fn(removed_PQNode->a_value);
    }
    free(removed_PQNode);
  }
}