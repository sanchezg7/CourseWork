--  Before you try the code in this file from the psql client, you need to create your database NBA-xxx and copy data from NBA to it. For example,
--  createdb NBA-tuy
--  pg_dump -t player_rs_career NBA | psql NBA-tuy
--  Note that those should be done under the Linux console. Then you can log into NBA-xxx and try the following scripts.

-- function 1 : seasons_played

--  The following line only needs to be done once before you do anything with pgplsql functions
-- CREATE LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION seasons_played (firstn VARCHAR, lastn VARCHAR) RETURNS INTEGER AS $$
DECLARE
   num_seasons INTEGER;
BEGIN
   select into num_seasons count(*) 
      from player_rs as prs 
      where prs.firstname=firstn and prs.lastname=lastn;
   
return num_seasons;
END;
$$ LANGUAGE plpgsql;
-- calling the function, try more test cases by changing the name
-- select * from seasons_played('Michael', 'Jordan');

-- point_matrix
-- This is my way of doing this: I first create a table to hold player named and four different place holders for the points

create table matrix (firstname varchar(30), lastname varchar(30),
		st_10000 integer, st_20000 integer, st_30000 integer,
		ge_30000 integer);

create or replace function point_matrix (varchar) returns setof matrix as $$ --this means it returns a whole table
DECLARE mviews RECORD;
BEGIN
  FOR mviews IN SELECT p.firstname, p.lastname, p.pts FROM player_rs_career p, player_rs r 
  WHERE p.ilkid = r.ilkid AND r.tid = $1 LOOP
    IF mviews.pts < 10000 THEN 
      INSERT INTO matrix(firstname, lastname, st_10000, st_20000, st_30000, ge_30000)
      VALUES(mviews.firstname, mviews.lastname, mviews.pts, NULL, NULL, NULL);
    ELSIF mviews.pts < 20000 THEN 
      INSERT INTO matrix(firstname, lastname, st_10000, st_20000, st_30000, ge_30000)
      VALUES(mviews.firstname, mviews.lastname, NULL, mviews.pts, NULL, NULL);
    ELSIF mviews.pts < 30000 THEN 
      INSERT INTO matrix(firstname, lastname, st_10000, st_20000, st_30000, ge_30000)
      VALUES(mviews.firstname, mviews.lastname, NULL, NULL, mviews.pts, NULL);
    ELSE 
      INSERT INTO matrix(firstname, lastname, st_10000, st_20000, st_30000, ge_30000)
      VALUES(mviews.firstname, mviews.lastname, NULL, NULL, NULL, mviews.pts);
    END IF;
  END LOOP;
-- loop through the matrix table and append all tuples in it to the resultset of this function using RETURN NEXT
  FOR mviews in SELECT DISTINCT * FROM matrix m ORDER BY m.firstname, m.lastname LOOP
    RETURN NEXT mviews;
  END LOOP;
  return;
END;
$$ LANGUAGE plpgsql;

-- executing the above function
-- select * from point_matrix ('IND');
-- clean up the things you just built
-- drop function seasons_played(varchar, varchar);
-- drop function point_matrix(varchar);
-- drop table matrix;