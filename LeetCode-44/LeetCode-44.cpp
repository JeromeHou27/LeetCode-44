#include <iostream>
#include <vector>

using namespace std;

struct Str {
    bool preSkip = false;
    string str = "";
    int backStrCount = 0;
};

vector<Str> split(string p) {
    vector<Str> vecStr;
    bool preStar = false;
    string str = "";

    for (int i = 0; i < p.size(); ++i) {
        if (p[i] == '*') {
            if (str != "") {
                vecStr.push_back(Str{ preStar = preStar, str = str });
                preStar = false;
                str = "";
            }

            preStar = true;
        }
        else if (p[i] != '*') {
            str += p[i];
        }
    }

    if (preStar || str != "") {
        vecStr.push_back(Str{ preStar = preStar, str = str });
    }

    int size = 0;
    for (int i = vecStr.size() - 1; i >= 0; --i) {
        vecStr[i].backStrCount = size;
        size = vecStr[i].str.size();
    }

    return vecStr;
}

bool startWith(const string& s, int offset, const string& p) {
    if (s.size() < p.size()) {
        return false;
    }

    for (int i = 0; i < p.size(); ++i) {
        if (s[i + offset] == p[i] || p[i] == '?')
            continue;

        return false;
    }

    return true;
}

bool endWith(const string& s, const string& p) {
    int sSize = s.size();
    int pSize = p.size();
    for (int i = 1; i <= pSize; ++i) {
        if (p[pSize - i] == '?' || s[sSize - i] == p[pSize - i])
            continue;

        return false;
    }

    return true;
}

int find(const string& s, int offset, const string& p) {
    for (int i = offset; i < s.size(); ++i) {
        if (startWith(s, i, p))
            return i + p.size();
    }

    return -1;
}

bool isMatch(string s, string p) {

    if (p == "") {
        return s == "";
    }

    vector<Str> v = split(p);
    int miniOffset = 0;

    for (int i = 0; i < v.size(); ++i) {
        if (s.size() - miniOffset < v[i].str.size())
            return false;

        if (!v[i].preSkip) {
            if (v.size() == i + 1) {
                if (s.size() != v[i].str.size())
                    return false;

                return endWith(s, v[i].str);
            }

            if (!startWith(s, miniOffset, v[i].str)) {
                return false;
            }

            miniOffset = miniOffset + v[i].str.size();
            continue;
        }

        if (v[i].str.size() > 0) {
            if (v.size() == i + 1) {
                return endWith(s, v[i].str);
            }

            miniOffset = find(s, miniOffset, v[i].str);
            if (miniOffset < 0) {
                return false;
            }

            continue;
        }

        return true;
    }

    return true;
}

int main()
{
    string s = "mississippi";
    string p = "m??*ss*?i*pi";

    cout << (isMatch(s, p) ? "true" : "false");

    return 0;
}
