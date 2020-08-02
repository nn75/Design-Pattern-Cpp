#include <iostream>
#include <vector>
#include <tuple>

//A. High-level modules should not depend on low-level modules,
//   Both should depend on abstractions.
//B. Abstraction should not depend on details,
//   Details should depend on abstraction.

enum class Relationship {
    parent,
    child,
    sibling
};


struct Person {
    std::string name;
};

//We use abstraction to solve the problem
struct RelationshipBrowser {
    virtual std::vector<Person> find_all_children_of(const std::string& name) = 0;
};


struct Relationships : RelationshipBrowser {            //low-level module
    std::vector<std::tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child) {
        relations.push_back({parent, Relationship ::parent, child});
        relations.push_back({child, Relationship ::child, parent});
    }

    std::vector<Person> find_all_children_of(const std::string &name) override {
        std::vector<Person> result;
        for(auto&& [ first, rel, second ] : relations) {
            if(first.name == "John" && rel == Relationship::parent) {
                result.push_back(second);
            }
        }
        return result;
    }
};


struct Research {         //High-level module
//    Research(Relationships& relationships) {    //If the low-level module set the vector to private, we need to change the implementation of high-level
//        auto& relations = relationships.relations;
//        for(auto&& [ first, rel, second ] : relations) {
//            if(first.name == "John" && rel == Relationship::parent) {
//                std::cout << "John has a child called " << second.name << std::endl;
//            }
//        }
//    };

    Research(RelationshipBrowser& browser) {
        for(auto&& child : browser.find_all_children_of("John")) {
            std::cout << "John has a child called " << child.name << std::endl;
        }
    }

};

int main() {

    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);
    return 0;
}
