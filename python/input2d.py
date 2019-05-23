from numpy import *
n = int(input())
for _ in range(n):
	k = list(map(int,input().split()))
	r = k[0]
	c = k[1]
	z = list(map(int,input().split()))
	M = reshape(z,(r,c))
	for i in range(r):
		for j in range(c):
			print(M[i][j],end=" ")
		print()
