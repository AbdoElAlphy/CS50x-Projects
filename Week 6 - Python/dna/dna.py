import csv
import sys


def main():

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    rows = []
    filename = sys.argv[1]
    with open(filename, "r") as file:
        reader = csv.DictReader(file)
        str_names = reader.fieldnames[1:]
        for row in reader:
            rows.append(row)

    seq_filename = sys.argv[2]
    with open(seq_filename, "r") as file:
        dna_sequence = file.read()

    results = {}
    for str_name in str_names:
        results[str_name] = longest_match(dna_sequence, str_name)
    for person in rows:
        match = True
        for str_name in str_names:
            if int(person[str_name]) != results[str_name]:
                match = False
                break

        if match == True:
            print(person["name"])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break
        longest_run = max(longest_run, count)

    return longest_run


main()
