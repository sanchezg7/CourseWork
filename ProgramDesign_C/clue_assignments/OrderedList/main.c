#include "orderedList.h"
#include <stdlib.h>

int main()
{
  Node * p = NULL;
  p = orderedInsert(p,2);
  printList(p);
  p = orderedInsert(p,0);
  printList(p);
  p = orderedInsert(p,3);
  printList(p);
  p = orderedInsert(p,3);
  printList(p);
  p = orderedInsert(p,5);
  printList(p);
  clearList(&p);
  p = orderedInsert(p,6);
  printList(p);
  return 0;
}
