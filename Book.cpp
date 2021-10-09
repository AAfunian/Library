// Book
// 10/07/2021
// Amir Afunian
// Exercise #8

#include <iostream>
#include <ctype.h>
#include <vector>
using namespace std;

enum class Genre {
    fiction, nonfiction, periodical, biography, children
};
class Patron {
private:
    string name;
    int lib_number;
    double balance;
public:
    Patron(string name, int lib_number, double balance);
    string get_name();
    int get_lib();
    double get_balance();
    void set_balance(double);
    bool has_balance();
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
class Book {
private:
    string isbn;
    string title;
    string author;
    string copyright;
    Genre type;
    bool available = true;
public:
    Book(string isbn, string title, string author, string copyright, Genre type);
    void check_in();
    void check_out();
    string get_isbn();
    string get_title();
    string get_author();
    string get_copyright();
    Genre get_genre();
    bool validISBN(string);
};
Book::Book(string i, string t, string a, string c, Genre g) {
    if (validISBN(i)) isbn = i;
    else return;
    //cout << "ISBN: " << isbn << " SUCCESS!\n"; // TEST
    title = t;
    author = a;
    copyright = c;
    type = g;
    cout << "Book listed!\n";
}
void Book::check_in() {
    if (!available) available = true;
    else cout << "Book already checked in!\n";
}
void Book::check_out() {
    if (available) available = false;
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
        cout << "Same book!\n";
        return false;
    }
    else cout << "Different books!\n";
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

int main()
{
    Patron amir("Amir", 1, 5.99);
    amir.has_balance();
    amir.set_balance(-20);
    amir.has_balance();
    Book test("39-66-73-K", "Amir's Book", "Amir Afunian", "2007", Genre::nonfiction);
    cout << test;
    Book test2("54-2-973-z", "Joe's Book", "Joe Smith", "1988", Genre::periodical);
    cout << test2;
    test != test2;
}
