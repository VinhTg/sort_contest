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

void test5() {
    ofstream fout("test5.in");

    vector<string> ans;

    for (int g = 0; g < 2000; g++) {

        int bucket = (g & 1) ? 16 : 32;

        string pref(70, 'a');

        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));

        for (int i = 0; i < bucket; i++) {

            string s = pref;

            s += string(20, 'a');

            s += tail_string(bucket - i);

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

    test5();

    cout << "Da tao xong test5.in\n";

    return 0;
}