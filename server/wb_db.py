#!/usr/bin/python
#-*- coding: utf-8 -*-
from os import path, remove
from flask import Flask
from contextlib import closing
import sqlite3

class database(object):
    '''
    Represent a database.
    init_db, get_db, close_db, connect_db
    '''
    def __init__(self, app):
        self.app = app

    def connect_db(self):
        return sqlite3.connect(self.app.config['DATABASE'])

    def init_db(self):
        with closing(self.connect_db()) as db:
            with self.app.open_resource('whaleBank.sql', "r") as f:
                db.cursor().executescript(f.read())
            db.commit()

    def get_db(self):
        if not hasattr(g, 'sqlite_db'):
            g.sqlite_db = connect_db()
        return g.sqlite_db

    def close_db(self, error):
        if hasattr(g, 'sqlite_db'):
            g.sqlite_db.close()

if __name__ == '__main__':
    #remove exsist db file
    if path.exists('whaleBank.db'):
        remove('whaleBank.db')
    #init app
    app = Flask(__name__)
    app.config.update(dict(
        DATABASE=path.join(app.root_path, 'whaleBank.db'),
        DEBUG=True,
        SECRET_KEY='development key',
        USERNAME='admin',
        PASSWORD='default'
    ))
    app.config.from_envvar('FLASKR_SETTINGS', silent=True)
    #try init_db()
    db = database(app)
    try:
        db.init_db()
        print('initilize database finished!')
    except:
        print('error occuer')