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
    if(loaded==true)
        return false;
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

void Book::setAuthor(const char * text)
{
    char *&field = author;
    delete[] field;
    field = new char[ strlen(text)+1 ];
    strcpy( field,text );
}

void Book::setHeading(const char * text)
{
    char *&field = heading;
    delete[] field;
    field = new char[ strlen(text)+1 ];
    strcpy( field,text );
}

void Book::setDirectory(const char * text)
{
    char *&field = directory;
    delete[] field;
    field = new char[ strlen(text)+1 ];
    strcpy( field,text );
}

void Book::setDescription(const char * text)
{
    char *&field = description;
    delete[] field;
    field = new char[ strlen(text)+1 ];
    strcpy( field,text );
}

void Book::setIsbn(const char * text)
{
    char *&field = isbn;
    delete[] field;
    field = new char[ strlen(text)+1 ];
    strcpy( field,text );
}

void Book::setRating(int rating)
{
    this->rating = rating;
}

void Book::setLoaded(bool loaded)
{
    this->loaded = loaded;
}

void Book::print()
{
    cout<<"Title: "<<heading<<endl;
    cout<<"Author: "<<author<<endl;
    cout<<"Description: "<<description<<endl;
    cout<<"Directory: "<<directory<<endl;
    cout<<"ISBN: "<<isbn<<endl;
    cout<<"rating: "<<rating<<endl;
}
