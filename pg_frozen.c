#include "postgres.h"
#include "fmgr.h"

#include "access/heapam.h"
#include "utils/snapmgr.h"
#include "storage/bufmgr.h"

#if PG_MAJOR < 12
#include "access/htup_details.h"
#endif

PG_MODULE_MAGIC;

#define DatumGetItemPointer(X)	 ((ItemPointer) DatumGetPointer(X))
#define ItemPointerGetDatum(X)	 PointerGetDatum(X)
#define PG_GETARG_ITEMPOINTER(n) DatumGetItemPointer(PG_GETARG_DATUM(n))
#define PG_RETURN_ITEMPOINTER(x) return ItemPointerGetDatum(x)

PG_FUNCTION_INFO_V1(frozen);

Datum
frozen(PG_FUNCTION_ARGS)
{
	Oid	reloid = PG_GETARG_OID(0);
	ItemPointer	tid = PG_GETARG_ITEMPOINTER(1);

	Relation	  rel;
	Snapshot	  snapshot;
	HeapTupleData tuple;
	Buffer		  buf;
	int			  result;

	// Open table and snapshot- ensuring we later close them
	rel = heap_open(reloid, AccessShareLock);
	snapshot = RegisterSnapshot(GetLatestSnapshot());

	// Initialise the tuple data with a tid that matches our input
	ItemPointerCopy(tid, &(tuple.t_self));
#if PG_MAJOR < 12
	if (!heap_fetch(rel, snapshot, &tuple, &buf, true, NULL))
#else
	if (!heap_fetch(rel, snapshot, &tuple, &buf))
#endif
	{
	  result = 3;
	}
	else
	{
	  result = HeapTupleHeaderXminFrozen(tuple.t_data);
	}

	// Close any opened resources here
	UnregisterSnapshot(snapshot);
	heap_close(rel, AccessShareLock);
	ReleaseBuffer(buf);

	PG_RETURN_INT32(result);
}
