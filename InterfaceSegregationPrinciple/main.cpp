#include <iostream>


struct Document;

//Do not make interface toooooo large!

//struct IMachine {
//    virtual void print(Document& doc) = 0;
//    virtual void scan(Document& doc) = 0;
//    virtual void fax(Document& doc) = 0;
//};


//Segregate the interface

struct IPrinter {
    virtual void print(Document& doc) = 0;
};

struct IScanner {
    virtual void scan(Document& doc) = 0;
};

struct IFax {
    virtual void fax(Document& doc) = 0;
};


struct Printer : IPrinter {
    void print(Document &doc) override {
        std::cout << "I can print" << std::endl;
    }
};

//struct Scanner : IScanner {
//
//};


struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine {
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}


    void print(Document &doc) override {
        printer.print(doc);
    }

    void scan(Document &doc) override {
        scanner.scan(doc);
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
