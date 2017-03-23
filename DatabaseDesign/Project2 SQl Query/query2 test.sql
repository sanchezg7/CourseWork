NBA=> SELECT DISTINCT cs.firstname, cs.lastname, cs.year, t.name
FROM coaches_season cs, player_rs prs, teams t
WHERE cs.year = prs.year AND
cs.cid = prs.ilkid AND
prs.tid = t.tid AND
cs.tid = t.tid
order by cs.lastname;
 firstname |  lastname   | year |      name
-----------+-------------+------+----------------
 Al        | Attles      | 1969 | Warriors
 Al        | Attles      | 1970 | Warriors
 Cliff     | Barker      | 1949 | Olympians
 Cliff     | Barker      | 1950 | Olympians
 Carl      | Braun       | 1959 | Knicks
 Carl      | Braun       | 1960 | Knicks
 Walt      | Budko       | 1950 | Bullets
 Al        | Cervi       | 1949 | Nationals
 Al        | Cervi       | 1950 | Nationals
 Al        | Cervi       | 1951 | Nationals
 Al        | Cervi       | 1952 | Nationals
 Bob       | Cousy       | 1969 | Royals
 Dave      | Cowens      | 1978 | Celtics
 Jimmy     | Darden      | 1949 | Nuggets
 Dave      | DeBusschere | 1964 | Pistons
 Dave      | DeBusschere | 1965 | Pistons
 Dave      | DeBusschere | 1966 | Pistons
 Bob       | Feerick     | 1949 | Capitols
 Richie    | Guerin      | 1964 | Hawks
 Richie    | Guerin      | 1964 | Spirits
 Richie    | Guerin      | 1965 | Hawks
 Richie    | Guerin      | 1965 | Spirits
 Richie    | Guerin      | 1966 | Hawks
 Richie    | Guerin      | 1966 | Spirits
 Richie    | Guerin      | 1968 | Hawks
 Richie    | Guerin      | 1969 | Hawks
 Bruce     | Hale        | 1948 | Jets
 Alex      | Hannum      | 1956 | Hawks
 Alex      | Hannum      | 1956 | Spirits
 Red       | Holzman     | 1953 | Hawks
 Buddy     | Jeannette   | 1947 | Bullets
 Buddy     | Jeannette   | 1948 | Bullets
 Buddy     | Jeannette   | 1949 | Bullets
 Bob       | Leonard     | 1962 | Zephyrs
 Andrew    | Levane      | 1952 | Hawks
 Grady     | Lewis       | 1948 | Bombers
 John      | Logan       | 1950 | Blackhawks
 Kevin     | Loughery    | 1972 | 76ers
 Ed        | Macauley    | 1958 | Hawks
 Ed        | Macauley    | 1958 | Spirits
 Tom       | Marshall    | 1958 | Royals
 Slater    | Martin      | 1956 | Hawks
 Slater    | Martin      | 1956 | Spirits
 Dick      | McGuire     | 1959 | Pistons
 Bob       | Pettit      | 1961 | Hawks
 Bob       | Pettit      | 1961 | Spirits
 Bill      | Russell     | 1966 | Celtics
 Bill      | Russell     | 1967 | Celtics
 Bill      | Russell     | 1968 | Celtics
 Ed        | Sadowski    | 1946 | Huskies
 Dolph     | Schayes     | 1963 | 76ers
 Howie     | Schultz     | 1949 | Duffey Packers
 Fred      | Scolari     | 1951 | Bullets
 Paul      | Seymour     | 1956 | Nationals
 Paul      | Seymour     | 1957 | Nationals
 Paul      | Seymour     | 1958 | Nationals
 Paul      | Seymour     | 1959 | Nationals
 Charley   | Shipp       | 1949 | Hawks
 Jack      | Smiley      | 1949 | Hawks
 Bob       | Wanzer      | 1955 | Royals
 Bob       | Wanzer      | 1956 | Royals
 Lenny     | Wilkens     | 1969 | Supersonics
 Lenny     | Wilkens     | 1970 | Supersonics
 Lenny     | Wilkens     | 1971 | Supersonics
 Lenny     | Wilkens     | 1974 | Trailblazers
(65 rows)

NBA=>
