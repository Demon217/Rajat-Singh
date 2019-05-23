class node:
	def __init__(self,data):
		self.data=data
		self.next=None
class LinkL:
	def __init__(self):
		self.head=None
	def reverse(self):
		prev = None
		cur = self.head
		while(cur is not None):
			next = cur.next
			cur.next = prev
			prev = cur
			cur = next
		self.head = prev
	def push(self,data):
		newN = node(data)
		newN.next = self.head
		self.head = newN
	def printL(self):
		temp = self.head
		while(temp):
			print(temp.data)
			temp=temp.next
ll = LinkL()
ll.push(20)
ll.push(10)
ll.push(15)
ll.push(31)
ll.printL()
ll.reverse()
ll.printL()
