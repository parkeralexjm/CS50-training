-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Open the schema and copy column titles into sheets to visualise the data
.schema
SELECT * FROM crime_scene_reports;
-- too many reports, cut it to reports from 7/28/21
SELECT description FROM crime_scene_reports WHERE year = "2021" AND month = "7" AND day = "28";
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three
-- witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- ## Find the witness names from the interview transcripts

SELECT name, transcript FROM interviews WHERE year = "2021" AND month = "7" AND day = "28";

-- "Ruth" Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--        If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- "Eugene" I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--          I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- "Raymond" As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief
--           say that they were planning to take the EARLIEST flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- "Emma" I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.

-- ## Use phone records to trace who the accomplice is by timing when they called out. Within 10 minutes of the theft. Security footage will start the timeline

SELECT hour, minute, activity, license_plate FROM bakery_security_logs WHERE year = "2021" AND month = "7" AND day = "28";

-- within 10 minutes of the theft, 8 cars left the bakery parking lot

-- | 10   | 16     | exit     | 5P2BI95       |
-- | 10   | 18     | exit     | 94KL13X       |
-- | 10   | 18     | exit     | 6P58WS2       |
-- | 10   | 19     | exit     | 4328GD8       |
-- | 10   | 20     | exit     | G412CB7       |
-- | 10   | 21     | exit     | L93JTIZ       |
-- | 10   | 23     | exit     | 322W7JE       |
-- | 10   | 23     | exit     | 0NTHK55       |
SELECT DISTINCT name, people.license_plate FROM people, bakery_security_logs WHERE bakery_security_logs.license_plate = people.license_plate AND year = "2021" AND month = "7" AND day = "28" AND hour = "10";
| Vanessa | 5P2BI95       |
| Bruce   | 94KL13X       |
| Barry   | 6P58WS2       |
| Luca    | 4328GD8       |
| Sofia   | G412CB7       |
| Iman    | L93JTIZ       |
| Diana   | 322W7JE       |
| Kelsey  | 0NTHK55       |

-- LEAD 1 - ATM before 10:15

SELECT name FROM atm_transactions, bank_accounts, people WHERE atm_transactions.account_number = bank_accounts.account_number AND bank_accounts.person_id = people.id AND year = "2021" AND month = "7" AND day ="28";
-- gave the list of all people who took out money on 7/28/21
-- # narrow list to only Leggett Street
-- # narrow list to withdraw
SELECT name FROM atm_transactions, bank_accounts, people WHERE atm_transactions.account_number = bank_accounts.account_number AND bank_accounts.person_id = people.id AND year = "2021" AND month = "7" AND day ="28" AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
| Bruce   | ++
| Diana   | ++
| Brooke  |
| Kenny   |
| Iman    | ++
| Luca    | ++
| Taylor  |
| Benista |
-- LEAD 2 - EARLIEST flight out of Fiftyville
-- find earliest flight
SELECT * from flights WHERE year = "2021" AND month = "7" AND day = "28" ORDER BY hour;
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 27 | 5                 | 8                      | 2021 | 7     | 28  | 8    | 35     |

SELECT * FROM passengers WHERE flight_id = "27";
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 27        | 4631067354      | 5C   |
| 27        | 9698118788      | 6B   |
| 27        | 9355133130      | 7D   |
| 27        | 1207566299      | 8C   |
| 27        | 6131360461      | 9A   |
| 27        | 4223654265      | 2C   |
| 27        | 7712200330      | 3C   |
-- gives all the passenger passports on flight 27
SELECT name FROM passengers, flights, people WHERE people.passport_number = passengers.passport_number AND passengers.flight_id = flights.id AND flight_id = "27";
+-----------+
|   name    |
+-----------+
| Mark      |
| Keith     |
| Amy       |
| Jeremy    |
| Kristina  |
| Walter    |
| Stephanie |

-- name of all passengers that are on flight 27, none overlap with the atm withdrawl or bakery log, list of passengers seems very small?
-- Recheck passenger list from flight TOMORROW

sqlite> SELECT * from flights WHERE year = "2021" AND month = "7" AND day = "29" ORDER BY hour;
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
+----+-------------------+------------------------+------+-------+-----+------+--------+

sqlite> SELECT * FROM passengers WHERE flight_id = "36";
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 7214083635      | 2A   |
| 36        | 1695452385      | 3B   |
| 36        | 5773159633      | 4A   |
| 36        | 1540955065      | 5C   |
| 36        | 8294398571      | 6C   |
| 36        | 1988161715      | 6D   |
| 36        | 9878712108      | 7A   |
| 36        | 8496433585      | 7B   |

sqlite> SELECT name FROM passengers, flights, people WHERE people.passport_number = passengers.passport_number AND passengers.flight_id = flights.id AND flight_id = "36";
+--------+
|  name  |
+--------+
| Doris  |
| Sofia  |
| Bruce  | +
| Edward |
| Kelsey |
| Taylor |
| Kenny  | +
| Luca   |
+--------+
SELECT name FROM atm_transactions, bank_accounts, people WHERE atm_transactions.account_number = bank_accounts.account_number AND bank_accounts.person_id = people.id AND year = "2021" AND month = "7" AND day ="28" AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
| Bruce   | ++
| Diana   | -+
| Brooke  | -
| Kenny   | +
| Iman    | -+
| Luca    | ++
| Taylor  | +
| Benista | -
SELECT DISTINCT name, people.license_plate FROM people, bakery_security_logs WHERE bakery_security_logs.license_plate = people.license_plate AND year = "2021" AND month = "7" AND day = "28" AND hour = "10";
| Vanessa | 5P2BI95       | -
| Bruce   | 94KL13X       | +
| Barry   | 6P58WS2       | -
| Luca    | 4328GD8       | +
| Sofia   | G412CB7       | -
| Iman    | L93JTIZ       | +
| Diana   | 322W7JE       | +
| Kelsey  | 0NTHK55       | -

-- Only names that leave the parking lot 10 mins after theft, on earliest flight and using ATM to withdraw on the day are Bruce and Luca
-- Left Fiftyville and arrived at LGA

-- "Emma" I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.
-- who spent 30 minutes (30*60 = 1800s) on the phone
sqlite> SELECT * FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28";
-- really long list but no duration over 1800 (multiple calls?)
-- check against the phone numbers of Bruce and Luca
sqlite> SELECT name, phone_number FROM people WHERE name IN ("Bruce", "Luca");
+-------+----------------+
| name  |  phone_number  |
+-------+----------------+
| Luca  | (389) 555-5198 |
| Bruce | (367) 555-5533 |
+-------+----------------+

sqlite> SELECT * FROM phone_calls WHERE caller LIKE "%555-5198"; -- Luca total calls in the db
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 57  | (389) 555-5198 | (368) 555-3561 | 2021 | 7     | 25  | 414      |
| 326 | (389) 555-5198 | (609) 555-5876 | 2021 | 7     | 29  | 397      |
+-----+----------------+----------------+------+-------+-----+----------+
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- Bruce calls on 28th less than 1 minute long
sqlite> SELECT * FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND caller LIKE "%555-5533" AND duration < 60;
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
+-----+----------------+----------------+------+-------+-----+----------+
-- lookup receiver in people

sqlite> SELECT DISTINCT name FROM people, phone_calls WHERE phone_calls.receiver = people.phone_number AND phone_calls.receiver = "(375) 555-8161";
+-------+
| name  |
+-------+
| Robin |
+-------+

-- Accomplice