import sys
def find(x) :
    if x==par[x] :
        return x
    par[x]=find(par[x])
    return par[x]
def union(a,b) :
    a=find(a)
    b=find(b)
    if rank[a]<rank[b] :
        par[a]=b
    elif rank[a]>rank[b] :
        par[b]=a
    else :
        par[a]=b
        rank[b]+=1
input=sys.stdin.readline
N,M=map(int,input().split())
par=[i for i in range(N+1)]
rank=[0]*(N+1)
arr=[]
for _ in range(M) :
    a,b,w=map(int,input().split())
    arr.append((w,a,b))
arr.sort(key=lambda x:x[0],reverse=True)
s,e=map(int,input().split())
for w,a,b in arr :
    if find(a)!=find(b) :
        union(a,b)
        if find(s)==find(e) :
            print(w)
            sys.exit()