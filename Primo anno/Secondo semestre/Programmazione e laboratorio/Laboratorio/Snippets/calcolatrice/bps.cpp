#include <iostream>
#include <string>
#include <cassert>

int T(); // forward declaration

// read from std::cin a sequence of balanced parenthesis
// representing a sequence of trees
// and output the height of the hoghest tree
int S() {
    // S -> epsilon | TS
    char c = 0;
    std::cin >> c; // read and consume next parenthesis
    std::cin.putback(c); // put back the consumed parenthesis
    if (c == '(') {
        int h1 = T(); // height of the first tree in the sequence
        int h2 = S(); // height of the tallest tree in the rest of the sequence
        return std::max(h1, h2);
    } else { // c == ')'
        return 0;
    }
}

// read from std::cin a sequence of balanced parenthesis
// representing a tree
// and output the height of the tree
int T() {
    // T -> (S)
    // e.g. ( () () ), S eats " () () "
    char c = ' ';
    std::cin >> c; // eat '('
    assert(c=='(');
    int h = S();
    std::cin >> c; // eat ')'
    assert(c==')');
    return h + 1;
}

int main () {
    std::cout << "Insert the parenthesis tree: " << std::endl;
    int h = T()-1;
    std::cout << "Height of the tree: " << h << std::endl;
    return 0;
}
