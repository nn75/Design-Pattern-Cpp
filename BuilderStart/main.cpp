#include <iostream>
#include <vector>
#include <sstream>


struct HtmlElement {
    std::string name, text;
    std::vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}

    HtmlElement(const std::string name, const std::string &text) : name(name), text(text) {}

    std::string str(int indent = 0) const {
        std::ostringstream oss;
        std::string i(indent_size*indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if(text.size() > 0) {
            oss << std::string(indent_size*(indent+1), ' ') << text << std::endl;
        }
        for (const auto& e : elements) {
            oss << e.str(indent + 1);
        }

        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

struct HtmlBuilder {
    HtmlElement root;
    HtmlBuilder(std::string root_name) {
        root.name = root_name;
    }

    //Improvement1: change void to HtmlBuilder&
    HtmlBuilder& add_child(std::string child_name, std::string child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    std::string str() const {
        return root.str();
    }

    //Improvement2:
    static HtmlBuilder build(std::string root_name) {
        return {root_name};
    }
};

int main() {
    HtmlBuilder builder("ul");
//    builder.add_child("li", "hello");
//    builder.add_child("li", "world");

    //Improvement1:Fluent interface
    builder.add_child("li", "hello").add_child("li", "world");

    std::cout << builder.str() << std::endl;


    //Improvement2:
    auto builder2 = HtmlBuilder::build("ul").add_child("li", "hello").add_child("li", "world");
    std::cout << builder2.str() << std::endl;

    return 0;
}
