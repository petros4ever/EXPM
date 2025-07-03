def naivemethod(P, T):
    m = len(P)
    n = len(T)
    for j in range(n - m + 1):
        i = 0
        while i < m and P[i] == T[j + i]:
            i += 1
        if i == m:
            print(f"Pattern found at index {j}")
κείμενο = "ababcabcabababd"
πρότυπο = "ababd"

naivemethod(πρότυπο, κείμενο)