#ifndef FAB_EVENTS_H
#define FAB_EVENTS_H

#include <vector>
#include "event.h"

class Events {
    private:
        std::vector<Event> events;
        float startTime;
        float endTime;
    public:
        // Initializers
        Events(char *fileName);

        // Getters
        Event &operator[](unsigned int i);
        float getStartTime();
        float getEndTime();
        std::vector<Event> getEventsAsVector();

        // Functionality
        void sort();
        void print();
};

#endif
