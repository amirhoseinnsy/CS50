from cs50 import get_int


while True:
    number = get_int("Height: ")
    if number > 0 and number < 9:
        break

for i in range(number):
    for p in range(number - (i + 1)):
        print(" ", end="")
    for j in range(i + 1):
        print("#", end="")
    print()
