#include <iostream>
#include <string>

using std::cin;
using std::cerr;
using std::endl;
using std::cout;
using std::string;

struct parse_errors {
    string msg;
};

int evaluate () {
    char op = ' ';
    double lval, rval;
    lval = rval = 0;

    cout << "Insert expression (valid operands: +-*/): " << endl;
    cout << "The expression must end with =" << endl;
    cin >> lval >> op;

    if (!cin) throw parse_errors{"The first operand or operator are wrong"};

    while(op != '=') {
        cin >> rval;
        if (!cin) throw parse_errors{"invalid operand"};

        switch(op) {
            case '+': lval += rval; break;
            case '-': lval -= rval; break;
            case '*': lval *= rval; break;
            case '/': lval /= rval; break;
            if (!cin) throw parse_errors{"invalid operator"};
        }
        cin >> op;
    }
    cout << "The result is: " << lval << endl;
    return 0;
}

int main () {
    try {
        return evaluate();
    } catch (const parse_errors& e) {
        cerr << e.msg << endl;
        return 1;
    }
    return 0;
}
