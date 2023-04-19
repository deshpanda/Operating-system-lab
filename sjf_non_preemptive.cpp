#include<bits/stdc++.h>
#define f(i,a,n,c)          for(int i=a;i<n;i+=c)
#define fr(i,a,n,c)         for(int i=a;i>=n;i-=c)
#define ll                  long long int
#define l(s)                s.size()
#define all(x)              (x).begin(), (x).end()
#define vll ;               vector<ll>
#define vsort(v)            sort(v.begin(), v.end());
#define vrsort(v)           sort(v.begin(), v.end(),greater<ll>());
#define vmax(v)             *max_element(all(v))
#define vmin(v)             *min_element(all(v))
#define vsum(v)             accumulate(all(v),0ll)
#define vprint(v);          f(i,0,l(v),1){cout<<v[i]<<' ';}cout<<endl;
#define pb                  push_back
#define ff                  first
#define ss                  second
#define mpll ;              map<ll,ll>
#define p(x);               cout<<x<<endl;
#define setbit(x)           __builtin_popcountll(x)
const ll mod = 1e9 + 7;
using namespace std;
mpll wait;
vector<pair<ll, pair<ll, ll>>>vp;

    vector<int> getOrder(vector<vector<int>>& tasks)
    {
        vector<int> ans;
        ll z = 0;
        for (auto i : tasks) vp.pb({ i[0],{i[1],z} }),z++;
        vsort(vp);
        priority_queue <pair<ll, pair<ll, ll>>, vector<pair<ll, pair<ll, ll>>>, greater<pair<ll, pair<ll, ll>>>> pq;
        ll curr = vp[0].ff;
        ll it = 0;
        while (it < l(vp))
        {
            if (pq.empty() and curr<vp[it].ff)
            {
                curr = vp[it].ff;
            }

            while (it < l(vp) and vp[it].ff <= curr)
            {
                pq.push({ vp[it].ss.ff,{vp[it].ss.ss,vp[it].ff} });
                it++;
            }
            ans.pb(pq.top().ss.ff);
            
            curr += pq.top().ff;
            pq.pop();
        }
        while (!pq.empty())
        {
            ans.pb(pq.top().ss.ff);
            wait[pq.top().ss.ff] = curr - vp[pq.top().ss.ff].ff;
            pq.pop();
        }
        return ans;
    }



int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("err.txt", "w", stderr);
#endif

    vector<vector<int>>aa;
    ll n;
    cin >> n;
    f(i, 0, n, 1)
    {
        ll a, b;
        cin >> a >> b;
        vector<int> c;
        c.pb(a);
        c.pb(b);
        aa.pb(c);
    }
    
    vector<int>ans = getOrder(aa);
    cout << "PROCESS" << "   " << "ARRIVAL-TIME" << "   " << "BURST-TIME" <<"   "<< "WATING-TIME"<<"   "<<"TURNOVER-TIME" << endl;
    f(i, 0, n, 1)
    {
        cout << ans[i] << "              " << vp[ans[i]].ff << "           " << vp[ans[i]].ss.ff << "         " << wait[ans[i]] << "                 " << wait[ans[i]] + vp[ans[i]].ss.ff << endl;
    }
}