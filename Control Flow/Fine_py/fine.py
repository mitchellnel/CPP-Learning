"""
fine.py
Fine_py

(Project adapted from C++ implementation)
"""

import sys

def main():
    # Bribe bracket bounds
    LOWER_BRIBE_BRACKET_BOUND = 40.0
    UPPER_BRIBE_BRACKET_BOUND = 250.0

    # Get input
    defendant_name = input("Defendant: ")
    amount_paid = float(input("Amount paid (in thousands): "))
    fake_athlete = input("Fake athlete? (y/n): ")

    # Validate user input
    if defendant_name == "":
        print("---")
        print("You must enter a defendant name.")
        exit(-1)

    if amount_paid <= 0:
        print("---")
        print("The amount paid must not be negative.")
        exit(-1)

    if (fake_athlete != 'y') and (fake_athlete != 'n'):
        print("---")
        print(fake_athlete)
        print("You must enter y or n.")
        exit(-1)

    # Calculate suggested fine using brackets
    suggested_fine = 20.0       # base amount

    if amount_paid <= LOWER_BRIBE_BRACKET_BOUND:    # <= $40,000
        suggested_fine += 0.66 * amount_paid
    elif amount_paid <= UPPER_BRIBE_BRACKET_BOUND:  # $40,000 < x <= $250,000
        suggested_fine += 0.66 * 40.0

        if fake_athlete == 'y':
            suggested_fine += 0.22 * (amount_paid - 40.0)
        else:
            suggested_fine += 0.10 * (amount_paid - 40.0)
    else:                                           # > $250,000
        suggested_fine += 0.66 * 40.0

        if fake_athlete == 'y':
            suggested_fine += 0.22 * 210.0
        else:
            suggested_fine += 0.10 * 210.0

        suggested_fine += 0.14 (amount_paid - 250.0)

    # Round suggested_fine to 2 decimal places
    suggested_fine_str = "{:.1f}".format(suggested_fine)

    print("---")
    print("The suggested fine for {0} is ${1} thousand.".format(defendant_name, suggested_fine_str))


if __name__ == "__main__":
    main()


