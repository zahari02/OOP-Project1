#include <iostream>
#include "Library.h"
#include "PasswordManager.h"
using namespace std;

const char * const lib_dir = "LibraryDatabase.dat";
const char * const pass_dir = "PasswordDatabase.txt";

void clearCin()
{
    cin.clear();
    while(cin.peek() != '\n')
        cin.ignore();
    cin.ignore();
}

bool checkCin()
{
    if(!cin)
    {
        cout<<"Input too long\n\n";
        clearCin();
        return false;
    }
    return true;
}

bool checkCommand(const char * command,char minval,char maxval)
{
    if(!checkCin())
        return false;

    if( strlen(command) != 1 || command[0] < minval || command[0] > maxval)
    {
        cout<<"Wrong command\n\n";
        return false;
    }
    return true;
}

void saveLib(Library& lib)
{
    ofstream file(lib_dir,ios::binary);
    if(!file)
    {
        cout<<"Error Saving Library"<< endl;
        return;
    }
    lib.save(file);
    file.close();
}

void savePass(PasswordManager &mgr)
{
    ofstream file(pass_dir);
    if(!file)
    {
        cout<<"Error Saving Passwords"<< endl;
        return;
    }
    mgr.save(file);
    file.close();
}

void printSorted(Library &lib)
{
    char buff[5];
    SortMode mode;
    bool des;

    cout<<"Choose sort criterion:\n";
    cout<<"(1) Sort by title\n";
    cout<<"(2) Sort by author\n";
    cout<<"(3) Sort by rating\n";

    cin.getline(buff,3);
    if(!checkCommand(buff,'1','3'))
        return;
//   for debug
//    if(buff[0] == '4')
//    {
//        lib.simplePrint();
//        return;
//    }

    mode = (SortMode)(buff[0] - '1');

    cout<<"Choose sort criterion:\n";
    cout<<"(1) Sort ascending\n";
    cout<<"(2) Sort descending\n";

    cin.getline(buff,3);
    if(!checkCommand(buff,'1','2'))
        return;

    des = buff[0] - '1';

    lib.printSorted(mode,des);
}

void findBook(Library& lib)
{
    char buff[max_description+10];
    cout<<"Write one of the following: title, author, ISBN, part of description."<< endl;
    cin.getline(buff,max_description);
    if(!checkCin())
        return;

    Book res;
    if(!lib.findBook(res,buff,title_m,true))
        if(!lib.findBook(res,buff,author_m,true))
            if(!lib.findBook(res,buff,isbn_m,true))
                if(!lib.findBook(res,buff,description_m,true))
                {
                    cout<<"Book not found.\n\n";
                    return;
                }
    cout<<"Book found!\n\n";
    res.print();
    cout<<endl;
}

void wait()
{
    char buff[5];
    cin.getline(buff,3);
    if(!cin)
        clearCin();
}

void printContent(Library& lib)
{
    char buff[max_heading+5];
    bool sent=false;
    Book res;
    ifstream file;

    cout<<"Write book title\n";
    cin.getline(buff,max_heading);
    if(!checkCin())
        return;

    if(!lib.findBook(res,buff,title_m,false))
    {
        cout<<"Book not found.\n\n";
        return;
    }

    if(!res.getFile(file))
    {
        cout<<"Error opening file.\n\n";
        return;
    }

    cout<<"Choose print mode:\n";
    cout<<"(1) Print rows\n";
    cout<<"(2) Print sentences\n";

    cin.getline(buff,3);
    if(!checkCommand(buff,'1','2'))
        return;

    sent = buff[0] - '1';

    cout<<"Press enter for next\n";
    char buff2 = file.get();
    while(!file.eof())
    {
        if(!sent)
        {
            if(buff2=='\n')
                wait();
            else
                cout<<buff2;
        }
        else
        {
            if(buff2 !='\n')
                cout<<buff2;
            if(buff2 == '.' || buff2 == '?' || buff2 == '!')
                wait();
        }
        buff2 = file.get();
    }
    cout<<endl<<endl;
    file.close();
}

