from functions import print_fun
from utility import funDecorator

def legendre():
    # pobranie funkcji
    FUNSTR, FUN = print_fun()

    # pobierz przedział
    A = int(input("Podaj początek przedziału: "))
    B = int(input("Podaj koniec przedziału: "))
    if A > B: A,B = B,A

    # "dekoracja" funkcji (w celu zeskalowania przedziału do [-1, 1])
    FUN = funDecorator(FUN, A, B)

    # COEFS i X z `https://www.pamoc.it/tpc_num_int.html#GLQ`

    # w_i
    COEFS = [
        [1, 1, 0, 0, 0],
        [0.55556, 0.88889, 0.55556, 0, 0 ],
        [0.347855, 0.652145, 0.652145, 0.347855, 0 ],
        [0.236927, 0.478629, 0.568889, 0.478629, 0.236927],
        [0.171324, 0.360762, 0.467914, 0.467914, 0.360762, 0.171324]
    ]

    # q_i
    X = [
        [-0.57735, 0.57735, 0, 0, 0],
        [-0.774597, 0, 0.774597, 0, 0],
        [-0.861136, -0.339981, 0.339981, 0.861136, 0],
        [-0.906180, -0.538469, 0, 0.538469, 0.906180],
        [-0.932470, -0.661209, -0.238619, 0.238619, 0.661209, 0.932470]
    ]

    # pobierz m (dokładność)
    m = -1
    while m < 2 or m > 6:
        m = int(input("Podaj m z przedziału 2-6: "))

    # policz wynik
    result = 0
    for i in range(0,m):
        result += COEFS[m-2][i] * FUN(X[m-2][i])
    # poprawa wyniku w celu zeskalowania przedziału do [-1, 1]
    result *= (B-A) / 2

    print("Wynik to {}".format(result))