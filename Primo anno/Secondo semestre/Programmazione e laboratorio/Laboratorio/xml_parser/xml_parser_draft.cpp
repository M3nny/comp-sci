#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cassert>

// XML tutorial: https://www.w3schools.com/xml/
// XML viewer online: https://countwordsfree.com/xmlviewer
// dataset:
// https://aiweb.cs.washington.edu/research/projects/xmltk/xmldata/data/mondial/mondial-3.0.xml

/*
    XML Grammar (after removing comments and XML preamble):

    note: X,Y are not nonterminals: they stand for "any string"

    A tree is either an enclosed sequence of trees (S)
    or an enclosed string (leaf) or self-closing tag.
    T -> <X A> TS </X> | <X A> Y </X> | <X A/>

    sequence of trees
    S -> epsilon | TS

    a list of attributes
    A -> epsilon | X="Y" A | X='Y' A
 */

struct keyvalue {
    std::string key;
    std::string val;
};

std::vector<keyvalue> kv;

struct parse_error {
    std::string msg;
};

// check if 'read' and 'expected' characters match
void check(char read, char expected) {
    std::string err{"Parse error. Read: '"};
    err += read;
    err.append("'. Expected: '");
    err += expected;
    err.append("'.");
    if (read != expected) throw parse_error{err};
}

// removes from std::cin:
// 1) the XML preamble <?xml string ?>
// 2) all comments, of the form   <!-- string -->
std::string remove_comments() {
    std::string res;

    while (std::cin) {
        char c1 = 0, c2 = 0;
        c1 = std::cin.get();

        if (c1 == '<') {
            c2 = std::cin.get();

            if (c2 == '!' or c2 == '?') {
                char buf[2];
                buf[0] = std::cin.get();
                buf[1] = std::cin.get();

                int i = 0;  // start position in buf

                while (not((buf[i % 2] == '-' and buf[(i + 1) % 2] == '>') or
                           (buf[i % 2] == '?' and buf[(i + 1) % 2] == '>'))) {
                    buf[i % 2] = std::cin.get();
                    i++;
                }

            } else {
                res += c1;
                res += c2;
            }

        } else {
            if (not std::cin.eof()) res += c1;
        }
    }

    return res;
}

// T inizia sempre con <nome ...
// epsilon inizia con </nome>

void T(std::istream&);

void S(std::istream& is) {
    // S -> epsilon | TS
    char c1 = 0, c2 = 0;
    is >> c1 >> c2;
    is.putback(c2);
    is.putback(c1);

    if (c1 == '<' and c2 != '/') { // caso TS
        T(is);
        S(is);
    }
};

void A(std::istream& is) {
    // is è nel formato 'A' oppure 'A/'
    // A -> epsilon | X = "Y" | X = 'Y'

    char c = 0;
    is >> c;
    if (is.eof() or c == '/') return;

    is.putback(c);

    // A -> X = "Y" | X = 'Y'

    std::string x;
    std::string y;
};

void T(std::istream& is) {
    // T -> <XA> TS </X> | <XA> Y </X> | <XA/>
    char c = 0;
    is >> c; // consume '<'
    check(c, 'c');
    std::string tag; // contiene la stringa che andrò ad estrarre
    std::getline(is, tag, '>'); // tag conterrà XA oppure XA/

    std::istringstream iss {tag};
    std::string x1;
    std::getline(iss, x1, ' ');

    // iss contiene 'A' oppure 'A/'
    A(iss);
    // iss contiene ' ' oppure '/'

    if (tag.back() == '/') return; // caso T -> <XA/>
    // T -> <XA> TS </X> | <XA> Y </X>
    // is può essere "TS </X>" oppure "Y </X>"
    is >> c;
    is.putback(c);

    if (c == '<') {
        // T -> <XA> TS </X>
        // is è "TS </X>"
        T(is);
        S(is);
        is >> c;
        check(c, '<');
    } else {
        // T -> <XA> Y </X>
        // is è "Y </X>"

        std::string Y;
        std::getline(is, Y, '<');
    }
    // is è "/X>"
    is >> c;
    check(c, '/');

    std::string x2;
    std::getline(is, x2, '>');

    // is è vuoto
    //
    if (x1 != x2) {
        throw parse_error{"Parse error: closing tag '" + x2 + "' does not match opening tag '" + x1 + "'."};
    }

}

// 1) parses the XML from std::cin, checking some (not all) format errors
// 2) extract all values of attributes "population" and stores them as integers to file "population"
// 3) loads back the integers from file "population" and stores them in a vector.

int main() {
    std::string xml = remove_comments();
    std::istringstream iss{xml};
    try {
        T(iss);
    } catch (const parse_error& e) {
        std::cout << e.msg << std::endl;
        return 1;
    }
    std::cout << "XML is in correct format." << std::endl;

    std::vector<uint64_t> population;
    for (auto p : kv) {  // extract all populations
        if (p.key == "population") population.push_back(stoi(p.val));
    }
    uint64_t N = population.size();

    // store populations in a binary file called "population"
    std::ofstream ofs{"population", std::ios::binary};
    ofs.write(reinterpret_cast<const char*>(population.data()), N * sizeof(uint64_t));
    ofs.close();

    // read back populations from file and store them in a new vector
    std::ifstream ifs{"population", std::ios::binary};
    std::vector<uint64_t> population2(N, 0);
    ifs.read(reinterpret_cast<char*>(population2.data()), N * sizeof(uint64_t));
    ifs.close();

    assert(population == population2);
    return 0;
}
