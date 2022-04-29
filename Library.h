#include "Book.h"

const int max_books=1000000;

class Library
{
    Book *list;
    int book_amount;

public:
    Library();
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;
    ~Library();

    bool load(ifstream&);
    void add(const Book &);
    void print();

    void save(ofstream&);
};
