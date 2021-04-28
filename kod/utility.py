class funDecorator:

    FUN = None
    a = 0
    b = 0

    def __init__(self, fun, a, b):
        self.FUN = fun
        self.a = a
        self.b = b
    
    # overload opertatora "()"
    # dzięki temu obiekt zachowuje się jak funkcja
    def __call__(self, x):
        return self.FUN(\
            (self.a+self.b)/2 +\
            ((self.b-self.a)*x)/2\
        )