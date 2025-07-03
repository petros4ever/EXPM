from Bio import Entrez, SeqIO
from Bio.Blast import NCBIWWW, NCBIXML
import subprocess
import os

# 1. Ανάγνωση πρωτεΐνης από το αρχείο FASTA
def read_fasta(file_path):
    with open(file_path, "r") as fasta_file:
        sequence = SeqIO.read(fasta_file, "fasta")
    return sequence

# Διαβάζουμε το αρχείο FASTA που περιέχει την αλληλουχία της πρωτεΐνης
protein_sequence = read_fasta("protein1.fasta")

# 2. Εκτέλεση BLASTP
def run_blastp(sequence):
    """Εκτελεί BLASTP αναζήτηση στο NCBI για την επιλεγμένη πρωτεΐνη."""
    result_handle = NCBIWWW.qblast("blastp", "nr", sequence.seq)
    blast_records = NCBIXML.read(result_handle)
    result_handle.close()
    return blast_records

# 3. Εκτέλεση BLASTP για την αλληλουχία της πρωτεΐνης
blast_records = run_blastp(protein_sequence)

# 4. Ανάκτηση 8 ομόλογων ακολουθιών
sequences = []
for alignment in blast_records.alignments[:8]:
    for hsp in alignment.hsps:
        sequences.append(f">{alignment.accession}\n{hsp.sbjct}\n")

# 5. Αποθήκευση των ακολουθιών σε αρχείο FASTA
with open("sequences.fasta", "w") as fasta_file:
    fasta_file.writelines(sequences)

# 6. Εκτέλεση πολλαπλής στοίχισης με χρήση subprocess
subprocess.run(["clustalo", "-i", "sequences.fasta", "-o", "alignment.aln5", "--auto", "--verbose"])

print("Η στοίχιση ολοκληρώθηκε και αποθηκεύτηκε στο alignment.aln5")
