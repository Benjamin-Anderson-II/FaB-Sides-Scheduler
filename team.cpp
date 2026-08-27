#include "team.h"

#include <algorithm>
#include <vector>
#include <iostream>

Team Team::create(int numTeam, enum BreakType breakType, float startTime, float endTime) {
    std::vector<Judge> judges(numTeam);
    for (auto &j : judges) {
        j.startTime = startTime;
        j.endTime = endTime;
        j.breakType = breakType;
    }

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
auto Team::sortByStartTime() -> SortProof {
    auto v = &this->m.judges;
    std::sort(v->begin(), v->end(), [](Judge a, Judge b) {
        return a.startTime < b.startTime;
    });
    return {};
}


bool Team::allotTo(const std::vector<Event> &events, const SortProof &proof) {
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
        while(judge.endTime < event.getStartTime() ||
              isJudgeActive[judgeIndex]){
            judgeIndex = (judgeIndex + 1) % numJudges;
            judge = (*judges)[judgeIndex];
        }

        //Split Event if judge can't finish it
        if(judge.endTime < event.getEndTime()){
            auto split = Event::splitEventAtTime(event, judge.endTime);
            splitEvents.erase(splitEvents.begin()+eventIndex);
            splitEvents.insert(splitEvents.begin()+eventIndex, split[0]);
            splitEvents.push_back(split[1]);
            isJudgeActive[judgeIndex] = true;
        }

        // Give Judge Event
        (*judges)[judgeIndex].events.push_back(event);

        judgeIndex = (judgeIndex + 1) % numJudges;
    }
    return true;
}

void EprintRound(std::string name, float roundLength){
    std::cout << "|" + name.substr(0, roundLength * 5);
}

void Team::print() {
    std::cout << std::endl;
    for(float i = 9; i < 21.5; i++)
        printf("|%2d|.5", (int)i);
    printf("|\n");
    for(auto j : this->m.judges) {
        float prevEventEnd = 0;
        for(auto e : j.events){
            for(float i = prevEventEnd; i < e.getStartTime() - 9; i+=0.5)
                std::cout << "|  ";
            for(int i = 0; i < e.getNumRounds(); i++)
                EprintRound(e.getName(), e[i].roundLength);

            prevEventEnd = e.getEndTime() - 9;
        }
        std::cout << std::endl;
    }
}
