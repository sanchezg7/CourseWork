CREATE OR REPLACE FUNCTION get_height(firstn VARCHAR, lastn VARCHAR) RETURNS FLOAT AS $$
DECLARE totalH FLOAT;
BEGIN
totalH := -1;
SELECT INTO totalH sum((p.h_feet * 30.48) + (p.h_inches *2.54)) 
FROM players p
WHERE p.firstname = firstn AND p.lastname = lastn;
IF totalH is NULL THEN 
	return 0.0;
ELSIF totalH > 0 THEN
	return totalH;
END IF;
END;
$$ LANGUAGE plpgsql;



--row_number() over (ORDER BY sum) AS rowindex
--this table will hold the results of that year
CREATE TABLE ranking(netwins integer, firstname VARCHAR(30), lastname VARCHAR (30), rindex INTEGER);

CREATE OR REPLACE FUNCTION get_coach_rank(int, VARCHAR, VARCHAR) RETURNS INTEGER AS $$
DECLARE mviews RECORD;
DECLARE rowindex INTEGER;
DECLARE finalRank INTEGER;
BEGIN
	finalRank := -1;
	rowindex := 1;
	FOR mviews IN SELECT sum(cs.season_win + cs.playoff_win - cs.season_loss - cs.playoff_loss), cs.firstname, cs.lastname 
		FROM coaches_season cs 
		WHERE cs.year = $1 
		GROUP BY cs.firstname, cs.lastname 
		ORDER BY sum DESC
LOOP
	INSERT INTO ranking(netwins, firstname, lastname, rindex)
		VALUES(mviews.sum, mviews.firstname, mviews.lastname, rowindex);
	rowindex := rowindex + 1;
END LOOP;

SELECT INTO finalRank r.rindex FROM ranking r WHERE r.firstname = $2 AND r.lastname = $3;
DELETE FROM ranking;
IF finalRank is NULL THEN
	return -1;
ELSIF 1 then
	return finalRank;
END IF;
END;
$$ LANGUAGE plpgsql;





