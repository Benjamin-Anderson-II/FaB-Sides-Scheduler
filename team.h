#ifndef FAB_TEAM_H
#define FAB_TEAM_H

#include <vector>
#include "event.h"
#include "show.h"

struct Team;
enum BreakType {
    NOBREAKS,
    HOURONLY,
    HOURANDHALF
};

struct Judge {
    struct Member { 
        float startTime;
        float endTime;
        enum BreakType breakType;
        std::vector<Event> events;
    } m;
    explicit Judge(Member m) : m(std::move(m)) {}
    static Judge create(float,float,BreakType);

    void print();
};


class TeamSortedProof {
    TeamSortedProof() = default;
    friend auto sortTeamByStartTime(Team&) -> TeamSortedProof;
};

auto sortTeamByStartTime(Team&) -> TeamSortedProof;

struct Team {
        struct Member {
            std::vector<Judge> judges;
        } m;
        explicit Team(Member m) : m(std::move(m)) {}

        static Team create(int, enum BreakType, float, float);
        static Team merge(Team&, Team&);

        bool allotTo(const std::vector<Event>&, const ShowSortedProof&, const TeamSortedProof&);

        size_t size() {return this->m.judges.size();}

        void print();
};

#endif
