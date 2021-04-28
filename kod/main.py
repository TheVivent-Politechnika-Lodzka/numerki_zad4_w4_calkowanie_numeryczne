from functions import print_fun
from utility import funUtil

# pobranie funkcji
FUNSTR, FUN = print_fun()

# pobierz przedział
A = int(input("Podaj początek przedziału: "))
B = int(input("Podaj koniec przedziału: "))
if A > B: A,B = B,A

# "dekoracja" funkcji
FUN = funUtil(FUN, A, B)


print(FUNSTR)
print(A)
print(B)
print(FUN(0))