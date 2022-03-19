SELECT title
    FROM movies, people, ratings, stars
    WHERE movies.id = stars.movie_id
    AND people.id = stars.person_id
    AND movies.id = ratings.movie_id
        AND name = "Chadwick Boseman"
        ORDER BY rating DESC 
        LIMIT 5;