
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

	def banklist(self):
		cur = self.db.cursor()
		cur.execute('SELECT bankid, bankname FROM bank WHERE uid = ?', (self.uid, ))
		return cur.fetchall()

	def register(self, bankid, bankname):
		result = (None, None)
		cur = self.db.cursor()
		self.bankid = bankid
		self.bankname = bankname
		self.session_bankin = False

		if '' in [bankid, bankname]:
		    result = ('error', "필드가 비어있어요.")
		elif len(self.bankid) != 11:
			result = ('error', "바르지 않은 저금통 고유 번호입니다.")
		else:
			bankid_ = cur.execute(u'SELECT EXISTS (SELECT bankid FROM bank WHERE bankid = ?)', (self.bankid, )).fetchone()
			bankname_ = cur.execute(u'SELECT EXISTS (SELECT bankname FROM bank WHERE bankname = ?)', (self.bankname, )).fetchone()
			if bankid_[0] == 0 and bankname_[0] == 0:
				result = ('flash', '저금통이 만들어졌어요')
				self.db.execute('insert into bank (bankid, bankname, uid) values (?, ?, ?)', [self.bankid, self.bankname, self.uid])
				self.db.commit()
			else:
				result = ('error', "이미 등록된 저금통이거나 이미 존재하는 저금통 이름입니다.")
		return result

	def entrance(self, bankid):
		result = (None, None)
		cur = self.db.cursor()
		self.bankid = bankid
		bid_ = cur.execute(u"SELECT EXISTS ( SELECT bankid FROM bank where bankid = ?)", (self.bankid, ) ).fetchone()
		if bid_[0] == 0:
		    result = ('error', "존재하지 않는 저금통입니다.")
		else:
			uid_ = cur.execute(u"SELECT uid FROM bank where bankid = ?", (self.bankid, ) ).fetchone()
			if uid_[0] != self.uid:
			    result = ('error', "권한없는 사용자입니다.")
			else:
			    self.session_bankin = True
			    self.bankname = self.db.execute('select bankname from bank where bankid=\'' + self.bankid + '\'').fetchone()[0]
		return result

	def bankdata(self):
		cur = self.db.cursor()
		return cur.execute(u'SELECT * FROM bankdata WHERE bankid = ? ORDER BY time DESC', (self.bankid, )).fetchall()

if __name__ == '__main__':
	print('run itself, c')