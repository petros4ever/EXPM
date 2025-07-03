def preprocess_strong_suffix(shift, bpos, pat, m):
    i = m
    j = m + 1
    bpos[i] = j
    while i > 0:
        while j <= m and pat[i - 1] != pat[j - 1]:
            if shift[j] == 0:
                shift[j] = j - i
            j = bpos[j]
        i -= 1
        j -= 1
        bpos[i] = j

def preprocess_case2(shift, bpos, m):
    j = bpos[0]
    for i in range(m + 1):
        if shift[i] == 0:
            shift[i] = j
        if i == j:
            j = bpos[j]

def good_suffix_table(pat):
    m = len(pat)
    shift = [0] * (m + 1)
    bpos = [0] * (m + 1)
    preprocess_strong_suffix(shift, bpos, pat, m)
    preprocess_case2(shift, bpos, m)
    return shift


pattern = "abcdabcy"
shift_table = good_suffix_table(pattern)

print("Good Suffix Shift Table:")
for i in range(len(shift_table)):
    print(f"shift[{i}] = {shift_table[i]}")
