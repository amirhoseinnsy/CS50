from cs50 import get_float

while True:
    doller = get_float("Change owed: ")
    if doller > 0:
        break

cents = round(doller * 100)
totall = 0

while(cents >= 25):
    totall += 1
    cents -= 25

while(cents >= 10):
    totall += 1
    cents -= 10

while(cents >= 5):
    totall += 1
    cents -= 5

while(cents >= 1):
    totall += 1
    cents -= 1

print(totall)