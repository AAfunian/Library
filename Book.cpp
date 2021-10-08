// Book
// 10/06/2021
// Amir Afunian

#include <iostream>
#include <ctype.h>
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    string copyright;
    bool available = true;
public:
    Book(string isbn, string title, string author, string copyright);
    void check_in();
    void check_out();
    string get_isbn();
    string get_title();
    string get_author();
    string get_copyright();
    bool validISBN(string);
};
Book::Book(string i, string t, string a, string c) {

    if (validISBN(i)) isbn = i;
    else return;
    //cout << "ISBN: " << isbn << " SUCCESS!\n"; // TEST
    title = t;
    author = a;
    copyright = c;
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
    Book test("39-66-73-K", "Amir's Book", "Amir Afunian", "2007");
}
