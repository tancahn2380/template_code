#include "bits/stdc++.h"
using namespace std;
typedef string::const_iterator State;
class ParseError {};

//https://gist.github.com/draftcode/1357281

//数字の列をパースして、その数を返す
int number(State &Begin){
    int ret = 0;

    while('0' <= *Begin && *Begin <= '9'){
        ret *= 10;
        ret += *Begin - '0';
        Begin++;
    }

    return ret;
}

//乗算除算の式をパースして、その評価結果を返す
int term(State &Begin){
    int ret = number(Begin);

    while(true){
        if(*Begin == '*'){
            Begin++;
            ret *= number(Begin);
        }else if(*Begin == '/'){
            Begin++;
            ret /= number(Begin);
        }else{
            break;
        }
    }
    return ret;
}

//四則演算の式をパースして、その評価結果を返す
int expression(State &Begin){
    int ret = term(Begin);
    while(true){
        if(*Begin == '+'){
            Begin++;
            ret += term(Begin);
        }else if(*Begin == '-'){
            Begin++;
            ret -= term(Begin);
        }else{
            break;
        }
    }
    return ret;
}

//括弧か数をパースして、その評価結果を返す
int factor(State &Begin){
    if(*Begin == '('){
        Begin++;
        int ret = expression(Begin);
        Begin++;
    }else{
        return number(Begin);
    }
}

int n;
string s;

int main(){
    cin >> n;
    cin.ignore();
    for(int i = 0;i < n;i+++){
        string s;
        getline(cin, s);

        State Begin = s.begin();
        int ans = expression(Begin);
        cout << ans << endl;
    }
}