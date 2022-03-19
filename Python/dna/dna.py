import csv
import sys


def main():

    # TODO: Check for command-line usage - DONE
    if len(sys.argv) != 3:
        sys.exit("Incorrect command-line usage")

    # TODO: Read database file into a variable - DONE
    database = []
    f = sys.argv[1]
    with open(f) as file:
        reader = csv.DictReader(file)
        for name in reader:
            database.append(name)

    # TODO: Read DNA sequence file into a variable - DONE
    text_file = open(sys.argv[2], "r")
    dna_seq = text_file.read()
    text_file.close

    # TODO: Find longest match of each STR in DNA sequence
    match_lengths = []
    for row in database[0]:
        if row != "name":
            match_length = longest_match(dna_seq, row)
            match_lengths.append(match_length)

    # TODO: Check database for matching profiles
    for i in range(len(database)):
        counter = 0
        j = 0
        for row in database[i]:
            if row != 'name':
                # print(f"db:  {database[i][row]}")
                # print(f"dna: {match_lengths[j]}")
                if int(database[i][row]) == match_lengths[j]:  # this was the key to figure it out, database[i][row] indexes into the correct spot
                    # print("match")
                    counter += 1
                    if counter == len(match_lengths):
                        print(f"{database[i]['name']}")
                        return 1
                j += 1

    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
