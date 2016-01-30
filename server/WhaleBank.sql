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
  bankname text not null,
  uid text not null
);
create table bankdata (
  id integer primary key autoincrement,
  bankid text not null,
  time text not null,
  value integer
);
create table hof (
  id integer primary key autoincrement,
  uid text not null,
  bid text not null,
  time text not null,
  archive text not null,
  value integer
);