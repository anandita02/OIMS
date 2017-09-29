# -*- coding: utf-8 -*-
##########################################################################
## This is a admin controller
## - registerCompany is for registering company on OIMS
## - createUser is for creating users for given company
##########################################################################
import datetime

def registerCompanyValidation(form):
    company_url_list = db(db.company.company_url==form.vars.company_url).select().as_list()
    if len(company_url_list) != 0:
        form.errors.company_url = "Company URL is already registered !"

def registerCompany():
    form = SQLFORM.factory(
           Field('company_url','string' ,requires=IS_NOT_EMPTY()),
           Field('company_name','string',requires=IS_NOT_EMPTY()),
           Field('admin_emp_id','string',requires=IS_NOT_EMPTY()),
           Field('admin_first_name','string',requires=IS_NOT_EMPTY()),
           Field('admin_last_name','string',requires=IS_NOT_EMPTY()),
           Field('date_of_birth','date',requires=IS_DATE(format=T('%Y-%m-%d'), error_message='must be YYYY-MM-DD!')),
           Field('email',requires=IS_EMAIL()),
           Field('password','password',requires=CRYPT(min_length=8)))

    if form.process(onvalidation=registerCompanyValidation,message_onfailure="Please fill all values correctly!").accepted:
        new_company_id=db.company.insert(company_url=form.vars.company_url,
                                         company_name=form.vars.company_name,
                                         admin_emp_id=form.vars.admin_emp_id,
                                         admin_first_name=form.vars.admin_first_name,
                                         admin_last_name=form.vars.admin_last_name,
                                         date_of_birth=form.vars.date_of_birth,
                                         email=form.vars.email,
                                         password=form.vars.password)
        session.company_id = new_company_id
        new_user_id=db.auth_user.insert( first_name=form.vars.admin_first_name,
                                         last_name=form.vars.admin_last_name,
                                         emp_id=form.vars.admin_emp_id,
                                         date_of_birth=form.vars.date_of_birth,
                                         email=form.vars.email,
                                         password=form.vars.password,
                                         company_id=new_company_id)

        admin_group_id = ROLE_DICT['Admin']
        auth.add_membership(admin_group_id, new_user_id)

        redirect(URL('admin','index'))
    elif form.errors:
        response.flash = "Please fill the form correctly !"

    return dict(form=form)

def generateRandomPassword():
    import string
    import random
    password = ''
    for i in range(3):
        password += random.choice(string.lowercase)
        password += random.choice(string.uppercase)
        password += random.choice(string.digits)

    return password

def sendMail(reciever,subject,message):

    if subject == "Welcome to OIMS":
        message = "Welcome to OIMS. You are now registered user to OIMS." + message

    return mail.send(to=[reciever],
                     subject=subject,
                     reply_to="utsav.chokshi.29@gmail.com",
                     message=message)

def createUserValidation(form):

    rows = db(db.auth_user.company_id==session.company_id and
              db.auth_user.email==form.vars.email).select().as_list()

    if len(rows) != 0:
        form.errors.email = "Email Address is already in use!"

    rows =  db(db.auth_user.company_id==session.company_id and
               db.auth_user.emp_id==form.vars.emp_id).select().as_list()

    if len(rows) != 0:
        form.errors.emp_id = "Emp ID already assigned!"

@auth.requires_membership("Admin")
def createUser():
    
    company_id = session.new_company_id
    password = generateRandomPassword()

    #Preparing Fields array for Form
    fields = [field for field in db.auth_user if field.name != 'company_id' and field.name != 'password']
    fields += [Field('role', requires=IS_IN_SET(ROLE_DICT.keys()))]
    fields += [Field('password', 'password',default=password, requires=CRYPT(min_length=8))]
    
    form = SQLFORM.factory(*fields, submit_button="Create")

    if form.process(onvalidation=createUserValidation,message_onfailure="Please fill form correctly!").accepted:
        new_user_id = db.auth_user.insert(first_name=form.vars.first_name,
                                          last_name=form.vars.last_name,
                                          emp_id=form.vars.emp_id,
                                          date_of_birth=form.vars.date_of_birth,
                                          email=form.vars.email,
                                          password=form.vars.password,
                                          company_id=company_id)
        group_id = ROLE_DICT[form.vars.role]
        auth.add_membership(group_id, new_user_id)

        msg = "Your Credentials: Email : " + form.vars.email + "Password: " + password
        status = sendMail(form.vars.email,"Welcome to OIMS",msg)

        if status==True:
            session.flash = "Created User and Mail is sent."
        else:
            session.flash = "Created User and Failed to send the mail."

        event_desc = "Created user " + form.vars.first_name + " " + form.vars.last_name +" with role " + form.vars.role + "."     
        db.event_log.insert(company_id=company_id,
                            event_owner_id=auth.user.id,
                            event_time=datetime.datetime.now(),
                            event_type="User",
                            event_desc=event_desc)
        redirect(URL('admin','index'))
    
    elif form.errors:
        response.flash = "Please fill the form correctly !"

    return dict(form=form)

