#pragma once

#include <string>

namespace Troopy {

class Nameable {
	public:
		Nameable(std::string name_);
		virtual ~Nameable();

		void setName(std::string name_);
		std::string getName() const;

	protected:
		std::string name;
};

}