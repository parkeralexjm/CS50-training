-- gives a list of all kevin bacon movies
SELECT name FROM people WHERE people.id IN (
    SELECT person_id
    FROM stars, movies
    WHERE movies.id = stars.movie_id
    AND movie_id IN (
        SELECT movie_id
        FROM stars, movies, people
        WHERE movies.id = stars.movie_id
        AND people.id = stars.person_id
        AND people.id IN(
            SELECT id
            FROM people
            WHERE name = "Kevin Bacon"
            AND birth = "1958"
        )
    )
)
AND NOT name = "Kevin Bacon"
AND NOT birth = "1958"
;