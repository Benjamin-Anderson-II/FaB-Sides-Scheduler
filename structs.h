#ifndef FAB_STRUCTS_H
#define FAB_STRUCTS_H

#include <vector>

typedef struct {
    float startTime;      // Beginning of the Judge's Shift
    float endTime;        // End of the Judge's Shift
    bool breakHalf;     // Whether they have their 0.5 hr break still (1=yes)
    bool breakFull;     // Whether they have their 1.0 hr break still (1=yes)
} Judge;

typedef struct {
    float startTime;    // What time the round is supposed to start
} Round;

typedef struct {
    char  name[128];
    float roundLength;  // Length of the round (either .5 or 1 hr)
    int   numRounds;
    std::vector<Round> rounds;
} Event;

#endif
