#pragma once

namespace CourseWork
{
	class Character
	{
	public:
		Character(int health, int armor, int damage, int dodge);
		void Attack(Character* target);
		void ReceiveDamage(int damage);
		bool IsDodge();
	private:
		int _health;
		int _armor;
		int _damage;
		int _dodge;
	};
}