@auth.requires_membership("Admin")
def viewUsers():
    query  = (db.auth_user.company_id==session.company_id)
    fields = [field for field in db.auth_user if field.name != 'company_id']
    grid = SQLFORM.smartgrid(db.auth_user,
                             constraints=dict(auth_user=query),
                             fields=fields,
                             linked_tables=[],
                             deletable=False,
                             editable=False,
                             searchable=True,
                             sortable=False,
                             details=False,
                             create=False,
                             csv=False,
                             links_in_grid=False)
    return dict(grid=grid)

def onUpdateUser(form):
     event_desc = "Updated user " + form.vars.first_name + " " + form.vars.last_name + "."     
     db.event_log.insert(company_id=session.company_id,
                         event_owner_id=auth.user.id,
                         event_time=datetime.datetime.now(),
                         event_type="User",
                         event_desc=event_desc)


def onDeleteUser(table,id):
     row = db(db.auth_user.id==id).select()
     event_desc = "Deleted user " + row[0]['first_name'] + " " + row[0]['last_name'] + "."
     db.event_log.insert(company_id=session.company_id,
                         event_owner_id=auth.user.id,
                         event_time=datetime.datetime.now(),
                         event_type="User",
                         event_desc=event_desc)         

@auth.requires_membership("Admin")
def editUsers():

    #make an entry in log_event table for edit and delete users
    query  = (db.auth_user.company_id==session.company_id)
    fields = [field for field in db.auth_user if field.name != 'company_id']
    grid = SQLFORM.smartgrid(db.auth_user,
                             constraints=dict(auth_user=query),
                             fields=fields,
                             linked_tables=[],
                             deletable=True,
                             editable=True,
                             searchable=False,
                             sortable=False,
                             details=False,
                             create=False,
                             csv=False,
                             links_in_grid=False,
                             paginate=7,
                             showbuttontext=False,
                             onupdate=onUpdateUser,
                             ondelete=onDeleteUser)
    return dict(grid=grid)

@auth.requires_membership("Admin")
def createLocation():
    user_dict = {x['emp_id'] : x['id'] for x in db(db.auth_user.company_id==session.company_id).select()}
    fields = [field for field in db.locations if field.name != 'company_id' and field.name != 'person_incharge' ]
    fields += [Field('person_incharge', requires=IS_IN_SET(user_dict.keys()))]
    company_id = session.company_id
    form = SQLFORM.factory(*fields, submit_button="Create")
    temp_var=form.accepts(request,session)
    phone_no=str(form.vars.phone_number)
    if len(phone_no)>10:
        response.flash = 'Mobile number should only be of 10 digits'
    else:
        try:
            db.locations.insert(company_id=session.company_id,
                                location_name=form.vars.location_name,
                                location_address=form.vars.location_address,
                                location_city=form.vars.location_city,
                                location_country=form.vars.location_country,
                                location_zip_code=form.vars.location_zip_code,
                                person_incharge=user_dict[form.vars.person_incharge],
                                phone_number=form.vars.phone_number)
        except:
            response.flash=""
    return dict(form=form)


@auth.requires_membership("Admin")
def viewLocations():
    grid = SQLFORM.smartgrid(db.locations,
                             linked_tables=[],
                             deletable=False,
                             editable=False,
                             searchable=False,
                             sortable=False,
                             details=False,
                             create=False,
                             csv=False,
                             links_in_grid=False)
    return dict(grid=grid)

@auth.requires_membership("Admin")
def editLocation():
    grid = SQLFORM.smartgrid(db.locations,
                             linked_tables=[],
                             deletable=True,
                             editable=True,
                             searchable=False,
                             sortable=False,
                             details=False,
                             create=False,
                             csv=False,
                             links_in_grid=False)
    return dict(grid=grid)

@auth.requires_membership("Admin")
def index():
    event_user_list = db(db.event_log.event_owner_id==auth.user.id and 
                         db.event_log.company_id==session.company_id and
                         db.event_log.event_type=='User').select(limitby=(0,5)).as_list()
    event_location_list = db(db.event_log.event_owner_id==auth.user.id and 
                             db.event_log.company_id==session.company_id and
                             db.event_log.event_type=='Location').select(limitby=(0,5)).as_list()
    return locals()
