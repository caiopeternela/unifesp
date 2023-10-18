def main():
    dollars = dollars_to_float(input("How much was the meal? "))
    percent = percent_to_float(input("What percentage would you like to tip? "))
    tip = dollars * percent
    print(f"Leave ${tip:.2f}")


def dollars_to_float(dollars):
    to_float = float(dollars.strip().replace("$", ""))
    return to_float


def percent_to_float(percent):
    to_float = float(percent.strip().replace("%", "")) / 100.0
    return to_float


main()