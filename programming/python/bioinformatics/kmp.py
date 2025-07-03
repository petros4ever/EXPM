def kmp_search(T, P):
    m = len(P)
    n = len(T)

    
    LPS = [0] * m
    length = 0
    i = 1
    while i < m:
        if P[i] == P[length]:
            length += 1
            LPS[i] = length
            i += 1
        else:
            if length != 0:
                length = LPS[length - 1]
            else:
                LPS[i] = 0
                i += 1

    # Αναζήτηση προτύπου στο κείμενο
    i = 0  
    j = 0  
    while i < n:
        if P[j] == T[i]:
            i += 1
            j += 1

        if j == m:
            print(f"✅ Το πρότυπο βρέθηκε στη θέση {i - j}")
            j = LPS[j - 1]

        elif i < n and P[j] != T[i]:
            if j != 0:
                j = LPS[j - 1]
            else:
                i += 1


T = "abxabcabcaby"
P = "abcaby"
kmp_search(T, P)

