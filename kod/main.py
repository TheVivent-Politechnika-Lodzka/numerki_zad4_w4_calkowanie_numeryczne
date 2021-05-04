
from functions import print_fun
from legendre import Legendre
from simpson import Simp
from charts import gen_chart

FUNSTR, FUN = print_fun()

# pobierz przedział
A = float(input("Podaj początek przedziału: "))
B = float(input("Podaj koniec przedziału: "))
if A > B: A,B = B,A

# EPS = float(input("Podaj epsilon (dla metody Newtona-Cotesa): "))
EPS = float(0.0001)

FILENAME = input("Podaj nazwę pliku: ")

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
gen_chart(FUN, A, B, "wykresy/{}_eps{}_od{}_do{}.png".format(FILENAME, EPS, A, B), LEGE.calcX(), None)
while SIMP.error() > EPS: SIMP.next()
# for i in range(6): SIMP.next()
print("Wartość całki wg metody Newtona-Cotesa")
print("Wartość:     {}".format(SIMP.curr))
print("iteracji:    {}".format(SIMP.i))
print("wielomianów: {}".format(SIMP.n))
print("epsilon:     {}".format(EPS))

print()

# gen_chart(FUN, A, B, "wykresy/{}_eps{}_od{}_do{}.png".format(FILENAME, EPS, A, B), LEGE.calcX(), SIMP.test)