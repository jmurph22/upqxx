/*
--- upqxxobj ---
Main class for working with pqxx.

First arg is connection string.
Second arg is whether it should print debug information.
*/
upqxxobj my_upqxxobj("dbname=postgres user=postgres hostaddr=127.0.0.1 port=5432", true);

/*
--- non_transact_query ---
Returns pqxx::result.
*/
pqxx::result ntq = my_upqxxobj.non_transact_query("SELECT * FROM table");

/*
--- transact_query ---
void for doing a query.
Used for queries that put into the DB.
*/
my_upqxxobj.transact_query("INSERT INTO table");

/*
--- Sanitize ---
Used to safely escape a string.
*/
std::string sanitized = my_upqxxobj.Sanitize("SELECT * FROM table; drop table; --");


/*
--- CheckTable ---
Sees if a table exists.
*/
if(my_upqxxobj.CheckTable("users")) //If the "users" table exists.
{
	//Table exists!
}
