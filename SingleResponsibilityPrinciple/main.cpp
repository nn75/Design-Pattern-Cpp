#include <iostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <fstream>


using namespace std;


struct Journal {
    string title;
    vector<string> entries;

    Journal(const string &title): title(title) {}

    void add_entry(const string &entry) {
        static int count = 1;
        entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
    }

    void save(const string& filename) {
        ofstream ofs(filename);
        for(auto& e : entries) {
            ofs << e << endl;
        }
    }
};

struct PersistenceManager {
    static  void save(const Journal& j, const string& filename) {
        ofstream ofs(filename);
        for(auto& e : j.entries) {
            ofs << e << endl;
        }
    }
};

int main() {
    Journal journal("Dear Diary");
    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");

    PersistenceManager pm;
    pm.save(journal, "diary.txt");

    return 0;
}
