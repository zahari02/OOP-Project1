#include "Book.h"

void Book::deleteDyn()
{
    delete[] author;
    delete[] heading;
    delete[] directory;
    delete[] description;
    delete[] isbn;
}

Book::Book()
{
    author=heading=directory=description=isbn=nullptr;
    rating = loaded = 0;
}

Book::Book(const Book& other)
{
    if(other.loaded == false)
    {
        author=heading=directory=description=isbn=nullptr;
        rating = loaded = 0;
        return;
    }
    author = new char[ strlen(other.author)+1 ];
    strcpy(author,other.author);

    heading = new char[ strlen(other.heading)+1 ];
    strcpy(heading,other.heading);

    directory = new char[ strlen(other.directory)+1 ];
    strcpy(directory,other.directory);

    description = new char[ strlen(other.description)+1 ];
    strcpy(description,other.description);

    isbn = new char[ strlen(other.isbn)+1 ];
    strcpy(isbn,other.isbn);

    rating = other.rating;

    loaded = true;
}

Book::Book(Book&& other)
{
    if(other.loaded == false)
    {
        author=heading=directory=description=isbn=nullptr;
        rating = loaded = 0;
        return;
    }
    author = other.author;
    heading = other.heading;
    directory = other.directory;
    description = other.description;
    isbn = other.isbn;
    rating = other.rating;
    loaded = true;
}

Book& Book::operator=(const Book& other)
{
    deleteDyn();
    if(other.loaded == false)
    {
        author=heading=directory=description=isbn=nullptr;
        rating = loaded = 0;
        return *this;
    }
    author = new char[ strlen(other.author)+1 ];
    strcpy(author,other.author);

    heading = new char[ strlen(other.heading)+1 ];
    strcpy(heading,other.heading);

    directory = new char[ strlen(other.directory)+1 ];
    strcpy(directory,other.directory);

    description = new char[ strlen(other.description)+1 ];
    strcpy(description,other.description);

    isbn = new char[ strlen(other.isbn)+1 ];
    strcpy(isbn,other.isbn);

    rating = other.rating;

    loaded = true;

    return *this;
}

Book& Book::operator=(Book&& other)
{
    deleteDyn();
    if(other.loaded == false)
    {
        author=heading=directory=description=isbn=nullptr;
        rating = loaded = 0;
        return *this;
    }
    author = other.author;
    heading = other.heading;
    directory = other.directory;
    description = other.description;
    isbn = other.isbn;
    rating = other.rating;
    loaded = true;

    return *this;
}

Book::~Book()
{
    deleteDyn();
}

bool Book::load(ifstream &str)
{
    deleteDyn();
    int size;

    if(! str.read( (char*)&size , sizeof(int) ) )
        return false;

    author = new char[size];
    if(! str.read( author, size ))
        return false;

    if(! str.read( (char*)&size , sizeof(int) ) )
        return false;
    heading = new char[size];
    if(! str.read( heading, size ))
        return false;

    if(! str.read( (char*)&size , sizeof(int) ) )
        return false;
    directory = new char[size];
    if(! str.read( directory, size ))
        return false;

    if(! str.read( (char*)&size , sizeof(int) ) )
        return false;
    description = new char[size];
    if(! str.read( description, size ))
        return false;

    if(! str.read( (char*)&size , sizeof(int) ) )
        return false;
    isbn = new char[size];
    if(! str.read( isbn, size ))
        return false;


    if(! str.read( (char*)&rating , sizeof(int) ) )
        return false;

    loaded = true;
    return true;
}
