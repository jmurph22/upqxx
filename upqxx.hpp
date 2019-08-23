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

You should have received a copy of the GNU General Public License`
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UPQXX_H
#define UPQXX_H

namespace upqxx {
	class upqxxobj {
	private:
		bool CanConnect();
		pqxx::result do_query(const std::string q_type, const std::string &query);
	public:
		upqxxobj(std::string Connstring, bool PrintDebug);

		//Functions for working with database
		pqxx::result non_transact_query(const std::string query);
		void transact_query(const std::string query);
		std::string Sanitize(const std::string s);
		bool CheckTable(const std::string table);

		//Options
		std::string local_Connstring;
		bool local_PrintDebug;
	};
}

#endif
