-- Keep a log of any SQL queries you execute as you solve the mystery.

--To check the description i used the code

SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

--MAIN data 10:15am ,Humphrey Street bakery
--3 witness of interviews each transcripts shows bakery

SELECT transcript FROM interviews WHERE month = 7 AND day = 28;
--10 minutes ,thief in car drove away
--saw the same thief at the atm morning that day on legget street , withdrawing money
--flight of fiftyville tomorrow.


-- Indication i found to be important
-- 1.number plate 2.phone number 3.passport number 4.transaction-details

SELECT activity FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND hour = 10 AND minute = 20;

--Shows activity is exit makes us go to next part

SELECT bakery_security_logs.activity, bakery_security_logs.license_plate, people.name FROM people --READ 2 COLUMNS GIVING ACTIVITY,LIC_PLATE AND NAME
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate --NUMBER PLATE TO SECURITY_LOG NUMBER PLATE
WHERE bakery_security_logs.year = 2024
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >=15
AND bakery_security_logs.minute >=25;


SELECT people.name, atm_transactions.transaction_type FROM people
JOIN bank_accounts ON bank_accounts.person_id=people.id --joining people id with bank id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number --trying to connect transaction details to acc details
WHERE atm_transactions.year = 2024
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_location = "Leggett Street" --remembering the transcript where she spotted the thief
AND atm_transactions.transaction_type = "withdraw";

--saw BRUCE again along with other peoples

UPDATE phone_calls
SET receiver = people.name
FROM people
WHERE phone_calls.receiver = people.phone_number;

SELECT caller, receiver FROM phone_calls --caller and receiver details
WHERE year = 2024
AND month = 7
AND day = 28
AND duration < 60;


SELECT id, hour , minute,origin_airport_id, destination_airport_id FROM flights
WHERE year = 2024
AND month = 7
AND day = 29
ORDER BY hour ASC
LIMIT 1;

--DESTINATION AIRPORT ID 4 , ORGIN ID 8, ID 36

SELECT flights.destination_airport_id, name, phone_number, license_plate FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id = 36
ORDER BY flights.hour ASC;

--found BRUCE again

SELECT people.name
FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE atm_transactions.year = 2024 AND atm_transactions.month =7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = "Leggett Street"
AND bakery_security_logs.hour >9 AND bakery_security_logs.hour < 11
ORDER BY bakery_security_logs.minute;


-- found BRUCE as a thief
-- acquintace kinda suspect Robin bcz of calling details
-- from airport_destination we found airport id 4 make it new york if search via name terminal

