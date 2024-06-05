def forall(lst, predicate):
    return all(map(lambda x: predicate(x), lst))

def exists(lst, predicate):
    return any(map(lambda x: predicate(x), lst))

def atleast(n, lst, predicate):
    return len(list(filter(lambda x: predicate(x), lst))) >= n

def atmost(n, lst, predicate):
    return len(list(filter(lambda x: predicate(x), lst))) <= n