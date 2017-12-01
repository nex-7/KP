#include "saver_registers.h"
std::ostream & operator<<(std::ostream &out, byte &rhs)
{
	for (int i = 7; i >= 0; --i)
		out << rhs.getbit(i);
	return out;
}
std::ostream & operator<<(std::ostream &out, registers &rhs)
{
	for (size_t i = 0; i < 4; ++i) {
		out << rhs.return_byte(i) << " : ";
	}
	return out;
}
byte& saver_registers::return_by_string(const std::string &title) {
	if (title == "AH") return EAX.return_byte(3);
	else if (title == "AL") return EAX.return_byte(2);
	else if (title == "BH") return EBX.return_byte(3);
	else if (title == "BL") return EBX.return_byte(2);
}

registers& saver_registers::return_reg_by_string(const std::string &title) {
	if (title == "EAX") return EAX;
	else if (title == "EBX") return EBX;
}

registers saver_registers::mov_reg(const std::string &in, const std::string &out) {
	return_reg_by_string(in) = return_reg_by_string(out);
	return return_reg_by_string(in);
}
byte saver_registers::mov(const std::string &in, const std::string &out) {
	return_by_string(in) = return_by_string(out);
	return return_by_string(in);
}
byte saver_registers::mov(const std::string &in, int out) {
	return_by_string(in) = out;
	return return_by_string(in);
}
byte saver_registers::add(const std::string &in, const std::string &out) {
	return_by_string(in) += return_by_string(out);
	return return_by_string(in);
}
byte saver_registers::add(const std::string &in, int out) {
	return_by_string(in) += out;
	return return_by_string(in);
}
byte saver_registers::sub(const std::string &in, const std::string &out) {
	return_by_string(in) -= return_by_string(out);
	return return_by_string(in);
}
byte saver_registers::sub(const std::string &in, int out) {
	return_by_string(in) -= out;
	return return_by_string(in);
}
bool saver_registers::cmp(const std::string &in, const std::string &out) {
	if (return_by_string(in) == return_by_string(out)) {
		std::cout << "eq" << std::endl;
		return true;
	}
	if (return_by_string(in) != return_by_string(out)) {
		std::cout << "not eq" << std::endl;
		return false;
	}
}
bool saver_registers::parser(const std::string &input) {
	if (input == "mov") {
		std::string in, out;
		std::cin >> in >> out;
		if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
			mov(in, out);
		else if (out == "EAX" || out == "EBX")
			mov_reg(in, out);
		else {
			int i = std::atoi(out.c_str());
			if (in == "EAX" || in == "EBX") {
				//mov_reg(in, i);
			}
			if (in == "AH" || in == "BH" || in == "AL" || in == "BL")
				mov(in, i);
		}

		return true;
	}
	if (input == "add") {
		std::string in, out;
		std::cin >> in >> out;
		if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
			add(in, out);
		else {
			int i = std::atoi(out.c_str());
			add(in, i);
		}
		return true;
	}
	if (input == "sub") {
		std::string in, out;
		std::cin >> in >> out;
		if (out == "AH" || out == "BH" || out == "AL" || out == "BL")
			sub(in, out);
		else {
			int i = std::atoi(out.c_str());
			sub(in, i);
		}
		return true;
	}
	if (input == "cmp") {
		std::string in, out;
		std::cin >> in >> out;
		cmp(in, out);
		return true;
	}
	if (input == "out") {
		std::cout <<
			"EAX: " << EAX << std::endl <<
			"EBX: " << EBX << std::endl << std::endl;
		return true;
	}
	else if (input == "exit") throw false;
	else {
		std::cout << "unavailable command" << std::endl;
		return true;
	}
}