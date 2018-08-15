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
	extern "C++" class Object_EN
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
		float x=0;
		float y=0;
		float speed=0;
		float time=0;
		sf::Text text;
		sf::Font font;
		//------------------------------------------//
		///////////////////функции/////////////
		__declspec(dllexport) float getX()
		{
			return x;
		}
		__declspec(dllexport) float getY()
		{
			return y;
		}
		__declspec(dllexport) void loadingSprite(string dir)
		{
			if (spriteload == false)
			{
				texture.loadFromFile(dir);
				sprite.setTexture(texture);
				spriteload = true;
				textureload = true;
			}
			else
			{
				std::cout << "sprite uge zgrugen !!!";
			}
			
		}
		__declspec(dllexport) void mowe(float X, float Y)
		{
			if (spriteload)
			{
            x += X;
			y += Y;
			sprite.setPosition(x, y);
			}
			else
			{
				std::cout << "sprite is not found ";
			}
			
		}
		__declspec(dllexport) double VectorEN_getVectorAngle(float X, float Y)
		{

			float a_x = X - x;
			float a_y = Y - y;
			double angle = (atan2(a_y, a_x)) * 180 / 3.14;
			return angle;
		}
		__declspec(dllexport) float VectorEN_getVectorDistnce(float XX, float YY)
		{

			float distance;
			distance = sqrt((XX - x)*(XX - x) + (YY - y)*(YY - y));
			return distance;
		}
		__declspec(dllexport) void VectorEN_getVectorMove(float tempX, float tempY)
		{
			x += speed * time*(tempX - x);
			y += speed * time*(tempY - y);

		}
		__declspec(dllexport) void TextEN_setFont(std::string &file)
		{
			if (!font.loadFromFile(file))
			{
				std::cout << "font dont loding";
			}
		}
		__declspec(dllexport) void TextEN_draw_text(float x, float y, std::string text_, sf::RenderWindow &window)
		{
			text.setString(text_);
			text.setPosition(x, y);
			window.draw(text);

		}
		__declspec(dllexport) void AnimationEN_setPosAnim(int x, int y)
		{
			pos_x = x;
			pos_y = y;
		}
		__declspec(dllexport) void AnimationEN_setLineAnim(std::string dir, int X, int Y)
		{
			std::string left, right, up, down;
			left = "left";
			right = "right";
			up = "up";
			down = "down";
			A_x = X;
			A_y = Y;
			if (dir == left) { x_anim = -X; }
			if (dir == right) { x_anim = X; }
			if (dir == up) { y_anim = -Y; }
			if (dir == down) { y_anim = Y; }
		}
		__declspec(dllexport) void AnimationEN_setTimerAnim(int t)
		{
			timer = t;
		}
		__declspec(dllexport) int AnimationEN_getTimer()
		{
			return timer;
		}
		__declspec(dllexport) void AnimationEN_getPlayAnimations(int images)
		{
			for (timer = 0; timer < images; timer++)
			{
				sprite.setTextureRect(sf::IntRect(pos_x, pos_y, A_x, A_y));
				pos_x += x;
				pos_y += y;

			}
		}
		__declspec(dllexport) void apdateTimer()
		{
			time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 800;
			
		}
		//----------------------------------//

	};
	extern "C++" struct Object
	{
		__declspec(dllexport)	int GetPropertyInt(std::string name)//возвращаем номер свойства в нашем списке
		{
			return atoi(properties[name].c_str());
		}
		__declspec(dllexport)   float GetPropertyFloat(std::string name)
		{
			return strtod(properties[name].c_str(), NULL);
		}
		__declspec(dllexport)	std::string GetPropertyString(std::string name)//получить имя в виде строки.вроде понятно
		{
			return properties[name];
		}
		std::string name;//объявили переменную name типа string
		std::string type;//а здесь переменную type типа string
		sf::Rect<float> rect;//тип Rect с нецелыми значениями
		std::map<std::string, std::string> properties;//создаём ассоциатиный массив. ключ - строковый тип, значение - строковый
		sf::Sprite sprite;//объявили спрайт
	};
	extern "C++" struct Layer//слои
	{
		int opacity;//непрозрачность слоя
		std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
	};
	extern "C++" class Level//главный класс - уровень
	{
	public:

		__declspec(dllexport) bool LLoadFromFile(std::string filename)//двоеточия-обращение к методам класса вне класса 
		{
			TiXmlDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument
													  // загружаем XML-карту
			if (!levelFile.LoadFile())//если не удалось загрузить карту
			{
				std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//выдаем ошибку
				return false;
			}
			// работаем с контейнером map
			TiXmlElement *map;
			map = levelFile.FirstChildElement("map");
			// пример карты: <map version="1.0" orientation="orthogonal"
			// width="10" height="10" tilewidth="34" tileheight="34">
			width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
			height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
			tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
			tileHeight = atoi(map->Attribute("tileheight"));
			// Берем описание тайлсета и идентификатор первого тайла
			TiXmlElement *tilesetElement;
			tilesetElement = map->FirstChildElement("tileset");
			firstTileID = atoi(tilesetElement->Attribute("firstgid"));
			// source - путь до картинки в контейнере image
			TiXmlElement *image;
			image = tilesetElement->FirstChildElement("image");
			std::string imagepath = image->Attribute("source");
			// пытаемся загрузить тайлсет
			sf::Image img;
			if (!img.loadFromFile(imagepath))
			{
				std::cout << "Failed to load tile sheet." << std::endl;//если не удалось загрузить тайлсет-выводим ошибку в консоль
				return false;
			}
			img.createMaskFromColor(sf::Color(255, 255, 255));//для маски цвета.сейчас нет маски
			tilesetImage.loadFromImage(img);
			tilesetImage.setSmooth(false);//сглаживание
										  // получаем количество столбцов и строк тайлсета
			int columns = tilesetImage.getSize().x / tileWidth;
			int rows = tilesetImage.getSize().y / tileHeight;
			// вектор из прямоугольников изображений (TextureRect)
			std::vector<sf::Rect<int>> subRects;
			for (int y = 0; y < rows; y++)
				for (int x = 0; x < columns; x++)
				{
					sf::Rect<int> rect;
					rect.top = y * tileHeight;
					rect.height = tileHeight;
					rect.left = x * tileWidth;
					rect.width = tileWidth;
					subRects.push_back(rect);
				}
			// работа со слоями
			TiXmlElement *layerElement;
			layerElement = map->FirstChildElement("layer");
			while (layerElement)
			{
				Layer layer;
				// если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
				if (layerElement->Attribute("opacity") != NULL)
				{
					float opacity = strtod(layerElement->Attribute("opacity"), NULL);
					layer.opacity = 255 * opacity;
				}
				else
				{
					layer.opacity = 255;
				}
				//  контейнер <data> 
				TiXmlElement *layerDataElement;
				layerDataElement = layerElement->FirstChildElement("data");
				if (layerDataElement == NULL)
				{
					std::cout << "Bad map. No layer information found." << std::endl;
				}
				//  контейнер <tile> - описание тайлов каждого слоя
				TiXmlElement *tileElement;
				tileElement = layerDataElement->FirstChildElement("tile");
				if (tileElement == NULL)
				{
					std::cout << "Bad map. No tile information found." << std::endl;
					return false;
				}
				int x = 0;
				int y = 0;
				while (tileElement)
				{
					int tileGID = atoi(tileElement->Attribute("gid"));
					int subRectToUse = tileGID - firstTileID;
					// Устанавливаем TextureRect каждого тайла
					if (subRectToUse >= 0)
					{
						sf::Sprite sprite;
						sprite.setTexture(tilesetImage);
						sprite.setTextureRect(subRects[subRectToUse]);
						sprite.setPosition(x * tileWidth, y * tileHeight);
						sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
						layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
					}
					tileElement = tileElement->NextSiblingElement("tile");
					x++;
					if (x >= width)
					{
						x = 0;
						y++;
						if (y >= height)
							y = 0;
					}
				}
				layers.push_back(layer);
				layerElement = layerElement->NextSiblingElement("layer");
			}
			// работа с объектами
			TiXmlElement *objectGroupElement;
			// если есть слои объектов
			if (map->FirstChildElement("objectgroup") != NULL)
			{
				objectGroupElement = map->FirstChildElement("objectgroup");
				while (objectGroupElement)
				{
					//  контейнер <object>
					TiXmlElement *objectElement;
					objectElement = objectGroupElement->FirstChildElement("object");
					while (objectElement)
					{
						// получаем все данные - тип, имя, позиция, и тд
						std::string objectType;
						if (objectElement->Attribute("type") != NULL)
						{
							objectType = objectElement->Attribute("type");
						}
						std::string objectName;
						if (objectElement->Attribute("name") != NULL)
						{
							objectName = objectElement->Attribute("name");
						}
						int x = atoi(objectElement->Attribute("x"));
						int y = atoi(objectElement->Attribute("y"));
						int width, height;
						sf::Sprite sprite;
						sprite.setTexture(tilesetImage);
						sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
						sprite.setPosition(x, y);
						if (objectElement->Attribute("width") != NULL)
						{
							width = atoi(objectElement->Attribute("width"));
							height = atoi(objectElement->Attribute("height"));
						}
						else
						{
							width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
							height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
							sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
						}
						// экземпляр объекта
						Object object;
						object.name = objectName;
						object.type = objectType;
						object.sprite = sprite;
						sf::Rect <float> objectRect;
						objectRect.top = y;
						objectRect.left = x;
						objectRect.height = height;
						objectRect.width = width;
						object.rect = objectRect;
						// "переменные" объекта
						TiXmlElement *properties;
						properties = objectElement->FirstChildElement("properties");
						if (properties != NULL)
						{
							TiXmlElement *prop;
							prop = properties->FirstChildElement("property");
							if (prop != NULL)
							{
								while (prop)
								{
									std::string propertyName = prop->Attribute("name");
									std::string propertyValue = prop->Attribute("value");
									object.properties[propertyName] = propertyValue;
									prop = prop->NextSiblingElement("property");
								}
							}
						}
						objects.push_back(object);
						objectElement = objectElement->NextSiblingElement("object");
					}
					objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
				}
			}
			else
			{
				std::cout << "No object layers found..." << std::endl;
			}
			return true;
		}
		__declspec(dllexport) Object GetObject(std::string name)
		{
			// только первый объект с заданным именем
			for (int i = 0; i < objects.size(); i++)
				if (objects[i].name == name)
					return objects[i];
		}
		__declspec(dllexport) std::vector<Object> GetObjects(std::string name)
		{
			// все объекты с заданным именем
			std::vector<Object> vec;
			for (int i = 0; i < objects.size(); i++)
				if (objects[i].name == name)
					vec.push_back(objects[i]);
			return vec;
		}
		__declspec(dllexport) std::vector<Object> GetAllObjects()
		{
			return objects;
		};
		__declspec(dllexport) sf::Vector2i GetTileSize()
		{
			return sf::Vector2i(tileWidth, tileHeight);
		}
		__declspec(dllexport) void Draw(sf::RenderWindow &window)
		{
			// рисуем все тайлы (объекты не рисуем!)
			for (int layer = 0; layer < layers.size(); layer++)
				for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
					window.draw(layers[layer].tiles[tile]);
		}
	private:
		int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
		int firstTileID;//получаем айди первого тайла
		sf::Rect<float> drawingBounds;//размер части карты которую рисуем
		sf::Texture tilesetImage;//текстура карты
		std::vector<Object> objects;//массив типа Объекты, который мы создали
		std::vector<Layer> layers;
	};

}



