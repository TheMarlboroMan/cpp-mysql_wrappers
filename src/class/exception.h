#ifndef MYSQLDB_MYSQL_EXCEPTION_H
#define MYSQLDB_MYSQL_EXCEPTION_H

#include <stdexcept>

namespace mysql_db {

class exception:
	public std::runtime_error {

	public:

				exception(const std::string& _err):
					std::runtime_error(_err) {

	}
};

class set_value_exception:
	public exception {

	public:
				set_value_exception(int _index, int _val, const std::string& _rq, const std::string& _err):
					exception(
						generate_exception_str(
							"int", _index, std::to_string(_val), _rq, _err
						)
					)
				{}

				set_value_exception(int _index, double _val, const std::string& _rq, const std::string& _err):
					exception(
						generate_exception_str(
							"double", _index, std::to_string(_val), _rq, _err
						)
					)
				{}

				set_value_exception(int _index, const std::string& _val, const std::string& _rq, const std::string& _err):
					exception(
						generate_exception_str(
							"string", _index, _val, _rq, _err
						)
					)
				{}

				set_value_exception(int _index, const std::string& _rq, const std::string& _err):
					exception(
						generate_exception_str(
							"null", _index, "null", _rq, _err
						)
					)
				{}

	private:

	std::string			generate_exception_str(const std::string& _type, int _index, const std::string& _val, const std::string& _rq, const std::string& _err) {

		return std::string("failed prepared_query::set_")
		+_type
		+" index: "+std::to_string(_index),
		+" value: '"+_val+"'"
		+" error: "+_err
		+" qstr: "+_rq;
	}
};

}

#endif
