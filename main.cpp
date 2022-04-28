#include <iostream>
#include "Library.h"
using namespace std;



int mainPage(bool &admin)
{
    if(admin)
        cout<<"----- Authorized access -----"<< endl;
    else
        cout<<"----- Unauthorized access -----"<< endl;
    cout<<"Enter number to choose command: "<< endl;
    cout<<"(0) Exit"<< endl;
    cout<<"(1) Print sorted list"<< endl;
    cout<<"(2) Find book"<< endl;
    cout<<"(3) Print book content"<< endl;
    if(admin)
    {
        cout<<"(4) Add book"<< endl;
        cout<<"(5) Remove book"<< endl;
        cout<<"(6) Register new user"<< endl;
    }
    else
    {
        cout<<"(4) Login"<< endl;
    }

    char buff[100];
    cin.getline(buff,90);

}

void run()
{
    bool admin = false;
    while(1)
    {
        mainPage(admin);
    }
}

int main()
{
   // run();
    fstream f;
    f.open("LibraryDataBase.dat", ios::binary | ios::out);
    int t=5;
    f.write((char*)&t,sizeof(int));
    f.write("abcd",5);
    f.close();

    ifstream f2;

   f2.open("LibraryDataBase.dat", ios::binary);

    Book b;
    cout<<b.load(f2)<< endl;
    cout<<b.author<< endl;


    f2.close();
    return 0;
}
