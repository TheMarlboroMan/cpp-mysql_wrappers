#include "resultset.h"

using namespace mysql_db;

//Ojo.. total es mutable.
void resultset::calculate_total() const {

	if(rs) {
		int current=rs->getRow();
		rs->last();
		total=rs->getRow();
		rs->absolute(current);
	}
}

resultset::resultset(std::shared_ptr<sql::Statement> pstat, const std::string& texto)
	:rs(pstat->executeQuery(texto)), total(-1) {

}

resultset::resultset(std::shared_ptr<sql::PreparedStatement> ppstat)
	:rs(ppstat->executeQuery()), total(-1) {

}

resultset::resultset()
	:total(-1) {

}

resultset::operator bool() const {

	return is_ok();
}

bool resultset::is_ok() const {

	return nullptr!=rs;
}

bool resultset::first() {

	return rs->first();
}

bool resultset::last() {

	return rs->last();
}

bool resultset::next() {

	return rs->next();
}

bool resultset::previous() {

	return rs->previous();
}

bool resultset::get_row() const {

	return rs->getRow();
}

bool resultset::is_first() const {

	return rs->isFirst();
}

bool resultset::is_before_first() const {

	return rs->isBeforeFirst();
}

int resultset::find_column(const std::string& c) {

	return rs->findColumn(c);
}

int resultset::get_int(const std::string& c) const {

	return rs->getInt(c);
}

std::string resultset::get_string(const std::string& c) const {

	return rs->getString(c);
}

double resultset::get_double(const std::string& c) const {

	return rs->getDouble(c);
}

int resultset::get_int(unsigned int c) const {

	return rs->getInt(c);
}

std::string resultset::get_string(unsigned int c) const {

	return rs->getString(c);
}

double resultset::get_double(unsigned int c) const {

	return rs->getDouble(c);
}

int resultset::get_total() const {

	if(total==-1) {
		calculate_total();
	}

	return total;
}
