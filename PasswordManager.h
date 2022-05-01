#include <cstdio>
#include <fstream>
#include <cstring>
const int max_pass=15;

using namespace std;
class PasswordManager
{
public:
    char **arr;
    int size;

//public:
    PasswordManager();
    PasswordManager(const PasswordManager&) = delete;
    PasswordManager& operator=(const PasswordManager&) = delete;
    ~PasswordManager();

    bool load(ifstream&);
    bool find(const char *);
    bool save(ofstream&);
};
