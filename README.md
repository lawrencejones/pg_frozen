# `pg_frozen`

The scrappiest of Postgres extensions that can be used to detect whether a tuple
has been frozen. Use it like so:

```sql
database=# drop extension if exists pg_frozen; create extension pg_frozen;
DROP EXTENSION
CREATE EXTENSION

database=# create table messages (id bigserial, msg text, primary key(id));
CREATE TABLE

database=# insert into messages (msg) values ('hello');
INSERT 0 1

database=# select id, msg, ctid, xmin, frozen(tableoid, ctid) from messages;
 id |  msg  | ctid  |  xmin  | frozen 
----+-------+-------+--------+--------
  1 | hello | (0,1) | 215938 |      0
(1 row)

database=# vacuum (freeze) messages;
VACUUM

database=# select id, msg, ctid, xmin, frozen(tableoid, ctid) from messages;
 id |  msg  | ctid  |  xmin  | frozen 
----+-------+-------+--------+--------
  1 | hello | (0,1) | 215938 |      1
(1 row)
```
