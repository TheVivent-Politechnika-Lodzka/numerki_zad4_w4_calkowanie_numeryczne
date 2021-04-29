
from functions import print_fun
from legendre import Legendre
from simpson import Simp

FUNSTR, FUN = print_fun()

# pobierz przedział
A = float(input("Podaj początek przedziału: "))
B = float(input("Podaj koniec przedziału: "))
if A > B: A,B = B,A

EPS = float(input("Podaj epsilon (dla metody Newtona-Cotesa): "))

SIMP = Simp(FUN, A, B)
LEGE = Legendre(FUN, A, B)

for i in range(10): print()

print("Wybrany przedział: {} do {}".format(A, B))
print("Wybrana funkcja:   {}".format(FUNSTR))

print()

print("Wartość całki wg wielomianów Legendre'a")
for i in range(2, 7):
    print("dla m={} wartość całki wynosi: {}".format(i, LEGE.calc(i)))

print()

# policz Simpsona - jest tutaj, ponieważ dla większych
# przedziałów funkcji "szalonych" może się długo liczyć
while SIMP.error() > EPS: SIMP.next()
print("Wartość całki wg metody Newtona-Cotesa")
print("Wartość:     {}".format(SIMP.curr))
print("iteracji:    {}".format(SIMP.i))
print("wielomianów: {}".format(SIMP.n))
print("epsilon:     {}".format(EPS))

print()