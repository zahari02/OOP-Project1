#include "PasswordManager.h"

PasswordManager::PasswordManager()
{
    arr = nullptr;
    size=0;
}

PasswordManager::~PasswordManager()
{
    for(int i=0; i<size; i++)
        delete[] arr[i];
}

bool PasswordManager::load(ifstream & str)
{
    if(size!=0)
        return false;
    str>>size;
    if(!str) return false;
    str.ignore();

    arr = new char*[size];

    char buff[20];
    for(int i=0; i<size; i++)
    {
        str.getline(buff,20);
        if(!str) return false;

        arr[i] = new char[ strlen(buff) +1 ];
        strcpy( arr[i], buff);
    }
    return true;
}

bool PasswordManager::find(const char* pass)
{
    bool found = false;
    for(int i=0; i<size; i++)
        if(strcmp( arr[i], pass ) == 0 )
            found = true;
    return found;
}
