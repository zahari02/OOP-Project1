#include <cstring>
#include <fstream>
using namespace std;

class Book
{
public:
    char *author,*heading,*directory,*description,*isbn;
    int rating;
    bool loaded;

    void deleteDyn();


    Book();
    Book(const Book&);
    Book(Book&&);
    Book& operator=(const Book&);
    Book& operator=(Book&&);
    ~Book();

    bool load(ifstream& str);
};
