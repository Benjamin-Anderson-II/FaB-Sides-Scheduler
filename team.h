#ifndef FAB_TEAM_H
#define FAB_TEAM_H

#include <vector>
#include "event.h"
#include "show.h"

enum BreakType {
    NOBREAKS,
    HOURONLY,
    HOURANDHALF
};

struct Judge {
    float startTime;
    float endTime;
    enum BreakType breakType;
    std::vector<Event> events;
};


class Team {
    private:
        struct Member {
            std::vector<Judge> judges;
        } m;
        explicit Team(Member m) : m(std::move(m)) {}
    public:
        class SortProof {
            SortProof() = default;
            friend SortProof sortByStartTime();
        };
        static Team create(int, enum BreakType, float, float);
        static Team merge(Team&, Team&);
        
        auto sortByStartTime() -> SortProof;
        bool allotTo(const std::vector<Event>&, const SortProof&);

        int getNumJudges(){return this->m.judges.size();}
        
        void print();
};

#endif
