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
void simulate_priority_scheduling_with_sjf() {
    ll n;
    cin >> n;
    vector<vector<ll>> jobs;
    vector<ll> completion_time(n), turnaround_time(n), waiting_time(n);
    for (ll i = 0; i < n; i++) {
        vector<ll> job(3);
        cin >> job[0] >> job[1] >> job[2];
        jobs.push_back(job);
    }
    priority_queue<pair<ll, pair<ll, ll>>, vector<pair<ll, pair<ll, ll>>>, greater<pair<ll, pair<ll, ll>>>> ready_queue;
    function<void()> print_waiting_queue = [&](){
        auto temp = ready_queue;
        auto x = temp.top();
        cout <<"Process "<< x.second.second + 1<< " is currently executing, " << "Waiting queue = ";
        temp.pop();
        cout << "[" << " ";
        while (temp.size() > 0) {
            cout << temp.top().second.second + 1 << " ";
            temp.pop();
        }
        cout << "]" << endl;
    };
    vector<ll> visited(n, 0);
    ll prev = -1;
    for (ll t = 0; t < 1000; t++) {
        for (ll i = 0; i < n; i++) {
            if (!visited[i] and jobs[i][0] <= t) {
                ready_queue.push({ jobs[i][2], { jobs[i][1], i } });
                visited[i] = 1;
            }
        }
        if (ready_queue.size()) {
            auto current_job = ready_queue.top();
            current_job.second.first--;
            ready_queue.pop();
            if (current_job.second.first > 0) {
                ready_queue.push(current_job);
            }
            else {
                completion_time[current_job.second.second] = t+1;
            }
            if (ready_queue.size()) {
                print_waiting_queue();
            }
        }
    }
    cout << endl;
    for (ll i = 0; i < n; ++i) {
      turnaround_time[i] = completion_time[i] - jobs[i][0];
      waiting_time[i] = turnaround_time[i] - jobs[i][1];
    }
    cout << "pid\t\tArrival time\tBurst time\tPriority\tCompletion time\tTurn Around time\tWaiting time" << endl;

    for(ll i = 0; i < n; ++i) cout << i+1 << "\t\t" << jobs[i][0] << "\t\t\t\t" << jobs[i][1] << "\t\t\t" << jobs[i][2] << "\t\t\t" << completion_time[i] << "\t\t\t\t" << turnaround_time[i] << "\t\t\t\t\t" << waiting_time[i] << endl;
    cout << endl;
    cout << "Average Turnaround time = " << float(accumulate(turnaround_time.begin(), turnaround_time.end(), 0ll)) / n << endl;
    cout << "Average Waiting time = " << float(accumulate(waiting_time.begin(), waiting_time.end(), 0ll)) / n << endl;
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
    simulate_priority_scheduling_with_sjf();
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
    cerr << "Time: " << duration.count() / 1000 << endl;
    return 0;
}

/*
pr_exec 1    Waiting queue   [ ]
pr_exec 2    Waiting queue   [ ]
pr_exec 3    Waiting queue   [ 2 ]
pr_exec 3    Waiting queue   [ 2 4 ]
pr_exec 2    Waiting queue   [ 4 ]
pr_exec 4    Waiting queue   [ ]
pr_exec 4    Waiting queue   [ ]
pr_exec 5    Waiting queue   [ 4 ]
pr_exec 5    Waiting queue   [ 4 ]
pr_exec 4    Waiting queue   [ ]
pr_exec 4    Waiting queue   [ ]
pr_exec 4    Waiting queue   [ ]
pr_exec 4    Waiting queue   [ ]

pr_no	Arrival time	Burst time	Priority	Comp time	Turn A. time	Waiting time
1		1				2			2			3			2				0
2		3				2			3			8			5				3
3		4				3			2			7			3				0
4		5				5			3			16			11				6
5		9				3			3			12			3				0

Avg. tat time: 4.8
Avg. Waiting time: 1.8

*/