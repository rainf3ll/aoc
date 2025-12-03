filename = "in.txt"

f = open(filename)
fcontent = f.read()
f.close()

whatever = fcontent.rstrip('\n').split(',')
data = []

# mysterious trick - we unwrap all the ranges into a complete list of numbers we will be analyzing
# this lets us skip doing exactly that in both parts of the puzzle. why do it twice when you can do it once?
for i in range(len(whatever)):
    a, b = whatever[i].split('-')
    a = int(a)
    b = int(b)
    for j in range(a, b+1):
        data.append(str(j))

def solve1():
    sum = 0
    for item in data:
        length = len(item)
        if length % 2 != 0:
            continue
        sub1 = item[:(length//2)]
        sub2 = item[(length//2):]
        if sub1 == sub2:
            sum += int(item)
    return sum

def solve2():
    sum = 0
    for item in data:
        length = len(item)
        for i in range(1, length):
            pattern = item[:i]
            if item == (pattern * (length // len(pattern))):
                sum += int(item)
                break
    return sum

print(f"silver: {solve1()}")
print(f"gold: {solve2()}")
