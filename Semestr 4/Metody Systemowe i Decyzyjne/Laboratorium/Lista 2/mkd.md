1. **Jako rejestrator chcę umożliwić rejestrację pacjentów, aby wprowadzić ich do systemu.**
   - Scenariusz: Rejestracja pacjentów
     - **Given** Jestem zalogowany jako rejestrator w systemie.
     - **When** Nowy pacjent zgłasza się do rejestracji.
     - **Then** Wypełniam formularz rejestracyjny z danymi osobowymi pacjenta, takimi jak imię, nazwisko, adres, numer telefonu, adres e-mail.
     - **And** Wprowadzam dodatkowe informacje, jeśli są potrzebne, takie jak grupa krwi, informacje o ubezpieczeniu zdrowotnym itp.
     - **And** Tworzę nową kartę pacjenta w systemie, nadając jej unikalny numer identyfikacyjny.
     - **And** Potwierdzam rejestrację pacjenta i wydrukowuję lub wysyłam potwierdzenie rejestracji.

2. **Jako rejestrator chcę mieć możliwość anulowania wizyt, jeśli pacjent zdecyduje się nie przyjść.**
   - Scenariusz: Anulowanie wizyt
     - **Given** Jestem zalogowany jako rejestrator w systemie.
     - **When** Pacjent zgłasza chęć anulowania wizyty, dzwoniąc lub przychodząc osobiście.
     - **Then** Wyszukuję w systemie zaplanowaną wizytę pacjenta na podstawie jego danych osobowych lub numeru identyfikacyjnego.
     - **And** Anuluję wizytę w systemie, wprowadzając powód anulacji podany przez pacjenta.
     - **And** Aktualizuję harmonogram wizyt, uwzględniając zwolniony termin.

3. **Jako rejestrator chcę mieć możliwość przyjmowania opłat za wizyty od pacjentów.**
   - Scenariusz: Przyjmowanie opłat za wizytę
     - **Given** Jestem zalogowany jako rejestrator w systemie.
     - **When** Pacjent zgłasza się do rejestracji po wizycie.
     - **Then** Sprawdzam w systemie informacje o przeprowadzonej wizycie pacjenta oraz ustaloną opłatę za nią.
     - **And** Informuję pacjenta o kwocie do zapłaty oraz dostępnych opcjach płatności.
     - **And** Przyjmuję opłatę gotówką, kartą lub innym środkiem płatniczym, wystawiając paragon lub fakturę.
     - **And** Aktualizuję status płatności w systemie oraz ewentualnie wydaję potwierdzenie opłaty.

4. **Jako lekarz chcę mieć możliwość obsługi kart pacjenta, aby mieć dostęp do historii medycznej.**
   - Scenariusz: Obsługa kart pacjenta
     - **Given** Jestem zalogowany jako lekarz w systemie.
     - **When** Przechodzę do zakładki "Karty pacjentów".
     - **Then** Wybieram kartę konkretnego pacjenta z listy.
     - **And** Przeglądam dane osobowe pacjenta, historię chorób, wyniki badań, aktualne leczenie oraz ewentualne uwagi medyczne.
     - **And** Jeśli potrzebne, aktualizuję informacje dotyczące bieżącej wizyty lub wprowadzam nowe dane.

5. **Jako lekarz chcę mieć możliwość wystawiania recept dla pacjentów.**
   - Scenariusz: Wystawianie recepty
     - **Given** Jestem zalogowany jako lekarz w systemie.
     - **When** Pacjent konsultuje się ze mną i potrzebuje przepisania leków.
     - **Then** Wybieram opcję wystawienia nowej recepty z menu.
     - **And** Wprowadzam nazwy leków, dawkowanie, ilość oraz ewentualne instrukcje dotyczące przyjmowania.
     - **And** Potwierdzam dane recepty i wysyłam ją elektronicznie do apteki pacjenta.

6. **Jako lekarz chcę mieć możliwość wystawiania zwolnień lekarskich dla pacjentów.**
   - Scenariusz: Wystawianie zwolnienia lekarskiego
     - **Given** Jestem zalogowany jako lekarz w systemie.
     - **When** Pacjent zgłasza się do mnie z prośbą o wystawienie zwolnienia lekarskiego.
     - **Then** Przeglądam historię medyczną pacjenta i diagnozę.
     - **And** Tworzę nowe zwolnienie lekarskie, wprowadzając datę rozpoczęcia i zakończenia, oraz ewentualne ograniczenia lub uwagi.
     - **And** Wystawiam zwolnienie, które automatycznie trafia do systemu ubezpieczeń społecznych.

7. **Jako lekarz chcę mieć możliwość wystawiania skierowań dla pacjentów.**
   - Scenariusz: Wystawianie skierowania
     - **Given** Jestem zalogowany jako lekarz w systemie.
     - **When** Pacjent potrzebuje skierowania na specjalistyczne badania lub konsultację.
     - **Then** Wypełniam formularz skierowania, zawierający dane pacjenta, diagnozę oraz informacje o placówce, do której ma być skierowany.
     - **And** Wystawiam skierowanie elektronicznie, które jest automatycznie wysyłane do wybranej placówki medycznej.

8. **Jako pacjent chcę mieć możliwość rejestracji do wybranego lekarza, aby uzyskać dostęp do opieki medycznej.**
   - Scenariusz: Rejestracja do lekarza
     - **Given** Jestem zalogowany jako pacjent w systemie.
     - **When** Wybieram opcję rejestracji do konkretnego lekarza.
     - **Then** Przeglądam dostępne terminy wizyt u wybranego lekarza.
     - **And** Wybieram dogodny termin wizyty i potwierdzam rejestrację.
     - **And** Otrzymuję potwierdzenie rejestracji oraz przypomnienie o nadchodzącej wizycie.
