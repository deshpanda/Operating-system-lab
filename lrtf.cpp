#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;
using namespace chrono;
typedef long long int ll;
#ifndef ONLINE_JUDGE
#define debug(x) cerr<<#x<<" ";_print_(x);cerr<<endl;
#else
#define debug(x)
#endif
void _print_(ll t) { cerr << t; }
void _print_(int t) { cerr << t; }
void _print_(string t) { cerr << t; }
void _print_(char t) { cerr << t; }
void _print_(long double t) { cerr << t; }
void _print_(double t) { cerr << t; }
template <class T, class V> void _print_(pair <T, V> p);
template <class T, class V> void _print_(pair <T, V> p) { cerr << "{"; _print_(p.first); cerr << ","; _print_(p.second); cerr << "}"; }
template <class T> void _print_(set <T> v);
template <class T> void _print_(set <T> v) { cerr << "[ "; for (T i : v) { _print_(i); cerr << " "; } cerr << "]"; }
template <class T, class V> void _print_(map <T, V> v);
template <class T, class V> void _print_(map <T, V> v) { cerr << "[ "; for (auto i : v) { _print_(i); cerr << " "; } cerr << "]"; }
template <class T> void _print_(multiset <T> v);
template <class T> void _print_(multiset <T> v) { cerr << "[ "; for (T i : v) { _print_(i); cerr << " "; } cerr << "]"; }
template <class T> void _print_(vector <T> v);
template <class T> void _print_(vector <T> v) { cerr << "[ "; for (T i : v) { _print_(i); cerr << " "; } cerr << "]"; }
#define endl "\n";
#define ceil(x, y) x / y + (x % y != 0)
#define ppc __builtin_popcount
#define ppcll __builtin_popcountll
#define MOD 1000000007
#define MOD1 998244353
#define PI 3.141592653589793238462
// template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
vector<ll> sieve(int n) { int* arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) { vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1; } return vect; }
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
vector<ll> factors(ll n){ vector<ll> a; while(n % 2 == 0){ a.push_back(2); n /= 2; } for (int i = 3; i * i <= n; i+=2){ while (n % i == 0){ a.push_back(i); n /= i; } } if (n > 2){ a.push_back(n); } return a; }
ll nCr(ll n, ll r) { r = max(r, n - r);ll ans = 1;for (ll i = n; i > r; i--) { ans *= i;ans /= (n - i + 1); }return ans; }
ll modpow(ll x, ll n, ll m) { if (n == 0) return 1 % m;ll u = modpow(x, n / 2, m);u = (u * u) % m;if (n % 2 == 1) u = (u * x) % m;return u; }//x^n mod m
ll expo(ll a, ll b, ll mod) { ll res = 1; while (b > 0) { if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1; } return res; }
ll mminvprime(ll a, ll b) { return expo(a, b - 2, b); }
ll mod_add(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a + b) % m) + m) % m; }
ll mod_mul(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a * b) % m) + m) % m; }
ll mod_sub(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a - b) % m) + m) % m; }
ll mod_div(ll a, ll b, ll m) { a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m; }  //only for prime m
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int backup_burst_time;
    int waiting_time;
    int turn_around_time;
    int completion_time;
};
void go(){
    int n;
    cin>>n;
    struct process p[n];
    int total_burst_time = 0;
    for (int i = 0; i < n; i++){
        p[i].pid = i + 1;
        cin>>p[i].arrival_time>>p[i].burst_time;
        p[i].backup_burst_time = p[i].burst_time;
        total_burst_time += p[i].burst_time;
    }
    function<bool(process, process)> compare = [&](process p1, process p2){
        return p1.arrival_time < p2.arrival_time;
    };
    sort(p, p + n, compare);
    int total_time = 0;
    total_time += p[0].arrival_time;
    total_burst_time += p[0].arrival_time;
    function<int(int)> find_largest = [&](int at){
        int max = 0;
        int i;
        for (int i = 0; i < n; i++){
            if (p[i].arrival_time <= at){
                if (p[i].burst_time > p[max].burst_time){
                    max = i;
                }
            }
        }
        return max;
    };
    function<void()> find_completion_time = [&](){
        int index;
        int flag = 0;
        int i = p[0].arrival_time;
        while (1){
            if (i <= 4){
                index = find_largest(i);
            }
            else{
                index = find_largest(n);
            }
            p[index].burst_time -= 1;
            total_time += 1;
            i++;

            if (p[index].burst_time == 0){
                p[index].completion_time = total_time;
            }
            if (total_time == total_burst_time){
                break;
            }
        }
    };
    find_completion_time();
    int total_waiting_time = 0;
    int total_turn_around_time = 0;
    for (int i = 0; i < n; i++){
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turn_around_time - p[i].backup_burst_time;
        total_waiting_time += p[i].waiting_time;
        total_turn_around_time += p[i].turn_around_time;
    }
    cout << "P\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n";
    for (int i = 0; i < n; i++){
        cout<<p[i].pid<<"\t\t";
        cout<<p[i].arrival_time<<"\t\t";
        cout<<p[i].backup_burst_time<<"\t\t";
        cout<<p[i].completion_time<<"\t\t";
        cout<<p[i].turn_around_time<<"\t\t";
        cout<<p[i].waiting_time<<"\t\t";
        cout<<endl;
    }
    cout<<endl;
    cout<<"Average waiting time = " <<((float)total_waiting_time / (float)n)<<endl;
    cout<<"Average turn around time = "<<((float)total_turn_around_time / (float) n)<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    freopen("err1.txt", "w", stderr);
#endif
    auto start1 = high_resolution_clock::now();
    go();
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
    cerr << "Time: " << duration.count() / 1000 << endl;
    return 0;
}