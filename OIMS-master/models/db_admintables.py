# -*- coding: utf-8 -*-
#This file contains application specific table definitions

#Following table is required to store comapny details
'''
db.define_table('company',
   Field('company_url',notnull=True,unique=True),
   Field('company_name','string',required=True),
   Field('admin_emp_id','string',required=True),
   Field('admin_first_name','string',required=True),
   Field('admin_last_name','string',required=True),
   Field('date_of_birth','date',required=True),
   Field('email',requires=IS_EMAIL()),
   Field('password','password',requires=CRYPT(min_length=8)),
   format='%(company_url)s')
'''

db.define_table('locations',
                Field('company_id','reference company'),
                Field('location_name','string',required=True),
                Field('location_address','string',required=True),
                Field('location_city','string',required=True),
                Field('location_country','string',required=True),
                Field('location_zip_code','string',required=IS_MATCH('^\d{5}(-\d{4})?$',error_message='not a zip code')),
                Field('person_incharge','reference auth_user'),
                Field('phone_number','string',required=IS_MATCH('^\d{10}$',error_message='phone number should be of ten digits')))

db.define_table('event_log',
                Field('company_id','reference company'),
                Field('event_owner_id','reference auth_user'),
                Field('event_time','datetime',required=True),
                Field('event_type','string', required=True),
                Field('event_desc','string', required=True))
