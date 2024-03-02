N = int(input())
A = list(map(int, input().split()))

count = 0
product_map = {}
for i in range(0, N):
    product_map[A[i]] += 1

for i in range(0, N):
    for j in range(0, N):
            product = A[i] * A[j]
            count += product_map[product]

print(count)
count = 0
product_map = {}
for i in range(0, N):
    product_map.setdefault(A[i], 0)
    product_map[A[i]] += 1

for i in range(0, N):
    for j in range(0, N):
            product = A[i] * A[j]
            if product in product_map:
              count += product_map[product]

print(count)