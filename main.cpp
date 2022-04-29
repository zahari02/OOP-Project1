#include <iostream>
#include "Library.h"
#include "PasswordManager.h"
using namespace std;

void clearCin()
{
    cin.clear();
    while(cin.peek() != '\n')
        cin.ignore();
    cin.ignore();
}

void login(bool &admin, PasswordManager &mgr)
{
    char buff[20];

    cout<<"\nWrite Password:\n";

    cin.getline(buff,max_pass);
    if(!cin)
    {
        cout<<"Error: Input too long\n\n";
        clearCin();
        return;
    }
    if(mgr.find(buff))
    {
        admin = true;
        cout<<"Successful login!\n\n";
    }
    else
    {
        cout<<"Wrong Password\n\n";
    }
}

void addBook(Library &lib)
{
    Book book;
    char buff[max_description+10];

    cout<<"Enter book title: "<< endl;
    cin.getline(buff,max_heading);
    if(!cin)
    {
        clearCin();
        cout<<"Input too long"<< endl;
        return;
    }
    book.setHeading(buff);

    cout<<"Enter book author: "<< endl;
    cin.getline(buff,max_author);
    if(!cin)
    {
        clearCin();
        cout<<"Input too long"<< endl;
        return;
    }
    book.setAuthor(buff);

    cout<<"Enter book description: "<< endl;
    cin.getline(buff,max_description);
    if(!cin)
    {
        clearCin();
        cout<<"Input too long"<< endl;
        return;
    }
    book.setDescription(buff);

    cout<<"Enter book text directory: "<< endl;
    cin.getline(buff,max_directory);
    if(!cin)
    {
        clearCin();
        cout<<"Input too long"<< endl;
        return;
    }
    book.setDirectory(buff);

    cout<<"Enter book isbn: "<< endl;
    cin.getline(buff,max_isbn);
    if(!cin)
    {
        clearCin();
        cout<<"Input too long"<< endl;
        return;
    }
    book.setIsbn(buff);

    cout<<"Enter book rating: "<< endl;
    int temp;
    cin>>temp;
    if(!cin)
    {
        clearCin();
        cout<<"Wrong Input"<< endl;
        return;
    }
    cin.ignore();
    book.setRating(temp);

    book.setLoaded(true);
    lib.add(book);
    cout<<"Book successfully added\n\n";
}

int mainPage(bool &admin, Library &lib, PasswordManager &mgr)
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

    char buff[10];
    cin.getline(buff,5);

    if(!cin)
    {
        clearCin();
        cout<<"Error: Command too long"<< endl<< endl;
        return -1;
    }
    if(strlen(buff)!=1)
    {
        cout<<"Error: Invalid command"<< endl<<endl;
        return -1;
    }

    char number = buff[0];
    if(number<'0' || (number>'4' && admin == false) || number>'6')
    {
        cout<<"Error:Invalid command"<<endl<< endl;
        return -1;
    }

    if(number == '0')
        return 0;

    if(number == '3')
        lib.print();

    if(admin)
    {
        if(number=='4')
            addBook(lib);
    }
    else
    {
        if(number=='4')
            login(admin,mgr);
    }
    return -1;
}

void loadLib(Library &lib)
{
    ifstream file("LibraryDatabase.dat", ios::binary);
    if(!file)
    {
        cout<<"No libdatabase"<< endl;
        return;
    }
    lib.load(file);
}

void loadMgr(PasswordManager &mgr)
{
    ifstream file("PasswordDatabase.txt");
    if(!file)
    {
        cout<<"Error"<< endl;
        return;
    }
    mgr.load(file);
    file.close();
}

void run()
{
    bool admin = false;

    Library lib;
    loadLib(lib);

    PasswordManager mgr;
    loadMgr(mgr);

    int result;
    while(1)
    {
        result = mainPage(admin,lib,mgr);
        if(result == 0)
            break;
    }
}

int main()
{
    run();
    return 0;
}
