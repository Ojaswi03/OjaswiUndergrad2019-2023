import sys
import heapq


def file_character_frequencies(file_name):
    # Suggested helper
    with open(file_name, 'r') as f:
        content = f.read()
        freq = {}   #dictionary
        for i in content:
            if i in freq:
                freq[i] += 1
            else:
                freq[i] = 1
    return freq


class PriorityTuple(tuple):
    """A specialization of tuple that compares only its first item when sorting.
    Create one using double parens e.g. PriorityTuple((x, (y, z))) """
    def __lt__(self, other):
        return self[0] < other[0]

    def __le__(self, other):
        return self[0] <= other[0]

    def __gt__(self, other):
        return self[0] > other[0]

    def __ge__(self, other):
        return self[0] >= other[0]

    def __eq__(self, other):
        return self[0] == other[0]

    def __ne__(self, other):
        x = self.__eq__(other)
        return not x

def huffman_codes_from_frequencies(frequencies):
    # Suggested helper
    
    pq = []
    codes = {}
    for symbols in frequencies:
        pq.append(PriorityTuple((frequencies[symbols], (symbols,))))
    heapq.heapify(pq)
    if len(pq) == 1:
        for s in frequencies:
            codes[s] = "0"
        return codes
    ##    Encoding 
    while len(pq) > 1:
        n1freq, n1let = heapq.heappop(pq)    # n1 is left child n2 is right child
        for letters in n1let:
            codes[letters] = "0" + codes.get(letters, "")
        n2freq, n2let = heapq.heappop(pq)
        for letters in n2let:
            codes[letters] = "1" + codes.get(letters, "")
        n3 = PriorityTuple((n1freq+n2freq, n1let+n2let))
        heapq.heappush(pq, n3)

    return codes


def huffman_letter_codes_from_file_contents(file_name):
    """WE WILL GRADE BASED ON THIS FUNCTION."""
    # Suggested strategy...
    freqs = file_character_frequencies(file_name)
    return huffman_codes_from_frequencies(freqs)


def encode_file_using_codes(file_name, letter_codes):
    """Provided to help you play with your code."""
    contents = ""
    with open(file_name) as f:
        contents = f.read()
    file_name_encoded = file_name + "_encoded"
    with open(file_name_encoded, 'w') as fout:
        for c in contents:
            fout.write(letter_codes[c])
    print("Wrote encoded text to {}".format(file_name_encoded))


def decode_file_using_codes(file_name_encoded, letter_codes):
    """Provided to help you play with your code."""
    contents = ""
    with open(file_name_encoded) as f:
        contents = f.read()
    file_name_encoded_decoded = file_name_encoded + "_decoded"
    codes_to_letters = {v: k for k, v in letter_codes.items()}
    with open(file_name_encoded_decoded, 'w') as fout:
        num_decoded_chars = 0
        partial_code = ""
        while num_decoded_chars < len(contents):
            partial_code += contents[num_decoded_chars]
            num_decoded_chars += 1
            letter = codes_to_letters.get(partial_code)
            if letter:
                fout.write(letter)
                partial_code = ""
    print("Wrote decoded text to {}".format(file_name_encoded_decoded))


def main():
    """Provided to help you play with your code."""
    import pprint
    frequencies = file_character_frequencies(sys.argv[1])
    pprint.pprint(frequencies)
    codes = huffman_codes_from_frequencies(frequencies)
    pprint.pprint(codes)
    encode_file_using_codes("example.txt", codes)
    decode_file_using_codes("example.txt_encoded", codes)


if __name__ == '__main__':
    """We are NOT grading you based on main, this is for you to play with."""
    main()