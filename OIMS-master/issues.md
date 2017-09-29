##1
Company Database is written in db.py should be moved to db_admintables.py

##2
update repsonse.logo in menu.py , once website is deployed on pythonanywhere.com

##3
include company-id in login page

##4
redirect user to appropriate page (based on its role) after login

##5
ask for emp-id pattern while registering
enable validation against emp-id pattern

##6
move generateRandomPassword to utilities.py 
move sendMail to utilities.py
decide location of utilities.py so that it is not exposed at all

##7
allow admin to create emp-id pattern while registering for company
adding validation while creating users

##8
Update user/profile so that company can not be changed.
[Resolved : @db.py => auth_user : make field company_id writeable=False]

##9
session.company_id is not captured everytime.

