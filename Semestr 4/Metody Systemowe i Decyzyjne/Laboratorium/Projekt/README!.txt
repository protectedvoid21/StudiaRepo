Dzień dobry, z tej strony autor pracy, Michał Puchyr

Dane pobierane były z serwisów Pracuj.pl oraz NoFluffJobs

Z racji, że dane były pobierane wpierw z serwisu NoFluffJobs a dopiero potem z Pracuj.pl,
to dane z serwisu Pracuj.pl zostały przekształcone i oczyszczone pod kątem współdziania z tymi z NFJ.

Większa część oczyszczania danych została wykonana przy pomocy kwerend w SQL oraz krótkich skryptów w Pythonie.
Oczyszczanie danych było procesem w większości ręcznym, na podstawie danych z query wyszukujących
podejmowałem odpowiednie kroki w celu unifikacji danych.

Zapytania w języku SQL wraz z komentarzem zamieszczam w pliku 'oczyszczanie_danych.sql'

Wykorzystane technologie i narzędzia:
    Przygotowanie danych:
        - C# (.NET 8)
        - Microsoft SQL Server
    
    Wizualizacja danych:
        - Python (numpy, pandas, matplotlib, seaborn)
        - Jupyter Notebook

    Modelowanie:
        - Python (numpy, pandas, scikit-learn)

W przypadku włączenia scrapera po raz pierwszy może wystąpić błąd NETSDK1004
Aby przywrócić paczki i pozbyć się błędu wystarczy wpisać komendę:
dotnet restore