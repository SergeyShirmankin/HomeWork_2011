#include <iostream>
#include <vector>

void StartMessage(bool startFunction)//Создаесм стартовое окно ссобщениями
{
    std::string tempOP;
    char* op;//запись символа операции
//----------------------------------------------------------------------
	if (startFunction)
    {
    while (true) {
		std::cout << "Press key:'q'-quit, 'n'-create , 'd'-delete , 'e'-enter , 's'- show\n";
		//std::cout << "Выберите опцию:'в'-Выход, 'н'-Создать нового пользователя , 'л'-Войти под лог. и паролем\n";
		std::cout << ">> ";
		std::cin >> tempOP;
		if (tempOP.size() == 1) {
			std::vector<char>chars(tempOP.begin(), tempOP.end());//преобразователь string ->char
			chars.push_back('\0');
			op = &chars[0];

			if (*op == 'q') {
				exit(0);
			}
			switch (*op) {
			case'n':
				 return;
			case'e':
				return;
			defalt:
				std::cout << "Неправильно выбрали букву";
			}
		}
	}
}
//----------------------------------------------------------------------

}