/*
upqxx by James Murphy

Created to simplify common tasks with libpqxx.

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
#include "upqxx.hpp"
#include <pqxx/except>
#include <stdexcept>

namespace upqxx {
	//Initialize the class.
	//This prevents missing values.
	upqxxobj::upqxxobj(std::string Connstring, bool PrintDebug)
	{
		this->local_Connstring = Connstring;
		this->local_PrintDebug = PrintDebug;
	}

	//Something about this is akward and clunky.
	bool upqxxobj::CanConnect(void)
	{
		//Temporary connection object.
		pqxx::connection test_conn(this->local_Connstring);

		//If it's true, we connected successfully.
		if(test_conn.is_open())
		{
			if(this->local_PrintDebug)
			{
				std::cerr << "Successfully connected to: " << test_conn.dbname() << std::endl;
			}

			test_conn.disconnect();
			return true;
		}

		throw pqxx::broken_connection("Cannot connect to database.");
		return false;
	}
	
	pqxx::result upqxxobj::do_query(const std::string q_type, const std::string &query)
	{
		if(this->local_PrintDebug)
		{
			std::cerr << "Attempting to run " << q_type << " query: " << query << std::endl;
		}

		if(this->CanConnect())
		{
			pqxx::connection local_temporary_connection(this->local_Connstring);
			pqxx::result local_temp_result;

			if(q_type == "transactional")
			{
				pqxx::work temp_work(local_temporary_connection);
				temp_work.exec(query);
				temp_work.commit();
			}

			if(q_type == "non-transactional")
			{
				pqxx::nontransaction nt(local_temporary_connection);
				local_temp_result = nt.exec(query);
			}

			local_temporary_connection.disconnect();
			return local_temp_result;
		}
	}

	//Result function for transactional queries.
	void upqxxobj::transact_query(const std::string query)
	{
		do_query("transactional", query);
	}

	//Result function for non-transactional queries.
	pqxx::result upqxxobj::non_transact_query(const std::string query)
	{
		return do_query("non-transactional", query);
	}

	bool upqxxobj::CheckTable(const std::string table)
	{
		pqxx::result GetTable = non_transact_query("SELECT relname FROM pg_class WHERE relname = " + Sanitize(table));

		if(GetTable.empty())
		{
			if(this->local_PrintDebug)
			{
				std::cerr << table << " not found." << std::endl;
			}
		}

		return !GetTable.empty();
	}

	std::string upqxxobj::Sanitize(const std::string s)
	{
		pqxx::connection c(this->local_Connstring);
		pqxx::work w(c);
		return w.quote(s);
	}
}
