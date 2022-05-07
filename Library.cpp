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
    {
        bool res = list[i].load(str);
        if(res==false) return false;
    }
    return true;
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

bool Library::findBook(Book& result,const char* str,SearchMode mode, bool ignore)
{
    for(int i=0; i<book_amount; i++)
        if(list[i].compBook(str,mode,ignore))
        {
            result = list[i];
            return true;
        }
    return false;
}


void Library::simplePrint()
{
    cout<<"Book amount: "<<book_amount<< endl<<endl;
    for(int i=0; i<book_amount; i++)
    {
        list[i].print();
        cout<<endl;
    }
}

void Library::printSorted(SortMode mode,bool des)
{
    cout<<"Book amount: "<<book_amount<< endl<<endl;

    if(book_amount ==0)
        return;

    Book** arr = new Book*[book_amount];
    for(int i=0; i<book_amount; i++)
        arr[i] = list+i;
    // bubble sort ascending

    for(int i=0; i<book_amount-1; i++)
        for(int j=book_amount-2; j>=i; j--)
            if( (*arr[j+1]).lessThan( *arr[j] , mode) )
                swap( arr[j+1], arr[j]);

    if(des)
        for(int i=book_amount-1; i>=0; i--)
        {
            (*arr[i]).shortPrint();
            cout<<endl;
        }
    else
        for(int i=0; i<book_amount; i++)
        {
            (*arr[i]).shortPrint();
            cout<<endl;
        }
}

void Library::delBook(const char * heading)
{
    int pos=-1;
    for(int i=0; i<book_amount; i++)
        if(list[i].compBook(heading,title_m,false))
        {
            pos = i;
            break;
        }
    if(pos==-1)
        return;
    if(book_amount == 1)
    {
        delete[] list;
        list = nullptr;
        book_amount = 0;
        return;
    }
    Book *temp = new Book[book_amount-1];
    for(int i=0; i<pos; i++)
        temp[i] = move(list[i]);
    for(int i=pos; i<=book_amount-2; i++)
        temp[i] = move(list[i+1]);
    delete[] list;
    list = temp;
    book_amount--;
}

void Library::save(ofstream & str)
{
//    if(book_amount==0)
//        return;
    str.write((char*)&book_amount,sizeof(int));
    for(int i=0; i<book_amount; i++)
        list[i].save(str);
}
