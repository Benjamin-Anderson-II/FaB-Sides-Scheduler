#include "team.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

// Helper Function Prototypes
void allotNoBreaks(std::vector<Judge> &judges, Show show);
void allotHourOnly(std::vector<Judge> &judges, Show show);
void allotHourAndHalf(std::vector<Judge> &judges, Show show);
void splitEventAtRoundIndex(Show &show, int eventIndex, int roundIndex);

// round index is the first round that is to be split off
void splitEventAtRoundIndex(Show &show, int eventIndex, int roundIndex){
    if(roundIndex < 1) return;
    Event event = show[eventIndex];

    Event newEvent;
    memcpy(newEvent.name, event.name, 128);
    newEvent.roundLength = event.roundLength;
    newEvent.numRounds = event.numRounds - roundIndex;
    newEvent.startTime = event.rounds[roundIndex].startTime;
    newEvent.endTime = event.endTime;
    printf("1");
    for(int i = 0; show[eventIndex].numRounds > roundIndex; i++){
        printf("2");
        newEvent.rounds.push_back(event.rounds[roundIndex+i]); // shallow copy OK, since it's a struct
        event.rounds.erase(event.rounds.begin() + roundIndex+i);
        show[eventIndex].numRounds--;
    }
    printf("3");
    show[eventIndex].endTime = show[eventIndex].rounds.back().endTime;
    printf("4");
    show.push_back(newEvent);
    printf("\n");
}

// CONSTRUCTOR
Team::Team(uint32_t numTeam, enum BreakType breakType, float startAM, float startPM) {
    this->breakType = breakType;
    this->judges.resize(numTeam);
    // NOTE: THIS IS TEMPORARY, AND JUST A HEURISTIC
    for(int i = 0; i < numTeam; i++){
        this->judges[i].startShiftTime = (i<=numTeam/2) ? startAM : startPM;
        this->judges[i].endShiftTime   = (i<=numTeam/2) ? startAM+11: startPM+11;
    }
}

// MEMBER FUNCTIONS
void Team::allotTo(Show show) {
    switch(this->breakType){
        case NOBREAKS:
            allotNoBreaks(this->judges, show);
            break;
        case HOURONLY:
            allotHourOnly(this->judges, show);
            break;
        case HOURANDHALF:
            allotHourAndHalf(this->judges, show);
            break;
        default:
            break;
    }
}
void allotNoBreaks(std::vector<Judge> &judges, Show show){
    // give each judge their initial event
    // repeat this process
    while(!show.empty()){
        for(size_t i = 0; i < judges.size(); i++){
            Judge judge = judges[i];
            for(size_t j = 0; j < show.size(); j++){
                Event event = show[j];
                if(event.startTime < judge.startShiftTime)
                    continue;
                if(!judge.events.empty() && (
                    event.startTime < judge.events.back().endTime
                ))
                    continue;
                
                // For Show that end after judge's shift
                if(event.endTime > judge.endShiftTime){
                    printf("Judge will end shift too early\n");
                    // Find which round is the one that goes over
                    // Create a new event for it and push it to the back of the events list
                    for(int x = 0; x < event.numRounds; x++){
                        if(event.rounds[x].endTime <= judge.endShiftTime){
                            // printf("  - roundEnd: %f\n", event.rounds[x].endTime);
                            continue;
                        }
                        printf("splitting\n");
                        splitEventAtRoundIndex(show, j, x);
                        break;
                    }
                }
                judges[i].events.push_back(show[j]);
                printf("judge %2ld assigned %s\n", i, event.name);
                // printf("erased    - %s\n", event.name);
                // printf("numShow - %ld\n", events.size());
                show.pop(j);
                j--;
                break;
            }
        }
    }
}
void allotHourOnly(std::vector<Judge> &judges, Show events){}
void allotHourAndHalf(std::vector<Judge> &judges, Show events){}


void Team::resize(uint32_t numTeam) {
    this->judges.resize(numTeam);
}

void Team::print() {
    for(size_t j = 0; j < this->judges.size(); j++){
        Judge judge = this->judges[j];

        //printf("Judge %2ld: ", j);
        // skip unscheduled judges
        if(judge.events.size() <= 0){
            printf("\n");
            continue;
        }

        float start = judge.events[0].startTime;
        float end   = judge.events.back().endTime;

        // Leading characters
        for(float i = 0; i < start - 9; i +=0.5) printf("|  ");

        for(size_t i = 0; i < judge.events.size(); i++){
            Event event = judge.events[i];
            char sub[10];
            int sublen = event.roundLength * 5;
            memcpy(sub, event.name, sublen);
            sub[sublen] = 0;
            if(i==0){
                for(int a = 0; a < event.numRounds; a++)
                    printf("|%s", sub);
                continue;
            }
            for(float a = judge.events[i-1].endTime; a < event.startTime; a+=0.5)
                printf("|  ");
            for(float b = 0; b < event.numRounds; b++)
                printf("|%s", sub);
        }
        printf("|\t\tJudge: %2ld\n", j);
    }
}
