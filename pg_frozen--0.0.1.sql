CREATE OR REPLACE FUNCTION
frozen(tableoid oid, tid tid) RETURNS int AS 'MODULE_PATHNAME', 'frozen'
PARALLEL SAFE
LANGUAGE C STRICT;
