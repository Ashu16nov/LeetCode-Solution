# Write your MySQL query statement below
DELETE p1 From Person p1 JOIN Person p2 WHERE p2.email = p1.email AND p1.id > p2.id;