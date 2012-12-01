#pragma once

namespace Troopy {
namespace Navigation {

typedef enum ObjectNavProperty {
	WALKABLE,
	OBSTACLE
} ObjectNavProperty;

class NavProperty {
	public:
		NavProperty();
		NavProperty(ObjectNavProperty p_);
		virtual ~NavProperty();

		ObjectNavProperty getProperty();
		void setProperty(ObjectNavProperty p_);

	protected:
		ObjectNavProperty p;
};

}
}