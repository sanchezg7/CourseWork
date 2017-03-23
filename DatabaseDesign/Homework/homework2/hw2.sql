1.a.SELECT E.Ename,
	FROM Employee E, Works_on W, Project P
	WHERE E.Dno = 10 AND E.SSN = W.ESSN AND 
		W.Pno = P.Pnumber AND W.Hours > 15 AND
		P.Pname = 'X';
				
b. 	SELECT W.ESSN
	FROM Works_on W1, Projects P1
	WHERE W1.Pno = P.Pnumber AND P.Plocation = 'Brooklyn'
	EXCEPT
	SELECT 
	FROM Works_on W2, Projects P2
	WHERE W2.Pno = P2.Pnumber AND P2.Plocation = 'Long Island';
			
c. 	SELECT MAX(salary)
	FROM Employee E

//unsure
d.	SELECT E2.Ename
	FROM Employee E1, Employee E2, Department D
	WHERE D.Manager_SSN = E1.SSN AND E1.Supervisor_SSN = E2.SSN;
					
e.	SELECT E.Ename,
	FROM Employee E, Dependent D,
	WHERE E.name = D.D_name AND
			E.SSN = D.ESSN;
			
f. 	SELECT E.Ename,
	FROM Projects P, Works_on W, Employee E
	WHERE P.Plocation = 'Brooklyn' AND
			W.Pno = P.Pnumber AND
			W.ESSN = E.SSN;
			
g.	SELECT E1.Ename
	FROM Employee E1, Employee E2,
	WHERE E1.Supervisor_SSN = E2.SSN AND
			E2.Ename = 'John Doe';
			
h.	SELECT E1.Ename,
	FROM Employee E1
	EXCEPT
	SELECT E2.Ename,
	FROM Employee E2, Works_on W,
	WHERE E2.SSN = W.ESSN;
					
i. 	SELECT r.P
	FROM r
	WHERE r.R <= 6;

j.	SELECT *
	FROM r, s;
	
k. 	SELECT *
	FROM r
	NATURAL JOIN s;

l. 	SELECT *
	FROM r
	JOIN s 
	ON r.R > s.C;
	
m. 	SELECT *
	FROM r
	JOIN s
	ON r.P = s.A, s.C < r.R;

q. 	SELECT P, R
	FROM r
	WHERE UNIQUE ( SELECT P,R
					FROM r
					
					EXCEPT 
					
					SELECT A,C
					FROM s
					)