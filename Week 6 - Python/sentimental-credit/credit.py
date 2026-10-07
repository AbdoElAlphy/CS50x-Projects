from cs50 import get_string

card = get_string("Number: ")

total_sum = 0
reversed_card = card[::-1]

for i in range(len(reversed_card)):
    digit = int(reversed_card[i])
    if i % 2 == 1:
        digit = digit * 2
        if digit > 9:
            total_sum += (digit // 10) + (digit % 10)
        else:
            total_sum += digit
    else:
        total_sum += digit

if total_sum % 10 != 0:
    print("INVALID")
else:
    length = len(card)
    if length == 15 and (card.startswith("34") or card.startswith("37")):
        print("AMEX")
    elif length == 16 and (card.startswith("51") or card.startswith("52") or card.startswith("53") or card.startswith("54") or card.startswith("55")):
        print("MASTERCARD")
    elif (length == 13 or length == 16) and card.startswith("4"):
        print("VISA")
    else:
        print("INVALID")
