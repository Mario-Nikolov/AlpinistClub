//
// Created by mario on 11/11/2026.
//

#ifndef UNTITLED1_GROUP_H
#define UNTITLED1_GROUP_H

#endif //UNTITLED1_GROUP_H

#pragma once

#include <set>
#include "Climber.h"

class Group {
    Climber leader;
    std::set<Climber> climbers;

public:
    Group();

    Group(Climber leader, std::set<Climber> climbers);

    ~Group();

    Climber getLeader() const;
    std::set<Climber> getClimbers() const;
};
