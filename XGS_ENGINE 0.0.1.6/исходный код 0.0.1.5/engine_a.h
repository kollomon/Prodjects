#include<SFML/Graphics.hpp>
#include<string>
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include "TinyXML/tinyxml.h"
#include <vector>
using namespace std;
extern "C++" namespace XGS_ENGINE
{
	class Object_EN
	{
	private:
		int A_x;
		int A_y;
		int pos_x;
		int pos_y;
		int timer;
		int x_anim;
		int y_anim;

		sf::Texture texture;
		sf::Vector2f vector;
		//////проверки/////
		bool spriteload = false;
		bool textureload = false;
		//-----------------//

	public:


		//---------------------------------------------//
		////////////////классы объектов///////////////////
		sf::Sprite sprite;
		sf::Clock clock;
		//------------------------------------------//

		///////////////переменные////////////////////
		float x = 0;
		float y = 0;
		float speed = 0;
		float time = 0;
		sf::Text text;
		sf::Font font;
		//------------------------------------------//
		///////////////////функции/////////////
		__declspec(dllexport) float getX();
		__declspec(dllexport) float getY();
		__declspec(dllexport) void loadingSprite(string dir);
		__declspec(dllexport) void mowe(float X, float Y);
		__declspec(dllexport) double VectorEN_getVectorAngle(float X, float Y);
		__declspec(dllexport) float VectorEN_getVectorDistnce(float XX, float YY);
		__declspec(dllexport) void VectorEN_getVectorMove(float tempX, float tempY);
		__declspec(dllexport) void TextEN_setFont(std::string &file);
		__declspec(dllexport) void TextEN_draw_text(float x, float y, std::string text_, sf::RenderWindow &window);
		__declspec(dllexport) void AnimationEN_setPosAnim(int x, int y);
		__declspec(dllexport) void AnimationEN_setLineAnim(std::string dir, int X, int Y);
		__declspec(dllexport) void AnimationEN_setTimerAnim(int t);
		__declspec(dllexport) int AnimationEN_getTimer();
		__declspec(dllexport) void AnimationEN_getPlayAnimations(int images);

		//----------------------------------//

	};
	extern "C++" struct Object
	{
		__declspec(dllexport)	int GetPropertyInt(std::string name)//возвращаем номер свойства в нашем списке

			__declspec(dllexport)   float GetPropertyFloat(std::string name)

			__declspec(dllexport)	std::string GetPropertyString(std::string name)//получить им€ в виде строки.вроде пон€тно

		std::string name;//объ€вили переменную name типа string
		std::string type;//а здесь переменную type типа string
		sf::Rect<float> rect;//тип Rect с нецелыми значени€ми
		std::map<std::string, std::string> properties;//создаЄм ассоциатиный массив. ключ - строковый тип, значение - строковый
		sf::Sprite sprite;//объ€вили спрайт
	};
	extern "C++" struct Layer//слои
	{
		int opacity;//непрозрачность сло€
		std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
	};
	extern "C++" class Level//главный класс - уровень
	{
	public:

		__declspec(dllexport) bool LoadFromFile(std::string filename);//двоеточи€-обращение к методам класса вне класса 

		__declspec(dllexport) Object GetObject(std::string name);

		__declspec(dllexport) std::vector<Object> GetObjects(std::string name);

		__declspec(dllexport) std::vector<Object> GetAllObjects();

		__declspec(dllexport) sf::Vector2i GetTileSize();

		__declspec(dllexport) void Draw(sf::RenderWindow &window);

	private:
		int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
		int firstTileID;//получаем айди первого тайла
		sf::Rect<float> drawingBounds;//размер части карты которую рисуем
		sf::Texture tilesetImage;//текстура карты
		std::vector<Object> objects;//массив типа ќбъекты, который мы создали
		std::vector<Layer> layers;
	};
	extern "C++" class File_EN
	{
	private:
		ofstream in_file;
		ifstream out_file;
		std::string type_clear_in = "clear_in";
		std::string type_out = "out";
		std::string type_app = "app";
		bool chekcType_in = 0;
		bool chekcType_out = 0;
		bool chekcType_app = 0;
	public:
		__declspec(dllexport) File_EN(std::string dir, std::string type);

		__declspec(dllexport) void exit();

		__declspec(dllexport) void write(std::string text)//;

		__declspec(dllexport) std::string read(int buffer_);
	};
	

}

