-- emp_db 
    select * from employees WHERE name like '_y%';

    select * from employees WHERE name like '__n%';

    -- display employess name, salary and total salary (salary + bonus)
    -- display employees name, salary, bonus, incentive percentage, 
        caculated incentive, total salary (salary + bonus + incetive) 
        Note: incentive = 10% of salary = salary / 100 * 10
            (salary + bonus + ((salary / 100) * 10))
    -- display employees whose salary between

    select 12567 / 100, 12567 / 100 * 10 from dual;

    select * from employees;

    -- display employees name, department name, city name, 
    -- country name, city admin, country ruler, salary, bonus, total salary (salary + bonus)
    -- country name, city admin, country ruler, salary, bonus
        --   for the salary between 10000 and 12000 
                -- WHERE (salary >= 10000) AND (salary <= 12000)
                -- WHERE (salary BETWEEN 10000 AND 12000)
                -- WHERE (salary NOT BETWEEN 10000 AND 12000)
    -- country name, city admin, country ruler, salary, bonus
        -- where name ends with letter 'a'
        --       name starts with letter 'A' 
        --       name contains letter 'y'
        --       name's scond character to be e 
        --       name's third character to be n
        --       name's contains any where two 'e's   
            -- WHERE (name LIKE '%a')
    -- select employees whose salary is company's second max salary
        select * 
        from employees 
        where salary = (select max(salary) as second_max_salary
                        from employees
                        where salary < (select max(salary) as first_max_salary
                                        from employees))

    -- select employees whose salary is less than company's average salary 


    -- country id based total salary 

    -- country nanme based total salary 

    -- city name based total salary 

    -- country name then city name based total salary sort by country A-Z then by city name Z-A order 
        -- display the cities having salary less than 25000
        (group by, join, having)
        for example, 
            select cities.country_id, cities.name, sum(salary) 
            from employees 
                inner join cities on employees.city_id = cities.id
            group by cities.country_id, cities.name
            having sum(salary) < 25000

    -- display employees who are all getting second max salary from the company [using sub query]

    -- display employees whose salary matching their department's max salary [correlated sub query]
        --#1
            select department_id, max(salary)
            from employees 
            group by department_id;

            10 15000 [athira, not minhaj]
            20 13000 [dhaheen, not ayisha]
            30 10000 [nayana, not venkatesh]
        --#2
        select parent.name, parent.department_id, parent.salary
        from employees parent
        where parent.salary = (select max(child.salary) 
                            from employees child 
                            where child.department_id = parent.department_id);

            -- (1) For each employee in the outer query (parent), 
            -- the subquery calculates the maximum salary (max(child.salary)) 
            -- for the same department (parent.department_id).

            -- (2) The outer query then selects the employee 
            -- whose salary matches the maximum salary for their department.

    -- display employees whose salary matching their department's second max salary [correlated sub query]
        select parent.* 
        from employees parent 
        where salary = (select max(salary) as second_max_salary
                        from employees 
                        where (department_id = parent.department_id)
                            and (salary < (select max(salary) as first_max_salary
                                        from employees
                                        where (department_id = parent.department_id)
                                        )
                            ) 
                      )
    -- display employees whose salary less than their department's average salary [correlated sub query]
        
    

    -- display distinct job_titles 
    select job_title from employees; 

    select distinct job_title from employees; 

    select count(distinct job_title) as number_of_job_title  from employees; 

    select count(job_title) as number_of_job_title  from employees; 

    -- country name then city name based total salary sort by country A-Z then by city name Z-A order 
        -- display the cities having total salary less than 25000
        select 
            countries.name as country_name, 
            cities.name as city_name,  
            sum(employees.salary) as salary 
        from employees 
            inner join cities on employees.city_id = cities.id 
            inner join countries on cities.country_id = countries.id 
        group by countries.name,  cities.name
        -- having sum(employees.salary) < 25000
        order by countries.name Asc, cities.name DESC 
        -- order by country_name Asc, city_name DESC 
        -- order by 1 Asc, 2 DESC 
        --order by salary DESC
