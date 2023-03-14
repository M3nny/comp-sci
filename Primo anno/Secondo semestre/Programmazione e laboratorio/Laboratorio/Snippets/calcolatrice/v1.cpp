#include <iostream>

using std::cin;
using std::cerr;
using std::endl;
using std::cout;

// operatori formattati e non, la get non salta gli spazi (non formattato)
int main () {
    char op = ' ';
    int lval, rval, res;
    lval = rval = res = 0;

    cin >> lval >> op >> rval;

    if (op == '+') {
        res = lval + rval;
    } else if (op == '-') {
        res = lval - rval;
    } else {
        cerr << "Invalid operand: " << op << endl;
        return 1;
    }
    cout << "The result is: " << res << endl;
    return 0;
}
