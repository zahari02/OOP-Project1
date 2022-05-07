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
    delete[] arr;
}

bool PasswordManager::load(ifstream & str)
{
    if(size!=0)
        return false;
    str>>size;
    if(!str) return false;
    str.ignore();

    arr = new char*[size];

    char buff[max_pass+5];
    for(int i=0; i<size; i++)
    {
        str.getline(buff,max_pass);
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

void PasswordManager::addPass(const char * pass)
{
    char ** temp = new char*[size+1];
    for(int i=0; i<size; i++)
        temp[i] = arr[i];
    temp[size] = new char[ strlen(pass)+1 ];
    strcpy( temp[size], pass );
    delete[] arr;
    arr = temp;
    size++;
}

bool PasswordManager::save(ofstream &file)
{
    file<<size<<endl;
    for(int i=0; i<size; i++)
        file<<arr[i]<<endl;
}
