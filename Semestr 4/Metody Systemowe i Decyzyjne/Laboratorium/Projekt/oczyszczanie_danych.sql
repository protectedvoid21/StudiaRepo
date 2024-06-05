-- Query w języku T-SQL dla Microsoft SQL Server


-- Ujednolicenie wynagrodzeń do miesięcznych (w przypadku wynagrodzeń poniżej 300 zł - przyjmujemy, że są to wynagrodzenia godzinowe)
-- etat 168 godzin miesięcznie
UPDATE Offers
SET 
    SalaryFrom = SalaryFrom * 168,
    SalaryTo   = SalaryTo * 168
WHERE SalaryFrom < 300 AND SalaryFrom > 0

-- Aktualizacja kategorii z Pracuj.pl pod te z NoFluffJobs
UPDATE Offers
SET Category = CASE
                   WHEN Name LIKE '%projectManager%' THEN 'projectManager'
                   WHEN Name LIKE '%marketing%' THEN 'marketing'
                   WHEN Name LIKE '%embedded%' THEN 'embedded'
                   WHEN Name LIKE '%erp%' THEN 'erp'
                   WHEN Name LIKE '%businessAnalyst%' THEN 'businessAnalyst'
                   WHEN Name LIKE '%sales%' THEN 'sales'
                   WHEN Name LIKE '%automation%' THEN 'automation'
                   WHEN Name LIKE '%robotics%' THEN 'robotics'
                   WHEN Name LIKE '%customerService%' THEN 'customerService'
                   WHEN Name LIKE '%security%' THEN 'security'
                   WHEN Name LIKE '%logistics%' THEN 'logistics'
                   WHEN Name LIKE '%backend%' THEN 'backend'
                   WHEN Name LIKE '%artificialIntelligence%' THEN 'artificialIntelligence'
                   WHEN Name LIKE '%data%' THEN 'data'
                   WHEN Name LIKE '%fullstack%' THEN 'fullstack'
                   WHEN Name LIKE '%agile%' THEN 'agile'
                   WHEN Name LIKE '%testing%' THEN 'testing'
                   WHEN Name LIKE '%frontend%' THEN 'frontend'
                   WHEN Name LIKE '%law%' THEN 'law'
                   WHEN Name LIKE '%officeAdministration%' THEN 'officeAdministration'
                   WHEN Name LIKE '%productManagement%' THEN 'productManagement'
                   WHEN Name LIKE '%telecommunication%' THEN 'telecommunication'
                   WHEN Name LIKE '%sysAdministrator%' THEN 'sysAdministrator'
                   WHEN Name LIKE '%hr%' THEN 'hr'
                   WHEN Name LIKE '%ux%' THEN 'ux'
                   WHEN Name LIKE '%gameDev%' THEN 'gameDev'
                   WHEN Name LIKE '%electronics%' THEN 'electronics'
                   WHEN Name LIKE '%consulting%' THEN 'consulting'
                   WHEN Name LIKE '%support%' THEN 'support'
                   WHEN Name LIKE '%finance%' THEN 'finance'
                   WHEN Name LIKE '%other%' THEN 'other'
                   WHEN Name LIKE '%devops%' THEN 'devops'
                   WHEN Name LIKE '%architecture%' THEN 'architecture'
                   WHEN Name LIKE '%mobile%' THEN 'mobile'
                   WHEN Name LIKE '%businessIntelligence%' THEN 'businessIntelligence'
                   ELSE Category
    END
WHERE OfferPortalCompanyId = 4 -- <<<< Pracuj.pl Id

-- Przegląd lokalizacji mających mniej niż X ofert, pozwoliło to wybranie progu ustawienia lokalizacji na Other
SELECT Location, Count(*) AS LiczbaOfert
FROM Offers
GROUP BY Location
--HAVING Count(*) <= 5
ORDER BY LiczbaOfert DESC


-- Ustawienie lokalizacji na Other dla lokalizacji z liczbą ofert <= 5
UPDATE Offers SET Location = 'Other' WHERE Location IN (
    SELECT Location
    FROM Offers
    GROUP BY Location
    HAVING Count(*) <= 5
)

-- Ustawienie lokalizacji na Abroad dla lokalizacji zagranicznych
UPDATE Offers SET Location = 'Abroad' WHERE Location IN (
'Aalborg',
'Alsfeld',
'Amsterdam',
'Bergen',
'Berlin',
'Bratislava',
'Bremen',
'Denklingen',
'Denpasar',
'Frankfurt',
'Fulda',
'Hamburg',
'Haugesund',
'Luksemburg',
'Malmo',
'Memmingen',
'Monachium',
'Niemcy',
'Praga',
'Reykjavik',
'Rostock',
'Ryga',
'Saint Louis',
'Salmtal',
'Schweinfurt',
'Speyer',
'Ulm',
'Vienna'
)

-- Pracuj.pl ma więcej poziomów doświadczenia niż NoFluffJobs,
-- na bieżąco uruchamiałem odpowiednie zapytania w celach ujednolicenia
-- Przykład:
UPDATE Offers
SET ExpLevel = 'Mid'
WHERE ExpLevel = N'Specjalista (Mid / Regular)'