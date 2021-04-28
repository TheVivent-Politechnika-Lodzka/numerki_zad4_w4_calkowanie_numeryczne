from numpy import sin, cos, tan, exp, arctan

def cot(x):
    return 1/tan(x)

def csc(x):
    return 1/sin(x)

#####
def f0(x):
    # policzenie schematem hornera
    # 0.3*x³ - 0.1x² - 3.7x + 0.4
    coefficients = [0.3, -0.1, -3.7, 0.4]
    result = coefficients[0]
    for i in range(1, 4):
        result = result*x + coefficients[i]
    return result
#####

#---#
def f1(x):
    result = 2 * x + 5
    return result
#---#

#####
def f2(x):
    result = abs(x)
    return result
#####

#---#
def f3(x):
    result = sin(x)
    return result
#---#

#####
def f4(x):
    result = 17 + arctan(0.75*exp(sin(0.555*x)))+tan(7*x)
    return result
#####

#---#
def f5(x): 
    result = arctan(cos(abs(sin(x) * sin(x) * tan(x / 2)))) * x*x * sin( 26 + tan(sin(x) / cos(1999)))
    return result
#---#

'''
0. wielomian (horner)
1. liniowa
2. |x|
3. trygonometryczna
4. złożenie
5. złożenie
'''

functions = [
    # 0:
    ["0.3*x³ - 0.1x² - 3.7x + 0.4", f0],
    # 1:
    ["2x + 5", f1],
    # 2:
    ["|x|", f2],
    # 3:
    ["sin(x)", f3],
    # 4:
    ["arctan((7/4)exp(sin(0.555x)) + tan(7x) + 17", f4],
    # 5:
    ["arctan(cos(|sin²(x) * tan(x/2)|))sin(26 + tan(sin(x) /cos(1999)))x²", f5]
]

def print_fun():
    for i in range(len(functions)):
        print(str(i) + ". " + functions[i][0])
    i = int(input("Wybierz funkcję: "))
    return functions[i][0],functions[i][1]