static int sql_api_err = 0;


void init_sql_api_err(void)
{
    sql_api_err = 0;
}

int get_sql_api_err(void)
{
    return sql_api_err;
}

void set_sql_api_err(void)
{
    sql_api_err = 1;
}

