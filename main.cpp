#include "show.h"
#include "team.h"
#include <cstdio>

int main (int argc, const char *argv[]) {
    // initialize variables
    Team am = Team::create(4, NOBREAKS, 8.5, 19.5);
    Team pm = Team::create(4, NOBREAKS, 10.5, 21.5);

    auto maybeShow = Show::createFromFile("test1.event");
    if(maybeShow.has_value() == false)
        return 1;
    auto show = maybeShow.value();
    ShowSortedProof p_show = sortShowByStartTime(show);
    show.print();

    Team all = Team::merge(am, pm);
    TeamSortedProof p_team = sortTeamByStartTime(all);
    all.allotTo(show.m.events, p_show, p_team);

    all.print();

    return 0;
}
