def reverse(s):
	s = "".join(reversed(s))
	return s

n = int(input())
i = 0
while i in range(0,n):
	s = input()
	j = 0
	k = ""
	ns = ""
	for j in s:      
		if(j=='.'):
			k=reverse(k)
			ns=ns+k+'.'
			k=""
		else:
			k = k+j
	k=reverse(k)
	ns = ns + k
	i = i + 1
	print(ns)