void login(bool &admin, PasswordManager &mgr)
{
    char buff[20];

    cout<<"\nWrite Password:\n";

    cin.getline(buff,max_pass);
    if(!checkCin())
        return;

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
    if(!checkCin())
        return;

    book.setHeading(buff);

    cout<<"Enter book author: "<< endl;
    cin.getline(buff,max_author);
    if(!checkCin())
        return;

    book.setAuthor(buff);

    cout<<"Enter book description: "<< endl;
    cin.getline(buff,max_description);
    if(!checkCin())
        return;

    book.setDescription(buff);

    cout<<"Enter book text directory: "<< endl;
    cin.getline(buff,max_directory);
    if(!checkCin())
        return;

    book.setDirectory(buff);

    cout<<"Enter book isbn: "<< endl;
    cin.getline(buff,max_isbn);
    if(!checkCin())
        return;

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

void removeBook(Library &lib)
{
    char buff[max_heading+5],buff2[5];

    cout<<"Write book title\n";
    cin.getline(buff,max_heading);
    Book book;
    if(!lib.findBook(book,buff,title_m,false))
    {
        cout<<"Book not found"<< endl;
        return;
    }

    cout<<"Do you want to delete book content?\n";
    cout<<"(1) No.\n";
    cout<<"(2) Yes.\n";
    cin.getline(buff2,3);
    if(!checkCommand(buff2,'1','2'))
        return;

    if(buff2[0] == '2')
        if( !book.delFile() )
            cout<<"Error deleting book content.\n";
        else
            cout<<"File deleted successfully.\n";

    lib.delBook(buff);
    cout<<"Book deleted successfully\n\n";
}

void addUser(PasswordManager &mgr)
{
    char buff[max_pass+5];
    cout<<"Write new password:\n";
    cin.getline(buff,max_pass);
    if(!checkCin())
        return;
    mgr.addPass(buff);
    cout<<"New password added.\n\n";
}

int mainPage(bool &admin, Library &lib, PasswordManager &mgr)
{
    if(admin)
        cout<<"----- Authorized access -----"<< endl;
    else
        cout<<"----- Unauthorized access -----"<< endl;
    cout<<"Enter number to choose command: "<< endl;
    cout<<"(0) Exit and Save"<< endl;
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
    // command correctness
    if(!checkCin())
        return -1;

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
    //       command logic
    if(number == '0')
    {
        saveLib(lib);
        savePass(mgr);
        return 0;
    }

    if(number == '1')
    {
        printSorted(lib);
        return 1;
    }

    if(number == '2')
    {
        findBook(lib);
        return 2;
    }
    if(number == '3')
    {
        printContent(lib);
        return 3;
    }

    if(admin)
    {
        if(number=='4')
        {
            addBook(lib);
            return 4;
        }
        if(number=='5')
        {
            removeBook(lib);
            return 5;
        }
        if(number=='6')
        {
            addUser(mgr);
            return 6;
        }
    }
    else
    {
        if(number=='4')
        {
            login(admin,mgr);
            return 4;
        }
    }
    return -1;
}


void loadLib(Library &lib)
{
    ifstream file(lib_dir, ios::binary);
    if(!file)
    {
        ofstream ofile(lib_dir, ios::binary);
        int temp=0;
        ofile.write((char*)&temp,sizeof(int));
        ofile.close();

        file.open(lib_dir, ios::binary);
//        cout<<"No libdatabase"<< endl;
//        return;
    }
    bool res = lib.load(file);
    if(res==false)
        cout<<"Error loading Library Database"<< endl;
    file.close();
}

void loadMgr(PasswordManager &mgr)
{
    ifstream file(pass_dir);
    if(!file)
    {
        ofstream ofile(pass_dir);
        ofile<<"1\nadmin\n";
        ofile.close();

        file.open(pass_dir);
    }
    bool res = mgr.load(file);
    if(res == false)
        cout<<"Error loading Password Database"<< endl;
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
//    ofstream f;
//    char buff[50];
//    cin.getline(buff,30);
//    f.open(buff);
//    f.close();
    return 0;
}
