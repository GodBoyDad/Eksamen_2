/*В этой программе создан класс weapon, описывающий поведение обыкновенного немагического оружия в игре.
Задание: создать класс magic_weapon, являющийся наследником класса weapon.*/

#include <iostream>
#include <ctime>
using namespace std;

class weapon {
public:
    weapon(int base_damage, int durability, int degradation, int cost, int weight); //все важные значения задаются в конструкторе
    int get_base_damage() const;
    int get_durability() const;
    int get_degradation() const;
    void set_cost(int new_cost);
    int get_cost() const;
    int get_weight() const;
    int hit(); //здесь высчитывается результирующая сила удара для данного оружия

private:
    int base_damage; //базовый урон
    int durability; //максимальная прочность
    int degradation; //степень износа оружия
    int cost; //цена
    int weight; //вес
};

weapon::weapon(int base_damage = 10, int durability = 100, int degradation = 0, int cost = 250, int weight = 5) :
    //все важные величины имеют значения по умолчанию
    base_damage(base_damage),
    durability(durability),
    degradation(degradation),
    cost(cost),
    weight(weight)
    //список инициализации: значения аргументов присваиваются членам класса, позволяя оставить тело конструктора пустым
{

}

int weapon::get_base_damage() const { //функция-геттер для базового урона
    return this->base_damage;
}

int weapon::get_durability() const { //функция-геттер для прочности
    return this->durability;
}

int weapon::get_degradation() const { //функция-геттер для степени износа
    return this->degradation;
}

void weapon::set_cost(int new_cost) { //функция-сеттер для цены
    this->cost = new_cost;
}

int weapon::get_cost() const { //функция-геттер для цены
    return this->cost;
}

int weapon::get_weight() const { //функция-геттер для веса
    return this->weight;
}

class weapon_magic : public weapon { //Класс магическго оружия, являющийся наследником класса оружия.
public:

    int get_base_amountofmanaweapon();
    int hit_magic(); //сила удара и расход маны.
    weapon_magic(int base_amountofmanaweapon);

private:
    int base_amountofmanaweapon;

};

int weapon_magic::get_base_amountofmanaweapon() {
    return this->base_amountofmanaweapon;
}


//все геттеры определены, как константные методы, что позволяет обезопасить члены класса от нежелательных изменений

int weapon::hit() {
    srand(time(0));
    int random_effect = rand() % base_damage; //генерируем случайную величину в пределах от нуля до базового урона - 1
    int damage = this->base_damage - random_effect; //меняем урон: теперь он варьируется от нуля до изначального базового
    this->degradation++; //повышаем износ на единицу с каждым нанесенным ударом
    this->cost -= this->cost / durability; //уменьшаем цену соответственно изношенности оружия
    return damage; //возвращаем урон во внешнюю программу
}
weapon_magic::weapon_magic(int base_amountofmanaweapon = 10) :
    base_amountofmanaweapon(base_amountofmanaweapon) {

}

int weapon_magic::hit_magic() {
    srand(time(0));
    int random_mana = rand() % base_amountofmanaweapon;
    int losses = base_amountofmanaweapon - random_mana;
    return losses;
}




int main() {
    setlocale(LC_ALL, "ru");
    weapon simple_iron_sword, players_BIG_sword(20); //создаем два объекта - два меча, себе и противнику
    int enemy_health = 100, player_health = 100; //здоровье для протагониста и для противника
    cout << "Нажмите любую клавишу, чтобы начать бой с обычным оружием." << endl;
    while (enemy_health > 0 && player_health > 0) { //ни один из нас не покинет поле боя, пока жив другой...
        player_health = player_health - simple_iron_sword.hit(); //противник наносит удар, уменьшается здоровье протагониста
        cin.get(); //программа ждет нажатия любой клавиши
        enemy_health = enemy_health - players_BIG_sword.hit(); //игрок бьет, уменьшается здоровье врага
        cout << "Здоровье врага: " << enemy_health << endl;
        cout << "Моё здоровье: " << player_health << endl;
    }

    cout << "Состояние простого меча: " << simple_iron_sword.get_durability() - simple_iron_sword.get_degradation() << endl;
    cout << "Состояние БОЛЬШОГО меча игрока: " << players_BIG_sword.get_durability() - players_BIG_sword.get_degradation() << endl;


    weapon_magic demon_staff, ignis(30);



    cout << "Нажмите любую клавишу, чтобы начать бой с магическим оружием." << endl;

    int mag_enemy_health = 100, mag_player_health = 100;
    int my_mana = 100, enemy_mana = 100;

    while ((mag_enemy_health > 0 && mag_player_health > 0) && (my_mana > 0 && enemy_mana > 0)) {
        mag_player_health = mag_player_health - demon_staff.hit();
        cin.get();
        mag_enemy_health = mag_enemy_health - ignis.hit();
        cout << "Здоровье врага: " << mag_enemy_health << endl;
        cout << "Моё здоровье: " << mag_player_health << endl;

        my_mana = my_mana - demon_staff.hit_magic();
        enemy_mana = enemy_mana - ignis.hit_magic();

        cout << "Мана врага: " << enemy_mana << endl;
        cout << "Моя мана: " << my_mana << endl;
    }
    cout << "Состояние Демонического посоха: " << demon_staff.get_durability() - demon_staff.get_degradation() << endl;
    cout << "Состояние Игниса: " << ignis.get_durability() - ignis.get_degradation() << endl;
    return 0;
}