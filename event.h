#ifndef FAB_EVENT_H
#define FAB_EVENT_H

typedef struct {
    float startTime;    // What time the round is supposed to start
    float endTime;
} Round;

typedef struct {
    char  name[128];
    float roundLength;  // Length of the round (either .5 or 1 hr)
    int   numRounds;
    float startTime;
    float endTime;
    std::vector<Round> rounds;
} Event;

#endif
