#!/usr/bin/python
#-*- coding: utf-8 -*-

from os import path
from flask import Flask
from wb_db import database

class User(object):
    '''
    Represent a user.
    init whit login, have session
    '''

    def __init__(self, connect_db, uid):
        self.session_signin = False
        self.uid = uid
        self.db = connect_db

    def signin(self, pwss):
        result = ('None', None)
        cur = self.db.cursor()

        uid_ = cur.execute(u"SELECT EXISTS ( SELECT userid FROM userdata where userid = ?)", (self.uid, ) ).fetchone()
        if uid_[0] == 0:
            result = ('error', "아이디가 존재하지 않거나 비밀번호가 틀렸습니다.")
        else:
            pwss_ = cur.execute(u"SELECT EXISTS ( SELECT password FROM userdata where userid = ?)", (self.uid, ) ).fetchone()
            if pwss_[0] == pwss:
                result = ('error', "아이디가 존재하지 않거나 비밀번호가 틀렸습니다.")
            else:
                self.session_signin = True
                self.name = self.db.execute('select username from userdata where userid=\'' + self.uid + '\'').fetchone()
                result = ('flash', '환영해요, ' + self.name[0])
        return result

    def signup(self, uid, name, email, pwss):
        result = (None, None)
        cur = self.db.cursor()

        if '' in [email, name, pwss, uid]:
            result = ('error', "필드가 비어있어요.")
            error = ""
        elif not "@" in email:
            result = ('error', "메일 형식이 올바르지 않아요.")
        else:
            email_ = cur.execute(u'SELECT EXISTS (SELECT email FROM userdata WHERE email = ?)', (email, )).fetchone()
            uid_ = cur.execute(u'SELECT EXISTS (SELECT userid FROM userdata WHERE userid = ?)', (uid, )).fetchone()

            if email_[0] == 0 and uid_[0] == 0:
                result = ('flash', '계정이 만들어졌어요, ' + name)
                self.db.execute('insert into userdata (email, username, userid, password) values (?, ?, ?, ?)', [email, name, uid, pwss])
                self.db.commit()
            else:
                result = ('error', "이미 존재하는 아이디/이메일 입니다.")
        return result
    
    def changeinfo(self):
        if self.signin:
            return ('redirect', 'mypage')
        else:
            return (None, None)

    def signout(self):
        self.signin = False
        return ('redirect', 'front')

if __name__ == '__main__':
    #init app
    app = Flask(__name__)
    app.config.update(dict(
        DATABASE=path.join(app.root_path, 'flaskr.db'),
        DEBUG=True,
        SECRET_KEY='development key',
        USERNAME='admin',
        PASSWORD='default'
    ))
    app.config.from_envvar('FLASKR_SETTINGS', silent=True)
    #try user init()
    try:
        db = database(app)
        user = User(db.connect_db(), 10)
        print('initilize user finished!')
    except:
        print('error occuer')
