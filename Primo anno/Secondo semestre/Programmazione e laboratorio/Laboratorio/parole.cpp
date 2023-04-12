#include <string>
#include <vector>
#include <iostream>


using std::vector;
using std::string;
using std::cout;
using std::endl;

void all_words(const vector<char>& alphabet, string& prefix, int k) {
    cout << prefix <<  endl;
    if (prefix.length() == k) {
        return;
    }
    for (auto c:alphabet) {
        prefix.push_back(c);
        all_words(alphabet, prefix, k);
        prefix.pop_back();
    }

}


int main () {
    string prefix {};
    vector<char> alphabet = {'a', 'b', 'c'};
    int k = 3;

    all_words(alphabet, prefix, k);
}
