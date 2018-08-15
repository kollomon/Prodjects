#include<SFML/Graphics.hpp>
#include<string>
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include <vector>
using namespace std;
namespace XGS_ENGINE
{
	extern "C++" class XGS_EN
	{
	private:
		sf::Clock clock;
		float time;
	public:
		float getTime()
		{
			time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 800;
			return time;
		}
	};
	extern "C++" class Object_EN :public XGS_EN
	{
	public:
		__declspec(dllexport) void setTime(float timer);
		__declspec(dllexport) float getX();
		__declspec(dllexport) float getY();
		__declspec(dllexport) void loadingSprite(string dir, int W, int H);
		__declspec(dllexport) void mowe(float X, float Y);
		__declspec(dllexport) double VectorEN_getVectorAngle(float X, float Y);
		__declspec(dllexport) float VectorEN_getVectorDistnce(float XX, float YY);
		__declspec(dllexport) void VectorEN_getVectorMove(float tempX, float tempY);
		__declspec(dllexport) void TextEN_setFont(std::string &file);
		__declspec(dllexport) void TextEN_draw_text(float x, float y, std::string text_, sf::RenderWindow &window);
		__declspec(dllexport) void draw(sf::RenderWindow &window);

		/*__declspec(dllexport) void apdateTimer()
		{
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		}*/
		/*__declspec(dllexport) sf::FloatRect getRect()
		{
		return sf::FloatRect(x, y, w, h);
		}*/
		/*__declspec(dllexport) void GetObjects(Level_EN &lvl)
		{
		obj = lvl.GetAllObjects();
		}*/
		/*__declspec(dllexport) bool checkCollision(std::string Type)
		{
		for (int i = 0; i < obj.size(); i++)
		{
		if (getRect().intersects(obj[i].rect))
		{
		if (obj[i].name == Type)
		{
		return true;
		}
		else
		{
		return false;
		}
		}
		}
		}*/
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

		__declspec(dllexport) void write(std::string text);//

		__declspec(dllexport) std::string read(int buffer_);

	};
	/*extern "C++" class Level_EN
	{
	public:

	__declspec(dllexport) bool LoadFromFile(std::string filename)//���������-��������� � ������� ������ ��� ������
	{
	TiXmlDocument levelFile(filename.c_str());//��������� ���� � TiXmlDocument
	// ��������� XML-�����
	if (!levelFile.LoadFile())//���� �� ������� ��������� �����
	{
	std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//������ ������
	return false;
	}
	// �������� � ����������� map
	TiXmlElement *map;
	map = levelFile.FirstChildElement("map");
	// ������ �����: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));//��������� �� ����� ����� �� ��������
	height = atoi(map->Attribute("height"));//�� ��������, ������� �������� ��� ������ �
	tileWidth = atoi(map->Attribute("tilewidth"));//������� ���������
	tileHeight = atoi(map->Attribute("tileheight"));
	// ����� �������� �������� � ������������� ������� �����
	TiXmlElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));
	// source - ���� �� �������� � ���������� image
	TiXmlElement *image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");
	// �������� ��������� �������
	sf::Image img;
	if (!img.loadFromFile(imagepath))
	{
	std::cout << "Failed to load tile sheet." << std::endl;//���� �� ������� ��������� �������-������� ������ � �������
	return false;
	}
	img.createMaskFromColor(sf::Color(255, 255, 255));//��� ����� �����.������ ��� �����
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//�����������
	// �������� ���������� �������� � ����� ��������
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;
	// ������ �� ��������������� ����������� (TextureRect)
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
	// ������ �� ������
	TiXmlElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
	Layer layer;
	// ���� ������������ opacity, �� ������ ������������ ����, ����� �� ��������� �����������
	if (layerElement->Attribute("opacity") != NULL)
	{
	float opacity = strtod(layerElement->Attribute("opacity"), NULL);
	layer.opacity = 255 * opacity;
	}
	else
	{
	layer.opacity = 255;
	}
	//  ��������� <data>
	TiXmlElement *layerDataElement;
	layerDataElement = layerElement->FirstChildElement("data");
	if (layerDataElement == NULL)
	{
	std::cout << "Bad map. No layer information found." << std::endl;
	}
	//  ��������� <tile> - �������� ������ ������� ����
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
	// ������������� TextureRect ������� �����
	if (subRectToUse >= 0)
	{
	sf::Sprite sprite;
	sprite.setTexture(tilesetImage);
	sprite.setTextureRect(subRects[subRectToUse]);
	sprite.setPosition(x * tileWidth, y * tileHeight);
	sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
	layer.tiles.push_back(sprite);//���������� � ���� ������� ������
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
	// ������ � ���������
	TiXmlElement *objectGroupElement;
	// ���� ���� ���� ��������
	if (map->FirstChildElement("objectgroup") != NULL)
	{
	objectGroupElement = map->FirstChildElement("objectgroup");
	while (objectGroupElement)
	{
	//  ��������� <object>
	TiXmlElement *objectElement;
	objectElement = objectGroupElement->FirstChildElement("object");
	while (objectElement)
	{
	// �������� ��� ������ - ���, ���, �������, � ��
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
	// ��������� �������
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
	// "����������" �������
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
	// ������ ������ ������ � �������� ������
	for (int i = 0; i < objects.size(); i++)
	if (objects[i].name == name)
	return objects[i];
	}
	__declspec(dllexport) std::vector<Object> GetObjects(std::string name)
	{
	// ��� ������� � �������� ������
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
	// ������ ��� ����� (������� �� ������!)
	for (int layer = 0; layer < layers.size(); layer++)
	for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
	window.draw(layers[layer].tiles[tile]);
	}
	private:
	int width, height, tileWidth, tileHeight;//� tmx ����� width height � ������,����� ������ �����
	int firstTileID;//�������� ���� ������� �����
	sf::Rect<float> drawingBounds;//������ ����� ����� ������� ������
	sf::Texture tilesetImage;//�������� �����
	std::vector<Object> objects;//������ ���� �������, ������� �� �������
	std::vector<Layer> layers;
	};*/


