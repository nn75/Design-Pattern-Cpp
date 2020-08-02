#include <iostream>

class Rectangle {
protected:
    int width, height;
public:
    Rectangle(int width, int height) : width(width), height(height) {};

    int getWidth() const {
        return width;
    }

    virtual void setWidth(int width) {
        Rectangle::width = width;
    }

    int getHeight() const {
        return height;
    }

    virtual void setHeight(int height) {
        Rectangle::height = height;
    }

    int area() const { return width * height; }
};


class Square : public Rectangle {
public:
    Square(int size) : Rectangle(size, size) {}

    void setWidth(int width) override {
        this -> width = width;
        this -> height = width;
    }

    void setHeight(int height) override {
        this -> width = height;
        this -> height = height;
    }
};




void process(Rectangle& r) {
    int w = r.getHeight();
    r.setHeight(10);

    std::cout << "expected area = " << (w*10) << std::endl;
    std::cout << "we got " << r.area() << std::endl;
}

//Because the break the liskov substitution principle,
//The derived class (Square) should be able to substitute its parent class (Rectangle)
//We should do like this:
struct RectangleFactory {
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int size);
};

int main() {


    Rectangle r {3, 4};
    process(r);

    Square s{5};
    process(s);

    return 0;
}
