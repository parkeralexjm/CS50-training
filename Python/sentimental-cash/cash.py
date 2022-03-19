from cs50 import get_float
import math


def main():
    while True:
        try:
            cash = get_float("Change owed: ")
            if cash > 0:
                break
        except ValueError:
            print("Incorrect value")

    all_pennies = cash * 100
    cash = all_pennies
    quarters = calculate_quarters(cash)
    cash = cash - (quarters * 25)
    dimes = calculate_dimes(cash)
    cash = cash - (dimes * 10)
    nickels = calculate_nickels(cash)
    cash = cash - (nickels * 5)
    pennies = calculate_pennies(cash)
    cash = cash - (pennies * 1)
    coins = quarters + dimes + nickels + pennies

    print(f"{coins}")


def calculate_quarters(cash):
    quarters = 0
    if cash > 24:
        quarters += math.floor(cash / 25)
    return quarters


def calculate_dimes(cash):
    dimes = 0
    if cash > 9:
        dimes += math.floor(cash / 10)
    return dimes


def calculate_nickels(cash):
    quarters = 0
    if cash > 4:
        quarters += math.floor(cash / 5)
    return quarters


def calculate_pennies(cash):
    pennies = 0
    if cash > 0:
        pennies += cash
    return pennies


main()