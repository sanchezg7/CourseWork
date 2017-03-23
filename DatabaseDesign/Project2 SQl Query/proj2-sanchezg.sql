-- change xxx in this line to your NetID 

\o proj2-xxx.out



-- Put your SQL statement under the following lines:



-- 1. Find those who happened to be a coach and a player in the same season, list their first names, last names, and the year this happened (hint: you need to join coaches_season and player_rs);

--We filter people by their id (known as cid in the coaches_season table and ilkid in the player_rs table)
--Assume that ilkid and cid are interelated
--Assume that people can have different names on different relations
SELECT DISTINCT cs.firstname, cs.lastname, cs.year
FROM coaches_season cs, player_rs prs
WHERE cs.year = prs.year AND
cs.cid = prs.ilkid
order by cs.firstname;

-- 2. Same as the previous query, except that we only need to find those who played the two roles in the same team in the same season;
--assume people in coaches and player_rs use the same id system in cid and ilkid
SELECT DISTINCT cs.firstname, cs.lastname, cs.year
FROM coaches_season cs, player_rs prs, teams t
WHERE cs.year = prs.year AND
	cs.cid = prs.ilkid AND
	prs.tid = t.tid AND
	cs.tid = t.tid;

-- 3. List the average weight and height of Phil Jackson's team (players only) in each season he coached. Output the season (year), average weight. and average height only;
--assume there are no other Phil Jacksons
--assume that players are not represented more than one roll on the same team for that season
SELECT cs.year, AVG (p.weight) as avg_weight, AVG((p.h_feet * 30.48) + (p.h_inches*2.54)) as avg_height
FROM coaches_season cs, player_rs prs, players p
WHERE cs.firstname = 'Phil' AND
cs.lastname = 'Jackson' AND
cs.tid = prs.tid AND
cs.year = prs.year AND
prs.ilkid = p.ilkid
GROUP BY cs.year
ORDER BY cs.year ASC;


-- 4. Which college/university sent the largest number of drafts? List the name of the school and the number of drafts sent. Order the results by school names;
--assume no two schools will be tied
--top count will be at the top of the list

SELECT d.draft_from, count(*)
FROM draft d
GROUP BY d.draft_from
ORDER BY count desc
LIMIT 1;

--OR THIS QUERY ALSO WORKS

SELECT d.draft_from, count(*)
FROM draft d
GROUP BY d.draft_from
HAVING count(*) >= ALL (SELECT count(*)
FROM draft d1
GROUP BY d1.draft_from);


-- 5. Find the second most successful coach in regular seasons in history; The level of success of a coach is measured as season_win / (season_win + season_loss). Note that you have to count all seasons the coach attended to calculate this value;
--assume the ordering of the pct is from highest to lowest
--assume there are no two coaches with the same name

SELECT cs.firstname, cs.lastname, (sum(season_win)/(cast(sum(season_win) AS FLOAT) + cast (sum(season_loss)AS FLOAT))) AS pct
FROM coaches_season cs
group by cs.firstname, cs.lastname
order by pct desc
limit 1
offset 1;

-- 6. List the number and average weight of all drafts in year 2001;
--assume the there are not duplicate players in the draft table for the 2001 season
SELECT count(*), avg(p.weight) AS avg_weight
FROM draft d, players p
WHERE d.draft_year = 2001 AND
	d.ilkid = p.ilkid;

-- 7. Who coached in all leagues? Use the method introduced in class with 'NOT EXISTS -- EXCEPT -- ..." ;

SELECT DISTINCT cs.firstname, cs.lastname
FROM coaches_season cs
WHERE NOT EXISTS (SELECT t1.league
					FROM teams t1
					EXCEPT
					SELECT DISTINCT t.league
					FROM teams t
					WHERE cs.tid = t.tid);




-- 8. Same as in query 7, but use the approach with "GROUP BY ...";
SELECT cs.firstname, cs.lastname
FROM coaches_season cs, teams t1
WHERE cs.tid = t1.tid
GROUP BY cs.firstname, cs.lastname
HAVING count(DISTINCT t1.league) = (SELECT count(distinct t2.league) 
									FROM teams t2);

-- 9. Find all the players who ever played in a Chicago team and a Houston team. List their first names followed by their last names;
--assume there can be multiple teams in these locations 
--assume the same player will only be listed once
SELECT prs.firstname, prs.lastname
FROM player_rs prs, teams t
WHERE prs.tid = t.tid AND
t.location = 'Chicago'
INTERSECT
SELECT prs.firstname, prs.lastname
FROM player_rs prs, teams t
WHERE prs.tid = t.tid AND
t.location = 'Houston';
	

-- 10. List the top 10 players who scored the most points in history. List their last and first names and the points they scored (hint: use "order by" to sort the results and 'limit xxx' to limit the number of rows returned);
--assume we include all pts scored for multiple teams in the season
SELECT prs.firstname, prs.lastname, sum(prs.pts)
FROM player_rs prs
group by prs.lastname, prs.firstname
order by sum DESC
limit 10;




-- redirecting output to console
\o