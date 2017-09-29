# -*- coding: utf-8 -*-
# this file is released under public domain and you can use without limitations

##########################################################################
## This is a default controller
## - index is the default action of any application
## - user is required for authentication and authorization
## - download is for downloading files uploaded in the db (does streaming)
##########################################################################

#validation for company url
def companyUrlValidation(form):
    company_id_list = db(db.company.company_url==form.vars.company_url).select(db.company.id).as_list()
    if len(company_id_list) == 0:
        form.errors.company_url = "Company URL is not registered !"
    else:
        session.company_id = company_id_list[0]['id']
        session.company_url = form.vars.company_url

def index():
    form = FORM(INPUT(_type='text', _name='company_url', _placeholder="Enter company url", _size="30", requires=IS_NOT_EMPTY()),
                BR(),
                BR(),
                INPUT(_type='submit', _value='Login'),
                _method='post')

    form.add_button('Register Your Company', URL('admin','registerCompany'), _class='btn btn-default')

    if form.process(onvalidation=companyUrlValidation,message_onfailure="Company URL is not registered!").accepted:
        redirect(URL('default', 'user/login'))
    elif form.errors:
        response.flash = 'Please fill form correctly'

    return dict(form=form)

def loginValidation(form):
    company_id_list = db(db.company.company_url==form.vars.company_url).select(db.company.id).as_list()
    if len(company_id_list) == 0:
        form.errors.company_url = "Company Url is not registered !"
    else:
        encrypted_pwd = (db(db.auth_user.email==form.vars.email and
                        db.auth_user.company_id==company_id_list[0]['id']).select().first().password, None)
        if encrypted_pwd != db.auth_user.password.validate(form.vars.password) :
            form.errors.passowrd = "Credentials can not be verified !"

def user():
    """
    exposes:
    http://..../[app]/default/user/login
    http://..../[app]/default/user/logout
    http://..../[app]/default/user/register
    http://..../[app]/default/user/profile
    http://..../[app]/default/user/retrieve_password
    http://..../[app]/default/user/change_password
    http://..../[app]/default/user/manage_users (requires membership in
    http://..../[app]/default/user/bulk_register
    use @auth.requires_login()
        @auth.requires_membership('group name')
        @auth.requires_permission('read','table name',record_id)
    to decorate functions that need access control
    """
    '''
    if request.args(0) == "login":
        form = SQLFORM.factory(Field('company_url','string',default=session.company_url),
                               Field('email',requires=IS_EMAIL()),
                               Field('password','password'),
                               submit_button='LogIn')
        if form.process(onvalidation=loginValidation,message_onfailure="Credentials can not be verified !").accepted:
            auth.user.id = db.auth_user.id
            redirect(URL('admin', 'index'))
        elif form.errors:
            response.flash = "Credentials can not be verified !"
        return dict(form=form)
    '''
    return dict(form=auth())

@cache.action()
def download():
    """
    allows downloading of uploaded files
    http://..../[app]/default/download/[filename]
    """
    return response.download(request, db)


def call():
    """
    exposes services. for example:
    http://..../[app]/default/call/jsonrpc
    decorate with @services.jsonrpc the functions to expose
    supports xml, json, xmlrpc, jsonrpc, amfrpc, rss, csv
    """
    return service()
