def is_valid(s):
    if not 2 <= len(s) <= 6 and s.isalnum():
        return False
    if not s.isalpha():
        return False
    if not s.isalpha(): 
        if not s[:2].isalpha() and s[-2:].isdigit():
            return False
        for i in range(len(s)):
            if s[i].isdigit():
                if not s[i].startswith("0") or s[i:].isalpha():
                    return True
                return False
    return True


def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


main()