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
from wb_bank import Bank
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

def session_out(url):
    try:
        if session['signin'] == False or session['sigin'] == True:
            flash('비정상적인 시도입니다.')
            session.pop('signin', None)
            return redirect(url_for('front'))
    except:
        return render_template(url, error=None)

@app.route('/')
def front():
    return render_template('front.html')

@app.route('/.favicon.ico')
def favicon():
    return send_from_directory(os.path.join(app.root_path, 'static'), 'favicon.ico')

@app.route('/about')
def about():
    result = (None, None)
    return render_template('about.html', error=None)
    

@app.route('/contact')
def contact():
    result = (None, None)
    return render_template('contact.html', error=None)

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
        return session_out('signup.html')

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
            session['uid'] = user.uid
            session['username'] = user.name
        return render_redirect('signin.html', 'front', result)
    else:
        return session_out('signin.html')

@app.route('/signout')
def signout():
    try:
        if session['signin']:
            session.pop('signin', None)
            flash('로그아웃 되었습니다.')
            return redirect(url_for('front'))
    except:
        flash('비정상적인 시도입니다.')
        return redirect(url_for('front'))

@app.route('/mypage')
def mypage():
    result = (None, None)
    try:
        if(session['uid']):
            bank = Bank(db.connect_db(), session['uid'])
            blist = bank.banklist()
            return render_template('mypage.html', entries=blist, error=None)
    except:
        flash('비정상적인 시도입니다.')
        return redirect(url_for('front'))

@app.route('/bankreg', methods=['GET', 'POST'])
def bankreg():
    result = (None, None)
    if request.method == 'POST':
        bankname = request.form['bankname']
        bankid = request.form['bankid']
        bankid = bankid.replace('-', '')
        bank = Bank(db.connect_db(), session['uid'])
        result = bank.register(bankid, bankname)
        return render_redirect('bankreg.html', 'mypage', result)
    else:
        try:
            if session['signin']:
                return render_template('bankreg.html', error=None)
        except:
            flash('비정상적인 시도입니다.')
            return redirect(url_for('front'))

@app.route('/banksetting', methods=['GET', 'POST'])
def banksetting():
    result = (None, None)
    return render_template('banksetting.html', error=None)

@app.route('/bankdetail/<bid>', methods=['GET', 'POST'])
def bankdetail(bid):
    result = (None, None)
    try:
        if request.method == 'POST' or bid:
            bank = Bank(db.connect_db(), session['uid'])
            result = bank.entrance(bid)
            (msg, arg) = result
            session['bid'] = bank.bankid
            datas = bank.bankdata()
            if msg == None:
                return render_template('bankdetail.html', entries=(bid, bank.bankname), datas=datas, error=None)
            else:
                raise 'TypeError'
        else:
            raise 'TypeError'
    except:
        flash('비정상적인 시도입니다.')
        return redirect(url_for('front'))


if __name__ == '__main__':
    app.config.update(dict(
        DATABASE=os.path.join(app.root_path, 'whaleBank.db'),
        DEBUG=True,
        SECRET_KEY='development key',
        USERNAME='admin',
        PASSWORD='default'
    ))
    app.config.from_envvar('FLASKR_SETTINGS', silent=True)
    db = database(app)
    app.run(host='0.0.0.0', port=80)