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

void tu_xao_tron(vector<string> &arr) {
    int n = arr.size();

    for (int i = n - 1; i > 0; i--) {
        int j = rng() % (i + 1);

        swap(arr[i], arr[j]);
    }
}

void test3() {
    ofstream fout("test3.in");

    vector<string> ans;

    int groups = 2500;
    int bucket = 32;
    int prefA = 90;
    int prefB = 5;

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

    tu_xao_tron(ans);

    fout << ans.size() << '\n';

    for (const string &s : ans) {
        fout << s << '\n';
    }

    fout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test3();

    cout << "Da tao xong test3.in\n";

    return 0;
}