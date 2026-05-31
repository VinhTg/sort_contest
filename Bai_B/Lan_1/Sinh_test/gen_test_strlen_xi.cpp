#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

void hoan_doi(string &a, string &b) {
    string temp = a;
    a = b;
    b = temp;
}

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
        int j = rand() % (i + 1);
        hoan_doi(arr[i], arr[j]);
    }
}

void test1() {
    ofstream fout("test1.in");
    vector<string> ans;
    int groups = 3125, bucket = 32, prefA = 45, prefB = 45;
    for (int g = 0; g < groups; g++) {
        string pref(prefA, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));
        for (int i = 0; i < bucket; i++) {
            ans.push_back(pref + string(prefB, 'a') + tail_string(bucket - i));
        }
    }
    tu_xao_tron(ans);
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
    fout.close();
}

void test2() {
    ofstream fout("test2.in");
    vector<string> ans;
    int groups = 6250, bucket = 16, prefA = 45, prefB = 45;
    for (int g = 0; g < groups; g++) {
        string pref(prefA, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));
        for (int i = 0; i < bucket; i++) {
            ans.push_back(pref + string(prefB, 'a') + tail_string(bucket - i));
        }
    }
    tu_xao_tron(ans);
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
    fout.close();
}

void test3() {
    ofstream fout("test3.in");
    vector<string> ans;
    int groups = 2500, bucket = 32, prefA = 90, prefB = 5;
    for (int g = 0; g < groups; g++) {
        string pref(prefA, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));
        for (int i = 0; i < bucket; i++) {
            ans.push_back(pref + string(prefB, 'a') + tail_string(bucket - i));
        }
    }
    tu_xao_tron(ans);
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
    fout.close();
}

void test4() {
    ofstream fout("test4.in");
    vector<string> ans;
    int groups = 2000, bucket = 50, prefA = 95, prefB = 1;
    for (int g = 0; g < groups; g++) {
        string pref(prefA, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));
        for (int i = 0; i < bucket; i++) {
            ans.push_back(pref + string(prefB, 'a') + tail_string(bucket - i));
        }
    }
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
    fout.close();
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
            ans.push_back(pref + string(20, 'a') + tail_string(bucket - i));
        }
    }
    tu_xao_tron(ans);
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
    fout.close();
}

int main(int argc, char* argv[]) {
    srand(12345);
    if (argc < 3) return 1;
    int test_num = stoi(argv[2]);
    switch (test_num) {
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); break;
        case 4: test4(); break;
        case 5: test5(); break;
        default: return 1;
    }
    return 0;
}