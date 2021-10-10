// Book
// 10/07/2021
// Amir Afunian

#include <iostream>
#include <ctype.h>
#include <vector>
using namespace std;

enum class Genre {
    fiction, nonfiction, periodical, biography, children
};
class Patron {
public:
    Patron(string name, int lib_number, double balance);
    string get_name();
    int get_lib();
    double get_balance();
    void set_balance(double);
    bool has_balance();
private:
    string name;
    int lib_number;
    double balance;
};
Patron::Patron(string n, int l, double b) {
    name = n;
    lib_number = l;
    balance = b;
}
string Patron::get_name() {
    return name;
}
int Patron::get_lib() {
    return lib_number;
}
double Patron::get_balance() {
    return balance;
}
void Patron::set_balance(double fee) {
    balance += fee; // Assumes fee is positive or negative depending on dues or payment
}
bool Patron::has_balance() {
    //return balance > 0 ? true : false; // Optimal if cout not required
    if (balance > 0) {
        cout << get_name() << "'s current dues: $" << get_balance() << '\n';
        return true;
    }
    else {
        int neg = get_balance() < 0 ? -1 : 1;
        cout << get_name() << "'s current balance: $" << neg*get_balance() << '\n';
        return false;
    }
}
bool operator==(Patron x, Patron y) {
    if (x.get_lib() == y.get_lib()) return true;
    return false;
}
ostream& operator<<(ostream& os, Patron p) {
    cout << p.get_name();
    return os;
}
class Book {
public:
    Book(string isbn, string title, string author, string copyright, Genre type);
    void check_in();
    void check_out();
    bool checked_out();
    string get_isbn();
    string get_title();
    string get_author();
    string get_copyright();
    Genre get_genre();
    bool validISBN(string);
private:
    string isbn;
    string title;
    string author;
    string copyright;
    Genre type;
    bool available = true;
};
Book::Book(string i, string t, string a, string c, Genre g) {
    if (validISBN(i)) isbn = i;
    else return;
    //cout << "ISBN: " << isbn << " SUCCESS!\n"; // TEST
    title = t;
    author = a;
    copyright = c;
    type = g;
}
bool Book::checked_out() {
    if (available) return false;
    else return true;
}
void Book::check_in() {
    if (checked_out()) {
        available = true;
        cout << "Checked in successfully!\n";
    }
    else cout << "Book already checked in!\n";
}
void Book::check_out() {
    if (!checked_out()) {
        available = false;
        cout << "Checked out successfully!\n";
    }
    else cout << "Book unavailable!\n";
}
string Book::get_isbn() {
    return isbn;
}
string Book::get_title() {
    return title;
}
string Book::get_author() {
    return author;
}
string Book::get_copyright() {
    return copyright;
}
Genre Book::get_genre() {
    return type;
}
ostream& operator<<(ostream& os, Genre g) {
    vector<string> store { "Fiction", "Nonfiction", "Periodical", "Biography", "Children" };
    for (int i = 0; i < store.size(); i++) {
        if (int(g) == i) {
            cout << store[i];
            return os;
        }
    }
}
ostream& operator<<(ostream& os, Book x) {
    cout << "Title: " << x.get_title() << ", Author: " << x.get_author() << ", Genre: " << x.get_genre() << ", ISBN: " << x.get_isbn();
    return os << '\n';
}
bool operator==(Book x, Book y) {
    if (x.get_isbn() == y.get_isbn()) {
        cout << "Same book!\n";
        return true;
    }
    else cout << "Different books!\n";
    return false;
}
bool operator!=(Book x, Book y) {
    if (x.get_isbn() == y.get_isbn()) {
        //cout << "Same book!\n";
        return false;
    }
    //else cout << "Different books!\n";
    return true;
}
bool Book::validISBN(string i) {
    char prev;
    int counter = 0;
    bool valid = false;
    if (isdigit(i[0])) {
        prev = i[0];
        for (int j = 1; j < i.size(); j++) {
            if (i[j] == '-') {
                if (prev == '-') {
                    cout << "ISBN invalid! Error Code: 1\n"; // TEST
                    return valid;
                }
                else {
                    prev = i[j];
                    counter++;
                }
            }
            else {
                if (counter == 3) {
                    if (j == i.size() - 1 && isalnum(i[j])) {
                        valid = true;
                    }
                    else {
                        cout << "ISBN invalid! Error Code: 2\n"; // TEST
                        return valid;
                    }
                }
                else {
                    if (!isdigit(i[j])) {
                        cout << "ISBN invalid! Error Code: 3\n"; // TEST
                        return valid;
                    }
                    else {
                        prev = i[j];
                    }
                }
            }
        }
    }
    else {
        cout << "ISBN invalid! Error Code: 4\n"; // TEST
        return valid;
    }
    return valid;
}
struct Transaction {
    Transaction(Book& b, Patron& p) : item(b), user(p) {};
    Book item;
    Patron user;
};
ostream& operator<<(ostream& os, Transaction t) {
    cout << "Patron: " << t.user << ", " << t.item;
    return os;
}
class Library {
public:
    Library() {};
    void add_book(Book& b) { books.push_back(b); }
    void add_patron(Patron& p) { patrons.push_back(p); }
    void check_out(Patron&, Book&);
    void print();
    vector<Patron> debtors();
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;
};
void Library::check_out(Patron& p, Book& b) {
    bool pExist = false;
    bool bExist = false;

    for (size_t i = 0; i < patrons.size(); i++) {
        if (p == patrons[i]) {
            pExist = true;
            break;
        }
    }
    for (size_t i = 0; i < books.size(); i++) {
        if (b == books[i]) {
            bExist = true;
            break;
        }
    }
    if (pExist && bExist) {
        if (!p.has_balance()) {
            if (b.checked_out()) {
                b.check_out();
            }
            else {
                b.check_out();
                transactions.push_back(Transaction(b, p));
            }
        }
        else cout << p.get_name() << " cannot check out due to a pending balance!\n";
    }
    else cout << (bExist ? "This patron is not in our system!\n" : "This book does not exist in our system!\n");
}
void Library::print() {
    for (size_t i = 0; i < transactions.size(); i++) {
        cout << transactions[i];
    }
}
vector<Patron> Library::debtors() {
    vector<Patron> store;
    for (size_t i = 0; i < patrons.size(); i++) {
        cout << "Checking balances: ";
        if (patrons[i].has_balance()) {
            store.push_back(patrons[i]);
        }
    }
    return patrons;
}
int main()
{
    Library lib;
    Patron amir("Amir", 1, -5.99);
    Patron joe("Joe", 2, 10);
    Patron alex("Alex", 3, -20);
    Book eragon("39-66-73-K", "Eragon", "Emelia Trude", "2007", Genre::fiction);
    Book treehouse("54-2-973-z", "The Magic Treehouse", "Jane Smith", "2011", Genre::children);
    Book ranger("36-82-6-A", "The Ranger's Apprentice", "Don Abble", "2013", Genre::fiction);
    lib.add_book(eragon);
    lib.add_book(treehouse);
    lib.add_book(ranger);
    lib.add_patron(amir);
    lib.add_patron(joe);
    lib.add_patron(alex);
    lib.check_out(amir, eragon);
    lib.print();
    lib.check_out(joe, treehouse);
    lib.print();
    lib.check_out(alex, ranger);
    lib.print();
    lib.debtors();
}
