
class Bank(object):
	'''
		this present bank object
	'''
	def __init__(self, connect_db, uid):
        self.session_bankin = False
        self.uid = uid
        self.bankid = None
        self.bankname = None
        self.db = connect_db

	def register(self, bankid, bankname):
		result = (None, None)
        cur = self.db.cursor()
        self.bankid = bankid
        self.bankname = bankname

        if '' in [bankid, bankname]:
            result = ('error', "필드가 비어있어요.")
        else:
            bankid_ = cur.execute(u'SELECT EXISTS (SELECT bankid FROM bank WHERE bankid = ?)', (bankid, )).fetchone()

            if bankid_[0] == 0:
                result = ('flash', '저금통이 만들어졌어요, ' + name)
                self.db.execute('insert into bank (bankid, bankname, uid) values (?, ?, ?)', [self.bankid, self.bankname, self.uid])
                self.db.commit()
            else:
                result = ('error', "이미 등록된 저금통입니다.")
        return result

	def entrance(self, bankid):
        result = (None, None)
        cur = self.db.cursor()
        self.bankid = bankid

        bid_ = cur.execute(u"SELECT EXISTS ( SELECT bankid FROM bank where bankid = ?)", (self.bankid, ) ).fetchone()
        if bid_[0] == 0:
            result = ('error', "존재하지 않는 저금통입니다.")
        else:
            uid_ = cur.execute(u"SELECT EXISTS ( SELECT uid FROM bank where bankid = ?)", (self.bankid, ) ).fetchone()
            if uid[0] != self.uid:
                result = ('error', "권한없는 사용자입니다.")
            else:
                self.session_signin = True
                self.bankname = self.db.execute('select bankname from bank where bankid=\'' + self.bankid + '\'').fetchone()
        return result