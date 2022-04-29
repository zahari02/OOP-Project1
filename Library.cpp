#include "Library.h"

Library::Library()
{
    list = nullptr;
    book_amount = 0;
}

Library::~Library()
{
    delete[] list;
}

bool Library::load(ifstream& str)
{
    if(book_amount!=0)
        return false;
    if(! str.read( (char*)&book_amount , sizeof(int) ) )
        return false;
    if(book_amount<1 && book_amount>max_books)
        return false;

    list = new Book[book_amount];
    for(int i=0; i<book_amount; i++)
        list[i].load(str);
}

void Library::add(const Book & book)
{
    Book *temp = new Book[book_amount+1];

    for(int i=0; i<book_amount; i++)
        temp[i] = move(list[i]);
    temp[book_amount] = book;
    book_amount++;

    delete[] list;
    list = temp;
}

void Library::print()
{
    cout<<"Book amount: "<<book_amount<< endl;
    for(int i=0; i<book_amount; i++)
    {
        list[i].print();
        cout<<endl;
    }
}

void Library::save(ofstream & str)
{
    if(book_amount==0)
        return;
    str.write((char*)&book_amount,sizeof(int));
    for(int i=0; i<book_amount; i++)
        list[i].save(str);
}
