class Book
{
    char *author,*heading,*directory,*description,*isbn;
    int rating

    void deleteDyn();

public:
    Book();
    Book(const Book&);
    Book(Book&&);
    Book& operator=(const Book&);
    Book& operator=(Book&&);
    ~Book();

    bool load();
};
