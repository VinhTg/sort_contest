#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

mt19937 rng(time(0));

string tail_string(int x, int len = 4) {
    string s = "";

    for (int i = 0; i < len; i++) {
        char c = 'z' - (x % 26);
        s += c;
        x /= 26;
    }

    return s;
}

void test4() {
    ofstream fout("test4.in");

    vector<string> ans;

    int groups = 2000;
    int bucket = 50;
    int prefA = 95;
    int prefB = 1;

    for (int g = 0; g < groups; g++) {

        string pref(prefA, 'a');

        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));

        for (int i = 0; i < bucket; i++) {

            int val = bucket - i;

            string s = pref;

            s += string(prefB, 'a');

            s += tail_string(val);

            ans.push_back(s);
        }
    }

    fout << ans.size() << '\n';

    for (const string &s : ans) {
        fout << s << '\n';
    }

    fout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test4();

    cout << "Da tao xong test4.in\n";

    return 0;
}