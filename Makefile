EXTENSION = pg_frozen
MODULE_big = pg_frozen
DATA = pg_frozen--0.0.1.sql
OBJS = pg_frozen.o
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
PG_MAJOR := $(shell $(PG_CONFIG) --version | awk '{{ print $$2 }}' | cut -d. -f 1)
PG_CFLAGS=-DPG_MAJOR=$(PG_MAJOR)
include $(PGXS)
