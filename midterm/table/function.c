#include "function.h"
#include <stdio.h>
#include <stdlib.h>

Table *createTable() {
  Table *t = (Table *)malloc(sizeof(Table));
  scanf("%d", &t->tableSize);
  t->guest = NULL;
  t->leaveTime = 0;
  return t;
}

Guest *createGuest() {
  Guest *g = (Guest *)malloc(sizeof(Guest));
  scanf("%s %d %d %d", g->guestName, &g->groupSize, &g->arriveTime,
        &g->diningTime);
  return g;
}

Guest *checkLeave(Table **table, int tableCount, int currentTime) {
  for (int i = 0; i < tableCount; i++) {
    if (table[i]->guest && table[i]->leaveTime == currentTime) {
      Guest *g = table[i]->guest;
      table[i]->guest = NULL;
      return g;
    }
  }
  return NULL;
}

int assignTable(Table **table, int tableCount, int currentTime, Guest *guest) {
  for (int i = 0; i < tableCount; i++) {
    if (!table[i]->guest && table[i]->tableSize >= guest->groupSize) {
      table[i]->guest = guest;
      table[i]->leaveTime = currentTime + guest->diningTime;
      return 1;
    }
  }
  return 0;
}
