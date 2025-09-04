from cs50 import get_int

while True:
    h = get_int("Height: ")
    if 1 <= h <= 8:
        break

for i in range(h):
    for k in range(h-(i+1)):
        print(" ", end="")
    for j in range(i+1):
        print("#", end="")
    print()
