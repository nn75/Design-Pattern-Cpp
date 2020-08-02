//
// Created by Nan Ni on 2020/7/22.
//

#ifndef MEDIATORCHARROOM_CHATROOM_H
#define MEDIATORCHARROOM_CHATROOM_H

#include <vector>

#include <algorithm>
#include "Person.h"

class ChatRoom {
public:
    std::vector<Person*> people;

    void broadCast(const std::string &origin, const std::string &message);

    void join(Person *p);

    void message(const std::string &origin, const std::string &who, const std::string &message) {
        auto target = std::find_if(begin(people),
                end(people),
                [&](const Person *p) {
            return p->name == who;
        });

        if(target != end(people)) {
            (*target)->receive(origin, message);
        }
    }

};


#endif //MEDIATORCHARROOM_CHATROOM_H
