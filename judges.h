#ifndef FAB_JUDGES_H
#define FAB_JUDGES_H

#include <vector>
#include "event.h"

typedef struct {
    std::vector<Event> events;
} Judge;

enum BreakType {
    NOBREAKS,
    HOURONLY,
    HOURANDHALF
};

class Judges {
    private:
        uint32_t numJudges;
        enum BreakType breakType;
        Judge *judges;
    public:
        Judges(uint32_t numJudges);

        void allotTo(Events events);
        void resize(uint32_t numJudges);
        
        void print();

        ~Judges();
};

#endif
