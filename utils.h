#ifndef FAB_UTILS_H
#define FAB_UTILS_H

#include <vector>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

void readEventsFromFile(std::vector<Event> &e);
void sortEvents(std::vector<Event> &e);
float getStartTime(std::vector<Event> e);
float getEndTime(std::vector<Event> e);

void printEvents(std::vector<Event> events);

#endif
