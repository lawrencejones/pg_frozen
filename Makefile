EXTENSION = pg_frozen
MODULE_big = pg_frozen
DATA = pg_frozen--0.0.1.sql
OBJS = pg_frozen.o
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
