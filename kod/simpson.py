# `https://4programmers.net/Algorytmy/Ca%C5%82kowanie_numeryczne/Metoda_parabol`
from functions import print_fun


class Simp:

    prev = 0
    curr = 0
    FUN  = None
    a = 0
    b = 0
    h = 0
    i = 0
    n = 0.5 # zaczyna się od 0.5, bo jest od początku mnożone x2, więc przejdzie od razu na 1

    def __init__(self, FUN, a, b):
        self.a = a # początek przedziału
        self.b = b # koniec przdziału
        self.FUN = FUN # funkcja całkowana

    def next(self):
        self.n *= 2 # n - ilość wielomianów, więc n = 2N przedziałów
        self.h = (self.b - self.a) / self.n
        self.i += 1

        # obliczenia wynikają ze zoptymalizowanego wzoru wymagającego 2N dodawań 3 mnożeń i 1 dzielenia
        sum_min_max = self.FUN(self.a) + self.FUN(self.b)
        sum_sub1 = 0
        sum_sub2 = 0

        for i in range(0, int(self.n), 2):
            x = self.a + i * self.h # policzenie obecnego x
            sum_sub1 += self.FUN(x)
            if i < self.n-1: # ulepszenie w stosunku do oryginalnego algorytmu (nie wymaga dwóch pętli)
                sum_sub2 += self.FUN(x)
        
        result = sum_min_max + 4*sum_sub1 + 2*sum_sub2
        result /= 3
        result *= self.h

        # zapisz poprzedni i obecny wynik
        # żeby móc liczyć błąd (zmianę)
        self.prev = self.curr
        self.curr = result

        return result
        
    def error(self):
        if self.curr == 0 and self.prev == 0:
            return 1
        return abs(self.curr - self.prev)
