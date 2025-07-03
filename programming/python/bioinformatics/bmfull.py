def bad_char_heuristic(pat):
    bad_char = [-1] * 256
    for i in range(len(pat)):
        bad_char[ord(pat[i])] = i
    return bad_char

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

def good_suffix_heuristic(pat):
    m = len(pat)
    shift = [0] * (m + 1)
    bpos = [0] * (m + 1)
    preprocess_strong_suffix(shift, bpos, pat, m)
    preprocess_case2(shift, bpos, m)
    return shift

def boyer_moore_search(txt, pat):
    m = len(pat)
    n = len(txt)
    bad_char = bad_char_heuristic(pat)
    shift = good_suffix_heuristic(pat)

    s = 0
    while s <= n - m:
        j = m - 1
        while j >= 0 and pat[j] == txt[s + j]:
            j -= 1
        if j < 0:
            print(f"✅ Το πρότυπο βρέθηκε στη θέση {s}")
            s += shift[0]
        else:
            bc_shift = j - bad_char[ord(txt[s + j])]
            gs_shift = shift[j + 1]
            s += max(1, max(bc_shift, gs_shift))
text = "abcxabcdabxabcdabcdabcy"
pattern = "abcdabcy"
boyer_moore_search(text, pattern)
