//
// Created by Nan Ni on 2020/7/22.
//

#include "Person.h"
#include "ChatRoom.h"

void ChatRoom::broadCast(const std::string &origin, const std::string &message) {
    for(auto p : people) {
        if(p -> name != origin) {
            p->receive(origin, message);
        }
    }
}


void ChatRoom::join(Person *p) {
    std::string join_msg = p->name + " joins the chat";
    broadCast("room", join_msg);

    p->room = this;
    people.push_back(p);
}

