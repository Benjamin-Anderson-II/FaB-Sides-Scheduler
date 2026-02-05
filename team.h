#ifndef FAB_TEAM_H
#define FAB_TEAM_H

#include <vector>
#include "event.h"
#include "show.h"
#include <cstdint>

typedef struct {
    float startShiftTime;
    float endShiftTime;
    std::vector<Event> events;
} Judge;

enum BreakType {
    NOBREAKS,
    HOURONLY,
    HOURANDHALF
};

class Team {
    private:
        enum BreakType breakType;
        std::vector<Judge> judges;
    public:
        Team(uint32_t numTeam, enum BreakType breakType, float AM, float PM);

        void allotTo(Show show);
        void resize(uint32_t numTeam);
        
        void print();
};

#endif
