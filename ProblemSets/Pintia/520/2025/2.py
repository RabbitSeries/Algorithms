age = min(list(map(int, input().split())))
print(age)
if age <= 20:
    print("XianHua")
elif age <= 40:
    print("XiangXun")
elif age <= 60:
    print("BaoWenBei")
else:
    print("HunShaZhao")
