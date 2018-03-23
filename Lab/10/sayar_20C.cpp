#include<stdio.h>
#include<set>
#include<vector>
#include<iterator>
using namespace std;
typedef long long int lint;
vector<pair<lint,lint> > adj[200009];
set<pair<lint,lint> > consider;
lint prevNode[200009],pathLen[200009],done[200009],final_List[200009];
lint N,M;

int main()
{
	lint a,b,w;
	scanf("%lld %lld",&N,&M);
	while(M--)
	{
		scanf("%lld %lld %lld",&a,&b,&w);
		if(a==b)
			continue;
		pair<lint,lint> linkage;
		linkage.first=b;
		linkage.second=w;
		adj[a].push_back(linkage);
		linkage.first=a;
		adj[b].push_back(linkage);
	}
	pair<lint,lint> sendIn;
	sendIn.first=0;
	sendIn.second=1;
	consider.insert(sendIn);
	set <pair<lint,lint> > ::iterator it;
	while(!consider.empty())
	{
		it=consider.begin();
		lint nodeNum=(*it).second;
		if(done[nodeNum])
		{
			consider.erase(it);
			continue;
		}
		//done[(*it).second]=1;
		//consider.erase(it);
		lint adjacent_Num=adj[nodeNum].size();
		for(lint i=0;i<adjacent_Num;++i)
		{
			sendIn.first=adj[nodeNum][i].second+(*it).first;
			sendIn.second=adj[nodeNum][i].first;
			if(pathLen[sendIn.second]==0 && sendIn.second!=1)
			{
				consider.insert(sendIn);
				prevNode[sendIn.second]=nodeNum;
				pathLen[sendIn.second]=sendIn.first;
				continue;
			}
			else if(sendIn.second!=1)
			{
				if(pathLen[sendIn.second]>sendIn.first)
				{
					//pair<lint,lint> findIt;
					//findIt.first=pathLen[sendIn.second];
					//findIt.second=sendIn.second;
					//it=consider.find(findIt);
					//if(it!=consider.end())
					//	consider.erase(it);
					consider.insert(sendIn);
					prevNode[sendIn.second]=nodeNum;
					pathLen[sendIn.second]=sendIn.first;
				}
			}
		}
		done[(*it).second]=1;
		consider.erase(it);
	}
	lint now=N,i=0;
	if(prevNode[N]==0)
	{
		printf("-1\n");
		return 0;
	}
	while(now!=1)
	{
		final_List[i]=now;
		++i;
		now=prevNode[now];
	}
	printf("1 ");
	for(lint printIt=i-1;printIt>=0;--printIt)
		printf("%lld ",final_List[printIt]);
	printf("\n");
	return 0;
}
