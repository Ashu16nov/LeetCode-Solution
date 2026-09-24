# Write your MySQL query statement below
SELECT E.name AS name, B.bonus AS bonus
FROM Employee E
LEFT JOIN Bonus B 
ON E.empId = B.empId
WHERE Bonus < 1000 OR Bonus IS NULL;