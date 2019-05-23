#include<bits/stdc++.h>
using namespace std;

int slope(pair<int,int>p1,pair<int,int>p2,pair<int,int>p3)
{
  int val = (p1.first-p3.first)*(p2.second-p3.second)-(p1.second-p3.second)*(p2.first-p3.first);
  if(val==0)return 0;
  return (val>0?2:1);
}

bool onsegment(pair<int,int>p1,pair<int,int>p2,pair<int,int>p3)
{
  return(p3.first>=min(p1.first,p2.first) && p3.first<=max(p1.first,p2.first) &&
          p3.second>=min(p1.second,p2.second) && p3.second<=max(p1.second,p2.second));
}

bool checkIntersect(pair<int,int>p1,pair<int,int>q1,pair<int,int>p2,pair<int,int>q2)
{
    int o1=slope(p1,q1,p2);
    int o2=slope(p1,q1,q2);
    int o3=slope(p2,q2,p1);
    int o4=slope(p2,q2,q1);
    if(o1!=o2 && o3!=o4)
      return true;
    if(o1==0 && onsegment(p1,q1,p2))
        return true;
    if(o2==0 && onsegment(p1,q1,q2))
        return true;
    if(o3==0 && onsegment(p1,q1,p1))
        return true;
    if(o4==0 && onsegment(p1,q1,q1))
        return true;
    return false;
}

bool isinside(vector<pair<int,int>>point,int n,pair<int,int>p)
{
  pair<int,int>check(10000,p.second);
  int count=0,i=0;
  do
  {
      int next=(i+1)%n;
      if(checkIntersect(point[i],point[next],p,check))
      {
        if(slope(point[i],point[next],p)==0)
          return onsegment(point[i],point[next],p);
        count++;
      }
      i=next;
  }while(i!=0);
  return count&1;
}


int main()
{ int a,b;
  vector<pair<int,int>>point;
  for(int i=0;i<4;i++)
    {
      cin>>a>>b;
      point.push_back(make_pair(a,b));
    }
  pair<int,int>pt(5,5);
  if(isinside(point,4,pt))
    cout<<"Yes";
  return 0;
}
