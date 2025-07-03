from Bio.Blast import NCBIWWW, NCBIXML

# Η αλληλουχία της άγνωστης πρωτεΐνης
mystery_protein = """GATGAPGIAGAPGFPGARGAPGPQGPSGAPGPKXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXGVQGPPGPQGPR
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXGSAGPPGATGFP
GAAGRXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXGVVGLPGQR"""

# Εκτέλεση BLASTP στη βάση δεδομένων NR
result_handle = NCBIWWW.qblast("blastp", "nr", mystery_protein)

# Αποθήκευση των αποτελεσμάτων σε αρχείο
with open("blast_results.xml", "w") as out_file:
    out_file.write(result_handle.read())

# Διάβασμα των αποτελεσμάτων
result_handle = open("blast_results.xml")
blast_record = NCBIXML.read(result_handle)

# Εύρεση ομόλογων αλληλουχιών από οργανισμούς που ξεκινούν με "Tyr"
matches = []
for alignment in blast_record.alignments:
    for hsp in alignment.hsps:
        if "Tyr" in alignment.title:  # Φιλτράρισμα με βάση το όνομα του οργανισμού
            matches.append((alignment.title, hsp.expect))

# Εμφάνιση των κορυφαίων αποτελεσμάτων
for match in matches[:5]:
    print(match)
