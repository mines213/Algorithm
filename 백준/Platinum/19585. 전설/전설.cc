#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////
//전처리 시 cout << fixed; , cout.precision(N); 사용 불가
constexpr int SZ = 1 << 20;

class INPUT {
private:
    char read_buf[SZ];
    int read_idx, next_idx;
    bool __END_FLAG__, __GETLINE_FLAG__;

public:
    explicit operator bool() { return !__END_FLAG__; }
    bool IsBlank(char c) { return c == ' ' || c == '\n'; }
    bool IsEnd(char c) { return c == '\0'; }

    char _ReadChar() {
        if (read_idx == next_idx) {
            next_idx = fread(read_buf, sizeof(char), SZ, stdin);
            if (next_idx == 0) return 0;
            read_idx = 0;
        }
        return read_buf[read_idx++];
    }

    char ReadChar() {
        char ret = _ReadChar();
        for (; IsBlank(ret); ret = _ReadChar());
        return ret;
    }

    template<typename T>
    T ReadInt() {
        T ret = 0;
        char cur = _ReadChar();
        bool flag = 0;
        for (; IsBlank(cur); cur = _ReadChar());
        if (cur == '-') flag = 1, cur = _ReadChar();
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret = 10 * ret + (cur & 15);
        if (IsEnd(cur)) __END_FLAG__ = 1;
        return flag ? -ret : ret;
    }

    string ReadString() {
        string ret;
        char cur = _ReadChar();
        for (; IsBlank(cur); cur = _ReadChar());
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
        if (IsEnd(cur)) __END_FLAG__ = 1;
        return ret;
    }

    double ReadDouble() {
        string ret = ReadString();
        return stod(ret);
    }

    string getline() {
        string ret;
        char cur = _ReadChar();
        for (; cur != '\n' && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
        if (__GETLINE_FLAG__) __END_FLAG__ = 1;
        if (IsEnd(cur)) __GETLINE_FLAG__ = 1;
        return ret;
    }

    friend INPUT &getline(INPUT &in, string &s) {
        s = in.getline();
        return in;
    }
} _in;

class OUTPUT {
private:
    char write_buf[SZ];
    int write_idx;

public:
    ~OUTPUT() { Flush(); }
    explicit operator bool() { return 1; }

    void Flush() {
        fwrite(write_buf, sizeof(char), write_idx, stdout);
        write_idx = 0;
    }

    void WriteChar(char c) {
        if (write_idx == SZ) Flush();
        write_buf[write_idx++] = c;
    }

    template<typename T>
    int GetSize(T n) {
        int ret = 1;
        for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;
        return ret;
    }

    template<typename T>
    void WriteInt(T n) {
        int sz = GetSize(n);
        if (write_idx + sz >= SZ) Flush();
        if (n < 0) write_buf[write_idx++] = '-', n = -n;
        for (int i = sz; i-- > 0; n /= 10) write_buf[write_idx + i] = n % 10 | 48;
        write_idx += sz;
    }

    void WriteString(string s) { for (auto &c: s) WriteChar(c); }
    void WriteDouble(double d) { WriteString(to_string(d)); }
} _out;

/* operators */
INPUT &operator>>(INPUT &in, char &i) {
    i = in.ReadChar();
    return in;
}

INPUT &operator>>(INPUT &in, string &i) {
    i = in.ReadString();
    return in;
}

template<typename T, typename std::enable_if_t<is_arithmetic_v<T> >* = nullptr>
INPUT &operator>>(INPUT &in, T &i) {
    if constexpr (is_floating_point_v<T>) i = in.ReadDouble();
    else if constexpr (is_integral_v<T>) i = in.ReadInt<T>();
    return in;
}

OUTPUT &operator<<(OUTPUT &out, char i) {
    out.WriteChar(i);
    return out;
}

OUTPUT &operator<<(OUTPUT &out, string i) {
    out.WriteString(i);
    return out;
}

template<typename T, typename std::enable_if_t<is_arithmetic_v<T> >* = nullptr>
OUTPUT &operator<<(OUTPUT &out, T i) {
    if constexpr (is_floating_point_v<T>) out.WriteDouble(i);
    else if constexpr (is_integral_v<T>) out.WriteInt<T>(i);
    return out;
}

/* macros */
#define cin _in
#define cout _out
#define istream INPUT
#define ostream OUTPUT
#define fastio 1
/////////////////////////////////////////////////////////////////////////////////////////////
string name;
int length;
const int ROOT = 1;
int unused = 2;
const int MX = 4000000 + 5; // 최대 등장 가능한 글자의 수
bool chk[MX];
int nxt[MX][26];
unordered_set<string> SET;

int c2i(char c) {
    return c - 'a';
}

void insert(string &s) {
    int cur = ROOT;
    for (auto c: s) {
        if (nxt[cur][c2i(c)] == -1)
            nxt[cur][c2i(c)] = unused++;
        cur = nxt[cur][c2i(c)];
    }
    chk[cur] = true;
}

void bfs() {
    int cur = ROOT;
    for (int i = 0; i < length; i++) {
        cur = nxt[cur][c2i(name[i])];
        if (cur == -1) {
            cout << "No\n";
            return;
        }
        if (chk[cur] == true) {
            if (SET.find(name.substr(i + 1, length)) != SET.end()) {
                cout << "Yes\n";
                return;
            }
        }
    }
    cout << "No\n";
}

int main() {
    fastio;
    memset(nxt, -1, sizeof(nxt));
    int C, N;
    cin >> C >> N;
    for (int i = 0; i < C; i++) {
        string s;
        cin >> s;
        insert(s);
    }
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        SET.insert(s);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        cin >> name;
        length = name.length();
        bfs();
    }
}


























