def shift_or(text, pattern):
    m = len(pattern)
    if m == 0:
        return []

    if m > 64:
        raise ValueError("Το πρότυπο είναι πολύ μεγάλο για bitwise αναπαράσταση (μέγιστο 64 χαρακτήρες).")

    pattern_mask = {chr(i): ~0 for i in range(256)}
    for i in range(m):
        pattern_mask[pattern[i]] &= ~(1 << i)

    R = ~1
    result = []

    for i in range(len(text)):
        c = text[i]
        R = (R << 1) | pattern_mask.get(c, ~0)
        if (R & (1 << (m - 1))) == 0:
            result.append(i - m + 1)

    return result


text = "opengenus"
pattern = "genus"
matches = shift_or(text, pattern)

for pos in matches:
    print(f"✅ Το πρότυπο βρέθηκε στη θέση {pos}")
