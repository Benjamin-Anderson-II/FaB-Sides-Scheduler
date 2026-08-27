#ifndef FAB_SHOW_H
#define FAB_SHOW_H

#include <optional>
#include <vector>
#include "event.h"

class Show {
    private:
        struct Member {
            float startTime;
            float endTime;
            std::vector<Event> events;
        } m;
        explicit Show(Member m) : m(std::move(m)) {}
    public:
        static std::optional<Show> createFromFile(std::string);
        static Show createFromEventVec(const std::vector<Event>&);
        // Getters
        Event &operator[](unsigned int i){return this->m.events[i];}
        float getStartTime(){return this->m.startTime;}
        float getEndTime(){return this->m.endTime;}
        std::vector<Event> getEvents(){return this->m.events;}
        size_t size(){return this->m.events.size();}

        // Functionality
        void sortByStartTime();
        void print();
};

#endif
