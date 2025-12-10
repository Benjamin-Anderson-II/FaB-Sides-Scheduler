#ifndef FAB_EVENTS_H
#define FAB_EVENTS_H
#include <vector>

typedef struct {
    float startTime;    // What time the round is supposed to start
} Round;

typedef struct {
    char  name[128];
    float roundLength;  // Length of the round (either .5 or 1 hr)
    int   numRounds;
    std::vector<Round> rounds;
} Event;

class Events {
    private:
        std::vector<Event> events;
        float startTime;
        float endTime;
    public:
        Events(char *fileName);

        void sort();

        float getStartTime();
        float getEndTime();
        std::vector<Event> getEventsAsVector();
        void print();
};

#endif
