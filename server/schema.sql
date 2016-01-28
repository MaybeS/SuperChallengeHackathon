drop table if exists entries;
create table userdata (
	id integer primary key autoincrement,
	email text not null,
	username text not null,
	userid text not null,
	password text not null
);
create table bank (
  id integer primary key autoincrement,
  bankid text not null,
  userid text not null
);