-- -- departments [abel team]

-- Display all departments [abel]
    select * from departments;

    select id, name from departments; // best practice 
-- Display department by id (=10) [sreya]       // best practice
    -- select * from departments where id = 10;
    select id, name from departments where id = 10;

-- Display deparments names for ids 20 or 30 [minhaj] 
    select name from departments where (id = 20) or (id = 30);

    select name from departments where (id IN (10,20));    
-- Display number of departments 
    select count(*) AS number_of_departments from departments;

-- Display all departments sorted by name A-Z order [sooraj]
    select id, name from departments order by name asc;
    --  by default ASC for order by

-- Display all departments sorted by name Z-A order [sooraj]
    select id, name from departments order by name desc;

-- Display deparments names for ids 20 or 30 sort by Z-A order [venkatesh]
    select name 
    from departments 
    where (id IN (10,20)) 
    order by name desc;

-- Display deparment by name = 'Alpha' [athira]
    select id, name 
    from departments 
    where name = 'Alpha';

-- -- countries [josh team]

-- Display all countries [josh]
    -- select * from countries;
    select id, name, ruler 
    from countries;

-- Display countries by id (=10) [mani]
    select id, name, ruler 
    from countries 
    where id = 11;

-- Display countries names for ids 21 or 41 [nayana]
    select name 
    from countries 
    where (id = 21) or (id = 41);

    select name 
    from countries 
    where (id in (21,41));
-- Display number of countries [dhaheen]
    select count(*) AS number_of_countries
    from countries;

-- Display all countries sorted by name A-Z order [bhagya]
    select id, name, ruler 
    from countries 
    order by name asc;

-- Display all countries sorted by name Z-A order 
    select id, name, ruler 
    from countries 
    order by name desc;

-- Display countries names for ids 21 or 41 sort by Z-A order 
    select name
    from countries 
    where (id in (21,41))
    order by name desc;

-- -- cities [sana team]
-- Display all cities [sana]
    select id, name, admin, country_id
    from cities;

-- Display cities by id (=101) [vishak]
    select id, name, admin, country_id
    from cities
    where (id = 101);

-- Display cities names for ids 102 or 103 [vinayak]
    select name
    from cities
    where (id in (102, 103));

-- Display number of cities [nimisha]
    select count(*) AS number_of_cities
    from cities;

-- Display all cities sorted by name A-Z order [ayisha] 
    select id, name, admin, country_id
    from cities
    order by name asc;

-- Display all cities sorted by name Z-A order [ayisha]
    select id, name, admin, country_id
    from cities
    order by name desc;

-- Display cities names for ids 102 or 103 sort by Z-A order [ayisha]
    select name
    from cities
    where (id in (102, 103))
    order by name desc;

-- select cities data by country_id = 11 [abel]
    select id, name, admin, country_id
    from cities
    where (country_id = 11);

    -- select country id for given country name 
    select id 
    from countries 
    where name = 'India';

    -- select cities data by country name = 'India' [ayisha->abel]
    select id, name, admin, country_id
    from cities
    where (country_id = (select id 
                        from countries 
                        where name = 'India'));
    -- 8 x 2 x 4 = 64 batches 
    -- each batch 60 students 
    select 64 * (60 / 2) as total_projects from dual;
    
    -- select cities data by country ruler = 'Trump' [abel]
    select id, name, admin, country_id
    from cities
    where (country_id = (select id 
                        from countries 
                        where ruler = 'Trump'));

    -- select cities data by country ruler = 'Trump' or 'Modi' [abel]
    select id, name, admin, country_id
    from cities
    where (country_id IN (select id 
                        from countries 
                        where (ruler IN ('Trump','Modi'))));

-- -- employees 
    -- basic queries - practical [self - solving]
    
    [athira -> vinayak] 
    -- display employees from department name = 'Beta'
        select id 
        from departments 
        where (name = 'Beta');

        select id, name, job_title, department_id, address, city_id 
        from employees 
        where (department_id = 20);
        -- expected output 
    select id, name, job_title, department_id, address, city_id 
    from employees 
    where (department_id = (select id 
                            from departments 
                            where (name = 'Beta')));

    [bhagya -> nimisha]
    -- display employees from country name = 'India'
        --#1 
        select id 
        from countries 
        where (name = 'India');
        --#2    
        select id 
        from cities  
        where (country_id = 11);
        --#3   
        select id 
        from cities  
        where (country_id = (select id 
                            from countries 
                            where (name = 'India')));
        --#4
        select id, name, job_title, department_id, address, city_id
        from employees 
        where (city_id IN (102, 103));
        --#5
        -- expected output 
        select id, name, job_title, department_id, address, city_id, salary, bonus
        from employees 
        where (city_id IN (select id 
                            from cities  
                            where (country_id = (select id 
                                                from countries 
                                                where (name = 'India')))));

    -- [ayisha -> sreya]
    -- aggregators : count, sum, avg, min, max 
    -- department id based number_of_employees
    select department_id, COUNT(*) as number_of_employees
    from employees 
    group by department_id;

    -- job_title based number_of_employees
    select job_title, COUNT(*) as number_of_employees
    from employees 
    group by job_title;

    -- city_id based number_of_employees
    select city_id, COUNT(*) as number_of_employees
    from employees 
    group by city_id;

    -- find number_of_employees, total salary, 
    -- min salary, max salary, average salary
    select count(*) as number_of_employees, 
        sum(salary) as total_salary, 
        min(salary) as min_salary, 
        max(salary) as max_salary, 
        avg(salary) as average_salary
    from employees;

    -- find total salary each deparment id wise 
    select department_id, sum(salary) as total_salary
    from employees 
    group by department_id;

    -- find number of employees, total salary, min salary, max salary, average salary 
    -- each deparment id wise 
    select department_id, 
        count(*) as number_of_employees, 
        sum(salary) as total_salary, 
        min(salary) as min_salary, 
        max(salary) as max_salary, 
        avg(salary) as average_salary
    from employees 
    group by department_id;

    -- find emp name, country name 
    select employees.name as emp_name, countries.name as country_name
    from employees
        inner join cities on (employees.city_id = cities.id)
        inner join countries on (cities.country_id = countries.id);
