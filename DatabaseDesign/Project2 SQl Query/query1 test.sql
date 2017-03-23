NBA=> SELECT DISTINCT cs.firstname, cs.lastname, cs.year
FROM coaches_season cs, player_rs prs
WHERE cs.year = prs.year AND
cs.cid = prs.ilkid
order by cs.firstname;


 firstname |  lastname   | year
-----------+-------------+------
 Al        | Attles      | 1969
 Al        | Attles      | 1970
 Al        | Cervi       | 1949
 Al        | Cervi       | 1950
 Al        | Cervi       | 1951
 Al        | Cervi       | 1952
 Alex      | Hannum      | 1956
 Andrew    | Levane      | 1952
 Bill      | Russell     | 1966
 Bill      | Russell     | 1967
 Bill      | Russell     | 1968
 Bob       | Cousy       | 1969
 Bob       | Feerick     | 1949
 Bob       | Leonard     | 1962
 Bob       | Pettit      | 1961
 Bob       | Wanzer      | 1955
 Bob       | Wanzer      | 1956
 Bruce     | Hale        | 1948
 Buddy     | Jeannette   | 1947
 Buddy     | Jeannette   | 1948
 Buddy     | Jeannette   | 1949
 Carl      | Braun       | 1959
 Carl      | Braun       | 1960
 Charley   | Shipp       | 1949
 Cliff     | Barker      | 1949
 Cliff     | Barker      | 1950
 Dave      | Cowens      | 1978
 Dave      | DeBusschere | 1964
 Dave      | DeBusschere | 1965
 Dave      | DeBusschere | 1966
 Dick      | Fitzgerald  | 1946
 Dick      | McGuire     | 1959
 Dolph     | Schayes     | 1963
 Ed        | Macauley    | 1958
 Ed        | Sadowski    | 1946
 Fred      | Scolari     | 1951
 Grady     | Lewis       | 1948
 Horace    | McKinney    | 1950
 Howie     | Schultz     | 1949
 Jack      | Smiley      | 1949
 Jerry     | Reynolds    | 1986
 Jerry     | Reynolds    | 1987
 Jerry     | Reynolds    | 1988
 Jerry     | Reynolds    | 1989
 Jimmy     | Darden      | 1949
 John      | Logan       | 1950
 Kevin     | Loughery    | 1972
 Lenny     | Wilkens     | 1969
 Lenny     | Wilkens     | 1970
 Lenny     | Wilkens     | 1971
 Lenny     | Wilkens     | 1974
 Paul      | Armstrong   | 1948
 Paul      | Seymour     | 1956
 Paul      | Seymour     | 1957
 Paul      | Seymour     | 1958
 Paul      | Seymour     | 1959
 Red       | Holzman     | 1953
 Richie    | Guerin      | 1964
 Richie    | Guerin      | 1965
 Richie    | Guerin      | 1966
 Richie    | Guerin      | 1968
 Richie    | Guerin      | 1969
 Slater    | Martin      | 1956
 Tom       | Marshall    | 1958
 Walt      | Budko       | 1950
(65 rows)

NBA=>
