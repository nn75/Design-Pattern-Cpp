#include <iostream>




struct Creature {
    std::string name;
    int attack, defence;

    Creature(const std::string &name, int attack, int defence) : name(name), attack(attack), defence(defence) {}

    friend std::ostream &operator<<(std::ostream &os, const Creature &creature) {
        os << "name: " << creature.name << " attack: " << creature.attack << " defense: " << creature.defence;
        return os;
    }
};

class CreatureModifier {
    CreatureModifier* next{nullptr};
protected:
    Creature& creature;

public:
    CreatureModifier(Creature &creature) : creature(creature) {}
    void add(CreatureModifier *cm) {
        if(next) {
            next -> add(cm);
        } else {
            next = cm;
        }
    }

    virtual void handle() {
        if(next) {
            next->handle();
        }
    }
};


class DoubleAttackModifier : public CreatureModifier {
public:
    DoubleAttackModifier(Creature &creature) : CreatureModifier(creature) {}

    void handle() override {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreasedDefenseModifier : public CreatureModifier {
public:
    IncreasedDefenseModifier(Creature &creature) : CreatureModifier(creature) {}

    void handle() override {
        if(creature.attack <= 2) {
            creature.defence++;
        }
        CreatureModifier::handle();
    }
};


class NoBonusesModifier : public CreatureModifier {
public:
    NoBonusesModifier(Creature &creature) : CreatureModifier(creature) {}

    void handle() override {

    }
};



int main() {
    Creature goblin{"Goblin", 1, 1};

    CreatureModifier root{goblin};
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r1_2{goblin};
    IncreasedDefenseModifier r2{goblin};

    //If I add NoBonusesModifier here, the following modifier would not be executed
    NoBonusesModifier r3{goblin};
    root.add(&r3);

    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2); // not operated

    root.handle();

    std::cout << goblin << std::endl;

    return 0;
}
