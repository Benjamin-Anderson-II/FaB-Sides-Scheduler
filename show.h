#ifndef FAB_SHOW_H
#define FAB_SHOW_H

#include <vector>
#include <cstddef>
#include "event.h"

class Show {
    private:
        std::vector<Event> events;
        float startTime;
        float endTime;
    public:
        // Constructors
        Show(char *fileName);

        // Getters
        Event &operator[](unsigned int i);
        float getStartTime();
        float getEndTime();
        std::vector<Event> getShowAsVector();
        size_t size();

        // Functionality
        void sort();
        void print();
        void push_back(Event event);
        void pop(int index);
        bool empty();
};

#endif
