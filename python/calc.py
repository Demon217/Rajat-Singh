#import random

#print(random.randint(0,9))

 
def add(x, y):
   return x + y

def subtract(x, y):
   return x - y


def multiply(x, y):
   return x * y


def divide(x, y):
   return x / y

print("Select operation.")
print("1.Add")
print("2.Subtract")
print("3.Multiply")
print("4.Divide") 

choice = int(input("Enter choice(1/2/3/4):"))

num1 = int(input("Enter first number: "))
num2 = int(input("Enter second number: "))

if choice == 1:
   print(add(num1,num2))
elif choice == 2:
   print(subtract(num1,num2))
elif choice == 3:
   print(multiply(num1,num2))
elif choidivide(num1,num2))
else:
   print("Invalid input")
