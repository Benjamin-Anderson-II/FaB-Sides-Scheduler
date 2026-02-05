#include "show.h"
#include "team.h"

int main (int argc, const char *argv[]) {
    // initialize variables
    Show show((char *)"test1.event");
    show.sort();
    show.print();

    Team team(7, NOBREAKS, 8.5, 10.5);
    team.allotTo(show);
    team.print();

    return 0;
}
