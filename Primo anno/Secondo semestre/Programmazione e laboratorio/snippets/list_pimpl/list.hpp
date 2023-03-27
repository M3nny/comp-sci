class List_int {
public:
    List_int();
    List_int(const List_int& l);
    ~List_int();

    void prepend(int el);
    void append(int el);
    void stampa() const;
private:
    struct impl; // implementation
    // i byte che uso per un puntatore a char rispetto ad un puntatore a qualcos'altro sono uguali, quindi il compilatore sa quanto spazio allocare
    impl* pimpl;
};
