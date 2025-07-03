def boyer_moore_search(T, P):
    m = len(P)
    n = len(T)

    
    badchar = [-1] * 256  # Για ASCII χαρακτήρες
    for i in range(m):
        badchar[ord(P[i])] = i

    s = 0  # αρχικό shift

    while s <= n - m:
        j = m - 1

        
        while j >= 0 and P[j] == T[s + j]:
            j -= 1

        if j < 0:
            print(f"Το πρότυπο βρέθηκε στη θέση {s}")
            s += m - badchar[ord(T[s + m])] if s + m < n else 1
        else:
            s += max(1, j - badchar[ord(T[s + j])])

T = "ababcabcabababd"
P = "ababd"
boyer_moore_search(T, P)
