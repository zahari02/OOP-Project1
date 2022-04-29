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

    if(number=='4' && admin==false)
        login(admin,mgr);
}

void loadLib(Library &lib)
{

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


    PasswordManager mgr;
    loadMgr(mgr);

    while(1)
    {
        mainPage(admin,lib,mgr);
    }
}

int main()
{
    run();
    return 0;
}
