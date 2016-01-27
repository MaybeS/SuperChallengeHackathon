#
import os
from flask import Flask
from contextlib import closing
import sqlite3

app = Flask(__name__)
app.config.update(dict(
    DATABASE=os.path.join(app.root_path, 'flaskr.db'),
    DEBUG=True,
    SECRET_KEY='development key',
    USERNAME='admin',
    PASSWORD='default'
))
app.config.from_envvar('FLASKR_SETTINGS', silent=True)
def connect_db():
    return sqlite3.connect(app.config['DATABASE'])

def init_db():
    with closing(connect_db()) as db:
        with app.open_resource('schema.sql', "r") as f:
            db.cursor().executescript(f.read())
        db.commit()

def get_db():
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = connect_db()
    return g.sqlite_db

def close_db(error):
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()

if __name__ == '__main__':
	os.remove('flaskr.db')
	init_db()