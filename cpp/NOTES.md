# 1. Δημιουργία του build folder (γίνεται μία φορά)
cmake -B build

# 2. Compile (κάθε φορά που αλλάζεις κώδικα)
cmake --build build

# 3. Εκτέλεση app ή tests
./build/lob_app
./build/lob_tests