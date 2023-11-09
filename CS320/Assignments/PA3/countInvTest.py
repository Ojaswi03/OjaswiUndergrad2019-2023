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
    if(len(in_list) == 1):
        return 0
    mid = (len(in_list)//2)
    a = in_list[:mid]
    b = in_list[mid:]
    print("countInv",a,b,in_list)
    rA = count_inversions(a)
    rB = count_inversions(b)
    rM = merge_i(a,b,in_list) 

    return rA + rB + rM


# implement
#
# Merge the left & right lists into in_list.  in_list already contains
# values--replace those with the merged values.
#
# Return value: inversion count
def merge_i(l_list, r_list, in_list):
    count = 0
    print("l_list:",l_list,"r_list:",r_list,"in_list:",in_list)
    # in_list.clear()
    print("inlist",in_list)
    while(len(l_list) > 0 and len(r_list) > 0):
        for i in l_list:
            for j in r_list:
                print(i,j)
                if(i<j):
                    print("i is smaller" , l_list)
                    l_list.remove(i)
                    temp = in_list.pop(in_list.index(i))
                    print("temp",temp,"inlist",in_list)
                    in_list.append(i)
                    
                else:
                    print("j is smaller",r_list)
                    r_list.remove(j)
                    temp = in_list.pop(in_list.index(j))
                    print("temp",temp,"inlist",in_list)
                    in_list.append(j)
                    # print(in_list)
                    
                    count += len(l_list)
    if (len(l_list) == 0 or len(r_list) == 0):

        if len(l_list) == 0:
            print("extending",r_list)
            in_list.extend(r_list)
        if len(r_list) == 0:
            print("extending",l_list)
            in_list.extend(l_list)
    print("end inlist",in_list)
    return count



# provided
if __name__ == '__main__':
    if len(argv) != 2:
        exit("usage: python3 "+argv[0]+" datafile")
    in_list = read_array(argv[1])
    print(count_inversions(in_list))
    
