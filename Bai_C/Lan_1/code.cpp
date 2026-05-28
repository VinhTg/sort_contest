#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

const int R = 26;



void RadixSort(vector<string>&a,vector<string>&temp,int l,int r,int pos,int len){
    if(r-l<=1||pos>=len) return ;
    int cnt[R+1];
    memset(cnt,0,sizeof(cnt));

    for (int i=l;i<r;i++){
        char ch = a[i][pos];
        int c = ch - 'a';
        cnt[c+1]++;
    }

    for (int i=1;i<=R;i++){
        cnt[i]+=cnt[i-1];
    }

    int st[R+1];
    for (int i = 0; i <= R; i++) st[i] = cnt[i];

    for (int i = l; i < r; i++) {
        char ch = a[i][pos];
        int c = ch - 'a';
        temp[l + cnt[c]] = a[i];
        cnt[c]++;
    }

    for (int i=l;i<r;i++){
        a[i].swap(temp[i]);
    }
    
    for (int i=0;i<R;i++){
        int l1=l+st[i];
        int r1=l+st[i+1];
        if(r1-l1>1)RadixSort(a,temp,l1,r1,pos+1,len);
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n ;cin >> n;
    vector<string> a[101];

    for(int i=0;i<n;i++){
        string s;cin >>s;
        a[s.size()].push_back(s);
    }

    cout <<n<<'\n';


    for (int i=10;i<=100;i++){
        if(a[i].empty()) continue;

        vector<string> temp(a[i].size());

        RadixSort(a[i],temp,0,(int)a[i].size(),0,i);

        for (const string &x : a[i]) cout<<x<<'\n';

    }


 

    return 0;
}