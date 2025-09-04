from cs50 import get_float


def calculate_quarters(cents):  # quarters function
    quarters = 0
    while cents >= 0.25:
        quarters += 1
        cents -= 0.25
    return quarters


def calculate_dimes(cents):  # dimes function
    dimes = 0
    while cents >= 0.10:
        dimes += 1
        cents -= 0.10
    return dimes


def calculate_nickels(cents):  # nickels function
    nickels = 0
    while cents >= 0.05:
        nickels += 1
        cents -= 0.05
    return nickels


def calculate_pennys(cents):  # pennys function
    pennys = 0
    while cents >= 0.01:
        pennys += 1
        cents -= 0.01
    return pennys


while True:  # get input and check if value is not valid
    cents = get_float("Change:")
    if cents > 0:
        break

total_quarters = calculate_quarters(cents)
cents -= (total_quarters * 0.25)

total_dimes = calculate_dimes(cents)
cents -= (total_dimes * 0.10)

total_nickels = calculate_nickels(cents)
cents -= (total_nickels * 0.05)

total_pennys = calculate_pennys(cents)
cents -= (total_pennys * 0.01)


total_change = total_quarters+total_dimes+total_nickels + \
    total_pennys  # combine all the values to total_change
print(total_change)
