
-- find description from crime_scene_reports due to time and place of the crime
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- find three witnesses transcript interviews
SELECT name, transcript FROM Interviews  WHERE year = 2021 AND month = 7 AND day = 28;
-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- Raymond|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- # ruth clue #
-- find name of who exit from bakery in 10 miutes from crime time
SELECT name FROM people WHERE license_plate IN (SELECT DISTINCT(license_plate) FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute < 25 AND minute > 15);
-- Vanessa
-- Barry
-- Iman
-- Sofia
-- Luca
-- Diana
-- Kelsey
-- Bruce

-- # eugene clue #
-- find name of atm users
SELECT name from people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28;
-- Bruce
-- Kaelyn
-- Diana 
-- Brooke
-- Kenny
-- Iman
-- Luca|
-- Taylor 
-- Benista 

-- # raymond clues # 
-- find name of phone calls
SELECT DISTINCT(name) FROM phone_calls JOIN people ON people.phone_number = phone_calls.caller where year = 2021 AND month = 7 AND day = 28 AND duration < 60;
-- Sofia
-- Kelsey
-- Bruce 
-- Taylor 
-- Diana 
-- Carina
-- Kenny 
-- Benista 

-- find earlist fly in 29
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour;
-- 36|8|4|2021|7|29|8|20 --> earlist fly and destination airport id is 4
-- 43|8|1|2021|7|29|9|30
-- 23|8|11|2021|7|29|12|15
-- 53|8|9|2021|7|29|15|20
-- 18|8|6|2021|7|29|16|0

-- find name if the earleast fly
SELECT DISTINCT(name) FROM people WHERE passport_number IN (SELECT passport_number FROM passengers JOIN flights ON flights.id = passengers.flight_id WHERE year = 2021 AND month = 7 AND day = 29 AND flight_id = 36);
-- Kenny
-- Sofia
-- Taylor
-- Luca
-- Kelsey
-- Edward
-- Bruce
-- Doris

-- subscription from three clues
-- bruce is thief
SELECT phone_number FROM people WHERE name = "Bruce";
SELECT receiver FROM phone_calls WHERE caller = "(367) 555-5533" and year = 2021 AND month = 7 AND day = 28 AND duration < 60;
SELECT name FROM people WHERE phone_number = "(375) 555-8161"; -- ==> Robin
-- Robin is Acomplice
SELECT city FROM airports WHERE id = 4;
-- destination is New York City
