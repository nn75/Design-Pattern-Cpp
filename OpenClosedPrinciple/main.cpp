#include <iostream>
#include <vector>

//Class should be open for extension but closed for modification

enum class Color { red, green, blue };
enum class Size { small, medium, large };


struct Product {
    std::string name;
    Color color;
    Size size;
};


struct ProductFilter {
    //Filter by color
    std::vector<Product*> by_color(std::vector<Product*> items, Color color) {
        std::vector<Product*> result;
        for(auto &i : items) {
            if(i -> color == color) {
                result.push_back(i);
            }
        }
        return result;
    }

    //What if we need a filter by size??
};

template <typename T> struct AndSpecification;

template <typename T> struct Specification {
    virtual bool is_satisfied(T* item) const = 0;

//breaks OCP if you add it post-hoc
//    AndSpecification<T> operator&&(Specification<T>&& other) {
//        return AndSpecification<T>(*this, other);
//    }

};

template <typename T> AndSpecification<T> operator&& (const Specification<T>& first, const Specification<T>& second) {
    return {first, second};
};

template <typename T> struct Filter {
    virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
    std::vector<Product *> filter(std::vector<Product *> items, Specification<Product> &spec) override {
        std::vector<Product *> result;
        for(auto& item : items) {
            if(spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;
    ColorSpecification(Color color) : color(color) {};

    bool is_satisfied(Product *item) const override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;

    explicit SizeSpecification(const Size size) : size (size) {};

    bool is_satisfied(Product *item) const override {
        return item->size == size;
    }
};

template <typename T> struct AndSpecification : Specification<T> {
    const Specification<T>& first;
    const Specification<T>& second;

    AndSpecification(const Specification<T>& first, const Specification<T> &second) : first(first), second(second) {};

    bool is_satisfied(T *item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};


int main() {
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};


    std::vector<Product*> items {&apple, &tree, &house};


//    bad example;
//    ProductFilter pf;
//    auto green_things = pf.by_color(items, Color::green);
//    for(auto &item : green_things) {
//        std::cout << item->name << " is green\n";
//    }

    BetterFilter bf;

    ColorSpecification green(Color::green);
    for(auto& item : bf.filter(items, green)) {
        std::cout << item->name << " is green\n";
    }

    SizeSpecification large(Size::large);
    AndSpecification<Product> green_and_large(green, large);
    for(auto& item : bf.filter(items, green_and_large)) {
        std::cout << item->name << " is green and large\n";
    }

    //auto spec = ColorSpecification(Color::green) && SizeSpecification(Size::large);
    auto spec = green && large;
    for(auto& item : bf.filter(items, spec)) {
        std::cout << item->name << " is green and large\n";
    }

    return 0;
}
