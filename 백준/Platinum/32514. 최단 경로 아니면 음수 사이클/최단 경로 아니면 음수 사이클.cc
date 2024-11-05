#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fastio ios::sync_with_stdio(0),cin.tie(0)
#define X first
#define Y second
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
vector<pair<int, int> > v[20005];
int parent[20005];
bool visited[20005];
vector<int> tmp;
int N, M, s;
ll d[20005];

int main() {
    fastio;
    cin >> N >> M >> s;
    fill(d, d + 20005, 0x7f7f7f7f);
    while (M--) {
        int a, b, w;
        cin >> a >> b >> w;
        v[a].push_back({w, b});
    }
    d[s] = 0;
    for (int tc = 0; tc < N - 1; tc++) {
        for (int i = 0; i < N; i++) {
            if (d[i] == 0x7f7f7f7f) continue;
            for (auto cur: v[i]) {
                if (d[cur.Y] > d[i] + cur.X) {
                    parent[cur.Y] = i;
                    d[cur.Y] = d[i] + cur.X;
                }
            }
        }
    }
    bool flag = true;
    for (int i = 0; i < N && flag; i++) {
        if (d[i] == 0x7f7f7f7f) continue;
        for (auto cur: v[i]) {
            if (d[cur.Y] > d[i] + cur.X) {
                flag = false;
                int End = cur.Y;
                while (!visited[End]) {
                    visited[End] = true;
                    End = parent[End];
                }
                tmp.push_back(End);
                int nxt = parent[End];
                while (nxt != End) {
                    tmp.push_back(nxt);
                    nxt = parent[nxt];
                }
                tmp.push_back(nxt);
                break;
            }
        }
    }
    if (flag) {
        cout << "PATH\n";
        for (int i = 0; i < N; i++) {
            cout << d[i] << " ";
        }
    } else {
        cout << "CYCLE\n";
        cout << tmp.size() - 1 << "\n";
        reverse(tmp.begin(), tmp.end());
        for (int it: tmp) {
            cout << it << " ";
        }
    }
    return 0;
}
