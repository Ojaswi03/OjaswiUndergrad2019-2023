from sys import argv, exit

# provided
#
# Read integers from the given filename.
#
# Return value: list of integers
def read_array(filename):
    try:
        with open(filename) as f:
            return [int(n) for n in f.read().split()]
    except:
        exit("Couldn’t read numbers from file \""+filename+"\"")


# implement
#
# Return the number of inversions in the given list, by doing a merge
# sort and counting the inversions.
#
# Return value: number of inversions
def count_inversions(in_list):
    if len(in_list) <= 1:
        return 0
    a = int(len(in_list) / 2)
    A = in_list[:a]
    B = in_list[a:]
    Ra = count_inversions(A)
    Rb = count_inversions(B)
    Rm = merge_i(A, B, in_list)
    
    return Ra + Rb + Rm


# implement
#
# Merge the left & right lists into in_list.  in_list already contains
# values--replace those with the merged values.
#
# Return value: inversion count
def merge_i(l_list, r_list, in_list):
    count = 0
    i = 0
    in_list.clear()
    while (len(l_list) != 0 and len(r_list) != 0):
        if l_list[i] > r_list[i]:
            count += len(l_list)
            in_list.append(r_list.pop(i))
        else:
            in_list.append(l_list.pop(i))
        if len(l_list) == 0:
            in_list.extend(r_list)
            r_list.clear()
        if len(r_list) == 0:
            in_list.extend(l_list)
            l_list.clear()
    return count   


# provided
if __name__ == '__main__':
    if len(argv) != 2:
        exit("usage: python3 "+argv[0]+" datafile")
    in_list = read_array(argv[1])
    print(count_inversions(in_list))