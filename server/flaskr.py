#!/usr/bin/python
#-*- coding: utf-8 -*-
"""
	a microblog example application written as Flask tutorial
	with Flask and sqlite3.
"""
from __future__ import with_statement
import os
import sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash
from contextlib import closing
from wb_user import User
from wb_db import database

app = Flask(__name__)


def render_redirect(template, url, result):
    (func, arg) = result

    if func == None:
        arg = url

    if func == 'error':
        return render_template(template, error=arg)
    elif func == 'flash':
        flash(arg)
    return redirect(url_for(url))

@app.route('/')
def front():
    return render_template('front.html')

@app.route('/.favicon.ico')
def favicon():
    return send_from_directory(os.path.join(app.root_path, 'static'), 'favicon.ico')

@app.route('/add', methods=['POST'])
def add_entry():
    if not session.get('signin'):
        abort(401)
    db = get_db()
    db.execute('insert into entries (title, text) values (?, ?)', [request.form['title'], request.form['text']])
    db.commit()
    flash('New entry was successfully posted')
    return redirect(url_for('show_entries'))

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    result = (None, None)
    if request.method == 'POST':
        uid = request.form['userid']
        name = request.form['username']
        email = request.form['email']
        pwss = request.form['password']
        chkbox = request.form.getlist('chkbox')
        if(len(chkbox)):
            user = User(db.connect_db(), uid)
            result = user.signup(uid, name, email, pwss)
        else:
            result = ('error', '약관에 동의해야합니다.')
        return render_redirect('signup.html', 'signin', result)

    else:
        return render_template('signup.html', error=None)

@app.route('/signin', methods=['GET', 'POST'])
def signin():
    result = (None, None)
    if request.method == 'POST':
        uid = request.form['userid']
        pwss = request.form['password']
        if "" in [uid, pwss]:
            result = ('error', 'Empty Filed')
        else:
            user = User(db.connect_db(), uid)
            result = user.signin(pwss)
            session['signin'] = user.session_signin
        return render_redirect('signin.html', 'front', result)
    else:
        return render_template('signin.html', error=None)

@app.route('/signout')
def signout():
    if session['signin']:
        session.pop('signin', None)
        flash('로그아웃 되었습니다.')
    return redirect(url_for('front'))

@app.route('/mypage')
def mypage():
    result = (None, None)
    return render_template('mypage.html', error=None)

if __name__ == '__main__':
    app.config.update(dict(
        DATABASE=os.path.join(app.root_path, 'flaskr.db'),
        DEBUG=True,
        SECRET_KEY='development key',
        USERNAME='admin',
        PASSWORD='default'
    ))
    app.config.from_envvar('FLASKR_SETTINGS', silent=True)
    db = database(app)
    app.run(host='0.0.0.0', port=80)