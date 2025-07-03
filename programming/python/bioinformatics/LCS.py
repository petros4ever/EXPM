def lcs(s1: str, s2: str) -> str:
    n, m = len(s1), len(s2)
    dp = [[0] * (m + 1) for _ in range(n + 1)]

    # Υπολογισμός μήκους της LCS
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1  # Αν ταιριάζουν, αυξάνουμε το μήκος
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])  

    # Ανακατασκευή της LCS ακολουθώντας το dp
    i, j = n, m
    lcs_string = []

    while i > 0 and j > 0:
        if s1[i - 1] == s2[j - 1]:
            lcs_string.append(s1[i - 1])
            i -= 1
            j -= 1
        elif dp[i - 1][j] > dp[i][j - 1]:
            i -= 1
        else:
            j -= 1

    return ''.join(reversed(lcs_string))  # Αναστρέφουμε τη συμβολοσειρά αφού τη χτίσαμε ανάποδα



s1 = "AGGTAB"
s2 = "GXTXAYB"
print("LCS:", lcs(s1, s2))  