#ifndef SERIAL_HPP
#define SERIAL_HPP

class Wall;
class Player;

namespace boost
{
	namespace serialization
	{
		template <class archive>
		void serialize(archive &ar, Player &p, const unsigned int version);
		template <class archive>
		void serialize(archive &ar, Wall &w, const unsigned int version);
	}
}

#endif