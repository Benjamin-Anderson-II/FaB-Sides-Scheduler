#include "team.h"

#include <algorithm>
#include <vector>
#include <iostream>

Judge Judge::create(float start, float end, BreakType breakType) {
    return Judge(Member {
        .startTime = start,
        .endTime = end,
        .breakType = breakType,
        .events = std::vector<Event>(),
    });
}

Team Team::create(int numTeam, enum BreakType breakType, float startTime, float endTime) {
    std::vector<Judge> judges;
    for(int i = 0; i < numTeam; i++)
        judges.push_back(Judge::create((startTime), endTime, breakType));

    return Team(Member{
        .judges = std::move(judges),
    });
}
Team Team::merge(Team &a, Team &b) {
    std::vector<Judge> tempJudges = a.m.judges;
    tempJudges.insert(tempJudges.end(), b.m.judges.begin(), b.m.judges.end());
    return Team(Member{
        .judges = std::move(tempJudges),
    });
}

/***** MEMBER FUNCTIONS *****/
auto sortTeamByStartTime(Team& team) -> TeamSortedProof {
    auto v = &team.m.judges;
    std::sort(v->begin(), v->end(), [](Judge a, Judge b) {
        return a.m.startTime < b.m.startTime;
    });
    return {};
}


bool Team::allotTo(const std::vector<Event> &events,
                   const ShowSortedProof &s, const TeamSortedProof& t) {
    auto *judges = &(this->m.judges);
    const auto numJudges = judges->size();
    std::vector<bool> isJudgeActive;
    isJudgeActive.assign(numJudges, false);

    auto splitEvents = events;
    size_t judgeIndex = 0;
    for (size_t eventIndex = 0; eventIndex < splitEvents.size(); eventIndex++) {
        auto event = splitEvents[eventIndex];
        auto judge = (*judges)[judgeIndex];

        // Skip judges who aren't available
        while(judge.m.endTime < event.startTime() ||
              isJudgeActive[judgeIndex]){
            judgeIndex = (judgeIndex + 1) % numJudges;
            judge = (*judges)[judgeIndex];
        }

        //Split Event if judge can't finish it
        if(judge.m.endTime < event.endTime()){
            auto split = Event::splitEventAtTime(event, judge.m.endTime);
            splitEvents.erase(splitEvents.begin()+eventIndex);
            splitEvents.insert(splitEvents.begin()+eventIndex, split[0]);
            splitEvents.push_back(split[1]);
            isJudgeActive[judgeIndex] = true;
        }

        // Give Judge Event
        (*judges)[judgeIndex].m.events.push_back(event);

        judgeIndex = (judgeIndex + 1) % numJudges;
    }
    return true;
}

void EprintRound(std::string name, float roundLength){
    std::cout << "|" + name.substr(0, roundLength * 5);
}

void Judge::print() {
    float prevEventEnd = 0;
    for(auto e : this->m.events) {
        for(auto i = prevEventEnd; i < e.startTime() - 9; i+=0.5)
            std::cout << "| ";
        for(size_t i = 0; i < e.m.rounds.size(); i++)
            EprintRound(e.m.name, e[i].roundLength);
        prevEventEnd = e.endTime() - 9;
    }
    std::cout<<std::endl;
}

void Team::print() {
    std::cout << std::endl;
    for(float i = 9; i < 21.5; i++)
        printf("|%2d|.5", (int)i);
    printf("|\n");
    for(auto j : this->m.judges) j.print();
}
