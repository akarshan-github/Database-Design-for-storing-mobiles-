# Database-Design-for-storing-mobiles-
There is a supplier for mobile phones in locality named Sam  and he needs a database for mobile phones to be maintained,
the database stores the following information about each of the mobile phones:

> the model name (considering the unique string name for each mobile), 
> price (considering no two mobile have the same price), 
> company (string), 
> camera megapixels (float), 
> colour (string), 
> RAM(integer), 
> battery backup (integer), 
> removable batteries (boolean).

For Sam, the queries of concern are querying using Mobile Name and price (which are both unique, individual). 
The database is designed  using the AVL tree as the primary data structure. 
The database supports the following operations:
A: Add mobile to the database (name, price, company, camera, colour, RAM, battery, removable battery)
QP: Query database using price (prints “Not Found” in case of any issues)
QN: Query database using Name (prints “Not Found” in case of any issues)
DP: Query database using price and delete model for the database (prints “Not Found” in case of any issues)
DN: Query the database using the Name and delete model for the database (prints “Not Found” in case of any issues)
R: Get all mobile phones with price in a certain range (with price in ascending order)
T: Terminate the programme

Automatically   an auto-increment ID is also assigned to each database entry, 
and  operated id is printed in case of all operations


The inputs to the database and there corresponding outputs are as follows :

Sample Input is as follows:
A Nokia 6.2, 12000, Nokia, 24, Grey, 8, 3000, 0
A Samsung Galaxy A12, 10000, Samsung, 8, Red, 6, 5000, 0
A Dell 1001, 13000, Dell, 4.5, Green, 7, 45000, 0
QP 12000
QP 7000
R 11500 14500
DN Nokia 6.2
A Xperia, 15000, Sony, 5.9, Blue, 10, 60000, 1
T


Sample Output:
ID: 1
ID: 2
ID: 3
ID: 1, Nokia 6.2, 12000, Nokia, 24, Grey, 8, 3000, 0
Not Found
ID: 1, Nokia 6.2, 12000, Nokia, 24, Grey, 8, 3000, 0
ID: 3, Dell 1001, 13000, Dell, 4.5, Green, 7, 45000, 0
Deleted ID: 1
ID: 4

Working :
> A Nokia 6.2, 12000, Nokia, 24, Grey, 8, 3000, 0 - Inserts the mobile phone with name Nokia 6.2 in the database and similarly for other attributes as well. Id is also printed.
> A Samsung Galaxy A12, 10000, Samsung, 8, Red, 6, 5000, 0 -  Inserts the mobile phone with name Samsung Galaxy A12 in the database and similarly for other attributes as well.Id is also printed.
> A Dell 1001, 13000, Dell, 4.5, Green, 7, 45000, 0 - Inserts the mobile phone with name Dell in the database and similarly for other attributes as well.Id is also printed.
> QP 12000 - Queries The database for mobile phone having price = 120000 and displays the details of the found mobile phone.
> QP 7000 - Queries The database for mobile phone having price = 70000 and displays the details of the found mobile phone.
> R 11500 14500 - Displays details of all the mobile phones in the database  having price range from 11500 to 14500 in increasing order of the prices.
> DN Nokia 6.2 - Deletes the Mobile phone from the database by searching through name as Nokia 6.2 and prints the deleted ID.
> A Xperia, 15000, Sony, 5.9, Blue, 10, 60000, 1 -  Inserts the mobile phone with name Nokia 6.2 in the database and similarly for other attributes as well. Id is also printed.
> T - Terminates the programme.
