# -*- coding: utf-8 -*-
"""
Created on Wed Feb 20 16:12:54 2019

@author: Cole Southern
"""
import numpy as np

#Problem 1
v = np.array([1, -2])
print(np.linalg.norm(v)) #Validation code for Problem 1 A
vnormalized = v / np.linalg.norm(v) #Vector V normalized to unit length
print(vnormalized) #Validation code for Problem 1 B

#Helper function for Problems 2 and 3, finds the cosine of two vectors
def cosine(u, v):
    un = np.linalg.norm(u)
    vn = np.linalg.norm(v)
    return np.inner(u, v) / (un * vn)

#Problem 2
u = np.array([2, 1])
print(np.inner(v, u)) #Validation code for Problem 2 A
print(np.inner(u, v)) #Validation code for Problem 2 A
print(cosine(v, u)) #Validation code for Problem 2 B
# Because the cosine is 0, the two vectors are perpendicular

#Problem 3
v = np.array([1, -2, 1, -2])
u = np.array([2, 1, 2, 1])
print(np.inner(v, u)) #Validation code for Problem 3 A
print(np.inner(u, v)) #Validation code for Problem 3 A
print(cosine(v, u)) #Validation code for Problem 3 B
# Because the cosine is 0, the two vectors are perpendicular

#Problem 7
A = np.array([[1, -2],
             [0, 3],
             [2, -1]])
print(A.T) #Validation code for Problem 7 B

#Problem 8
A = np.array([[3, 1, 1],
              [1, 3, 1],
              [1, 1, 3]])
B = np.array([[2, 2],
              [2, 2],
              [2, 2]])
C = np.matmul(A, B)
print(C) #Code for Problem 8 A

#Problem 9
A = np.array([[1, 2], #Matrix A as defined in Problem 9 A
              [2, 4],
              [3, 6],
              [4, 8]])
I = np.array([[1, 0],
              [0, 1]])
P = np.array([[1, 0],
              [0, 0]])
P1 = np.array([[0, 0], #Answer to Problem 9 E
               [0, 1]])
C = np.matmul(A, I) #Code for Problem 9 A
D = np.matmul(A, P)

print(C)
print(D)
print(np.matmul(A, P1))