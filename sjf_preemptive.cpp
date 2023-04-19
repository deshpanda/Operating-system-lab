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
void go(){
    // turn around time = completion time - arrival time
    // waiting time = turn around time - burst time
    int n;
    cin>>n;
    vector<int> arrival_time(n);
    vector<int> burst_time(n);
    for (int i = 0; i < n; i++){
        cin>>arrival_time[i]>>burst_time[i];
    }
    vector<int> waiting_time(n);
    vector<int> turn_around_time(n);
    int total_waiting_time = 0;
    int total_turn_around_time = 0;
    function<void()> find_waiting_time = [&](){
        vector<int> remaining_time = burst_time;
        int number_of_completed_processes = 0;
        int t = 0;
        int curr_min = INT_MAX;
        int shortest = 0;
        bool check = false;
        int finish_time;
        while (number_of_completed_processes != n){
            for (int i = 0; i < n; i++){
                if (arrival_time[i] <= t && remaining_time[i] < curr_min && remaining_time[i] > 0){
                    curr_min = remaining_time[i];
                    check = true;
                    shortest = i;
                }
            }
            if (!check){
                t++;
                continue;
            }
            remaining_time[shortest]--;
            curr_min = remaining_time[shortest];
            if (curr_min == 0) curr_min = INT_MAX;
            if (remaining_time[shortest] == 0){
                number_of_completed_processes++;
                check = false;
                finish_time = t + 1;
                waiting_time[shortest] = finish_time - burst_time[shortest] - arrival_time[shortest];
                if (waiting_time[shortest] < 0) waiting_time[shortest] = 0;
            }
            t++;
        }
    };
    function<void()> find_turn_around_time = [&](){
        for (int i = 0; i < n; i++){
            turn_around_time[i] = burst_time[i] + waiting_time[i];
        }
    };
    find_waiting_time();
    find_turn_around_time();
    cout << " P\t\t"<< "AT\t\t"<< "BT\t\t"<< "WT\t\t"<< "TAT\t\t\n";
    for (int i = 0; i < n; i++){
        total_waiting_time += waiting_time[i];
        total_turn_around_time += turn_around_time[i];
        cout<<" "<<i + 1<<"\t\t"<<arrival_time[i]<<"\t\t"<<burst_time[i]<<"\t\t"<<waiting_time[i]<<"\t\t"<<turn_around_time[i]<<endl;
    }
    cout<<endl;
    cout<<"Average waiting time: "<<((float)total_waiting_time / (float) n)<<endl;
    cout<<"Average turn around time: "<<((float)total_turn_around_time / (float) n)<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("err.txt", "w", stderr);
#endif
    auto start1 = high_resolution_clock::now();
    go();
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
    cerr << "Time: " << duration.count() / 1000 << endl;
    return 0;
}