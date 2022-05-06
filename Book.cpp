#include "Book.h"

void write_bintext(ofstream&file,const char*text)
{
    int temp = strlen(text)+1;
    file.write( (char*)&temp,sizeof(int) );
    file.write(text,strlen(text)+1);
}

bool str_eq(const char* str1, const char*str2, bool ignore)
{
    if(strlen(str1) != strlen(str2))
        return false;
    int n = strlen(str1);
    for(int i=0; i<n; i++)
    {
        if(ignore)
        {
            if(tolower(str1[i]) != tolower(str2[i]))
                return false;
        }
        else
            if(str1[i] != str2[i])
                return false;
    }
    return true;
}

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

    other.author = other.heading = other.directory = other.description = other.heading = other.isbn = nullptr;
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

    other.author = other.heading = other.directory = other.description = other.heading = other.isbn = nullptr;

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

bool Book::compBook(const char* str,SearchMode mode,bool ignore)
{
    if(mode == title_m)
        return str_eq(str,heading,ignore);
    if(mode == author_m)
        return str_eq(str,author,ignore);
    if(mode == isbn_m)
        return str_eq(str,isbn,ignore);
    if(mode == description_m)
    {
        int n = strlen(description);
        int m = strlen(str);
        char * buff = new char[m+1];
        for(int i=0; i<=n-m; i++)
        {
            strncpy(buff,description+i,m);
            buff[m]='\0';
            if( str_eq(str,buff,ignore) )
            {
                delete[] buff;
                return true;
            }
        }
        delete[] buff;
    }
    return false;
}

bool Book::lessThan(const Book& book,SortMode mode)
{
    if(mode == title_s)
        return strcmp(heading, book.heading) < 0;
    if(mode == author_s)
        return strcmp(author, book.author) < 0;
    if(mode == rating_s)
        return rating < book.rating;
    return 0;
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

void Book::shortPrint()
{
    cout<<"Title: "<<heading<<endl;
    cout<<"Author: "<<author<<endl;
    cout<<"ISBN: "<<isbn<<endl;
}

bool Book::getFile(ifstream &file)
{
    file.open(directory);
    if(!file)
        return false;
    return true;
}


void Book::save(ofstream& file)
{
    write_bintext(file,author);
    write_bintext(file,heading);
    write_bintext(file,directory);
    write_bintext(file,description);
    write_bintext(file,isbn);
    file.write((char*)&rating,sizeof(int));
}
