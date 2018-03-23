#include <bits/stdc++.h>
using namespace std ;
typedef long long int ll;
typedef set<int> si;
#define F first
#define S second
vector<pair<ll,ll> > v[1000005];
ll dist[1000005];
int par[1000005] = {0};
bool fin[1000005] = {false};
priority_queue< pair<ll,ll> > pq;
void dijkstra(ll source , ll dest)
{
	dist[source]=0;
	par[source]=0;
	fin[source]=true;
	pq.push(make_pair(dist[source],source));
	while(pq.empty()==false)
	{
		ll s = pq.top().S;
		if (s==dest)
			return;
		fin[s]=true;
		pq.pop();
		for(ll i =0;i<v[s].size();i++)
		{
			if(!fin[v[s][i].F] && dist[v[s][i].F]>dist[s]+v[s][i].S)
			{
				dist[v[s][i].F]=dist[s]+v[s][i].S;
				par[v[s][i].F]=s;
				pq.push(make_pair(-dist[v[s][i].F],v[s][i].F));
			}
		}

	}
}
void printer(ll source , ll n)
{
	if(n==source)
		cout<<source<<" ";
	else if (par[n]==0)
		cout<<-1;
	else
	{
		printer(source,par[n]);
		cout<<n<<" ";
	}

}
int main()
{

	ll i,j,k,l,n,m;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		dist[i]=1e12;

	for(i=1;i<=m;i++)
	{
		cin>>j>>k>>l;
		v[j].push_back(make_pair(k,l));
		v[k].push_back(make_pair(j,l));

	}
	dijkstra(1,n);
	printer(1,n);
	cout<<endl;
	return 0;
}
