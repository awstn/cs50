-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Look at crime report on the day Duck was stolen 07/28/2023
SELECT * 
FROM crime_scene_reports 
WHERE year = 2023 AND month = 7 AND DAY = 28;

/*
295|2023|7|28|Humphrey Street|
Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. 
Interviews were conducted today with three witnesses who were present at the time – 
each of their interview transcripts mentions the bakery.
*/

-- Read interviews from THREE witnesses 
SELECT *
FROM interviews
WHERE year = 2023 AND month = 7 AND DAY = 28;

-- CHECK FLIGHT RECORDS LEAVING FIFTYVILLE ON 2023 - 7 - 29
SELECT full_name, city, flights.id
FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
WHERE flights.year = 2023 AND flights.month = 7 AND flights.day = 29
ORDER BY flights.hour ASC
LIMIT 1; 
-- LaGuardia Airport | New York City -- Flight 36

-- COMPARE license plate info to people table INTERSECT with people on flight 36
-- GET THE THIEF BUT NOT ACCOMPLICE
SELECT name, people.passport_number, license_plate, phone_number
FROM people
WHERE license_plate IN (
    SELECT license_plate 
    FROM bakery_security_logs
    WHERE year = 2023 AND month = 7 AND day = 28
    AND hour = 10 AND minute < 26 AND minute > 14
)
INTERSECT
SELECT name
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36;

-- Name of people that withdrew from Leggett Street on 2023-07-28
SELECT people.name, people.phone_number, people.license_plate, people.id
FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE year = 2023 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street' AND atm_transactions.transaction_type != 'deposit'
ORDER BY atm_transactions.id;

-- BRUCE AND LUCA have been at the atm, on flight 36 and left the bakery within 10 minutes of the crime

-- CHECK PHONECALLS ON 2023-07-28 AROUND 10:15
SELECT p1.name AS caller, p2.name AS receiver, duration
FROM phone_calls
JOIN people AS p1 ON caller = p1.phone_number
JOIN people AS p2 ON receiver = p2.phone_number
WHERE year = 2023 AND month = 7 AND day = 28 
AND duration < 60
ORDER BY duration ASC;

-- ONLY BRUCE has made a call less than a minute long on 2023-07-28
-- See who is on the plane that also received the call on 2023-07-28
SELECT name
FROM people, passengers
WHERE passengers.flight_id = 36 
INTERSECT
SELECT p2.name AS receiver
FROM phone_calls
JOIN people AS p1 ON caller = p1.phone_number
JOIN people AS p2 ON receiver = p2.phone_number
WHERE year = 2023 AND month = 7 AND day = 28 
AND duration < 60
;

-- ROBIN is on FLIGHT 36
-- BRUCE and Robin are the culprits


