#include "judges.h"

#include <stdio.h>
#include <stdlib.h>

void allotNoBreaks(Judge *judges, Events events){
    //
}

void Judges::allotTo(Events events) {
    switch(this->breakType){
        case NOBREAKS:
            allotNoBreaks(this->judges, events);
            break;
        case HOURONLY:
            allotHourOnly(this->judges, events);
            break;
        case HOURANDHALF:
            allotHourAndHalf(this->judges, events);
            break;
        default:
            break;
    }
}

Judges::Judges(uint32_t numJudges, enum BreakType breakType) {
    this->numJudges = numJudges;
    this->breakType = breakType;
    this->judges = malloc(numJudges*sizeof(Judge));
}

void Judges::resize(uint32_t numJudges) {
    this->numJudges = numJudges;
    this->judges = realloc(this->judges, numJudges*sizeof(Judge));
}

void Judges::print() {
    for(int i = 0; i < numJudges; i++) {
        printf("Judge %d:\n", i);
        for(int j = 0; j < this->judges.events.size(); j++){
            printf("%s\n", this->judges.events[j].name);
        }
    }
}

Judges::~Judges() {
    free(this->judges);
}
