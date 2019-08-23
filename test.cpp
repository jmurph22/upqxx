/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <pqxx/pqxx>
#include <upqxx.hpp>

int main(void)
{
	upqxx::upqxxobj test_upqxxobj("dbname=postgres user=postgres hostaddr=127.0.0.1 port=5432", true);

	if(test_upqxxobj.CheckTable("test")) //If the "test" table does not exist.
	{
		test_upqxxobj.transact_query("INSERT INTO test (val1, val2) VALUES ('test', 'test');");
		
		pqxx::result grab_data = test_upqxxobj.non_transact_query("SELECT * FROM test;");
		for(auto row : grab_data)
		{
			std::cout << row[0].c_str() << '\n';
		}

		std::string s = test_upqxxobj.Sanitize("//''");
	}

	else
	{
		test_upqxxobj.transact_query("CREATE TABLE test (val1 varchar(32), val2 varchar(32))");
	}

	return 0;
}
