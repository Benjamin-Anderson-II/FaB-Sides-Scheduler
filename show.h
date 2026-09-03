#ifndef FAB_SHOW_H
#define FAB_SHOW_H

#include <optional>
#include <vector>
#include "event.h"
struct Show;

class ShowSortedProof {
    ShowSortedProof() = default;
    friend auto sortShowByStartTime(Show&) -> ShowSortedProof;
};

auto sortShowByStartTime(Show&) -> ShowSortedProof;

struct Show {
    struct Member {
        float startTime;
        float endTime;
        std::vector<Event> events;
    } m;

    explicit Show(Member m) : m(std::move(m)) {}

    static std::optional<Show> createFromFile(std::string);
    static Show createFromEventVec(const std::vector<Event>&);

    // Functionality
    void print();
};

#endif
