import math
from platform import java_ver
import numpy as np
import argparse

# begin PROVIDED section - do NOT modify ##################################

count = 0

def getArgs() :
    
    parser = argparse.ArgumentParser()
    parser.add_argument('input_file', type = str, help = 'File containing terrain')
    
    parser.add_argument('h', type = float, help = 'h value')
    
    parser.add_argument('theta', type = float, help = 'Angle of elevation for Sun')
    parser.add_argument('algorithm', type = str, help = 'naive | early | fast')
    return parser.parse_args()

def compare(x,y):
    global count
    count += 1
    if abs(x-y) < .000000000001 :
        return False
    if x < y :
        return True
    else:
        return False

def print_shade(boolean_array):
    for row in boolean_array:
        for column in row:
            if column == True:
                print ('*    ', end = '')
            elif column == False:
                print ('0    ', end = '')
        print('\n')
        
def read2Dfloat(fileName) : # read CSV of floats into 2D array
    array2D = []
    # Read input file
    f = open(fileName, "r")
    data = f.read().split('\n')
    
    # Get 2-D array
    for row in data[0:-1]:
        float_list = list(map(float, row.split(',')[0:-1]))
        array2D.append(float_list)

    return array2D

def runTest(args, terrain = None) :

    
    # Initialize counter
    global count
    count = 0

    theta = np.deg2rad(args.theta)
    
    if terrain == None :
      terrain = read2Dfloat(args.input_file)

    N     = len(terrain)
    shade = [[False] * N for i in range(N)]

    if args.algorithm == 'naive':
        result = naive(terrain, args.h, theta, N, shade)
    elif args.algorithm == 'early':
        result = earlyexit(terrain, args.h, theta, N, shade)
    elif args.algorithm == 'fast':
        result = fast(terrain, args.h, theta, N, shade)

    return result

# end PROVIDED section ##################################

# Fritz Sieker 

def naive(image,h,angle,N,shade):
        
###### Complete this function
    val = 0.0
    angleVal = 0.0
    for i in range(N):
        for j in range(0,N):
            for k in range(0,j):
                val = (image[i][k] - image[i][j])/(h*(j-k))
                angleVal = math.tan(angle)
                if (compare(angleVal, val)):
                    shade[i][j] = 1         
    return shade

def earlyexit(image,h,angle, N, shade):
    
    
###### Complete this function
    val = 0.0
    angleVal = 0.0
    for i in range(N):
        for j in range(0,N):
            for k in range(j - 1, -1, -1):
                val = (image[i][k] - image[i][j])/(h*(j-k))
                angleVal = math.tan(angle)
                if (compare(angleVal, val)):
                    shade[i][j] = 1
                    break
    return shade

def fast(image,h,angle, N, shade):

###### Complete this function 

   
    for i in range (N):
        max = 0
        R = image[i]
        for j in range(1,N):
            shlen = (math.tan(angle)/R[max]) ** (-1)
            dif = (j-max) * h
            beat = float(math.tan(angle) * (shlen - dif))
            if (shlen - dif <= 0):
                beat = R[j] - 1
            if (compare(float(R[j]), beat)):
                shade[i][j] = 1
            else:
                max = j
    return shade     
if __name__ == '__main__':
    

    answer = runTest(getArgs())
    print_shade(answer)
    print('Number of comparisons: ' + str(count))
