# Zadání
Násobení matic je jedna z výpočetně nejzajímavějších operací v lineární algebře. Zaprvé protože je velmi časté, zadruhé protože je to operace, která dobře naimplementovaná opravdu může dosáhnout limitu výpočetní rychlosti procesoru (narozdíl třeba od sčítání vektorů, které jsou omezeny rychlostí přístupu do paměti).

Konkrétně budou počítány součty čtvercových matic. Tyto matice budou načteny ze vstupních sobourů předaných programu jako parameter. Výsledky budou zapsány do výstupních soborů se stejným názvem jen s příponou `.multiplied`.

# Řešení
K řešení je přistupováno pomocí konceptu [OperationQueue](https://developer.apple.com/documentation/foundation/operationqueue). To znamená, že jednotlivé části algoritmu jsou složený z operací zodpovídajících za načtení matice, rozdělení výpočtu, spočítání podvýpočtů, spojení podvýpočtů a výpis výsledku. Jednotlivé operace pracují nad výhledy do matice `MatrixView` a mohou mít závislosti na něž budou čekat než budou moct být samy zpracovány. Jednotlivé výhledy do matic není nutné zamykat, protože to je již zajištěno vynucením závislostí.

Lze počítat i více matic najednou s opakovaným použitím přepínače `-m`. Viz
```bash
./matrix-multiplication -t 8 -m /Users/Michal/Documents/FEL/B6B36PJC/PJC-matrix-multiplication/matrices/01.txt -m  /Users/Michal/Documents/FEL/B6B36PJC/PJC-matrix-multiplication/matrices/02.txt -m /Users/Michal/Documents/FEL/B6B36PJC/PJC-matrix-multiplication/matrices/03.txt -m  /Users/Michal/Documents/FEL/B6B36PJC/PJC-matrix-multiplication/matrices/04.txt -m  /Users/Michal/Documents/FEL/B6B36PJC/PJC-matrix-multiplication/matrices/05.txt
```

# Měření
Pro měření byl využit MacBook Pro 2015 se specifikací:

- Model Identifier: MacBookPro11,4
- Processor Name:   Intel Core i7
- Processor Speed:  2,2 GHz
- Number of Processors: 1
- Total Number of Cores:    4
- L2 Cache (per Core):  256 KB
- L3 Cache: 6 MB
- Memory:   16 GB

Matice | 1 vlákno | 8 vláken
--- | --- | ---
matrices/01.txt | 237 ms | 201 ms
matrices/02.txt | 1982 ms | 685 ms
matrices/03.txt | 16392 ms | 4733 ms
matrices/04.txt | 16324 ms | 4720 ms

