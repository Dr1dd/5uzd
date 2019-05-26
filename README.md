# 5 objektinio programavimo užduotis


Ši užduotis buvo skirta susipažinti su asociatyviais konteineriais. Iki šiol mes naudojome sekos/nuoseklaus tipo konteinerius (std::vector ir t.t)

Asociatyvieji konteineriai yra tokie konteineriai, kurie elementų į konteinerį įrašymo metu juos "surūšiuoja" yra labiau tinkami ir efektyvesni lyginant su sekos konteineriais.

Užduotis buvo suskaičiuoti, kiek kartų kiekvienas skirtingas žodis pasikartoja tekste.

Šiai programai naudojau `std::map` ir `std::multimap` asociatyviuosius konteinerius.
Tekstas buvo imtas iš įvairių puslapių pvz.: delfi.lt, vu.lt, github.com...

Rezultatai išvedimi į išorinį `output` failą.
![pic](https://imgur.com/9kOHw08.png)

## 1,2.
Užduotis reikalavo išvesti žodžius, kurie pasikartojo dažniau negu 1 kartą (žodžiai negalėjo turėti prie jų "prikibusius" kablelius ar kitus simbolius).
Taip pat reikalingas ir count'eris, kuris nurodo kiek kartų konkretus žodis pasikartojo.

Realizacija:
![pic](https://imgur.com/Ye7j0zv.png)

Jeigu randamas `,` ar koks nors kitas simbolis prie žodžio - jis yra ištrinamas:
![pic](https://imgur.com/JH6nFnc.png)
`zodis` yra std::string tipo.

## 3. Url suradimas:
![pic](https://imgur.com/bPlP26K.png)

Naudojama `<regex>` biblioteka (regular expression).
Ieškoma `pattern'ų`, kurie yra tinkami tik url tipo linkams.

Gauti rezultatai pvz.:
![pic](https://imgur.com/mK8UgKc.png)

