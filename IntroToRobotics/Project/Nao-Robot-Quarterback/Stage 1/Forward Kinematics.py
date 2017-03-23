import numpy as np

np.set_printoptions(precision = 1)
pi = np.pi

def convertRadian(theta):
    radian = (theta) * (np.pi) / 180
    return radian

def mkMatrix(radian, alpha, dis):
    matrix = np.matrix([[np.cos(radian),(-1)*np.sin(radian)*np.cos(alpha), np.sin(radian)*np.sin(alpha), a1 * np.cos(radian)],
                [np.sin(radian), np.cos(radian)*np.cos(alpha), (-1)*np.cos(radian)*np.sin(alpha), a1 * np.sin(radian)],
                [0,np.sin(alpha), np.cos(alpha), dis],
                [0,0,0,1]])
    return matrix

#nao robot DH parameters
#link1
a1 = 0
alpha1 = convertRadian(90)
d1 = 0

# link2
a2 = 105/1000 # convert to meters
alpha2 = convertRadian(90)
d2 = 15/1000

# link3
a3 = 0
alpha3 = convertRadian(-90)
d3 = 0

# link4
a4 = 55.95/1000
alpha4 = convertRadian(90)
d4 = 0

# link5
a5 = 0
alpha5 = 0
d5 = 55.75/1000



# input theta angles and convert them directly to radians
radian1 = convertRadian(input("Enter theta 1: "))
radian2 = convertRadian(input("Enter theta 2: "))
radian3 = convertRadian(input("Enter theta 3: "))
radian4 = convertRadian(input("Enter theta 4: "))

# compute them place them in their respective places


# link1 homogeneous transformation    4x4
A1 = mkMatrix(radian1, alpha1, d1)

# link2 homogeneous transformation    4x4
A2 = mkMatrix(radian2, alpha2, d2)

# link3 homogeneous transformation    4x4
A3 = mkMatrix(radian3, alpha3, d3)

# link4 homogeneous transformation    4x4
A4 = mkMatrix(radian4, alpha3, d4)

# link5 homogeneous transformation    4x4
A5 = mkMatrix(0, alpha5, d5)

print "A1: \n", A1
print "\nA2: \n", A2
print "\nA3: \n", A3
print "\nA4: \n", A4
print "\nA5: \n", A5

# save the matrix returned
# print the matrix
finalMatrix = A1*A2*A3*A4

print "\nFinal matrix\n", finalMatrix
