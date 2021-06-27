#include <postgres.h>
#include <fmgr.h>

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

typedef struct Company {
	unsigned long int index;
	char company_name[30];
} Company;

PG_FUNCTION_INFO_V1(company_in);

Datum  company_in(PG_FUNCTION_ARGS)
{
	char *str = PG_GETARG_CSTRING(0);
	int index = 0;
	char company_name[30];
	struct Company *result;
	int i = 0;
	if (!(*str))
		ereport(ERROR,
                 (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("invalid input syntax for complex: \"%s\"", str)));
	for (str++; *str && *str != ','; i++, str++) {
		company_name[i] = *str;
	}
	if (!i) ereport(ERROR,
                 (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("invalid input syntax for complex: \"%s\"", str)));
	str += 2;
	if (sscanf(str, "%d", &index) != 1) ereport(ERROR,
                 (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("invalid input syntax for complex: \"%s\"", str)));
	result = (Company *)palloc(sizeof(Company));
	result->index = index;
	for (int i = 0; i < 30; i++)
		result->company_name[i] = company_name[i];
	PG_RETURN_POINTER(result);
}


PG_FUNCTION_INFO_V1(company_out);

Datum company_out(PG_FUNCTION_ARGS) {
	struct Company *company = (struct Company *) PG_GETARG_POINTER(0);
	char *result;
	result = psprintf("(%s, %lu)", company->company_name, company->index);
	PG_RETURN_CSTRING(result);
}