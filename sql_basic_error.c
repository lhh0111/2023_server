static int sql_basic_err = 0;

void init_sql_basic_err(void)
{
    sql_basic_err = 0;
}

int get_sql_basic_err(void)
{
    return sql_basic_err;
}

void set_sql_basic_err(void)
{
    sql_basic_err = 1;
}