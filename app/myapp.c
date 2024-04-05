#include "tp.h"

int main()
{
  for (int i = 0; i < 10; i++) {
    // Just providing an empty array
    tracepoint(my_provider, my_tracepoint_does_not_work, NULL, 0U);
  }
  return 0;
}
