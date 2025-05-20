packages = list(map(int, input().split()))
for i,p in enumerate(packages,1):
    if p==520:
        print(i)
        break