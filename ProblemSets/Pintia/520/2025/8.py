series = [5, 2, 0]


def lastBit(number):
    return int(str(number)[-1])


n = int(input())

for i in range(3, n):
    series.append(lastBit(sum([series[j] for j in range(i-3, i)])))

print("".join(list(map(str, series[:n]))))
