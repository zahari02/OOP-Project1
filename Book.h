#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

const int max_author = 100;
const int max_heading = 100;
const int max_directory = 240;
const int max_description = 10000;
const int max_isbn = 15;

void write_bintext(ofstream&f,const char*);

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

    void setAuthor(const char *);
    void setHeading(const char *);
    void setDirectory(const char *);
    void setDescription(const char *);
    void setIsbn(const char *);
    void setRating(int);
    void setLoaded(bool loaded);

    void print();

    void save(ofstream&);
};
